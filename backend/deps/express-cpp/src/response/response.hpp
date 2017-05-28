#ifndef EXPRESS_RESPONSE_HPP
#define EXPRESS_RESPONSE_HPP

#include <router/common_types.hpp>

namespace express {

	class response {

    public:
		response(std::shared_ptr<HttpServer::Response> res);

        void append(std::string header_name, std::string header_content);
        //set content type to HTML
        void send(http_status status, htmlContent html);
        void send(htmlContent html);
        //void send(JSON) -- array or JSON ?
        //void send (Buffer) -- octet stream

        void sendStatus(http_status status);
        void sendFile(const boost::filesystem::path file);

    private:
        std::shared_ptr<HttpServer::Response> _res;
        std::string _header_append;
	};

}
#endif
