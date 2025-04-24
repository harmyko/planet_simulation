#ifndef SPACE_OBJECT_EXCEPTION_HPP
#define SPACE_OBJECT_EXCEPTION_HPP

#include <stdexcept>
#include <string>

class SpaceObjectException : public std::runtime_error
{
public:

    explicit SpaceObjectException(const std::string &message)
        : std::runtime_error(message) {}
};

#endif // SPACE_OBJECT_EXCEPTION_HPP
