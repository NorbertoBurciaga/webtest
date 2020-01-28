#include <iostream>
#include <restinio/all.hpp>
#include <rapidjson/document.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


using namespace std;
using router_t = restinio::router::express_router_t<>;


vector<std::string> users = {R"-({"user":"Norberto","password":"thisIsAP@ssword"})-", R"-({"user":"Gabriela","password":"An0th3rP@ssw0rd"})-"};


template < typename RESP >
RESP init_resp( RESP resp ) {
	resp.append_header(restinio::http_field::server, "Test web server");
	resp.append_header_date_field();

	return resp;
}


auto createServerHandler() {
	auto router = std::make_unique<router_t>();

	router->http_get(
		"/",
		[] (auto req, auto) {
			init_resp(req->create_response())
				.append_header(restinio::http_field::content_type, "text/html; charset=utf-8")
				.set_body(
					"<html>\r\n"
					"  <head><title>Hello from RESTinio!</title></head>\r\n"
					"  <body>\r\n"
					"    <center><h1>Hello world</h1></center>\r\n"
					"  </body>\r\n"
					"</html>\r\n"
				)
				.done();
			return restinio::request_accepted();
		}
	);

	router->http_get(
		"/v1/users",
		[] (auto req, auto) {
			rapidjson::Document document;

			document.SetArray();

			 rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

			 for (const auto user : users) {
				 rapidjson::Value value;
				 value.SetString(user.c_str(), user.length(), allocator);
				 document.PushBack(value, allocator);
			 }

			 rapidjson::StringBuffer strbuf;
			 rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
			 document.Accept(writer);

			init_resp(req->create_response())
				.append_header(restinio::http_field::content_type, "text/json; charset=utf-8")
				.set_body(strbuf.GetString())
				.done();
			return restinio::request_accepted();
		}
	);

	router->http_get(
		"/json",
		[] (auto req, auto) {
			init_resp(req->create_response())
				.append_header(restinio::http_field::content_type, "text/json; charset=utf-8")
				.set_body(R"-({"message" : "Hello world!"})-")
				.done();
			return restinio::request_accepted();
		}
	);

	router->http_get(
		"/plain",
		[] (auto req, auto) {
			init_resp(req->create_response())
				.append_header(restinio::http_field::content_type, "text/plain; charset=utf-8")
				.set_body("Hello World!")
				.done();
			return restinio::request_accepted();
		}
	);

	router->http_post(
		"/v1/credentials",
		[] (auto req, auto) {
			return
				init_resp( req->create_response())
				.append_header(restinio::http_field::content_type, "text/plain; charset=utf-8")
				.set_body( "POST request to the homepage.\nbody: " + req->body() )
				.done();
		}
	);

	router->non_matched_request_handler(
		[]( auto req ){
			return
				req->create_response( restinio::status_not_found() )
				.append_header_date_field()
				.connection_close()
				.done();
		}
	);

	return router;
}


int main(int argc, char **argv) {
	cout << "Iniciando web server..." << endl;

	restinio::asio_ns::io_context io_context;

	using traits_t = restinio::traits_t<restinio::asio_timer_manager_t, restinio::single_threaded_ostream_logger_t, router_t>;
	using my_server_t = restinio::http_server_t<traits_t>;

	my_server_t server {
		restinio::external_io_context(io_context),
		[](auto & settings) {
			settings.port(8080);
			settings.address("localhost");
			settings.request_handler(createServerHandler());
		}
	};

	try {
		restinio::asio_ns::signal_set break_signals{ io_context, SIGINT };
		break_signals.async_wait(
			[&]( const restinio::asio_ns::error_code & ec, int ) {
				if( !ec ) {
					server.close_sync();
				}
			}
		);

		restinio::asio_ns::post(
				io_context,
				[&]{
					server.open_sync();
				}
		);

		io_context.run();

	} catch (const exception & ex) {
		cerr << "Error: " << ex.what() << endl;
		return 1;
	}
	cout << "Terminando web server..." << endl;
	return 0;
}
