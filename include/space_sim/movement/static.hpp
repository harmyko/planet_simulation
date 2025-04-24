#ifndef STATIC_HPP
#define STATIC_HPP

#include "i_movement_strategy.hpp"

/**
 * Movement strategy for static objects with fixed position and velocity.
 * 
 * Does not change the position or velocity of the space object.
 */
class StaticMovementStrategy : public IMovementStrategy
{
public:

    /**
     * Constructor that initializes the static movement strategy.
     * 
     * @param mass_ptr Pointer to the object's mass.
     * @param radius_ptr Pointer to the object's radius.
     * @param position_ptr Pointer to the object's position.
     * @param velocity_ptr Pointer to the object's velocity.
     */
    StaticMovementStrategy(double *mass_ptr, double *radius_ptr, sf::Vector2f *position_ptr, sf::Vector2f *velocity_ptr)
        : IMovementStrategy(mass_ptr, radius_ptr, position_ptr, velocity_ptr) {}

     /**
     * Sets the objects velocity to zero.
     * 
     * @param others List of other space objects.
     * @param gravitational_constant Gravitational constant.
     * @param delta_time Time step for the update.
     */
    void update_velocity(const std::vector<const SpaceObject* > &others,
        const float gravitational_constant, const float delta_time) override;

    /**
     * Does not update the position for static objects.
     * 
     * @param delta_time Time step for the update.
     */
    void update_position(const float delta_time) override;
};


#endif // STATIC_HPP
