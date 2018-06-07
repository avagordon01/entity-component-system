#include <stdio.h>
#include <tuple>

#include "ecs.hpp"

struct vector {
    float x, y, z;
};
typedef vector position;
typedef vector velocity;

struct integrator {
    void operator()() {
        printf("WORKING\n");
    }
};

int main() {
    ecs::components_manager<position, velocity>::systems_manager<integrator> s;
    s.tick();
}
