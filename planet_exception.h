#ifndef PLANET_EXCEPTION_H
#define PLANET_EXCEPTION_H

#include <stdexcept>
#include <string>

class PlanetException : public std::runtime_error {
public:
    explicit PlanetException(const std::string &msg)
        : std::runtime_error(msg) {}
};

#endif // PLANET_EXCEPTION_H
