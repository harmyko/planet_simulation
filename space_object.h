#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H

#include <string>
#include <SFML/System.hpp>

class SpaceObject
{
private:

    // Pointer to an implementation of SpaceObject
    class SpaceObjectImpl;
    SpaceObjectImpl *impl;

public:

    // Constructors and Deconstructor
    SpaceObject();
    SpaceObject(std::string name, double mass, double radius, sf::Vector2f position, sf::Vector2f velocity = {0, 0}, bool is_movable = true);
    SpaceObject(const SpaceObject &other);
    ~SpaceObject();

    // Operators
    SpaceObject &operator=(const SpaceObject &other);

    // Methods
    void print_info(std::ostream &output) const;
    void update_velocity(sf::Vector2f velocity);

    // Getters
    static int get_object_count();
    int get_id() const;
    std::string get_name() const;
    double get_mass() const;
    double get_radius() const;
    sf::Vector2f get_velocity() const;
    sf::Vector2f get_position() const;
    bool is_movable() const;

    // Setters
    void set_name(std::string name);
    void set_mass(double mass);
    void set_radius(double radius);
    void set_position(sf::Vector2f position);
    void set_velocity(sf::Vector2f velocity);
    void set_movability(bool movable);
};

#endif // SPACE_OBJECT_H
