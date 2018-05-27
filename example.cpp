#include <stdio.h>

#include "ecs.hpp"

struct vector {
    float x, y, z;
};
typedef vector position;
typedef vector velocity;

int main() {
    ecs<position, velocity> ecs;
    printf("test\n");
}
