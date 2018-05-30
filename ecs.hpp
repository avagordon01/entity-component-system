#include <bitset>
#include <vector>
#include <array>
#include <tuple>

template <typename... Components> class ecs {
    //FIXME
    //static_assert(std::is_pod<Components...>(), "all component types must be POD");

    static constexpr size_t NumComponents = sizeof...(Components);
 
    std::vector<std::bitset<NumComponents>> entity_signatures;

    std::vector<std::bitset<NumComponents>> system_signatures;

    std::tuple<std::vector<Components>...> components;

    //TODO functions for adding entities, components and systems

    void tick() {
        for (size_t s = 0; s < system_signatures.size(); s++) {
            std::array<size_t, NumComponents> component_indices{};
            for (size_t e = 0; e < entity_signatures.size(); e++) {
                if ((entity_signatures[e] & system_signatures[s]) == system_signatures[s]) {
                    //TODO call system
                    std::get<Components...>(components);
                }
                for (size_t c = 0; c < component_indices.size(); c++) {
                    component_indices[c] += entity_signatures[e][c];
                }
            }
        }
    }
};
