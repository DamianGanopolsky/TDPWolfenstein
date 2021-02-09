#include "./response.h"

Response::Response(const bool success, const std::string& message) : success(success), message(message),
                                                                    value(-1) {}

Response::Response(const bool success, const int& value) : success(success), message(""),
                                                            value(value) {}

Response::~Response() {}

Response::Response(Response&& other) {
    this->success = other.success;
    this->message = other.message;
    this->value = other.value;
}

Response& Response::operator=(Response&& other) {
    this->success = other.success;
    this->message = other.message;
    this->value = other.value;
    return *this;
}