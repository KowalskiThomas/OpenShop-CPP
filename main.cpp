#include "config.hpp"
#include "logger.hpp"
#include "model.hpp"

const int teachers = 5;
const int students = 4;
const int durations[] = {1, 2, 3, 4, 5};

auto main() -> int {
    Solution S(teachers, students, durations);
    S.print_solution();
    S.generate();
    return 0; 
}