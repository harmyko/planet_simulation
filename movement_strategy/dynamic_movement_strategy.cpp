#include <cmath>
#include <iostream>

#include "dynamic_movement_strategy.h"

const float MIN_DISTANCE_SQUARED = 1.0f;
const float MAX_ACCELERATION = 1e5f;

void DynamicMovementStrategy::apply_velocity(SpaceObject &target, const std::vector<SpaceObject> &universe) const
{
    //std::cout << "(" << target.get_position().x << ", " << target.get_position().y << ")\n";

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

        // Skip instances when objects are very close to eachother to avoid undefined behaviour
        if (distance_squared < MIN_DISTANCE_SQUARED) 
        {
            std::cerr << "Distance too small, skipping " << target.get_name() << " & " << other.get_name() << "\n";
            continue;
        }
        
        // Calculate the magnitude of the gravitational force: force = G * target_mass * other_mass / distance_squared
        float force_magnitude = (G * target.get_mass() * other.get_mass()) / distance_squared;

        // Convert the magnitude to a vector (pointing the vector to the "other" SpaceObject)
        float distance = std::sqrt(distance_squared);
        sf::Vector2f force = (position_difference / distance) * force_magnitude;

        total_force += force;
    }

    // Newton's second law: force = mass * acceleration => acceleration = force / mass
    sf::Vector2f acceleration = sf::Vector2f(total_force.x / target.get_mass(), total_force.y / target.get_mass());
    sf::Vector2f new_velocity = target.get_velocity() + acceleration;

    if (std::abs(acceleration.x) > MAX_ACCELERATION || std::abs(acceleration.y) > MAX_ACCELERATION) {
        std::cerr << "Acceleration too high, skipping velocity update for " << target.get_name() << "\n";
        return;
    }

    // Update target's velocity with the newly computed value
    target.set_velocity(new_velocity);
}

