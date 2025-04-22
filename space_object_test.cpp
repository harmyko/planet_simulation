#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "space_object.h"
#include "movement_strategy/dynamic_movement_strategy.h"
#include "movement_strategy/static_movement_strategy.h"

const float SUN_RADIUS_SCALE = 2e4f;
const float MERCURY_RADIUS_SCALE = 400.f;
const float VENUS_RADIUS_SCALE = 450.f;
const float EARTH_RADIUS_SCALE = 470.f;
const float MARS_RADIUS_SCALE = 490.f;
const float JUPITER_RADIUS_SCALE = 1200.f;
const float SATURN_RADIUS_SCALE = 850.f;
const float URANUS_RADIUS_SCALE = 900.f;
const float NEPTUNE_RADIUS_SCALE = 920.f;

const float MASS_SCALE = 1e22f;
const float VELOCITY_SCALE = 1e4f;
const float POSITION_SCALE = 1e9f;
const float TIME_SCALE = 1e6;

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 800;
const float GRAVITATIONAL_CONSTANT = 6.67430e-11f;

bool pause_at_start = false;

sf::Vector2f compress_position(const sf::Vector2f &pos);

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Solar System Simulation");
    window.setFramerateLimit(60);

    std::vector<SpaceObject *> objects;

    objects.push_back(new SpaceObject("Sun", 1.989e30, 696340, {0, 0}, {0, 0}, false));
    objects.push_back(new SpaceObject("Mercury", 3.285e23, 2439.7, {0, -5.791e10}, {47870, 0}));
    objects.push_back(new SpaceObject("Venus", 4.867e24, 6051.8, {0, -1.082e11}, {35020, 0}));
    objects.push_back(new SpaceObject("Earth", 5.972e24, 6371, {0, -1.496e11}, {29780, 0}));
    objects.push_back(new SpaceObject("Mars", 6.39e23, 3389.5, {0, -2.279e11}, {24070, 0}));
    objects.push_back(new SpaceObject("Jupiter", 1.898e27, 69911, {0, -7.785e11}, {13070, 0}));
    objects.push_back(new SpaceObject("Saturn", 5.683e26, 58232, {0, -1.433e12}, {9680, 0}));
    objects.push_back(new SpaceObject("Uranus", 8.681e25, 25362, {0, -2.877e12}, {6800, 0}));
    objects.push_back(new SpaceObject("Neptune", 1.024e26, 24622, {0, -4.503e12}, {5430, 0}));

    std::vector<sf::CircleShape> shapes;
    for (const auto &object : objects)
    {
        sf::CircleShape shape(0);

        if (object->get_name() == "Sun")
        {
            shape.setFillColor(sf::Color::Yellow);
            shape.setRadius(object->get_radius() / SUN_RADIUS_SCALE);
        }
        else if (object->get_name() == "Mercury")
        {
            shape.setFillColor(sf::Color(169, 169, 169)); // Gray
            shape.setRadius(object->get_radius() / MERCURY_RADIUS_SCALE);
        }
        else if (object->get_name() == "Venus")
        {
            shape.setFillColor(sf::Color(255, 140, 0)); // Orange
            shape.setRadius(object->get_radius() / VENUS_RADIUS_SCALE);
        }
        else if (object->get_name() == "Earth")
        {
            shape.setFillColor(sf::Color::Blue);
            shape.setRadius(object->get_radius() / EARTH_RADIUS_SCALE);
        }
        else if (object->get_name() == "Mars")
        {
            shape.setFillColor(sf::Color::Red);
            shape.setRadius(object->get_radius() / MARS_RADIUS_SCALE);
        }
        else if (object->get_name() == "Jupiter")
        {
            shape.setFillColor(sf::Color(218, 165, 32)); // Golden
            shape.setRadius(object->get_radius() / JUPITER_RADIUS_SCALE);
        }
        else if (object->get_name() == "Saturn")
        {
            shape.setFillColor(sf::Color(210, 180, 140)); // Tan
            shape.setRadius(object->get_radius() / SATURN_RADIUS_SCALE);
        }
        else if (object->get_name() == "Uranus")
        {
            shape.setFillColor(sf::Color(0, 255, 255)); // Cyan
            shape.setRadius(object->get_radius() / URANUS_RADIUS_SCALE);
        }
        else if (object->get_name() == "Neptune")
        {
            shape.setFillColor(sf::Color(0, 0, 139)); // Dark Blue
            shape.setRadius(object->get_radius() / NEPTUNE_RADIUS_SCALE);
        }

        shape.setOrigin(shape.getRadius(), shape.getRadius());

        sf::Vector2f screen_position = compress_position(object->get_position());
        screen_position += sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

        shape.setPosition(screen_position);

        shapes.push_back(shape);
    }

    DynamicMovementStrategy dynamicStrategy(GRAVITATIONAL_CONSTANT);
    DynamicMovementStrategy *strategy = &dynamicStrategy;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float delta_time = clock.restart().asSeconds() * TIME_SCALE;

        if (!pause_at_start)
        {
            for (size_t i = 0; i < objects.size(); ++i)
            {
                if (!objects[i]->is_movable())
                {
                    continue;
                }

                std::vector<const SpaceObject *> others;

                for (size_t j = 0; j < objects.size(); ++j)
                {
                    if (i != j)
                    {
                        others.push_back(objects[j]);
                    }
                }

                strategy->apply_velocity(objects[i], others, delta_time);
            }

            for (size_t i = 0; i < objects.size(); ++i)
            {
                sf::Vector2f position = objects[i]->get_position();
                sf::Vector2f velocity = objects[i]->get_velocity();
                position += velocity * delta_time;

                objects[i]->set_position(position);

                sf::Vector2f screen_position = compress_position(objects[i]->get_position());
                screen_position += sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

                shapes[i].setPosition(screen_position);
            }
        }

        window.clear(sf::Color::Black);

        for (const auto &shape : shapes)
        {
            window.draw(shape);
        }

        window.display();

        if (pause_at_start)
        {
            std::cout << "Pause at start. Press Enter to quit...\n";
            std::cin.get();
            break;
        }
    }

    for (auto object : objects)
    {
        delete object;
    }

    return 0;
}

sf::Vector2f compress_position(const sf::Vector2f &pos)
{
    sf::Vector2f compressed;
    compressed.x = (pos.x / POSITION_SCALE) * std::atan(std::abs(pos.x) / POSITION_SCALE);
    compressed.y = (pos.y / POSITION_SCALE) * std::atan(std::abs(pos.y) / POSITION_SCALE);
    
    return compressed;
}
