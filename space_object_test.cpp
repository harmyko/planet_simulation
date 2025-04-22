#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "space_object.h"
#include "movement_strategy/dynamic_movement_strategy.h"
#include "movement_strategy/static_movement_strategy.h"

const float PLANET_RADIUS_SCALE = 1e2f;
const float SUN_RADIUS_SCALE = 1e4f;

const float MASS_SCALE = 1e22f;
const float VELOCITY_SCALE = 1e4f;

const float TIME_SCALE = 10;

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const float GRAVITATIONAL_CONSTANT = 1.0f; // not the scientific value

bool pause_at_start = false;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Object Simulation");
    window.setFramerateLimit(60);

    std::vector<SpaceObject> objects;
    objects.push_back(SpaceObject("Sun", 1.989e30 / MASS_SCALE, 696340, {600, 400}, {0, 0}, false));
    objects.push_back(SpaceObject("Earth", 5.972e24 / MASS_SCALE, 6371, {600, 100}, {29000 / VELOCITY_SCALE, 0}));
    objects.push_back(SpaceObject("Mars", 6.39e23 / MASS_SCALE, 3389, {600, 700}, {-24000 / VELOCITY_SCALE / VELOCITY_SCALE, 0}));

    std::vector<sf::CircleShape> shapes;
    for (const auto &object : objects)
    {
        sf::CircleShape shape(object.get_radius() / PLANET_RADIUS_SCALE);

        if (object.get_name() == "Sun")
        {
            shape.setRadius(object.get_radius() / SUN_RADIUS_SCALE);
            shape.setFillColor(sf::Color::Yellow);
        }
        else
        {
            shape.setFillColor(sf::Color::White);
        }

        shape.setOrigin(shape.getRadius(), shape.getRadius());
        shape.setPosition(object.get_position());

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
                if (!objects[i].is_movable())
                {
                    continue;
                }

                std::vector<SpaceObject> others;

                for (size_t j = 0; j < objects.size(); ++j)
                {
                    if (i != j)
                    {
                        others.push_back(objects[j]);
                    }
                }

                strategy->apply_velocity(objects[i], others);
            }

            for (size_t i = 0; i < objects.size(); ++i)
            {
                sf::Vector2f position = objects[i].get_position();
                sf::Vector2f velocity = objects[i].get_velocity();
                position += velocity * delta_time;
                objects[i].set_position(position);
                shapes[i].setPosition(position);
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


    return 0;
}
