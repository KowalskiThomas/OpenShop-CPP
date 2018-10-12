#include <math.h>

#include "config.hpp"
#include "logger.hpp"
#include "model.hpp"

const int teachers = 5;
const int students = 4;
const int durations[] = {1, 2, 3, 4, 5};

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

    auto S2 = S;

    S.print_solution();
    std::cout << "Perturbation" << std::endl;
    S.perturbate();
    S.print_solution();
    std::cout << "And for S2" << std::endl;
    S2.print_solution();

    satisfies_criterion(S2, S, 23, 7);

    return 0; 
}