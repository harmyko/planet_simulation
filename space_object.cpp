#include <iostream>
#include <fstream>
#include <SFML/System.hpp>

#include "space_object.h"
#include "space_object_exception.h"

class SpaceObject::SpaceObjectImpl
{
public:

    static int object_count;

    int id;
    std::string name;
    double mass;
    double radius;
    sf::Vector2f position;
    sf::Vector2f velocity;

    SpaceObjectImpl(std::string name, double mass, double radius, sf::Vector2f position, sf::Vector2f velocity)
    {
        set_name(name);
        set_mass(mass);
        set_radius(radius);
        set_position(position);
        set_velocity(velocity);

        id = ++object_count;
    }

    SpaceObjectImpl(const SpaceObjectImpl &other)
    {
        set_name(other.name);
        set_mass(other.mass);
        set_radius(other.radius);
        set_position(other.position);
        set_velocity(other.velocity);

        id = ++object_count;
    }

    ~SpaceObjectImpl()
    {
        --object_count;
    }

    // Setters responsible for input validation
    void set_name(std::string name)
    {
        this->name = name;
    }

    void set_mass(double mass)
    {
        if (mass < 0)
        {
            throw SpaceObjectException("SpaceObject mass must be positive!");
        }

        this->mass = mass;
    }

    void set_radius(double radius)
    {
        if (radius <= 0)
        {
            throw SpaceObjectException("SpaceObject radius must be positive!");
        }

        this->radius = radius;
    }

    void set_position(sf::Vector2f position)
    {
        this->position = position;
    }

    void set_velocity(sf::Vector2f velocity)
    {
        this->velocity = velocity;
    }
};

int SpaceObject::SpaceObjectImpl::object_count = 0;

// Constructors and destructor
SpaceObject::SpaceObject()
{
    impl = new SpaceObjectImpl("unnamed", 0, 0, {0, 0}, {0, 0});
}

SpaceObject::SpaceObject(std::string name, double mass, double radius, sf::Vector2f position, sf::Vector2f velocity)
{
    impl = new SpaceObjectImpl(name, mass, radius, position, velocity);
}

SpaceObject::SpaceObject(const SpaceObject &other)
{
    impl = new SpaceObjectImpl(*other.impl);
}

SpaceObject &SpaceObject::operator=(const SpaceObject &other)
{
    if (this != &other)
    {
        delete impl;
        impl = new SpaceObjectImpl(*other.impl);
    }
    return *this;
}

SpaceObject::~SpaceObject()
{
    delete impl;
}

// Methods
void SpaceObject::print_info(std::ostream &output) const
{
    output << "SpaceObject ID: " << impl->id << "\n"
           << "Name: " << impl->name << "\n"
           << "Mass: " << impl->mass << " kg\n"
           << "Radius: " << impl->radius << " km\n"
           << "Position: (" << impl->position.x << ", " << impl->position.y << ") m\n"
           << "Velocity: (" << impl->velocity.x << ", " << impl->velocity.y << ") m/s\n\n";
}

void SpaceObject::update_velocity(sf::Vector2f velocity)
{
    impl->set_velocity(velocity);
}

// Getters
int             SpaceObject::get_object_count()      { return SpaceObjectImpl::object_count; }
int             SpaceObject::get_id()          const { return impl->id; }
std::string     SpaceObject::get_name()        const { return impl->name; }
double          SpaceObject::get_mass()        const { return impl->mass; }
double          SpaceObject::get_radius()      const { return impl->radius; }
sf::Vector2f    SpaceObject::get_position()    const { return impl->position; }
sf::Vector2f    SpaceObject::get_velocity()    const { return impl->velocity; }

// Setters
void SpaceObject::set_name(std::string name)          { impl->set_name(name); }
void SpaceObject::set_mass(double mass)               { impl->set_mass(mass); }
void SpaceObject::set_radius(double radius)           { impl->set_radius(radius); }
void SpaceObject::set_position(sf::Vector2f position) { impl->set_position(position); }
void SpaceObject::set_velocity(sf::Vector2f velocity) { impl->set_velocity(velocity); }
