#ifndef SPACE_OBJECT_HPP
#define SPACE_OBJECT_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/System.hpp>

#include "exception.hpp"
#include "movement/dynamic.hpp"
#include "movement/static.hpp"

class SpaceObject
{
private:

    // Pointer to an implementation of SpaceObject
    class SpaceObjectImpl;
    SpaceObjectImpl *impl;

public:

    // Constructors and Deconstructor

    SpaceObject();

    /**
     * Constructs a SpaceObject with specified properties.
     * 
     * @param name Name of the space object.
     * @param mass Mass of the space object.
     * @param radius Radius of the space object.
     * @param position Position of the space object.
     * @param velocity Velocity of the space object (default is {0, 0}).
     * @param is_movable Whether the space object is movable (default is true).
     */
    SpaceObject(std::string name, double mass, double radius, sf::Vector2f position, sf::Vector2f velocity = {0, 0}, bool is_movable = true);

    /**
     * Copy constructor for SpaceObject.
     * 
     * @param other Another SpaceObject to copy from.
     */
    SpaceObject(const SpaceObject &other);

    ~SpaceObject();

    // Operators


    // Operators
    /**
     * Assignment operator for SpaceObject.
     * 
     * @param other Another SpaceObject to assign from.
     * @return A reference to this SpaceObject.
     */
    SpaceObject &operator=(const SpaceObject &other);

    /**
     * Serialization operator for saving SpaceObject to a file.
     * 
     * @param out Output file stream.
     * @param obj SpaceObject to write.
     * @return Output file stream.
     */
    friend std::ofstream &operator<<(std::ofstream &out, const SpaceObject &obj);

    /**
     * Deserialization operator for reading SpaceObject from a file.
     * 
     * @param in Input file stream.
     * @param obj SpaceObject to read into.
     * @return Input file stream.
     */
    friend std::ifstream &operator>>(std::ifstream &in, SpaceObject &obj);

    // Methods

    /**
     * @brief Prints the information of the space object.
     * 
     * @param output Output stream to print information.
     */
    void print_info(std::ostream &output) const;

    /**
     * Updates the velocity of the space object.
     * 
     * The velocity is updated based on the object's movement strategy (either dynamic or static).
     * If the object is dynamic, its velocity will be influenced by gravitational forces and other space objects.
     * If the object is static, its velocity will be set to zero.
     * 
     * @param others List of other space objects for gravitational calculation.
     * @param gravitational_constant Gravitational constant for the calculation.
     * @param delta_time Time step for the update.
     */
    void update_velocity(std::vector<const SpaceObject *> &others, const float gravitational_constant, const float delta_time);

    /**
     * Updates the position of the space object.
     * 
     * The position is updated based on the object's velocity and movement strategy (either dynamic or static).
     * If the object is dynamic, its position will be adjusted based on its velocity.
     * If the object is static, its position will remain unchanged.
     * 
     * @param delta_time Time step for the update.
     */
    void update_position(const float delta_time);

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

#endif // SPACE_OBJECT_HPP
