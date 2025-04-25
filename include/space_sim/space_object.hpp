#ifndef SPACE_OBJECT_HPP
#define SPACE_OBJECT_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/System.hpp>

#include "exception.hpp"

class SpaceObject
{
private:
    // Pointer to an implementation of SpaceObject
    class SpaceObjectImpl;
    SpaceObjectImpl *impl;

public:
    // Constructors and Deconstructor

    SpaceObject();

    /** @brief
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

    /** @brief
     * Copy constructor for SpaceObject.
     *
     * @param other Another SpaceObject to copy from.
     */
    SpaceObject(const SpaceObject &other);

    ~SpaceObject();

    // Operators

    /** @brief
     * Assignment operator for SpaceObject.
     *
     * @param other Another SpaceObject to assign from.
     * @return A reference to this SpaceObject.
     */
    SpaceObject &operator=(const SpaceObject &other);

    /** @brief
     * Serialization operator (<<) for saving SpaceObject to a file.
     *
     * @param out Output file stream.
     * @param obj SpaceObject to write.
     * @return Output file stream.
     */
    friend std::ofstream &operator<<(std::ofstream &out, const SpaceObject &obj);

    /** @brief
     * Deserialization operator (>>) for reading SpaceObject from a file.
     *
     * @param in Input file stream.
     * @param obj SpaceObject to read into.
     * @return Input file stream.
     */
    friend std::ifstream &operator>>(std::ifstream &in, SpaceObject &obj);

    // Methods

    /** @brief
     * Prints the information of the space object.
     *
     * @param output Output stream to print information.
     */
    void print_info(std::ostream &output) const;

    /** @brief
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

    /** @brief
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

    /** @brief
     * Gets the total number of active SpaceObject instances.
     * 
     * @return The current count of active SpaceObjects.
     */
    static int get_object_count();

    /** @brief
     * Gets the unique ID of the space object.
     * 
     * @return The ID of the space object.
     */
    int get_id() const;

    /** @brief
     * Gets the name of the space object.
     * 
     * @return The name as a string.
     */
    std::string get_name() const;

    /** @brief
     * Gets the mass of the space object.
     * 
     * @return The mass as a double.
     */
    double get_mass() const;

    /** @brief
     * Gets the radius of the space object.
     * 
     * @return The radius as a double.
     */
    double get_radius() const;

    /** @brief
     * Gets the current velocity of the space object.
     * 
     * @return The velocity as an sf::Vector2f.
     */
    sf::Vector2f get_velocity() const;

    /** @brief
     * Gets the current position of the space object.
     * 
     * @return The position as an sf::Vector2f.
     */
    sf::Vector2f get_position() const;

    /** @brief
     * Checks whether the space object is movable.
     * 
     * @return True if movable, false otherwise.
     */
    bool is_movable() const;

    // Setters

    /** @brief
     * Sets the name of the space object.
     * 
     * @param name New name as a string.
     */
    void set_name(std::string name);

    /** @brief
     * Sets the mass of the space object.
     * 
     * @param mass New mass value.
     */
    void set_mass(double mass);

    /** @brief
     * Sets the radius of the space object.
     * 
     * @param radius New radius value.
     */
    void set_radius(double radius);

    /** @brief
     * Sets the position of the space object.
     * 
     * @param position New position as an sf::Vector2f.
     */
    void set_position(sf::Vector2f position);

    /** @brief
     * Sets the velocity of the space object.
     * 
     * @param velocity New velocity as an sf::Vector2f.
     */
    void set_velocity(sf::Vector2f velocity);

    /** @brief
     * Sets whether the object is movable or static.
     * 
     * @param movable True to make the object movable, false to make it static.
     */
    void set_movability(bool movable);
};

#endif // SPACE_OBJECT_HPP
