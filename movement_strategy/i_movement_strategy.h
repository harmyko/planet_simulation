#ifndef I_MOVEMENT_STRATEGY_H
#define I_MOVEMENT_STRATEGY_H

#include <vector>

#include "space_object.h"

#define GRAVITATIONAL_CONSTANT 6.67430E-11f

class SpaceObject;

class IMovementStrategy
{
protected:

    float G;

public:

    IMovementStrategy(float gravity = GRAVITATIONAL_CONSTANT) : G(gravity) {}
    virtual ~IMovementStrategy() = default;

    virtual void apply_velocity(SpaceObject &target, const std::vector<SpaceObject> &others) const = 0;
};

#endif // I_MOVEMENT_STRATEGY_H
