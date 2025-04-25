#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP

#include "i_movement_strategy.hpp"

/**
 * Movement strategy for dynamic movement based on gravitational forces.
 *
 * Updates velocity and position of a space object considering gravitational forces from other objects.
 */
class DynamicMovementStrategy : public IMovementStrategy
{
public:
    /**
     * Constructor that initializes the dynamic movement strategy.
     *
     * @param mass_ptr Pointer to the object's mass.
     * @param radius_ptr Pointer to the object's radius.
     * @param position_ptr Pointer to the object's position.
     * @param velocity_ptr Pointer to the object's velocity.
     */
    DynamicMovementStrategy(double *mass_ptr, double *radius_ptr, sf::Vector2f *position_ptr, sf::Vector2f *velocity_ptr)
        : IMovementStrategy(mass_ptr, radius_ptr, position_ptr, velocity_ptr) {}

    /**
     * Updates the velocity based on gravitational interactions with other objects.
     *
     * @param others List of other space objects in the universe for gravitational calculation.
     * @param gravitational_constant The gravitational constant.
     * @param delta_time Time step for the update.
     */
    void update_velocity(const std::vector<const SpaceObject *> &others,
                         const float gravitational_constant, const float delta_time) override;

    /**
     * Updates the position based on the object's velocity.
     *
     * @param delta_time Time step for the update.
     */
    void update_position(const float delta_time) override;
};

#endif // DYNAMIC_HPP
