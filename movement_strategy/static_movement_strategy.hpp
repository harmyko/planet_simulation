#ifndef STATIC_MOVEMENT_STRATEGY_HPP
#define STATIC_MOVEMENT_STRATEGY_HPP

#include "i_movement_strategy.hpp"

class StaticMovementStrategy : public IMovementStrategy
{
private:
    sf::Vector2f new_velocity;

public:
    StaticMovementStrategy(std::shared_ptr<float> gravity, sf::Vector2f velocity = {0, 0})
        : IMovementStrategy(gravity), new_velocity(velocity) {}

    void update_velocity(SpaceObject *target, const std::vector<const SpaceObject* > &others, const float delta_time) const override;
};


#endif // STATIC_MOVEMENT_STRATEGY_HPP
