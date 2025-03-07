#include <iostream>
#include <string>

class Planet
{
private:
    static int objectCount;

    int id;
    std::string name;
    double mass;
    double radius;
    double distanceFromSun;
    double velocity;

public:
    Planet(std::string planetName, double planetMass, double planetRadius, double initialDistance, double initialVelocity = 0.0)
        : name(planetName), mass(planetMass), radius(planetRadius), distanceFromSun(initialDistance), velocity(initialVelocity)
    {
        id = ++objectCount;
    }

    ~Planet()
    {
        --objectCount;
    }

    void printInfo() const
    {
        std::cout << "Planet ID: " << id << "\n"
                  << "Name: " << name << "\n"
                  << "Mass: " << mass << " kg\n"
                  << "Radius: " << radius << " km\n"
                  << "Distance from Sun: " << distanceFromSun << " km\n"
                  << "Velocity: " << velocity << " m/s\n\n";
    }

    void changeVelocity(double deltaV)
    {
        velocity += deltaV;
    }

    int getId() const
    {
        return id;
    }

    std::string getName() const
    {
        return name;
    }

    double getMass() const
    {
        return mass;
    }

    double getRadius() const
    {
        return radius;
    }

    double getDistanceFromSun() const
    {
        return distanceFromSun;
    }

    double getVelocity() const
    {
        return velocity;
    }

    static int getObjectCount()
    {
        return objectCount;
    }
};

int Planet::objectCount = 0;

int main()
{
    std::cout << "\nStatic array of planets demonstration:\n\n";
    Planet planetArray[2] = {
        Planet("Venus", 4.867e24, 6051, 1.082e8, 1234),
        Planet("Neptune", 1.024e26, 24622, 4.498e9)};

    for (const auto &planet : planetArray)
    {
        planet.printInfo();
    }

    planetArray[0].changeVelocity(1000);
    std::cout << "New velocity of " << planetArray[0].getName() << ": " << planetArray[0].getVelocity() << " m/s\n\n";

    std::cout << "Total active planets: " << Planet::getObjectCount() << "\n";

    std::cout << "\nDynamic array of planets demonstration:\n\n";
    Planet *dynamicPlanets = new Planet[2]{
        Planet("Saturn", 5.683e26, 58232, 1.429e9, 100),
        Planet("Uranus", 8.681e25, 25362, 2.871e9)};

    for (int i = 0; i < 2; ++i)
    {
        dynamicPlanets[i].printInfo();
    }

    std::cout << "Total active planets: " << Planet::getObjectCount() << "\n";

    delete[] dynamicPlanets;
    std::cout << "Dynamic planets have been deleted.\n";
    std::cout << "Total active planets after deletion: " << Planet::getObjectCount() << "\n\n";

    std::cout << "Testing all the getter methods: \n";
    std::cout << "Planet ID: " << planetArray[0].getId() << "\n";
    std::cout << "Planet Name: " << planetArray[0].getName() << "\n";
    std::cout << "Planet Mass: " << planetArray[0].getMass() << "\n";
    std::cout << "Planet Radius: " << planetArray[0].getRadius() << "\n";
    std::cout << "Planet Distance from Sun: " << planetArray[0].getDistanceFromSun() << "\n";
    std::cout << "Planet Velocity: " << planetArray[0].getVelocity() << "\n";

    return 0;
}
