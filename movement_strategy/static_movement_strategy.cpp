#include "static_movement_strategy.h"

void StaticMovementStrategy::apply_velocity(SpaceObject &target, const std::vector<SpaceObject> &) const
{
    target.set_velocity(new_velocity);
}
