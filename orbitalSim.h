/**
 * @brief Orbital simulation
 * @author Marc S. Ressl, Ana Destefano, Juan I. Caorsi
 * EDA TP1 
 * @copyright Copyright (c) 2022-2023
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H
#define MAX_BODIES 10000
#include <raylib.h>
/**
 * @brief Orbital body with its essential properties is defined
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
    OrbitalBody bodies[MAX_BODIES];    
    unsigned int solarSystemBodies;

};

OrbitalSim *constructOrbitalSim(float timeStep);
void destroyOrbitalSim(OrbitalSim *sim);

void updateOrbitalSim(OrbitalSim *sim);

#endif
