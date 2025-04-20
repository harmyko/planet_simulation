#include <iostream>
#include <string>
#include <fstream>

#include "planet.h"
#include "planet_exception.h"

int main()
{
    std::ofstream outputFile("planet_test.txt");

    if (!outputFile)
    {
        std::cerr << "Failed to open file for writing.\n";
        return 1;
    }

    std::cout << "\nStatic array of planets demonstration:\n\n";
    outputFile << "Static array of planets demonstration:\n\n";

    Planet planetArray[2] = {
        Planet("Venus", 4.867e24, 6051, 1.082e8, 1234),
        Planet("Neptune", 1.024e26, 24622, 4.498e9)};

    for (const auto &planet : planetArray)
    {
        planet.printInfo(std::cout);
        planet.printInfo(outputFile);
    }

    planetArray[0].changeVelocity(1000);
    std::cout << "New velocity of " << planetArray[0].getName() << ": " << planetArray[0].getVelocity() << " m/s\n\n";
    outputFile << "New velocity of " << planetArray[0].getName() << ": " << planetArray[0].getVelocity() << " m/s\n\n";

    std::cout << "Total active planets: " << Planet::getObjectCount() << "\n";
    outputFile << "Total active planets: " << Planet::getObjectCount() << "\n";

    std::cout << "\nDynamic array of planets demonstration:\n\n";
    outputFile << "\nDynamic array of planets demonstration:\n\n";

    Planet *dynamicPlanets = new Planet[2]{
        Planet("Saturn", 5.683e26, 58232, 1.429e9, 100),
        Planet("Uranus", 8.681e25, 25362, 2.871e9)};

    for (int i = 0; i < 2; ++i)
    {
        dynamicPlanets[i].printInfo(std::cout);
        dynamicPlanets[i].printInfo(outputFile);
    }

    std::cout << "Total active planets: " << Planet::getObjectCount() << "\n";
    outputFile << "Total active planets: " << Planet::getObjectCount() << "\n";

    delete[] dynamicPlanets;
    std::cout << "Dynamic planets have been deleted.\n";
    outputFile << "Dynamic planets have been deleted.\n";

    std::cout << "Total active planets after deletion: " << Planet::getObjectCount() << "\n\n";
    outputFile << "Total active planets after deletion: " << Planet::getObjectCount() << "\n\n";

    std::cout   << "Testing all the getter methods: \n"
                << "Planet ID: " << planetArray[0].getId() << "\n"
                << "Planet Name: " << planetArray[0].getName() << "\n"
                << "Planet Mass: " << planetArray[0].getMass() << "\n"
                << "Planet Radius: " << planetArray[0].getRadius() << "\n"
                << "Planet Distance from Sun: " << planetArray[0].getDistanceFromSun() << "\n"
                << "Planet Velocity: " << planetArray[0].getVelocity() << "\n";

    outputFile  << "Testing all the getter methods: \n"
                << "Planet ID: " << planetArray[0].getId() << "\n"
                << "Planet Name: " << planetArray[0].getName() << "\n"
                << "Planet Mass: " << planetArray[0].getMass() << "\n"
                << "Planet Radius: " << planetArray[0].getRadius() << "\n"
                << "Planet Distance from Sun: " << planetArray[0].getDistanceFromSun() << "\n"
                << "Planet Velocity: " << planetArray[0].getVelocity() << "\n";

    Planet copyOfVenus = planetArray[0];
    Planet assigned;
    assigned = planetArray[1];

    std::cout << "\nCopied planet:\n";
    outputFile << "\nCopied planet:\n";
    copyOfVenus.printInfo(std::cout);
    copyOfVenus.printInfo(outputFile);

    std::cout << "Assigned planet:\n";
    outputFile << "Assigned planet:\n";
    assigned.printInfo(std::cout);
    assigned.printInfo(outputFile);

    
    std::cout << "\nSuccessful try block:\n";
    outputFile << "\nSuccessful try block:\n";

    try
    {
        Planet successfulPlanet("GoodPlanet", 1, 12, 132, 4);
        successfulPlanet.printInfo(std::cout);
        successfulPlanet.printInfo(outputFile);
    }
    catch (const PlanetException &e)
    {
        std::cerr << "Planet creation failed: " << e.what() << "\n";
        outputFile << "Planet creation failed: " << e.what() << "\n";
    }

    std::cout << "\nUnsuccessful try block:\n";
    outputFile << "\nUnsuccessful try block:\n";

    try
    {
        Planet errorPlanet("BadPlanet", -14, 12, 132, 4);
        errorPlanet.printInfo(std::cout);
        errorPlanet.printInfo(outputFile);
    }
    catch (const PlanetException &e)
    {
        std::cerr << "Planet creation failed: " << e.what() << "\n";
        outputFile << "Planet creation failed: " << e.what() << "\n";
    }

    std::cout << "\n\nTest results have been saved to PlanetRawPtrTest.txt!";
    

    return 0;
}