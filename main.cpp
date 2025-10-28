#include "Physics/Particles.hpp"
#include "Physics/Functions.hpp"

#include <vector>
#include <iostream>

int main() {
    std::vector<Fundamental> particles = std::vector<Fundamental>();
    Fundamental electron = Electron();
    electron.position = glm::dvec3(1e-13, 0, 0);
    Fundamental proton = Proton();
    proton.position = glm::vec3(-1e-13, 0, 0);
    particles.push_back(electron);
    particles.push_back(proton);

    for (size_t i = 0; i < particles.size(); i++) {
        std::cout << particles[i].toString();
    }
    std::cout << "\n";

    std::vector<glm::dvec3> accelerations = calculateClassicalForces(particles);

    for (size_t i = 0; i < particles.size(); i++) {
        particles[i].acceleration = accelerations[i];
    }

    for (size_t i = 0; i < particles.size(); i++) {
        std::cout << particles[i].toString();
    }
    std::cout << "\n";

    return 0;
}