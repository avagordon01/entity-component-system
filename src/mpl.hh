#include <tuple>
#include <type_traits>
#include <bitset>
#include <cassert>
#include <iostream>

namespace mpl {
    template <typename T, typename... Ts>
    constexpr bool contains = (std::is_same<T, Ts>{} || ...);


    template <typename Subset, typename Set>
    constexpr bool is_subset_of = false;

    template <typename... Ts, typename... Us>
    constexpr bool is_subset_of<std::tuple<Ts...>, std::tuple<Us...>> = (contains<Ts, Us...> && ...);
    

    template <typename Ts, typename... Us>
    constexpr bool is_unique = (!contains<Ts, Us> && ...);


    template <typename T, typename Tuple>
    constexpr size_t index = -1;

    template <typename T, typename... Types>
    constexpr size_t index<T, std::tuple<T, Types...>> = 0;

    template <typename T, typename U, typename... Types>
    constexpr size_t index<T, std::tuple<U, Types...>> = 1 + index<T, std::tuple<Types...>>;


    template <typename T, typename U>
    constexpr std::bitset<1> ordered_subset_to_bitset = {std::is_same<T, U>{}};

    template <size_t N, size_t... Is>
    constexpr std::bitset<N> bitset_indices_ones() {
        return std::bitset<N>{((1 << Is) | ...)};
    }

    template <typename... Ts, typename... Us>
    constexpr std::bitset<sizeof...(Us)> ordered_subset_to_bitset<std::tuple<Ts...>, std::tuple<Us...>> =
    bitset_indices_ones<sizeof...(Us), index<Ts, std::tuple<Us...>>...>();
    //{((std::bitset<sizeof...(Us)>{}[index<Ts, std::tuple<Us...>>] = 1) | ...)};

    void test() {
        assert((
            ordered_subset_to_bitset<
                std::tuple<uint8_t, uint16_t>,
                std::tuple<uint8_t, size_t, size_t, uint16_t, uint32_t>
            >
            ==
            std::bitset<5>{(1 << 3) | (1 << 0)}
        ));
        assert((
            ordered_subset_to_bitset<std::tuple<uint8_t, uint16_t>, std::tuple<uint8_t, uint32_t, uint16_t>>
            ==
            std::bitset<3>{(1 << 2) | (1 << 0)}
        ));


        static_assert(contains<size_t, size_t>, "hmm");
        static_assert(!contains<size_t, uint8_t>, "hmm");
        static_assert(contains<size_t, size_t, size_t, size_t>, "hmm");
        static_assert(!contains<size_t, uint8_t, uint16_t, uint32_t>, "hmm");

        static_assert(is_subset_of<std::tuple<size_t, size_t>, std::tuple<size_t>>, "hmm");
        static_assert(is_subset_of<std::tuple<size_t>, std::tuple<size_t, size_t>>, "hmm");
        static_assert(is_subset_of<std::tuple<size_t, uint8_t>, std::tuple<size_t, uint8_t>>, "hmm");
        static_assert(is_subset_of<std::tuple<size_t>, std::tuple<size_t, uint8_t>>, "hmm");
        static_assert(!is_subset_of<std::tuple<uint8_t>, std::tuple<size_t>>, "hmm");
        static_assert(!is_subset_of<std::tuple<size_t, uint8_t>, std::tuple<size_t>>, "hmm");

        static_assert(is_unique<size_t>, "hmm");
        static_assert(is_unique<size_t, uint32_t, uint16_t, uint8_t>, "hmm");
        static_assert(!is_unique<size_t, size_t, size_t>, "hmm");
        static_assert(!is_unique<size_t, uint32_t, uint16_t, uint8_t, size_t>, "hmm");
        static_assert(!is_unique<size_t, uint32_t, size_t, uint16_t, uint8_t>, "hmm");

        static_assert(index<size_t, std::tuple<size_t, uint8_t, uint16_t, uint32_t>> == 0, "hmm");
        static_assert(index<uint8_t, std::tuple<size_t, uint8_t, uint16_t, uint32_t>> == 1, "hmm");
        static_assert(index<uint16_t, std::tuple<size_t, uint8_t, uint16_t, uint32_t>> == 2, "hmm");
        static_assert(index<uint32_t, std::tuple<size_t, uint8_t, uint16_t, uint32_t>> == 3, "hmm");
        static_assert(index<size_t, std::tuple<size_t, size_t>> == 0, "hmm");
        static_assert(index<size_t, std::tuple<>> == -1, "hmm");
    }
}
