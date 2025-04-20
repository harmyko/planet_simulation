#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <SFML/System.hpp>

class Planet
{
private:
    class PlanetImpl;
    PlanetImpl *impl;

public:
    Planet();
    Planet(std::string name, double mass, double radius, sf::Vector2f position, sf::Vector2f velocity = {0, 0} );
    Planet(const Planet &other);
    Planet &operator=(const Planet &other);
    ~Planet();

    void printInfo(std::ostream &output) const;
    void changeVelocity(double deltaV);

    int getId() const;
    std::string getName() const;
    double getMass() const;
    double getRadius() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getPosition() const;
    void setName(std::string name);
    void setMass(double mass);
    void setRadius(double radius);
    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f velocity);

    static int getObjectCount();
};

#endif // PLANET_H
