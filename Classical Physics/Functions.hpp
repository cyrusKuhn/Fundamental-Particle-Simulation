#pragma once

#include <vector>

#include "Particles.hpp"

static constexpr double PI = 3.141592653589793;

static constexpr double GRAVITATIONAL_CONSTANT = 6.6743e-11;

static constexpr double STRONG_FORCE_ATTRACTIVE_POTENTIAL = 1.602e-10;
static constexpr double STRONG_FORCE_REPULSIVE_POTENTIAL = 5e-12;
static constexpr double STRONG_FORCE_ATTRACTIVE_RANGE = 8e-16;
static constexpr double STRONG_FORCE_REPULSIVE_RANGE = 1.407e-15;

static constexpr double COULOMB_CONSTANT = 8.987e9;

static constexpr double FREE_SPACE_PERMEABILITY = 4e-7 * PI;

double calculateGravity(Fundamental primary, Fundamental secondary, double distance) {
    double forceMagnitude = GRAVITATIONAL_CONSTANT * primary.mass * secondary.mass / (distance * distance);
    return forceMagnitude;
}

// Using Yukawa Potential with added repulsive term
double calculateStrongForce(Fundamental primary, Fundamental secondary, double distance) {
    double repulsiveStrength = STRONG_FORCE_REPULSIVE_POTENTIAL / (STRONG_FORCE_REPULSIVE_RANGE * STRONG_FORCE_REPULSIVE_RANGE) * std::exp(- (distance / STRONG_FORCE_REPULSIVE_RANGE) * (distance / STRONG_FORCE_REPULSIVE_RANGE));
    double attractiveStrength = STRONG_FORCE_ATTRACTIVE_POTENTIAL / (STRONG_FORCE_ATTRACTIVE_RANGE * STRONG_FORCE_ATTRACTIVE_RANGE) * std::exp(- (distance / STRONG_FORCE_ATTRACTIVE_RANGE) * (distance / STRONG_FORCE_ATTRACTIVE_RANGE));
    double forceMagnitude = 2.0 * distance * (attractiveStrength - repulsiveStrength);
    return forceMagnitude;
}

double calculateCoulombsMagnitude(Fundamental primary, Fundamental secondary, double distance) {
    double forceMagnitude = COULOMB_CONSTANT * primary.charge * secondary.charge / (distance * distance);
    return forceMagnitude;
}

glm::dvec3 calculateLorentzVector(Fundamental primary, Fundamental secondary) {
    glm::dvec3 relativePosition = primary.position - secondary.position;
    double distance = glm::length(relativePosition);
    glm::dvec3 magneticField = FREE_SPACE_PERMEABILITY / (4.0 * PI) * secondary.charge * glm::cross(secondary.velocity, relativePosition) / (distance * distance * distance);
    glm::dvec3 appliedForce = primary.charge * glm::cross(primary.velocity, magneticField);
    return appliedForce;
}


std::vector<glm::dvec3> calculateClassicalForces(std::vector<Fundamental> particles) {
    std::vector<glm::dvec3> accelerations = std::vector<glm::dvec3>();
    for (Fundamental particle : particles) {
        accelerations.push_back(glm::dvec3());
    }
    for (size_t i = 0; i < particles.size(); i++) {
        for (size_t j = 0; j < particles.size(); j++) {
            if (i == j) {
                continue;
            }
            Fundamental primary = particles[i];
            Fundamental secondary = particles[j];
            glm::dvec3 relativePosition = primary.position - secondary.position;
            double relativeDistance = glm::length(relativePosition);
            glm::dvec3 relativeUnit = relativePosition / relativeDistance;

            double gravityMagnitude = calculateGravity(primary, secondary, relativeDistance);
            double strongForceMagnitude = calculateStrongForce(primary, secondary, relativeDistance);
            double coulombsMagnitude = calculateCoulombsMagnitude(primary, secondary, relativeDistance);

            glm::dvec3 lorentzVector = calculateLorentzVector(primary, secondary);

            glm::dvec3 netForce = (gravityMagnitude + strongForceMagnitude + coulombsMagnitude) * relativeUnit + lorentzVector;

            accelerations[i] += netForce / particles[i].mass;
        }
    }
    return accelerations;
}