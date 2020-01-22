#include <iostream>
#include <restinio/all.hpp>

using namespace std;
using router_t = restinio::router::express_router_t<>;

template < typename RESP >
RESP init_resp( RESP resp ) {
	resp.append_header(restinio::http_field::server, "RESTinio sample server /v.0.2");
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

	return router;
}

int main(int argc, char **argv) {
	cout << "Iniciando web server..." << endl;

	using traits_t = restinio::traits_t<restinio::asio_timer_manager_t, restinio::single_threaded_ostream_logger_t, router_t>;

	try {
		restinio::run(
			restinio::on_this_thread<traits_t>()
				.port(8080)
				.address("localhost")
				.request_handler(createServerHandler())
		);

	} catch (const exception & ex) {
		cerr << "Error: " << ex.what() << endl;
		return 1;
	}
	cout << "Terminando web server..." << endl;
	return 0;
}
