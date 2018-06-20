# Entity Component System

This repo provides a single header, performance-first entity component system written using C++17 template metaprogramming.

## Storage

Components are stored densely in entity-order in std::vectors. This provides great cache and prefetch performance.

We favour a dense memory representation instead of random access to entities/components.

To iterate over the entities, we have to keep track of the current index for each component. If an entity contains a component `X` then at the end of the loop iteration, we increment the index for component `X`, otherwise we don't. This is how we iterate over the dense memory representation of components.

## API

adding/removing from not-the-end of a std::vector is not great, performance-wise. To support fine grained adding and removing of functionality, we have functions to enable/disable in a lightweight way (flipping a bit in a bitset). But we also allow adding/removing and doing the "defragmentation" at the end of the tick, so you don't get a "garbage collection" pause in your tight loop.
