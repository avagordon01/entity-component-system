#include <bitset>
#include <vector>
#include <array>
#include <tuple>

#include "mpl.hpp"

namespace ecs {
template <typename... Components> struct components_manager {
    static_assert(sizeof...(Components) > 0, "system components must be non-empty");
    static_assert((std::is_pod<Components>() && ...), "ECS component types must be POD");
    static_assert(mpl::is_unique<Components...>, "ECS component types must be unique");

    //TODO
    //interface functions for
    //adding/removing/enabling/disabling entities and components
    //and
    //enabling/disabling systems

    std::tuple<Components...> component_types;

    std::tuple<std::vector<Components>...> components_storage;

    std::vector<std::bitset<sizeof...(Components)>> entity_signatures;

    std::vector<std::bitset<sizeof...(Components)>> system_signatures;

    template <typename... SystemComponents>
    std::tuple<SystemComponents&...> iterate() {
        static_assert(sizeof...(SystemComponents) > 0, "system components must be non-empty");
        static_assert(mpl::is_subset_of<std::tuple<SystemComponents...>, std::tuple<Components...>>, "iterator access components must be a subset of ECS components");
        static_assert(mpl::is_unique<SystemComponents...>, "system component types must be unique");
        std::bitset<sizeof...(Components)> system_signature;
        typedef std::tuple<Components...> system_signature_tuple;
        std::array<size_t, sizeof...(Components)> component_indices{0};
        for (size_t e = 0; e < entity_signatures.size(); e++) {
            if ((entity_signatures[e] & system_signature) == system_signature) {
                //TODO turn this return into something like yield
                return std::tuple<SystemComponents&...>{
                    std::get<SystemComponents>(components_storage)[
                        component_indices[mpl::index<SystemComponents, system_signature_tuple>]
                    ]...
                };
            }
            for (size_t c = 0; c < component_indices.size(); c++) {
                component_indices[c] += entity_signatures[e][c];
            }
        }
    }
};
}
