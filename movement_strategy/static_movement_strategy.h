#ifndef STATIC_MOVEMENT_STRATEGY_H
#define STATIC_MOVEMENT_STRATEGY_H

#include "i_movement_strategy.h"

class StaticMovementStrategy : public IMovementStrategy
{
private:

    sf::Vector2f new_velocity;

public:

    explicit StaticMovementStrategy(sf::Vector2f velocity = {0, 0});

    void apply_velocity(SpaceObject &target, const std::vector<SpaceObject> &) const override;
};

#endif // STATIC_MOVEMENT_STRATEGY_H
