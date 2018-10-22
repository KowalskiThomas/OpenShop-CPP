#include <iostream>
#include "model.hpp"

#include "config.hpp"
#include "rand.hpp"

auto test_solution() {
    std::cout << std::endl << std::endl << "TEST SOLUTION" << std::endl << std::endl;

    Solution S(teachers, students, durations);
    auto S2 = S;

    std::cout << "Initial solution" << std::endl;
    S.print_solution();
    std::cout << "After perturbation" << std::endl;
    S.perturbate();
    S.print_solution();

    //std::cout << "And for S2" << std::endl;
    //S2.print_solution();
}

auto test_shuffle() {
    auto o = Order(9);
    auto sum = 0;

    for (auto const i : o)
        sum += i;

    o.print();
    for (int i = 0; i < 9999; i++) {
        o.shuffle();

        auto sum_2 = 0;
        for (auto j : o)
            sum_2 += j;

        if (sum_2 != sum) {
            std::cout << "Wrong sum found!" << std::endl;
            o.print();
        }
    }
}

auto test_perturbate() {
    std::cout << std::endl << std::endl << "TEST PERTURBATE" << std::endl << std::endl;

    auto o2 = Order(5);
    o2.print();
    o2.perturbate();
    o2.perturbate();
    o2.perturbate();
    o2.perturbate();
    o2.perturbate();
    o2.print();
}

auto test_generation()
{
    std::cout << std::endl << std::endl << "TEST SOLUTION" << std::endl << std::endl;

    auto S = Solution(teachers, students, durations);
    S.generate();
    auto S2 = S;
    S.print_timetable();
    S2.print_timetable();
    return;
    S.generate();
    S.generate();
    S.generate();
    S.generate();
    S.print_timetable();
    S2.generate();
    S2.print_timetable();
}

auto test_random()
{
    for(int i = 0; i < 9999; i++)
    {
        int min = 0;
        int max = 10;
        auto test = Random::random_from_range(min, max);
        if (test < min || test > max)
            std::cout << "error" << std::endl;
    }
    std::cout << "Tests random OK" << std::endl;
}

int main(void) {
    // test_shuffle();
    // test_perturbate();
    // test_solution();
    // test_generation();
    test_random();
}