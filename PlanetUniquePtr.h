#ifndef PLANETUNIQUEPTR_H
#define PLANETUNIQUEPTR_H

#include <string>
#include <memory>

class Planet
{
private:
    class PlanetImpl;
    std::unique_ptr<PlanetImpl> impl;

public:
    Planet();
    Planet(std::string name, double mass, double radius, double distance, double velocity = 0);
    Planet(const Planet &other);
    Planet &operator=(const Planet &other);
    ~Planet();

    void printInfo(std::ostream &output) const;
    void changeVelocity(double deltaV);

    int getId() const;
    std::string getName() const;
    double getMass() const;
    double getRadius() const;
    double getDistanceFromSun() const;
    double getVelocity() const;
    void setName(std::string name);
    void setMass(double mass);
    void setRadius(double radius);
    void setDistanceFromSun(double distance);
    void setVelocity(double velocity);

    static int getObjectCount();
};

#endif // PLANET_UNIQUE_PTR_H
