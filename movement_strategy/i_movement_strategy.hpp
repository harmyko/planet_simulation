#ifndef I_MOVEMENT_STRATEGY_HPP
#define I_MOVEMENT_STRATEGY_HPP

#include <vector>

#include "../space_object.hpp"

class SpaceObject;

class IMovementStrategy
{
protected:

    float G;

public:

    IMovementStrategy(float gravity) : G(gravity) {}
    virtual ~IMovementStrategy() = default;

    virtual void update_velocity(SpaceObject *target, const std::vector<const SpaceObject *> &others, const float delta_time) const = 0;
};

#endif // I_MOVEMENT_STRATEGY_HPP
