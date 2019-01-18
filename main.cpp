#include <math.h>
#include <cmath>
#include <random>
#include <chrono>
#include "config.hpp"
#include "logger.hpp"
#include "model.hpp"

#include "config.hpp"

#include "serializer.hpp"

enum MetropolisCriterionBehaviour
{
    KeepOld,
    KeepNew
};

auto satisfies_criterion(Solution &original, Solution &perturbated, const double& T, const double& constant)
{
    auto random = Random::random();
    auto delta_makespan = perturbated.makespan() - original.makespan();

    if (delta_makespan <= 0)
        // Perturbated has a lower makespan than original
        // return perturbated;
        return MetropolisCriterionBehaviour::KeepNew;

    // Original was better
    if (random < exp(-1 * delta_makespan / (constant * T)))
        // return perturbated;
        return MetropolisCriterionBehaviour::KeepOld;
    else
        // return original;
        return MetropolisCriterionBehaviour::KeepNew;
}

auto max = [](const int& a, const int& b) { return a > b ? a : b; };

auto solve_problem() -> int
{
    using namespace std::chrono;

    std::srand(std::time(nullptr));
    Solution S(teachers, students, durations);

    auto f = [](int t) { return max(0, t - 10); };
    auto T = 1000;
    auto K = 100;
    auto begin_time_optimize = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    while (T > 0)
    {
        auto S2 = S;
        S2.perturbate();
        if (satisfies_criterion(S, S2, T, K) == MetropolisCriterionBehaviour::KeepNew)
            S = S2;

        T = f(T);
    }
    auto end_time_optimize = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    auto begin_time_serialize = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    Serializer serializer(S);
    auto end_time_serialize = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    // std::cout << "Optimization time: " << (end_time_optimize - begin_time_optimize) << std::endl;
    // std::cout << "Serialization time: " << (end_time_serialize - begin_time_serialize) << std::endl;
    // std::cout << S.makespan() << std::endl;

    return S.makespan();
}

auto main() -> int
{
    auto best = 9999;
    for (auto i = 0; i < 100; i++)
    {
        auto makespan = solve_problem();
        if (makespan < best)
            best = makespan;
    }

    // std::cout << "Best : " <<  best << std::endl;

    return 0;
}