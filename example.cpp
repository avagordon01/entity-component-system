#include <stdio.h>
#include <tuple>
#include <bitset>

#include "ecs.hpp"

struct vector {
    float x, y, z;
};
struct position {
    vector pos;
};
struct velocity {
    vector vel;
};
struct force_accumulator {
    vector vel;
};
struct impulse_accumulator {
    vector vel;
};

struct integrator {
    void operator()() {
        printf("integrator system\n");
    }
};
struct physics {
    void operator()() {
        printf("physics system\n");
    }
};

int main() {
    mpl::test();

    /*
    ecs::components_manager<
        position, velocity, force_accumulator, impulse_accumulator
    > s;
    s.iterate<position>();
    */
}
