#include <cmath>

#include "movement/dynamic.hpp"

const float MIN_DISTANCE_SQUARED = 1.0f;
const float MAX_ACCELERATION = 1e5f;

void DynamicMovementStrategy::update_velocity(const std::vector<const SpaceObject *> &others,
                                              const float gravitational_constant, const float delta_time)
{

    sf::Vector2f total_force{0.f, 0.f};

    for (const auto &other : others)
    {
        sf::Vector2f position_difference = other->get_position() - *position;
        float distance_squared = position_difference.x * position_difference.x + position_difference.y * position_difference.y;

        // Skip instances when objects are very close to eachother to avoid undefined behaviour
        // Also skips the instances when target and other is the same planet
        if (distance_squared < MIN_DISTANCE_SQUARED)
        {
            continue;
        }

        // Calculate the magnitude of the gravitational force: force = G * target_mass * other_mass / distance_squared
        float force_magnitude = (gravitational_constant * *mass * other->get_mass()) / distance_squared;

        // Convert the magnitude to a vector (pointing the vector to the "other" SpaceObject)
        float distance = std::sqrt(distance_squared);
        sf::Vector2f force = (position_difference / distance) * force_magnitude;

        total_force += force;
    }

    // Newton's second law: force = mass * acceleration => acceleration = force / mass
    sf::Vector2f acceleration = sf::Vector2f(total_force.x / *mass, total_force.y / *mass);
    sf::Vector2f new_velocity = *velocity + acceleration * delta_time;

    if (std::abs(acceleration.x) > MAX_ACCELERATION || std::abs(acceleration.y) > MAX_ACCELERATION)
    {
        return;
    }

    // Update target's velocity with the newly computed value
    *velocity = new_velocity;
}

void DynamicMovementStrategy::update_position(const float delta_time)
{
    *position += *velocity * delta_time;
}
