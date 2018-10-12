#include <algorithm>
#include <ctime>
#include <array>
#include <iostream>
#include <vector>
#include <random>
#include <map>
#include "rand.hpp"

#ifndef MODEL_HPP
#define MODEL_HPP

class Order {
private:
    const int size_;
    int *order_;

public:
    Order(const int size) : size_(size) {
        order_ = new int[size];

        for (int i = 0; i < size_; i++)
            order_[i] = i;
    }

    Order(const Order &from) : size_(from.size_) {
        order_ = new int[size_];
        for (int i = 0; i < size_; i++)
            order_[i] = from.order_[i];
    }

    auto shuffle() {
        std::srand(std::time(nullptr));

        for (int i = size_ - 1; i >= 0; i--) {
            auto j = Random::random_from_range(0, i);
            if (i == j)
                continue;

            // auto temp = order_[i];
            // order_[i] = order_[j];
            // order_[j] = temp;
            std::swap(order_[i], order_[j]);
        }
    }

    auto perturbate() {
        auto index = Random::random_from_range(0, size_ - 1);

        if (index < size_ - 1)
            std::swap(order_[index], order_[index + 1]);
        else
            std::swap(order_[index], order_[0]);
    }

    auto begin() {
        return order_;
    }

    auto end() {
        return order_ + size_;
    }

    const auto begin() const {
        return order_;
    }

    const auto end() const {
        return order_ + size_;
    }


    ~Order() { delete[] order_; }
};

auto make_random_order(int length) {
    Order o(length);
    o.shuffle();
    return o;
}

class Solution {
private:
    /* Problem data */
    std::map<int, int> durations_;
    static const int pause = 2;

    const int teachers_;
    const int students_;

    /* Solution data */
    Order teacher_order;
    std::vector <Order> chromosomes;

    /* Generated solution data */
    std::map<int, std::map<int, int>> hours_teachers;

public:
    Solution(const int teachers, const int students, const int *durations)
            : teachers_(teachers), students_(students),
              teacher_order(make_random_order(teachers)) {
        for (int i = 0; i < teachers; i++) {
            chromosomes.push_back(make_random_order(students));
            durations_.insert(std::pair(i, durations[i]));

            hours_teachers.insert(std::make_pair(i, std::map<int, int>()));
            for (int j = 0; j < students; j++)
                hours_teachers.at(i).insert(std::pair(j, -1));
        }
    }

    Solution(const Solution &from) : teachers_(from.teachers_), students_(from.students_),
                                     teacher_order(from.teacher_order), chromosomes(from.chromosomes) {
        std::cout << "Solution copied" << std::endl;
    }

    auto perturbate() {
        auto index = Random::random_from_range(0, chromosomes.size());

        if (index < chromosomes.size())
            chromosomes[index].perturbate();
        else
            // Perturbate teacher order
            teacher_order.perturbate();
    }

    auto print_solution() const {
        std::cout << "Solution data: " << std::endl;
        std::cout << "Base chromosome data: ";
        for (auto const &x : teacher_order)
            std::cout << x << " ";
        std::cout << std::endl;

        auto i = int{0};
        std::cout << "Chromosomes: " << std::endl;
        for (auto const &chromosome : chromosomes) {
            ++i;
            std::cout << "  " << i << ". ";
            for (auto const &x : chromosome)
                std::cout << x << " ";
            std::cout << std::endl;
        }
    }

    auto find_hours_for_student(int student) {
        std::map<int, int> hours;
        for (const auto &teacherTimetablePair : hours_teachers) {
            const auto teacher = teacherTimetablePair.first;
            const auto timetable = teacherTimetablePair.second;

            const auto hour = timetable.at(student);

            hours.insert(std::pair(hour, teacher));
        }

        return hours;
    }

    auto student_is_available(int student, int time, int duration) {
        auto hours_student = find_hours_for_student(student);
        for (const auto &entry : hours_student) {
            auto entryHour = entry.first;
            auto entryTeacher = entry.second;

            if (entryHour == -1)
                continue;

            if (time <= entryHour && time + duration + pause > entryHour)
                return false;
            else if (time >= entryHour && entryHour + durations_[entryTeacher] + pause > time)
                return false;

            return true;
        }
    }

    auto teacher_is_available(int teacher, int time, int duration) {
        auto hours = hours_teachers.at(teacher);
        for (const auto &entry : hours) {
            auto entryHour = entry.second;

            if (entryHour == -1)
                continue;

            if (time <= entryHour && time + durations_.at(teacher) > entryHour)
                return false;
            else if (entryHour <= time && entryHour + durations_.at(teacher) > time)
                return false;

            return true;
        }
    }

    auto generate() {
    }

    auto makespan() {
        return 0;
    }
};

#endif