#ifndef I_MOVEMENT_STRATEGY_H
#define I_MOVEMENT_STRATEGY_H

#include <vector>

#include "../space_object.h"

class SpaceObject;

class IMovementStrategy
{
protected:

    float G;

public:

    IMovementStrategy(float gravity) : G(gravity) {}
    virtual ~IMovementStrategy() = default;

    virtual void apply_velocity(SpaceObject *target, const std::vector<const SpaceObject *> &others, const float delta_time) const = 0;
};

#endif // I_MOVEMENT_STRATEGY_H
