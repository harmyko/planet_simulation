#include "static_movement_strategy.h"

void StaticMovementStrategy::apply_velocity(SpaceObject *target, const std::vector<const SpaceObject *> &others, const float delta_time) const
{
    target->set_velocity(new_velocity);
}
