#include <math.h>

#include "config.hpp"
#include "logger.hpp"
#include "model.hpp"

#include "config.hpp"

#include "serializer.hpp"

Solution& satisfies_criterion(Solution& original, Solution& perturbated, const double T, const double constant)
{
    auto random = Random::random();
    auto delta_makespan = perturbated.makespan() - original.makespan();

    if (delta_makespan <= 0)
        // Perturbated has a lower makespan than original
        return perturbated;

    // Original was better
    if (random < exp(-1 * delta_makespan / (constant * T)))
        return perturbated;
    else
        return original;
}

auto main() -> int {
    Solution S(teachers, students, durations);
    Serializer serializer(S);

    return 0; 
}