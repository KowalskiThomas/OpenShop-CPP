#ifndef RANDOM
#define RANDOM

#include <random>

class Random {
public:
        // static int random_from_range(int min, int max)
        // {
        //     static std::random_device rd;
        //     static auto rng = std::mt19937(rd());
        //     static auto uni = std::uniform_int_distribution<int>(min, max);

        //     return uni(rng);
        // }

        static int random_from_range(int min, int max)
        {
            static bool started = false;
	    if (!started)
	    {
	    	srand(time(nullptr));
		started = true;
	    }

            return min + (rand() % (max - min));
        }

        static double random()
        {
            static std::random_device rd;
            static std::mt19937 rng(rd());

            auto uni = std::uniform_real_distribution<double>(0,1);

            return uni(rng);
        }
};

#endif
