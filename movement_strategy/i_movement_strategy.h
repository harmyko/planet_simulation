#ifndef I_MOVEMENT_STRATEGY_H
#define I_MOVEMENT_STRATEGY_H

#include <vector>

#include "space_object.h"

class SpaceObject;

class IMovementStrategy
{
public:

    virtual ~IMovementStrategy() = default;

    virtual void apply_velocity(SpaceObject &target, const std::vector<SpaceObject> &others) const = 0;
};

#endif // I_MOVEMENT_STRATEGY_H
