#include "./response.h"

Response::Response(const bool success, const std::string& message) : success(success), message(message) {}

Response::~Response() {}

Response::Response(Response&& other) {
    this->success = other.success;
    this->message = other.message;
}

Response& Response::operator=(Response&& other) {
    this->success = other.success;
    this->message = other.message;
    return *this;
}