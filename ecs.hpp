#include <bitset>
#include <vector>
#include <array>
#include <tuple>

namespace ecs {
template <typename... Components> struct components_manager {
    static_assert((std::is_pod<Components>() && ...), "all component types must be POD");

    //TODO functions for adding/removing/enabling/disabling entities and components

    template <typename... Systems> struct systems_manager {
        static_assert((std::is_invocable<Systems>() && ...), "all system types must be invocable");

        std::tuple<std::vector<Components>...> components_storage;

        std::vector<std::bitset<sizeof...(Components)>> entity_signatures;

        std::vector<std::bitset<sizeof...(Components)>> system_signatures;

        void tick() {
            (Systems()(), ...);
            for (size_t s = 0; s < system_signatures.size(); s++) {
                std::array<size_t, sizeof...(Components)> component_indices{};
                for (size_t e = 0; e < entity_signatures.size(); e++) {
                    if ((entity_signatures[e] & system_signatures[s]) == system_signatures[s]) {
                        for (size_t c = 0; c < sizeof...(Components); c++) {
                            if (system_signatures[s].test(c)) {
                                std::get<0>(components_storage)[component_indices[c]];
                            }
                        }
                        //TODO call system
                        //std::get<Components...>(components_storage);
                    }
                    for (size_t c = 0; c < component_indices.size(); c++) {
                        component_indices[c] += entity_signatures[e][c];
                    }
                }
            }
        }
    };
};
}
