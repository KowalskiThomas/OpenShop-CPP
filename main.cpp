#include <math.h>

#include "config.hpp"
#include "logger.hpp"
#include "model.hpp"

#include "config.hpp"

#include "serializer.hpp"

auto satisfies_criterion(Solution &original, Solution &perturbated, const double T, const double constant) {
    auto random = Random::random();
    auto delta_makespan = perturbated.makespan() - original.makespan();

    if (delta_makespan <= 0)
        // Perturbated has a lower makespan than original
        // return perturbated;
        return false;

    // Original was better
    if (random < exp(-1 * delta_makespan / (constant * T)))
        // return perturbated;
        return false;
    else
        // return original;
        return true;
}

auto main() -> int {
    Solution S(teachers, students, durations);

    for (int i = 0; i < 1000; i++) {
        S.perturbate();
        S.generate();
        std::cout << i << std::endl;
    }

    std::cout << "ok" << std::endl;

    auto T = 1000;
    auto K = 2.5;
    while (T > 0) {
        auto S2 = S;
        S2.perturbate();
        if (satisfies_criterion(S, S2, T, K))
            S = S2;

        T -= 10;
        std::cout << T << std::endl;
    }

    Serializer serializer(S);

    return 0;
}