#ifndef I_MOVEMENT_STRATEGY_HPP
#define I_MOVEMENT_STRATEGY_HPP

#include "../space_object.hpp"

class SpaceObject;

class IMovementStrategy
{
protected:

    double *mass;
    double *radius;
    sf::Vector2f *position;
    sf::Vector2f *velocity;

public:

    IMovementStrategy(double *mass_ptr, double *radius_ptr, sf::Vector2f *position_ptr, sf::Vector2f *velocity_ptr)
    : mass(mass_ptr), radius(radius_ptr), position(position_ptr), velocity(velocity_ptr) {}

    virtual ~IMovementStrategy() = default;

    virtual void update_velocity(const std::vector<const SpaceObject *> &others,
        const float gravitational_constant, const float delta_time) = 0;

    virtual void update_position(const float delta_time) = 0;
};

#endif // I_MOVEMENT_STRATEGY_HPP
