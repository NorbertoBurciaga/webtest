#include <iostream>
#include <restinio/all.hpp>

using namespace std;

restinio::request_handling_status_t handler(restinio::request_handle_t request) {
	// if method is get and request is "/"
	if (restinio::http_method_get() == request->header().method() && request->header().request_target() == "/") {
		request->create_response()
				.append_header(restinio::http_field::server, "Restinio hello world")
				.append_header_date_field()
				.append_header(restinio::http_field::content_type, "text/html; charset=utf-8")
				.set_body("<h1>Hello World!<h1>")
				.done();
		return restinio::request_accepted();
	} else {
		return restinio::request_rejected();
	}
}

int main(int argc, char **argv) {
	cout << "Iniciando web server..." << endl;

	restinio::run(
		restinio::on_this_thread()
			.port(8080)
			.address("localhost")
			.request_handler(handler)
	);
	cout << "Terminando web server..." << endl;
	return 0;
}
