#include "static_movement_strategy.h"

StaticMovementStrategy::StaticMovementStrategy(sf::Vector2f velocity, float gravity = GRAVITATIONAL_CONSTANT)
    : IMovementStrategy(gravity), new_velocity(velocity) {}

void StaticMovementStrategy::apply_velocity(SpaceObject &target, const std::vector<SpaceObject> &) const
{
    target.set_velocity(new_velocity);
}
