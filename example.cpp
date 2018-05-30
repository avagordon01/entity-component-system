#include <stdio.h>
#include <tuple>

#include "ecs.hpp"

struct vector {
    float x, y, z;
};
typedef vector position;
typedef vector velocity;

class integrator {
    void operator()(position p, velocity v) {
        p.x += v.x;
    }
};

int main() {
    ecs<position, velocity> ecs;
    printf("test\n");
}
