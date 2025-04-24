#ifndef DYNAMIC_MOVEMENT_STRATEGY_HPP
#define DYNAMIC_MOVEMENT_STRATEGY_HPP

#include <cmath>

#include "i_movement_strategy.hpp"

class DynamicMovementStrategy : public IMovementStrategy
{
public:

    DynamicMovementStrategy(std::shared_ptr<float> gravity)
        : IMovementStrategy(gravity) {}

    void update_velocity(SpaceObject *target, const std::vector<const SpaceObject *> &others, const float delta_time) const override;
};

#endif // DYNAMIC_MOVEMENT_STRATEGY_HPP
