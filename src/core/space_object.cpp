#include <iostream>
#include <fstream>
#include <SFML/System.hpp>

#include "space_object.hpp"
#include "movement/dynamic.hpp"
#include "movement/static.hpp"

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
    bool movable;

    IMovementStrategy *movement_strategy = nullptr;

    SpaceObjectImpl(std::string name, double mass, double radius, sf::Vector2f position, sf::Vector2f velocity, bool movable)
    {
        set_name(name);
        set_mass(mass);
        set_radius(radius);
        set_position(position);
        set_velocity(velocity);
        set_movability(movable);

        id = ++object_count;
    }

    SpaceObjectImpl(const SpaceObjectImpl &other)
    {
        set_name(other.name);
        set_mass(other.mass);
        set_radius(other.radius);
        set_position(other.position);
        set_velocity(other.velocity);
        set_movability(other.movable);

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
            throw SpaceObjectException("SpaceObject mass cannot be negative!");
        }

        this->mass = mass;
    }

    void set_radius(double radius)
    {
        if (radius < 0)
        {
            throw SpaceObjectException("SpaceObject radius cannot be negative!");
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

    void set_movability(bool movable)
    {
        this->movable = movable;

        if (movement_strategy != nullptr)
        {
            delete movement_strategy;
        }

        set_movement_strategy(movable);
    }

    void set_movement_strategy(bool movable)
    {
        if (movable == true)
        {
            this->movement_strategy = new DynamicMovementStrategy(&mass, &radius, &position, &velocity);
        }
        else
        {
            this->movement_strategy = new StaticMovementStrategy(&mass, &radius, &position, &velocity);
        }
    }
};

int SpaceObject::SpaceObjectImpl::object_count = 0;

// Constructors and destructor
SpaceObject::SpaceObject()
{
    impl = new SpaceObjectImpl("unnamed", 0, 0, {0, 0}, {0, 0}, false);
}

SpaceObject::SpaceObject(std::string name, double mass, double radius, sf::Vector2f position, sf::Vector2f velocity, bool movable)
{
    impl = new SpaceObjectImpl(name, mass, radius, position, velocity, movable);
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
           << "Velocity: (" << impl->velocity.x << ", " << impl->velocity.y << ") m/s\n"
           << "Is movable: " << impl->movable << "\n\n";
}

void SpaceObject::update_velocity(std::vector<const SpaceObject *> &others,
                                  const float gravitational_constant, const float delta_time)
{
    impl->movement_strategy->update_velocity(others, gravitational_constant, delta_time);
}

void SpaceObject::update_position(const float delta_time)
{
    impl->movement_strategy->update_position(delta_time);
}

// Getters
int SpaceObject::get_object_count() { return SpaceObjectImpl::object_count; }
int SpaceObject::get_id() const { return impl->id; }
std::string SpaceObject::get_name() const { return impl->name; }
double SpaceObject::get_mass() const { return impl->mass; }
double SpaceObject::get_radius() const { return impl->radius; }
sf::Vector2f SpaceObject::get_position() const { return impl->position; }
sf::Vector2f SpaceObject::get_velocity() const { return impl->velocity; }
bool SpaceObject::is_movable() const { return impl->movable; }

// Setters
void SpaceObject::set_name(std::string name) { impl->set_name(name); }
void SpaceObject::set_mass(double mass) { impl->set_mass(mass); }
void SpaceObject::set_radius(double radius) { impl->set_radius(radius); }
void SpaceObject::set_position(sf::Vector2f position) { impl->set_position(position); }
void SpaceObject::set_velocity(sf::Vector2f velocity) { impl->set_velocity(velocity); }
void SpaceObject::set_movability(bool movable) { impl->set_movability(movable); }

std::ofstream &operator<<(std::ofstream &out, const SpaceObject &obj)
{
    const SpaceObject::SpaceObjectImpl &impl = *obj.impl;

    out.write(reinterpret_cast<const char *>(&impl.id), sizeof(impl.id));
    size_t name_length = impl.name.size();
    out.write(reinterpret_cast<const char *>(&name_length), sizeof(name_length));
    out.write(impl.name.c_str(), name_length);
    out.write(reinterpret_cast<const char *>(&impl.mass), sizeof(impl.mass));
    out.write(reinterpret_cast<const char *>(&impl.radius), sizeof(impl.radius));
    out.write(reinterpret_cast<const char *>(&impl.position), sizeof(impl.position));
    out.write(reinterpret_cast<const char *>(&impl.velocity), sizeof(impl.velocity));
    out.write(reinterpret_cast<const char *>(&impl.movable), sizeof(impl.movable));

    int strategy_type = (impl.movable) ? 1 : 0;
    out.write(reinterpret_cast<const char *>(&strategy_type), sizeof(strategy_type));

    return out;
}

std::ifstream &operator>>(std::ifstream &in, SpaceObject &obj)
{
    SpaceObject::SpaceObjectImpl &impl = *obj.impl;

    in.read(reinterpret_cast<char *>(&impl.id), sizeof(impl.id));
    size_t name_length;
    in.read(reinterpret_cast<char *>(&name_length), sizeof(name_length));

    char *name_buffer = new char[name_length + 1];
    in.read(name_buffer, name_length);
    name_buffer[name_length] = '\0';
    impl.name = name_buffer;
    delete[] name_buffer;

    in.read(reinterpret_cast<char *>(&impl.mass), sizeof(impl.mass));
    in.read(reinterpret_cast<char *>(&impl.radius), sizeof(impl.radius));
    in.read(reinterpret_cast<char *>(&impl.position), sizeof(impl.position));
    in.read(reinterpret_cast<char *>(&impl.velocity), sizeof(impl.velocity));
    in.read(reinterpret_cast<char *>(&impl.movable), sizeof(impl.movable));

    int strategy_type;
    in.read(reinterpret_cast<char *>(&strategy_type), sizeof(strategy_type));
    if (strategy_type == 1)
    {
        impl.movement_strategy = new DynamicMovementStrategy(&impl.mass, &impl.radius, &impl.position, &impl.velocity);
    }
    else
    {
        impl.movement_strategy = new StaticMovementStrategy(&impl.mass, &impl.radius, &impl.position, &impl.velocity);
    }

    return in;
}