#include "movement/static.hpp"

void StaticMovementStrategy::update_velocity(const std::vector<const SpaceObject *> &others,
                                             const float gravitational_constant, const float delta_time)
{
    *velocity = {0.f, 0.f};
}

void StaticMovementStrategy::update_position(const float delta_time)
{
    return;
}
