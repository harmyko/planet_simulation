#include "dynamic_movement_strategy.h"

#include <cmath>

DynamicMovementStrategy::DynamicMovementStrategy(float gravity)
    : G(gravity) {}

void DynamicMovementStrategy::apply_velocity(SpaceObject &target, const std::vector<SpaceObject> &universe) const
{
    sf::Vector2f total_force{0, 0};

    for (const auto &other : universe)
    {   
        // Skip matching planets (a planet cannot impact its own velocity)
        if (target.get_id() == other.get_id())
        {
            continue;
        }

        sf::Vector2f position_difference = other.get_position() - target.get_position();
        float distance_squared = position_difference.x * position_difference.x + position_difference.y * position_difference.y;

        // Skip division by zero to avoid undefined behaviour
        if (distance_squared == 0) 
        {
            continue;
        }
        
        // Calculate the magnitude of the gravitational force: force = G * target_mass * other_mass / distance_squared
        float force_magnitude = (G * target.get_mass() * other.get_mass()) / distance_squared;

        // Convert the magnitude to a vector (pointing the vector to the "other" SpaceObject)
        float distance = std::sqrt(distance_squared);
        sf::Vector2f force = (position_difference / distance) * force_magnitude;

        total_force += force;
    }

    // Newtons second law: force = mass * acceleration => acceleration = force / mass
    sf::Vector2f acceleration = total_force / target.get_mass();
    sf::Vector2f new_velocity = target.get_velocity() + acceleration;

    // Update target's velocity with the newly computed value
    target.set_velocity(new_velocity);
}

// Helper function to allow the division of a vector by a scalar value
sf::Vector2f operator/(const sf::Vector2f& v, float scalar)
{
    return {v.x / scalar, v.y / scalar};
}

