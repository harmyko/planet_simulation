#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

#include "space_object.hpp"

const int WINDOW_WIDTH = 1900;
const int WINDOW_HEIGHT = 900;
const std::string FONT_DIRECTORY = "../resources/MontserratBlack.ttf";

// Playing around and experimenting with these values can be quite fun!
const int TILE_SIZE = 100;
const int MIN_OBJECTS = 30;
const int MAX_OBJECTS_DIVISOR = 5; // Total available positions get divided by this number to mitigate the max possible amount of objects
const int DELTA_TIME = 1;
const int VELOCITY_MAX = 2;
const float GRAVITATIONAL_CONSTANT = 5;
const int MASS_MIN = 5;
const int MASS_MAX = 10;
const int RADIUS_MIN = 5;
const int RADIUS_MAX = TILE_SIZE / 2;

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
    if (!font.loadFromFile(FONT_DIRECTORY))
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

        for (size_t i = 0; i < objects.size(); ++i)
        {
            std::vector<const SpaceObject *> others;

            for (size_t j = 0; j < objects.size(); ++j)
            {
                if (i != j)
                {
                    others.push_back(objects[j]);
                }
            }

            objects[i]->update_velocity(others, GRAVITATIONAL_CONSTANT, DELTA_TIME);
        }

        size_t i = 0;
        while (i < objects.size())
        {
            objects[i]->update_position(DELTA_TIME);
            sf::Vector2f position = objects[i]->get_position();

            if (position.x > WINDOW_WIDTH + objects[i]->get_radius() ||
                position.y > WINDOW_HEIGHT + objects[i]->get_radius() ||
                position.x < -objects[i]->get_radius() ||
                position.y < -objects[i]->get_radius())
            {
                delete objects[i];
                delete shapes[i];
                objects.erase(objects.begin() + i);
                shapes.erase(shapes.begin() + i);
            }
            else
            {
                objects[i]->set_position(position);
                shapes[i]->setPosition(position);
                ++i;
            }
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
    int random_objects_to_create = get_random_number(MIN_OBJECTS, available_positions.size() / MAX_OBJECTS_DIVISOR);

    while (random_objects_to_create)
    {
        int random_available_position_index = get_random_number(0, available_positions.size() - 1);
        sf::Vector2f random_position = available_positions[random_available_position_index];
        available_positions.erase(available_positions.begin() + random_available_position_index);

        double random_mass = get_random_number(MASS_MIN, MASS_MAX);
        double random_radius = get_random_number(RADIUS_MIN, RADIUS_MAX);
        sf::Vector2f random_velocity;

        if (random_position.x <= WINDOW_WIDTH / 2 && random_position.y <= WINDOW_HEIGHT)
        {
            random_velocity = {float(get_random_number(0, VELOCITY_MAX)), float(get_random_number(0, VELOCITY_MAX))};
        }
        else if (random_position.x > WINDOW_WIDTH / 2 && random_position.y <= WINDOW_HEIGHT)
        {
            random_velocity = {float(get_random_number(-VELOCITY_MAX, 0)), float(get_random_number(0, VELOCITY_MAX))};
        }
        else if (random_position.x <= WINDOW_WIDTH / 2 && random_position.y > WINDOW_HEIGHT)
        {
            random_velocity = {float(get_random_number(0, VELOCITY_MAX)), float(get_random_number(-VELOCITY_MAX, 0))};
        }
        else
        {
            random_velocity = {float(get_random_number(-VELOCITY_MAX, 0)), float(get_random_number(-VELOCITY_MAX, 0))};
        }

        random_objects.push_back(new SpaceObject("random_object", random_mass, random_radius, random_position, random_velocity));
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
