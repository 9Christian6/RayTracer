#pragma once
#include <exception>
#include <string>

class Exception : public std::exception
{
private:
    std::string _exception;

public:
    Exception(std::string message) : _exception{message} {};
    const char *what() const throw()
    {
        return _exception.c_str();
    };
};