/**
 * @brief Orbital simulation
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H
#include <raylib.h>
/**
 * @brief Orbital body definition
 */
struct OrbitalBody
{
    // Fill in your code here...
    float mass;		  // [kg]
    float radius;	  // [m]
    Color color;	  // Raylib color
    Vector3 position; // [m]
    Vector3 velocity; // [m/s]
    Vector3 aceleration; // [m/s^2]

};

/**
 * @brief Orbital simulation definition
 */
struct OrbitalSim
{
    // Fill in your code here...
    float timeStep;
    float elapsedTime;
    unsigned int numBodies;
    OrbitalBody bodies[50];     //Place a define so that the length of the array is well determined

};

OrbitalSim *constructOrbitalSim(float timeStep);
void destroyOrbitalSim(OrbitalSim *sim);

void updateOrbitalSim(OrbitalSim *sim);

#endif
