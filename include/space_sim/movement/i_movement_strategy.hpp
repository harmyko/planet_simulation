#ifndef I_MOVEMENT_STRATEGY_HPP
#define I_MOVEMENT_STRATEGY_HPP

#include "space_object.hpp"

class SpaceObject;

/**
 * Abstract base class for movement strategies of space objects.
 *
 * Defines the interface for updating velocity and position of space objects.
 */
class IMovementStrategy
{
protected:
    double *mass;           ///< Pointer to the object's mass
    double *radius;         ///< Pointer to the object's radius
    sf::Vector2f *position; ///< Pointer to the object's position
    sf::Vector2f *velocity; ///< Pointer to the object's velocity

public:
    /**
     * Constructor to initialize the movement strategy with required pointers.
     *
     * @param mass_ptr Pointer to the object's mass.
     * @param radius_ptr Pointer to the object's radius.
     * @param position_ptr Pointer to the object's position.
     * @param velocity_ptr Pointer to the object's velocity.
     */
    IMovementStrategy(double *mass_ptr, double *radius_ptr, sf::Vector2f *position_ptr, sf::Vector2f *velocity_ptr)
        : mass(mass_ptr), radius(radius_ptr), position(position_ptr), velocity(velocity_ptr) {}

    virtual ~IMovementStrategy() = default;

    /**
     * Updates the velocity based on the movement strategy.
     *
     * @param others List of other space objects.
     * @param gravitational_constant Gravitational constant.
     * @param delta_time Time step for the update.
     */
    virtual void update_velocity(const std::vector<const SpaceObject *> &others,
                                 const float gravitational_constant, const float delta_time) = 0;

    /**
     * Updates the position based on the movement strategy.
     *
     * @param delta_time Time step for the update.
     */
    virtual void update_position(const float delta_time) = 0;
};

#endif // I_MOVEMENT_STRATEGY_HPP
