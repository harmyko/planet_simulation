#ifndef DYNAMIC_MOVEMENT_STRATEGY_H
#define DYNAMIC_MOVEMENT_STRATEGY_H

#include <cmath>

#include "i_movement_strategy.h"

class DynamicMovementStrategy : public IMovementStrategy
{
public:

    DynamicMovementStrategy(float gravity)
        : IMovementStrategy(gravity) {}

    void apply_velocity(SpaceObject &target, const std::vector<SpaceObject> &universe) const override;
};

#endif // DYNAMIC_MOVEMENT_STRATEGY_H
