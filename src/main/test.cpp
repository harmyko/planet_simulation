#include <iostream>
#include <string>
#include <fstream>

#include "space_object.hpp"

const std::string RESULTS_FILENAME = "../resources/test_results.txt";
const std::string BINARY_FILENAME = "../resources/space_object.dat";
const float GRAVITATIONAL_CONSTANT = 6.67430e-11f;
const float DELTA_TIME = 86400.0f;

int main()
{
    std::ofstream output_file(RESULTS_FILENAME);

    if (!output_file)
    {
        std::cerr << "Failed to open file for writing.\n";
        return 1;
    }

    std::cout << "\n---------------------------------------------\n"
              << "Running tests for the following modules:\n"
              << "- space_object.hpp\n"
              << "- space_object_exception.hpp\n"
              << "- dynamic_movement_strategy.hpp\n"
              << "- static_movement_strategy.hpp"
              << "\n---------------------------------------------\n\n";

    output_file << "---------------------------------------------\n"
                << "Running tests for the following modules:\n"
                << "- space_object.hpp\n"
                << "- space_object_exception.hpp\n"
                << "- dynamic_movement_strategy.hpp\n"
                << "- static_movement_strategy.hpp"
                << "\n---------------------------------------------\n\n";

    std::cout << "\nTest results have been saved to " << RESULTS_FILENAME << " as well!\n";

    std::cout << "\nStatic array of SpaceObjects demonstration:\n\n";
    output_file << "Static array of SpaceObjects demonstration:\n\n";

    SpaceObject space_object_array[2] = {
        SpaceObject("Venus", 4.867e24, 6051.8, {2134, -1.082e11}, {35020, 0}),
        SpaceObject("Neptune", 1.024e26, 24622, {436734, -4.503e12}, {5430, 0})};

    for (const auto &space_object : space_object_array)
    {
        space_object.print_info(std::cout);
        space_object.print_info(output_file);
    }

    std::cout << "Total active SpaceObjects: " << SpaceObject::get_object_count() << "\n";
    output_file << "Total active SpaceObjects: " << SpaceObject::get_object_count() << "\n";

    std::cout << "\nDynamic array of SpaceObjects demonstration:\n\n";
    output_file << "\nDynamic array of SpaceObjects demonstration:\n\n";

    SpaceObject *dynamic_space_object_array = new SpaceObject[2]{
        SpaceObject("Saturn", 5.683e26, 58232, {234856, -1.433e12}, {9680, 0}),
        SpaceObject("Uranus", 8.681e25, 25362, {4, -2.877e12}, {6800, 0})};

    for (int i = 0; i < 2; ++i)
    {
        dynamic_space_object_array[i].print_info(std::cout);
        dynamic_space_object_array[i].print_info(output_file);
    }

    std::cout << "Testing all the getter methods:\n"
              << "SpaceObject ID: " << space_object_array[0].get_id() << "\n"
              << "SpaceObject Name: " << space_object_array[0].get_name() << "\n"
              << "SpaceObject Mass: " << space_object_array[0].get_mass() << "\n"
              << "SpaceObject Radius: " << space_object_array[0].get_radius() << "\n"
              << "SpaceObject Position: (" << space_object_array[0].get_position().x
              << ", " << space_object_array[0].get_position().y << ")\n"
              << "SpaceObject Velocity: (" << space_object_array[0].get_velocity().x
              << ", " << space_object_array[0].get_velocity().y << ")\n";

    output_file << "Testing all the getter methods:\n"
                << "SpaceObject ID: " << space_object_array[0].get_id() << "\n"
                << "SpaceObject Name: " << space_object_array[0].get_name() << "\n"
                << "SpaceObject Mass: " << space_object_array[0].get_mass() << "\n"
                << "SpaceObject Radius: " << space_object_array[0].get_radius() << "\n"
                << "SpaceObject Position: (" << space_object_array[0].get_position().x
                << ", " << space_object_array[0].get_position().y << ")\n"
                << "SpaceObject Velocity: (" << space_object_array[0].get_velocity().x
                << ", " << space_object_array[0].get_velocity().y << ")\n";

    SpaceObject copy_of_venus = space_object_array[0];

    std::cout << "\nCopied SpaceObject:\n";
    output_file << "\nCopied SpaceObject:\n";
    copy_of_venus.print_info(std::cout);
    copy_of_venus.print_info(output_file);

    std::vector<const SpaceObject *> other_objects;
    other_objects.push_back((&space_object_array[1]));
    other_objects.push_back((&dynamic_space_object_array[0]));
    other_objects.push_back((&dynamic_space_object_array[1]));

    std::cout << "Applying DynamicMovementStrategy to the original version of " << space_object_array[0].get_name() << ":\n";
    output_file << "Applying DynamicMovementStrategy to the original version of " << space_object_array[0].get_name() << ":\n";
    space_object_array[0].update_velocity(other_objects, GRAVITATIONAL_CONSTANT, DELTA_TIME);

    space_object_array[0].print_info(std::cout);
    space_object_array[0].print_info(output_file);

    std::cout << "\nApplying StaticMovementStrategy to the copied version of " << space_object_array[0].get_name() << ":\n";
    output_file << "\nApplying StaticMovementStrategy to the copied version of " << space_object_array[0].get_name() << ":\n";
    copy_of_venus.set_movability(false);
    copy_of_venus.update_velocity(other_objects, GRAVITATIONAL_CONSTANT, DELTA_TIME);

    copy_of_venus.print_info(std::cout);
    copy_of_venus.print_info(output_file);

    std::cout << "Total active SpaceObjects: " << SpaceObject::get_object_count() << "\n";
    output_file << "Total active SpaceObjects: " << SpaceObject::get_object_count() << "\n";

    delete[] dynamic_space_object_array;
    std::cout << "Dynamic SpaceObjects have been deleted.\n";
    output_file << "Dynamic SpaceObjects have been deleted.\n";

    std::cout << "Total active SpaceObjects after deletion: " << SpaceObject::get_object_count() << "\n\n";
    output_file << "Total active SpaceObjects after deletion: " << SpaceObject::get_object_count() << "\n\n";

    std::cout << "Saving " << space_object_array[0].get_name() << " data in binary file named: " << BINARY_FILENAME << "\n";
    output_file << "Saving " << space_object_array[0].get_name() << " data in binary file named: " << BINARY_FILENAME << "\n";
    std::ofstream out(BINARY_FILENAME, std::ios::binary);
    out << space_object_array[0];
    out.close();

    std::cout << "Writing data from " << BINARY_FILENAME << " to " << space_object_array[1].get_name() << "...\n";
    output_file << "Writing data from " << BINARY_FILENAME << " to " << space_object_array[1].get_name() << "...\n";

    std::ifstream in(BINARY_FILENAME, std::ios::binary);
    in >> space_object_array[1];
    in.close();

    space_object_array[1].print_info(std::cout);
    space_object_array[1].print_info(output_file);

    std::cout << "Successful try block:\n";
    output_file << "Successful try block:\n";

    try
    {
        SpaceObject successful_space_object("Good SpaceObject", 1, 12, {123, 123}); // Assigning valid parameters
        successful_space_object.print_info(std::cout);
        successful_space_object.print_info(output_file);
    }
    catch (const SpaceObjectException &e)
    {
        std::cerr << "SpaceObject creation failed: " << e.what() << "\n";
        output_file << "SpaceObject creation failed: " << e.what() << "\n";
    }

    std::cout << "Unsuccessful try block:\n";
    output_file << "Unsuccessful try block:\n";

    try
    {
        SpaceObject error_space_object("Bad SpaceObject", -14, 12, {123, 123}); // Attempting to assign a negative mass
        error_space_object.print_info(std::cout);
        error_space_object.print_info(output_file);
    }
    catch (const SpaceObjectException &e)
    {
        std::cerr << "SpaceObject creation failed: " << e.what() << "\n";
        output_file << "SpaceObject creation failed: " << e.what() << "\n";
    }

    output_file.close();

    return 0;
}