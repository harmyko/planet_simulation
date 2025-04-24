#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "space_object.hpp"
#include "movement_strategy/dynamic_movement_strategy.hpp"

const float SUN_RADIUS_SCALE =      12000.f;
const float MERCURY_RADIUS_SCALE =  300.f;
const float VENUS_RADIUS_SCALE =    450.f;
const float EARTH_RADIUS_SCALE =    400.f;
const float MARS_RADIUS_SCALE =     350.f;
const float JUPITER_RADIUS_SCALE =  1900.f;
const float SATURN_RADIUS_SCALE =   1800.f;
const float URANUS_RADIUS_SCALE =   1800.f;
const float NEPTUNE_RADIUS_SCALE =  1400.f;

const float SUN_POSITION_SCALE =        1000000000.f;
const float MERCURY_POSITION_SCALE =    700000000.f;
const float VENUS_POSITION_SCALE =      900000000.f;
const float EARTH_POSITION_SCALE =      950000000.f;
const float MARS_POSITION_SCALE =       1130000000.f;
const float JUPITER_POSITION_SCALE =    3000000000.f;
const float SATURN_POSITION_SCALE =     4300000000.f;
const float URANUS_POSITION_SCALE =     7500000000.f;
const float NEPTUNE_POSITION_SCALE =    10500000000.f;

const float TIME_SCALE = 5e6;

const int WINDOW_WIDTH = 1900;
const int WINDOW_HEIGHT = 1000;
const float GRAVITATIONAL_CONSTANT = 6.67430e-11f;

bool pause_at_start = false;

// Scales the position of an object so it can be seen on the window
sf::Vector2f scale_position(SpaceObject *object);

// Scales the radius of an object so it can be visible (not too small and not too big) on the window
double scale_radius(SpaceObject *object);

// Assigns the position to a CircleShape object so it can be visible on the window
void assign_position(sf::CircleShape *shape, sf::Vector2f position);

// Assigns a colour to the CircleShape object depending on the name of object
void assign_colour(sf::CircleShape *shape, std::string object_name);

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

        assign_colour(&shape, object->get_name());

        double scaled_radius = scale_radius(object);
        shape.setRadius(scaled_radius);
        shape.setOrigin(shape.getRadius(), shape.getRadius());

        sf::Vector2f scaled_position = scale_position(object);
        assign_position(&shape, scaled_position);

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

                strategy->update_velocity(objects[i], others, delta_time);
            }

            for (size_t i = 0; i < objects.size(); ++i)
            {
                sf::Vector2f position = objects[i]->get_position();
                sf::Vector2f velocity = objects[i]->get_velocity();
                position += velocity * delta_time;

                objects[i]->set_position(position);

                sf::Vector2f scaled_position = scale_position(objects[i]);
                assign_position(&shapes[i], scaled_position);
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

sf::Vector2f scale_position(SpaceObject *object)
{
    sf::Vector2f position = object->get_position();
    std::string object_name = object->get_name();
    sf::Vector2f scaled_position;

    if (object_name == "Sun")
    {
        scaled_position.x = position.x / SUN_POSITION_SCALE;
        scaled_position.y = position.y / SUN_POSITION_SCALE;
    }
    else if (object_name == "Mercury")
    {
        scaled_position.x = position.x / MERCURY_POSITION_SCALE;
        scaled_position.y = position.y / MERCURY_POSITION_SCALE;
    }
    else if (object_name == "Venus")
    {
        scaled_position.x = position.x / VENUS_POSITION_SCALE;
        scaled_position.y = position.y / VENUS_POSITION_SCALE;
    }
    else if (object_name == "Earth")
    {
        scaled_position.x = position.x / EARTH_POSITION_SCALE;
        scaled_position.y = position.y / EARTH_POSITION_SCALE;
    }
    else if (object_name == "Mars")
    {
        scaled_position.x = position.x / MARS_POSITION_SCALE;
        scaled_position.y = position.y / MARS_POSITION_SCALE;
    }
    else if (object_name == "Jupiter")
    {
        scaled_position.x = position.x / JUPITER_POSITION_SCALE;
        scaled_position.y = position.y / JUPITER_POSITION_SCALE;
    }
    else if (object_name == "Saturn")
    {
        scaled_position.x = position.x / SATURN_POSITION_SCALE;
        scaled_position.y = position.y / SATURN_POSITION_SCALE;
    }
    else if (object_name == "Uranus")
    {
        scaled_position.x = position.x / URANUS_POSITION_SCALE;
        scaled_position.y = position.y / URANUS_POSITION_SCALE;
    }
    else if (object_name == "Neptune")
    {
        scaled_position.x = position.x / NEPTUNE_POSITION_SCALE;
        scaled_position.y = position.y / NEPTUNE_POSITION_SCALE;
    }
    else
    {
        scaled_position.x = position.x / EARTH_POSITION_SCALE;
        scaled_position.y = position.y / EARTH_POSITION_SCALE;   
    }
    
    return scaled_position;
}

double scale_radius(SpaceObject *object)
{
    double radius = object->get_radius();
    std::string object_name = object->get_name();
    double scaled_radius;

    if (object_name == "Sun")
    {
        scaled_radius = radius / SUN_RADIUS_SCALE;
    }
    else if (object_name == "Mercury")
    {
        scaled_radius = radius / MERCURY_RADIUS_SCALE;
    }
    else if (object_name == "Venus")
    {
        scaled_radius = radius / VENUS_RADIUS_SCALE;
    }
    else if (object_name == "Earth")
    {
        scaled_radius = radius / EARTH_RADIUS_SCALE;
    }
    else if (object_name == "Mars")
    {
        scaled_radius = radius / MARS_RADIUS_SCALE;
    }
    else if (object_name == "Jupiter")
    {
        scaled_radius = radius / JUPITER_RADIUS_SCALE;
    }
    else if (object_name == "Saturn")
    {
        scaled_radius = radius / SATURN_RADIUS_SCALE;
    }
    else if (object_name == "Uranus")
    {
        scaled_radius = radius / URANUS_RADIUS_SCALE;
    }
    else if (object_name == "Neptune")
    {
        scaled_radius = radius / NEPTUNE_RADIUS_SCALE;
    }
    else
    {
        scaled_radius = radius / EARTH_RADIUS_SCALE;
    }

    return scaled_radius;
}

void assign_position(sf::CircleShape *shape, sf::Vector2f position)
{
    position += sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
    shape->setPosition(position);
}

void assign_colour(sf::CircleShape *shape, std::string object_name)
{
    if (object_name == "Sun")
    {
        shape->setFillColor(sf::Color::Yellow);
    }
    else if (object_name == "Mercury")
    {
        shape->setFillColor(sf::Color(169, 169, 169)); // Gray
    }
    else if (object_name == "Venus")
    {
        shape->setFillColor(sf::Color(255, 140, 0)); // Orange
    }
    else if (object_name == "Earth")
    {
        shape->setFillColor(sf::Color::Blue);
    }
    else if (object_name == "Mars")
    {
        shape->setFillColor(sf::Color::Red);
    }
    else if (object_name == "Jupiter")
    {
        shape->setFillColor(sf::Color(218, 165, 32)); // Golden
    }
    else if (object_name == "Saturn")
    {
        shape->setFillColor(sf::Color(210, 180, 140)); // Tan
    }
    else if (object_name == "Uranus")
    {
        shape->setFillColor(sf::Color(0, 255, 255)); // Cyan
    }
    else if (object_name == "Neptune")
    {
        shape->setFillColor(sf::Color(0, 0, 139)); // Dark Blue
    }
}