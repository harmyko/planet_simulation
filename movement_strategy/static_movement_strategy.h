#ifndef STATIC_MOVEMENT_STRATEGY_H
#define STATIC_MOVEMENT_STRATEGY_H

#include "i_movement_strategy.h"

class StaticMovementStrategy : public IMovementStrategy
{
private:
    sf::Vector2f new_velocity;

public:
    StaticMovementStrategy(sf::Vector2f velocity = {0, 0}, float gravity = GRAVITATIONAL_CONSTANT)
        : IMovementStrategy(gravity), new_velocity(velocity) {}

    void apply_velocity(SpaceObject &target, const std::vector<SpaceObject> &) const override;
};


#endif // STATIC_MOVEMENT_STRATEGY_H
