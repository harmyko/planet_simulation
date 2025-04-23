#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

#include "space_object.h"
#include "movement_strategy/dynamic_movement_strategy.h"

const int WINDOW_WIDTH = 1900;
const int WINDOW_HEIGHT = 900;
const int TILE_SIZE = 100;
const int MAX_OBJECTS_DIVISOR = 15; // Total available positions get divided by this number to mitigate the max possible amount of objects

const float GRAVITATIONAL_CONSTANT = 6.67430e-11f;

std::vector<SpaceObject *> create_random_objects();
int get_random_number(int min, int max);

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Random Object Sandbox");
    window.setFramerateLimit(60);

    std::vector<SpaceObject *> objects = create_random_objects();
    std::vector<sf::CircleShape *> shapes;

    for (const auto object : objects)
    {
        shapes.push_back(new sf::CircleShape(object->get_radius()));
        shapes.back()->setOrigin(object->get_radius(), object->get_radius());
        shapes.back()->setPosition(object->get_position());
        shapes.back()->setFillColor(sf::Color(get_random_number(0, 255), get_random_number(0, 255), get_random_number(0, 255)));
    }

    sf::Font font;
    if (!font.loadFromFile("resources/MontserratBlack.ttf"))
    {
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        text.setString("Object count: " + std::to_string(SpaceObject::get_object_count()));

        for (const auto shape : shapes)
        {
            window.draw(*shape);
        }

        window.draw(text);
        window.display();
    }

    return 0;
}

std::vector<SpaceObject *> create_random_objects()
{
    // Creating a grid for the window
    std::vector<sf::Vector2f> available_positions;

    int tile_count_x = WINDOW_WIDTH / TILE_SIZE;
    int tile_count_y = WINDOW_HEIGHT / TILE_SIZE;

    for (int i = 0; i < tile_count_x; ++i)
    {
        for (int j = 0; j < tile_count_y; ++j)
        {
            available_positions.push_back(sf::Vector2f(TILE_SIZE * i + TILE_SIZE / 2, TILE_SIZE * j + TILE_SIZE / 2));
        }
    }

    // Creating a random amount of random objects
    std::vector<SpaceObject *> random_objects;
    int random_objects_to_create = get_random_number(3, available_positions.size() / MAX_OBJECTS_DIVISOR);

    while (random_objects_to_create)
    {
        int random_available_position_index = get_random_number(0, available_positions.size() - 1);
        sf::Vector2f random_position = available_positions[random_available_position_index];
        available_positions.erase(available_positions.begin() + random_available_position_index);

        double random_mass = get_random_number(100, 1000);
        double random_radius = get_random_number(5, 50);

        random_objects.push_back(new SpaceObject("random_object", random_mass, random_radius, random_position));
        --random_objects_to_create;
    }

    return random_objects;
}

int get_random_number(int min, int max)
{
    static std::random_device random_device;
    static std::mt19937 generator(random_device());
    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(generator);
}
