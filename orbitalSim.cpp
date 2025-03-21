/**
 * @brief Orbital simulation
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

// Enables M_PI #define in Windows
#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>

#include "OrbitalSim.h"
#include "ephemerides.h"

#define GRAVITATIONAL_CONSTANT 6.6743E-11F
#define ASTEROIDS_MEAN_RADIUS 4E11F
#define ASTEROIDS_BODYNUM 89
#define ALPHASYSTEM

Vector3 calcGravitationalForce(OrbitalSim** ppsim, unsigned int i, unsigned int j);
/**
 * @brief Gets a uniform random value in a range
 *
 * @param min Minimum value
 * @param max Maximum value
 * @return The random value
 */
float getRandomFloat(float min, float max)
{
    return min + (max - min) * rand() / (float)RAND_MAX;
}

/**
 * @brief Configures an asteroid
 *
 * @param body An orbital body
 * @param centerMass The mass of the most massive object in the star system
 */
void configureAsteroid(OrbitalBody *body, float centerMass)
{
    // Logit distribution
    float x = getRandomFloat(0, 1);
    float l = logf(x) - logf(1 - x) + 1;

    // https://mathworld.wolfram.com/DiskPointPicking.html
    float r = ASTEROIDS_MEAN_RADIUS * sqrtf(fabsf(l));
    float phi = getRandomFloat(0, 2.0F * (float)M_PI);

    // Surprise!
    // phi = 0;

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    body->mass = 1E12F;  // Typical asteroid weight: 1 billion tons
    body->radius = 2E3F; // Typical asteroid radius: 2km
    body->color = GRAY;
    body->position = {r * cosf(phi), 0, r * sinf(phi)};
    body->velocity = {-v * sinf(phi), vy, v * cosf(phi)};
}

/**
 * @brief Constructs an orbital simulation
 *
 * @param float The time step
 * @return The orbital simulation
 */
OrbitalSim *constructOrbitalSim(float timeStep)
{
    // Your code goes here...

    /*Adds the Solar System and Alpha Centaury System data to the array as well as the proper timestep, elapsedtime and number of bodies initial values */
    OrbitalSim *newSim = new OrbitalSim;

    newSim->timeStep = timeStep;            //Simulacion mas lenta solo para ver mejor 
    newSim->elapsedTime = 0;
    newSim->numBodies = SOLARSYSTEM_BODYNUM + ASTEROIDS_BODYNUM; //ALPHACENTAURISYSTEM_BODYNUM +


    //inicialized planets
    for (unsigned int i = 0; i < SOLARSYSTEM_BODYNUM; i++) {
        newSim->bodies[i] = {
            solarSystem[i].mass,
            solarSystem[i].radius,
            solarSystem[i].color,
            solarSystem[i].position,
            solarSystem[i].velocity,
            {0,0,0}
        };
    }
    //iniciliazes asteroids after planets 
        for (unsigned int i = 0; i < ASTEROIDS_BODYNUM; i++) {
            configureAsteroid(&newSim->bodies[SOLARSYSTEM_BODYNUM + ALPHACENTAURISYSTEM_BODYNUM + i], solarSystem[0].mass);
        }
    /*
    //inicializes constelations after planets and asteroids
    for (unsigned int i = 0; i < ALPHACENTAURISYSTEM_BODYNUM; i++) {
        newSim->bodies[SOLARSYSTEM_BODYNUM + i] = {
            alphaCentauriSystem[i].mass,
            alphaCentauriSystem[i].radius,
            alphaCentauriSystem[i].color,
            alphaCentauriSystem[i].position,
            alphaCentauriSystem[i].velocity,
            {0,0,0}
        };
    }*/
    
    
    return newSim; // This should return your orbital sim
}

/**
 * @brief Destroys an orbital simulation
 */
void destroyOrbitalSim(OrbitalSim *sim)
{
    // Your code goes here...
    delete sim;

}

/**
 * @brief Simulates a timestep
 *
 * @param sim The orbital simulation
 */
void updateOrbitalSim(OrbitalSim *sim)
{
    // Your code goes here...
    /*Considering the reduced mass that asteroids have, we will focus solely on the calculation of gravitational force between every body,
    except for the one between asteroids. By doing this, we will greatly reduce the computing power required for the movement in our simulation*/
    Vector3 gravityForce = { 0,0,0 };

    for (unsigned int i = 0; i < sim->numBodies; ++i)
    {
        sim->bodies[i].aceleration = { 0,0,0 };
    }
    for (int i = 1; i < sim->numBodies; ++i)
    {
        for (int j = 0; j < SOLARSYSTEM_BODYNUM; j++)
        {
            if (i < SOLARSYSTEM_BODYNUM) 
            {
                gravityForce = calcGravitationalForce(&sim, i, j);
            }
            
            /*
            else if (i == ALPHACENTAURISYSTEM_BODYNUM + SOLARSYSTEM_BODYNUM - 1)
            {
#ifdef ALPHASYSTEM
                gravityForce = calcGravitationalForce(&sim, i, ALPHACENTAURISYSTEM_BODYNUM + SOLARSYSTEM_BODYNUM - 2);
#endif
            }
            else if (i == ALPHACENTAURISYSTEM_BODYNUM + SOLARSYSTEM_BODYNUM - 2)
            {
#ifdef ALPHASYSTEM
                gravityForce = calcGravitationalForce(&sim, i, ALPHACENTAURISYSTEM_BODYNUM + SOLARSYSTEM_BODYNUM - 1);
#endif
            }
            */
            else
            {
                gravityForce = calcGravitationalForce(&sim, i, j);
            }

            if(j != i)
                sim->bodies[i].aceleration = Vector3Add(Vector3Scale(gravityForce, 1 / sim->bodies[i].mass), sim->bodies[i].aceleration);

        }
        sim->bodies[i].velocity = Vector3Add(Vector3Scale(sim->bodies[i].aceleration, sim->timeStep), sim->bodies[i].velocity);
    }
    for (unsigned int i = 0; i < sim->numBodies; ++i)
    {
        sim->bodies[i].position += Vector3Scale(sim->bodies[i].velocity, sim->timeStep);
    }
    sim->elapsedTime += sim->timeStep; 
}

//Function that calculates the gravitational force between the body i and the body j


/**
 * @brief Gets a uniform random value in a range
 *
 * @param ppSim orbital simulation 
 * @param i first celestial body 
 * @param j second celestial body
 *
 * @return gravitational force between two bodies
 */
Vector3 calcGravitationalForce(OrbitalSim** ppSim, unsigned int i, unsigned int j) {

    float auxScalar;
    Vector3 auxVector;
    auxVector = Vector3Subtract((*ppSim)->bodies[i].position, (*ppSim)->bodies[j].position);                                         // The gravitational force is calculated by steps.
    auxScalar = Vector3Length(auxVector);
    auxScalar = -6.6743E-11 * (*ppSim)->bodies[i].mass * (*ppSim)->bodies[j].mass / (auxScalar * auxScalar);

    return Vector3Scale(Vector3Normalize(auxVector), auxScalar);
}