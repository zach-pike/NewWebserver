#include "Webserver.hpp"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

Webserver::Webserver(std::uint16_t _port, std::string _host):
    port{_port},
    host{_host} {}

Webserver::~Webserver() {
    shutdown(serverfd, SHUT_RDWR);
    close(serverfd);
}

void Webserver::setResourceController(std::shared_ptr<IResourceController> _controller) {
    controller = _controller;
}

bool Webserver::start(std::function<void(std::string)> cb) {
    serverfd = socket(AF_INET, SOCK_STREAM, 0);

    if(serverfd < 0) return false;

    sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverfd, (const sockaddr*)&server, sizeof(sockaddr_in)) < 0) return false;

    // Ready to start listening

    if(listen(serverfd, 25) < 0) return false;

    while(true) {
        sockaddr_in client_address;
        int client_size = sizeof(client_address);

        // Accept a new connection
        int client_fd = accept(serverfd, (sockaddr*)&client_address, (socklen_t*)&client_size);

        // Create buffer for incoming http header
        std::uint8_t* header_buffer = new std::uint8_t[4096];
        std::size_t header_buffer_size = 0;
        
        // Read until header is fully read;
        while (!strstr((const char*)header_buffer, "\r\n\r\n")) {
            // Append the bytes to the end of the buffer
            std::size_t read_size = read(client_fd, 
                header_buffer + header_buffer_size,
                4096 - header_buffer_size
            );

            if (read_size < 0) {
                return false;
            }

            header_buffer_size += read_size;
        }

        const char* header_end = strstr((const char*)header_buffer, "\r\n\r\n") + 4;
        std::size_t header_len = header_end - (const char*)header_buffer;

        HttpRequest request;
        request.parseHeader(header_buffer, header_len);
        Headers req_headers = request.getHeaders();

        // Now we need to read the entire body
        // Check for a content-length header
        if (request.getMethod() != HttpRequest::Methods::GET &&
            req_headers.hasHeader("content-length")) {
            // Read it
            std::size_t content_length = std::stoul(req_headers.getHeader("content-length"));

            // Create buffer to read rest of body
            std::uint8_t* body_buffer = new std::uint8_t[content_length];
            std::size_t read_bytes = header_buffer_size - header_len;

            // Copy any extra data got by the 
            memcpy(body_buffer, header_end, read_bytes);

            // Read rest of content
            while (read_bytes < content_length) {
                read_bytes += read(client_fd, body_buffer + read_bytes, content_length - read_bytes);
            }

            request.setBody(std::vector<std::uint8_t>(body_buffer, body_buffer + read_bytes));

            delete[] body_buffer;
        }

        // Free the header buffer
        delete[] header_buffer;

        // Get the response from the controller
        auto response = controller->
            getResource(request.getPath())->
            getResponse(request);
        
        // WIP
        response.getHeaders().addHeader("keep-alive", "close");

        // Convert response to a array of bytes
        auto bytes = response.toBytes();

        // Send the response
        send(client_fd, bytes.data(), bytes.size(), 0);

        // Close
        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
    }

    return true;
}