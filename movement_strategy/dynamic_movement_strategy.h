#ifndef DYNAMIC_MOVEMENT_STRATEGY_H
#define DYNAMIC_MOVEMENT_STRATEGY_H

#define GRAVITATIONAL_CONSTANT 6.67430E-11f

#include <cmath>

#include "i_movement_strategy.h"

class DynamicMovementStrategy : public IMovementStrategy
{
private:

    float G;

public:

    explicit DynamicMovementStrategy(float gravity = GRAVITATIONAL_CONSTANT);

    void apply_velocity(SpaceObject &target, const std::vector<SpaceObject> &universe) const override;
};

#endif // DYNAMIC_MOVEMENT_STRATEGY_H
