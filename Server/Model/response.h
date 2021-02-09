#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

struct Response{
    Response(const bool success, const std::string& message);
    Response(const bool success, const int& value);
    ~Response();
    
    Response(const Response&) = delete;
    Response& operator=(const Response&) = delete;
    Response(Response&& other);
    Response& operator=(Response&& other);

    bool success;
    std::string message;
    int value;
};

#endif