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

#define GRAVITATIONAL_CONSTANT 6.6743E-11
#define ASTEROIDS_MEAN_RADIUS 4E11F
#define ASTEROIDS_BODYNUM 1000

#define ALPHASYSTEM

Vector3 calcGravitationalForce(OrbitalSim* sim, unsigned int i, unsigned int j);

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

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf((float)GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

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
    /*Adds the Solar System and Alpha Centaury System data to the array as well as the proper timestep, elapsedtime and number of bodies initial values */
    OrbitalSim *newSim = new OrbitalSim;

    newSim->timeStep = timeStep; 
    newSim->elapsedTime = 0;
    newSim->numBodies = SOLARSYSTEM_BODYNUM + ASTEROIDS_BODYNUM; 
    newSim->solarSystemBodies = SOLARSYSTEM_BODYNUM;

#ifdef ALPHASYSTEM
    newSim->numBodies = ALPHACENTAURISYSTEM_BODYNUM;
    //inicializes constelations (if defined)
    for (unsigned int i = 0; i < ALPHACENTAURISYSTEM_BODYNUM; i++) {
        newSim->bodies[i] = {
            alphaCentauriSystem[i].mass,
            alphaCentauriSystem[i].radius,
            alphaCentauriSystem[i].color,
            alphaCentauriSystem[i].position,
            alphaCentauriSystem[i].velocity,
            {0,0,0}
        };
    }
#else
    //inicialized planets (after constelations if defined)
    for (unsigned int i = 0; i < SOLARSYSTEM_BODYNUM; i++)
    {
        newSim->bodies[i] = {
            solarSystem[i].mass,
            solarSystem[i].radius,
            solarSystem[i].color,
            solarSystem[i].position,
            solarSystem[i].velocity,
            {0,0,0}
        };
    }

    //iniciliazes asteroids after planets (and constelations if defined) 
        for (unsigned int i = 0; i < ASTEROIDS_BODYNUM; i++)
        {
            configureAsteroid(&newSim->bodies[SOLARSYSTEM_BODYNUM + ALPHACENTAURISYSTEM_BODYNUM + i], solarSystem[0].mass);
        }

#endif
    return newSim; // This should return your orbital sim
}

/**
 * @brief Destroys an orbital simulation
 */
void destroyOrbitalSim(OrbitalSim *sim)
{
    delete sim;

}

/**
 * @brief Simulates a timestep
 *
 * @param sim The orbital simulation
 */
void updateOrbitalSim(OrbitalSim* sim)
{
    /*Considering the reduced mass that asteroids have, we will focus solely on the calculation of gravitational force between every body,
    except for the one between asteroids. By doing this, we will greatly reduce the computing power required for the movement in our simulation*/
    Vector3 gravityForce = { 0,0,0 };

    // The sun keeps moving with a constant speed so we can totally apreciate the Solar System funtioning,
    // we avoid calculating its aceleration
    for (unsigned int i = 0; i < sim->numBodies; ++i)
    {
        sim->bodies[i].aceleration = { 0,0,0 };
    }
#ifndef ALPHASYSTEM
    for (unsigned int i = 1; i < sim->numBodies; ++i)
    {
        for (int j = 0; j < SOLARSYSTEM_BODYNUM; j++)
        {
            if (j != i)
            {
                gravityForce = calcGravitationalForce(sim, i, j);
                sim->bodies[i].aceleration = Vector3Add(Vector3Scale(gravityForce, 1 / sim->bodies[i].mass), sim->bodies[i].aceleration);
            }
        }
        sim->bodies[i].velocity = Vector3Add(Vector3Scale(sim->bodies[i].aceleration, sim->timeStep), sim->bodies[i].velocity);
    }
#else
    gravityForce = calcGravitationalForce(sim, ALPHACENTAURISYSTEM_BODYNUM - 1, ALPHACENTAURISYSTEM_BODYNUM - 2);
    sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 1].aceleration = Vector3Add(Vector3Scale(gravityForce, 1 / sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 1].mass), sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 1].aceleration);
    sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 1].velocity = Vector3Add(Vector3Scale(sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 1].aceleration, sim->timeStep), sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 1].velocity);

    gravityForce = calcGravitationalForce(sim, ALPHACENTAURISYSTEM_BODYNUM - 2, ALPHACENTAURISYSTEM_BODYNUM - 1);
    sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 2].aceleration = Vector3Add(Vector3Scale(gravityForce, 1 / sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 2].mass), sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 2].aceleration);
    sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 2].velocity = Vector3Add(Vector3Scale(sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 2].aceleration, sim->timeStep), sim->bodies[ALPHACENTAURISYSTEM_BODYNUM - 2].velocity);
#endif
            
    for(unsigned int i = 0; i < sim->numBodies; ++i)
    {
        sim->bodies[i].position += Vector3Scale(sim->bodies[i].velocity, sim->timeStep);
    }
    sim->elapsedTime += sim->timeStep; 
}


/**
 * @brief Calculates the gravitational force between the body i and the body j
 *
 * @param sim orbital simulation 
 * @param i first celestial body 
 * @param j second celestial body
 *
 * @return gravitational force between two bodies
 */
Vector3 calcGravitationalForce(OrbitalSim* sim, unsigned int i, unsigned int j)
{
    if (j != i)
    {
        double auxScalar;
        Vector3 auxVector;
        auxVector = Vector3Subtract(sim->bodies[i].position, sim->bodies[j].position);    // The gravitational force is calculated by steps.
        auxScalar = Vector3Length(auxVector);
        auxScalar = -GRAVITATIONAL_CONSTANT * sim->bodies[i].mass * sim->bodies[j].mass / (auxScalar * auxScalar);

        return Vector3Scale(Vector3Normalize(auxVector), (float)auxScalar);
    }
    else
        return { 0,0,0 };
}