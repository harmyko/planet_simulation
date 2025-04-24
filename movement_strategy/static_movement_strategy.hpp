#ifndef STATIC_MOVEMENT_STRATEGY_HPP
#define STATIC_MOVEMENT_STRATEGY_HPP

#include "i_movement_strategy.hpp"

class StaticMovementStrategy : public IMovementStrategy
{
public:

    StaticMovementStrategy(double *mass_ptr, double *radius_ptr, sf::Vector2f *position_ptr, sf::Vector2f *velocity_ptr)
        : IMovementStrategy(mass_ptr, radius_ptr, position_ptr, velocity_ptr) {}

    void update_velocity(const std::vector<const SpaceObject* > &others,
        const float gravitational_constant, const float delta_time) override;
    void update_position(const float delta_time) override;
};


#endif // STATIC_MOVEMENT_STRATEGY_HPP
