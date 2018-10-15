#ifndef RANDOM
#define RANDOM

#include <random>

class Random {
private:

public:
    static bool started_;

        static auto random_from_range(int min, int max)
        {
            if (!started_) {
                std::srand(std::time(nullptr));
                started_ = true;
            }

            static auto rd = std::random_device();
            static auto rng = std::mt19937(rd());
            static auto uni = std::uniform_int_distribution<int>(min, max);

            return uni(rng);
        }

        static auto random()
        {
            if (!started_) {
                std::srand(std::time(nullptr));
                started_ = true;
            }

            static std::random_device rd;
            static std::mt19937 rng(rd());

            auto uni = std::uniform_real_distribution<double>(0,1);

            return uni(rng);
        }
};

bool Random::started_ = false;

#endif