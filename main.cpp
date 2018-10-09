#include "config.hpp"
#include "logger.hpp"
#include "model.hpp"

const unsigned int teachers = 5;
const unsigned int students = 4;
const unsigned int durations[] = {1,2,3,4,5};

auto main() -> int { 
    Solution S(teachers, students, durations);
    return 0; 
}