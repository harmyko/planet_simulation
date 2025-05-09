#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>
#include <string>

/** @brief
 * Exception class for handling errors related to SpaceObject.
 *
 * This class extends `std::runtime_error` to provide a custom exception for errors
 * that occur during the processing of space objects.
 */
class SpaceObjectException : public std::runtime_error
{
public:
    /** @brief
     * Constructs a SpaceObjectException with a given message.
     *
     * @param message The error message to describe the exception.
     */
    explicit SpaceObjectException(const std::string &message)
        : std::runtime_error(message) {}
};

#endif // EXCEPTION_HPP
