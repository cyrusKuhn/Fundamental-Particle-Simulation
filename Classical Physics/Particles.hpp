#pragma once

#include <glm/glm.hpp>

#include <cmath>
#include <string>
#include <sstream>

static double ELECTRON_MASS = 9.1093 * std::pow(10.0, -31);
static double ELECTRON_CHARGE = -1.6021 * std::pow(10, -19);
static double ELECTRON_SPIN = 0.5;

static double PROTON_MASS = 1.6726 * std::pow(10, -27);
static double PROTON_CHARGE = 1.602 * std::pow(10, -19);
static double PROTON_SPIN = 0.5;

static double NEUTRON_MASS = 1.6749 * std::pow(10, -27);
static double NEUTRON_CHARGE = 0;
static double NEUTRON_SPIN = 0.5;

class Fundamental {
public:
    double mass;
    double charge;
    double spin;

    glm::dvec3 position;
    glm::dvec3 velocity;
    glm::dvec3 acceleration;

    Fundamental() {
        this->position = glm::dvec3();
        this->velocity = glm::dvec3();
        this->acceleration = glm::dvec3();
    }

    std::string toString() {
        std::stringstream ss;
        ss << "Position (m): " << position.x << ", " << position.y << ", " << position.z << "\n";
        ss << "Velocity (m/s): " << velocity.x << ", " << velocity.y << ", " << velocity.z << "\n";
        ss << "Acceleration (m/s^2): " << acceleration.x << ", " << acceleration.y << ", " << acceleration.z << "\n";
        return ss.str();
    }
};

class Electron : public Fundamental {
public:
    Electron() {
        this->mass = ELECTRON_MASS;
        this->charge = ELECTRON_CHARGE;
        this->spin = ELECTRON_SPIN;
    }
};

class Proton : public Fundamental {
public:
    Proton() {
        this->mass = PROTON_MASS;
        this->charge = PROTON_CHARGE;
        this->spin = PROTON_SPIN;
    }
};

class Neutron : public Fundamental {
public:
    Neutron() {
        this->mass = NEUTRON_MASS;
        this->charge = NEUTRON_CHARGE;
        this->spin = NEUTRON_SPIN;
    }
};