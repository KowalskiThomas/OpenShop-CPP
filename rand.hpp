#include <random>

class Random {
    public:
        static auto random_from_range(int min, int max)
        {
            static auto rd = std::random_device();
            static auto rng = std::mt19937(rd());
            static auto uni = std::uniform_int_distribution<int>(min, max);

            auto random_integer = uni(rng);
            return random_integer;
        }

        static auto random()
        {
            static std::random_device rd;
            static std::mt19937 rng(rd());

            auto uni = std::uniform_real_distribution<double>(0,1);

            return uni(rng);
        }
};