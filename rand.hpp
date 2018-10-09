#include <random>

class Random {
    public:
        static auto random_from_range(int min, int max)
        {
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> uni(min, max);

            auto random_integer = uni(rng);
            return random_integer;
        }

        static auto random_from_range_2(int low, int high)
        {
            static std::default_random_engine re {};
            using Dist = std::uniform_int_distribution<int>;
            static Dist uid {};
            return uid(re, Dist::param_type{low,high});
        }
};