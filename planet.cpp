#include <iostream>
#include <fstream>
#include <SFML/System.hpp>

#include "planet.h"
#include "planet_exception.h"

class Planet::PlanetImpl
{
public:
    static int objectCount;

    int id;
    std::string name;
    double mass;
    double radius;
    sf::Vector2f position;
    sf::Vector2f velocity;

    PlanetImpl(std::string name, double mass, double radius, sf::Vector2f position, sf::Vector2f velocity)
    {
        setName(name);
        setMass(mass);
        setRadius(radius);
        setPosition(position);
        setVelocity(velocity);

        id = ++objectCount;
    }

    PlanetImpl(const PlanetImpl &other)
    {
        setName(other.name);
        setMass(other.mass);
        setRadius(other.radius);
        setPosition(other.position);
        setVelocity(other.velocity);

        id = ++objectCount;
    }

    ~PlanetImpl()
    {
        --objectCount;
    }

    void setName(std::string name)
    {
        this->name = name;
    }

    void setMass(double mass)
    {   
        if (mass < 0)
        {
            throw PlanetException("Planet mass cannot be negative!");
        }

        this->mass = mass;
    }

    void setRadius(double radius)
    {
        if (radius < 0)
        {
            throw PlanetException("Planet radius cannot be negative!");
        }

        this->radius = radius;
    }

    void setPosition(sf::Vector2f position)
    {
        this->position = position;
    }

    void setVelocity(sf::Vector2f velocity)
    {
        this->velocity = velocity;
    }
};

int Planet::PlanetImpl::objectCount = 0;

Planet::Planet()
{
    impl = new PlanetImpl("Unnamed", 0, 0, {0, 0}, {0, 0});
}

Planet::Planet(std::string name, double mass, double radius, sf::Vector2f position, sf::Vector2f velocity)
{
    impl = new PlanetImpl(name, mass, radius, position, velocity);
}

Planet::Planet(const Planet &other)
{
    impl = new PlanetImpl(*other.impl);
}

Planet &Planet::operator=(const Planet &other)
{
    if (this != &other)
    {
        delete impl;
        impl = new PlanetImpl(*other.impl);
    }
    return *this;
}

Planet::~Planet()
{
    delete impl;
}

void Planet::printInfo(std::ostream &output) const
{
    output  << "Planet ID: " << impl->id << "\n"
            << "Name: " << impl->name << "\n"
            << "Mass: " << impl->mass << " kg\n"
            << "Radius: " << impl->radius << " km\n"
            << "Position: (" << impl->position.x << ", " << impl->position.y << ") m/s\n\n"
            << "Velocity: (" << impl->velocity.x << ", " << impl->velocity.y << ") m/s\n\n";
}

void Planet::changeVelocity(double deltaV)
{
    
}

int Planet::getId() const
{
     return impl->id;
}

std::string Planet::getName() const {
    return impl->name;
}
double Planet::getMass() const
{
    return impl->mass;
}

double Planet::getRadius() const
{
    return impl->radius;

}

sf::Vector2f Planet::getPosition() const
{
    return impl->position;
}

sf::Vector2f Planet::getVelocity() const
{
    return impl->velocity;
}

int Planet::getObjectCount()
{
    return PlanetImpl::objectCount;
}

void Planet::setName(std::string name)
{
    impl->setName(name);
}

void Planet::setMass(double mass)
{
    impl->setMass(mass);
}

void Planet::setRadius(double radius)
{
    impl->setRadius(radius);

}

void Planet::setPosition(sf::Vector2f position)
{
    impl->setPosition(position);
}

void Planet::setVelocity(sf::Vector2f velocity)
{
    impl->setVelocity(velocity);
}
