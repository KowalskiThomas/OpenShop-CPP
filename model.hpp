#include <algorithm>
#include <ctime>
#include <array>
#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <cassert>
#include <memory>

#include "rand.hpp"

#ifndef MODEL_HPP
#define MODEL_HPP

class Order
{
  private:
    const int size_;
    int *order_;

  public:
    Order(const int size) : size_(size)
    {
        order_ = new int[size];

        for (int i = 0; i < size_; i++)
            order_[i] = i;
    }

    Order(const Order &from) : size_(from.size_)
    {
        order_ = new int[size_];

        for (int i = 0; i < size_; i++)
            order_[i] = from.order_[i];
    }

    auto shuffle()
    {
        std::random_device random_dev;
        std::mt19937 generator(random_dev());

        std::shuffle(order_, order_ + size_, generator);
    }

    auto print()
    {
        for (auto i = 0; i < size_; i++)
            std::cout << order_[i] << "; ";
        std::cout << std::endl;
    }

    auto perturbate()
    {
        auto index = Random::random_from_range(0, size_ - 2);

        int temp;
        if (index < size_ - 1)
        {
            temp = order_[index];
            order_[index] = order_[index + 1];
            order_[index + 1] = temp;
            // std::swap(order_[index], order_[index + 1]);
        }
        else
        {
            temp = order_[index];
            order_[index] = order_[0];
            order_[0] = temp;
            // std::swap(order_[index], order_[0]);
        }

        // std::cout << "Perturbated Order: Size = " << size_ << " Index = " << index << ", temp = " << temp << std::endl;
    }

    auto begin()
    {
        return order_;
    }

    auto end()
    {
        return order_ + size_;
    }

    const auto begin() const
    {
        return order_;
    }

    const auto end() const
    {
        return order_ + size_;
    }

    auto operator==(const Order &o)
    {
        if (size_ != o.size_)
            return false;

        auto it1 = order_;
        auto it2 = o.begin();

        for (; it1 != this->end() && it2 != o.end();)
        {
            if (*it1 != *it2)
                return false;

            it1++;
            it2++;
        }

        return true;
    }

    auto operator!=(const Order &o)
    {
        return !this->operator==(o);
    }

    auto operator=(const Order &other)
    {
        assert(other.size_ == size_);

        std::copy(other.begin(), other.end(), this->begin());

        return *this;
    }

    ~Order() { delete[] order_; }
};

std::ostream &operator<<(std::ostream &s, const Order &o)
{
    for (auto it = o.begin(); it != o.end(); it++)
        s << *it << " ";
    return s;
}

auto make_random_order(const int length)
{
    Order o(length);
    o.shuffle();
    return o;
}

class Solution
{
  private:
    /* Problem data */
    std::map<int, int> durations_;
    static const int pause = 2;

    const int teachers_;
    const int students_;

    /* Solution data */
    Order teacher_order;
    std::vector<Order> chromosomes;

    /* Whether the solution in its current state has been generated */
    bool generated_;

    /* Generated solution data */
    std::map<int, std::map<int, int>> hours_teachers;
    std::map<int, std::map<int, int>> hours_students;

  public:
    Solution(const int teachers, const int students, const int *durations)
        : teachers_(teachers), students_(students),
          teacher_order(make_random_order(teachers)), generated_(false)
    {

        for (int i = 0; i < teachers; i++)
        {
            chromosomes.push_back(make_random_order(students));
            std::cout << chromosomes[chromosomes.size() - 1] << std::endl;
            durations_.insert(std::pair<int, int>(i, durations[i]));
        }

        initialize_maps();
    }

    Solution(const Solution &from) : durations_(from.durations_), teachers_(from.teachers_), students_(from.students_),
                                     teacher_order(from.teacher_order), chromosomes(from.chromosomes),
                                     generated_(false)
    {
        initialize_maps();
        // std::cout << "Solution copied" << std::endl;
    }

    auto operator=(const Solution &o)
    {
        generated_ = false;
        initialize_maps();
        teacher_order = o.teacher_order;
        std::copy(begin(o.chromosomes), end(o.chromosomes), begin(chromosomes));
        return *this;
    }

    void initialize_maps()
    {
        for (int i = 0; i < teachers_; i++)
        {
            if (!hours_teachers.count(i))
            {
                hours_teachers.insert(std::make_pair(i, std::map<int, int>()));
                for (int j = 0; j < students_; j++)
                    hours_teachers.at(i).insert(std::pair<int, int>(j, -1));
            }
            else
                for (int j = 0; j < students_; j++)
                    hours_teachers.at(i)[j] = -1;
        }

        for (int i = 0; i < students_; i++)
        {
            if (!hours_students.count(i))
            {
                hours_students.insert(std::make_pair(i, std::map<int, int>()));
                for (int j = 0; j < teachers_; j++)
                    hours_students[i].insert(std::pair<int, int>(j, -1));
            }
            else
                for (int j = 0; j < students_; j++)
                    hours_students[i][j] = -1;
        }
    }

    auto operator==(const Solution &o)
    {
        std::cout << "Operator==" << std::endl;
        if (teacher_order == o.teacher_order)
            return false;

        auto it1 = begin(chromosomes);
        auto it2 = begin(o.chromosomes);
        for (; it1 != end(chromosomes) && it2 != end(o.chromosomes);)
        {
            if (*it1 != *it2)
                return false;
        }

        return true;
    }

    auto perturbate()
    {
        // this->print_solution();
        auto index = Random::random_from_range(0, chromosomes.size());

        auto before = &teacher_order;
        auto after = &teacher_order;

        if (index < chromosomes.size())
        {
            // Perturbate a "real" chromosome
            before = &chromosomes[index];
            chromosomes[index].perturbate();
            after = &chromosomes[index];
        }
        else
        {
            // Perturbate teacher order
            teacher_order.perturbate();
            after = &teacher_order;
        }

        generated_ = false;
        // std::cout << "Perturbation over (perturbated " << index << ")" << std::endl;
        // std::cout << "B: " << *before << std::endl;
        // std::cout << "A: " << *after << std::endl;
        // this->print_solution();
        // std::cout << std::endl;
        // std::string test;
        // std::cin >> test;
    }

    void print_solution() const
    {
        std::cout << "Solution data: " << std::endl;
        std::cout << "Base chromosome data: ";
        for (auto const &x : teacher_order)
            std::cout << x << " ";
        std::cout << std::endl;

        auto i = int{0};
        std::cout << "Chromosomes: " << std::endl;
        for (auto const &chromosome : chromosomes)
        {
            ++i;
            std::cout << "  " << i << ". ";
            for (auto const &x : chromosome)
                std::cout << x << " ";
            std::cout << std::endl;
        }
    }

    auto find_hours_for_student(int student)
    {
        std::map<int, int> hours;
        for (const auto &teacherTimetablePair : hours_teachers)
        {
            const auto teacher = teacherTimetablePair.first;
            const auto timetable = teacherTimetablePair.second;

            const auto hour = timetable.at(student);

            hours.insert(std::pair<int, int>(hour, teacher));
        }

        return hours;
    }

    auto student_is_available(int student, int time, int duration)
    {
        auto hours_student = find_hours_for_student(student);
        for (const auto &entry : hours_student)
        {
            auto entryHour = entry.first;
            auto entryTeacher = entry.second;

            if (entryHour == -1)
                continue;

            if (time <= entryHour && time + duration + pause > entryHour)
                return false;
            else if (time >= entryHour && entryHour + durations_[entryTeacher] + pause > time)
                return false;
        }

        return true;
    }

    auto teacher_is_available(int teacher, int time)
    {
        auto duration = durations_[teacher];
        auto hours = hours_teachers.at(teacher);
        for (const auto &entry : hours)
        {
            auto entryHour = entry.second;

            if (entryHour == -1)
                continue;

            if (time <= entryHour && time + duration > entryHour)
                return false;
            else if (entryHour <= time && entryHour + duration > time)
                return false;
        }

        return true;
    }

    void generate()
    {
        if (generated_)
        {
            // std::cout << "Solution already generated. Exiting." << std::endl;
            return;
        }

        initialize_maps();

        for (int i = 0; i < teachers_; i++)
        {
            // For each teacher, create a map for their hours
            hours_teachers.insert(std::pair<int, std::map<int, int>>(i, std::map<int, int>()));
            for (int j = 0; j < students_; j++)
                // Set the student at -1
                hours_teachers.at(i).insert(std::pair<int, int>(j, -1));
        }

        for (auto const j : teacher_order)
        {
            auto all_set = false;
            auto t = 0;
            while (!all_set)
            {
                // std::cout << "People left, t = " << t << std::endl;
                all_set = true;
                for (auto student_hour_pair : hours_teachers[j])
                    if (student_hour_pair.second == -1)
                        all_set = false;

                if (all_set)
                    break;

                // all_set = std::all_of(
                //     begin(hours_teachers.at(j)),
                //     end(hours_teachers.at(j)),
                //     [](std::pair<int, int> x) {
                //         return x.second > -1;
                //     });

                /* Whether or not we found a student to place at t */
                auto set = false;
                for (auto const student : chromosomes[j])
                {
                    // std::cout << "Chromosome: " << chromosomes[j] << std::endl;
                    /* Student already placed */
                    if (hours_teachers[j][student] > -1)
                    {
                        // std::cout << "Student " << student << " already placed for teacher " << j << " at " << hours_teachers[j][student] << std::endl;
                        continue;
                    }

                    if (student_is_available(student, t, durations_[j]))
                    {
                        if (teacher_is_available(j, t))
                        {
                            set = true;
                            // hours_students.at(student)[j] = t;
                            hours_teachers.at(j)[student] = t;
                            break;
                        }
                        else
                        {
                            // std::cout << "Teacher " << j << " is not available at " << t << " for " << durations_[j] << " units" << std::endl;
                        }
                    }
                    else
                    {
                        // std::cout << "Student " << student << "is not available at " << t << " for " << durations_[j] << " units." << std::endl;
                    }
                }

                if (!set)
                    t++;
                else
                    t += durations_[j];
            }
        }

        generated_ = true;
    }

    void print_timetable()
    {
        generate();

        for (int i = 0; i < teachers_; i++)
        {
            // std::cout << "Teacher " << i << " (duration: " << durations_[i] << ")" << std::endl;
            for (int j = 0; j < students_; j++) {
                // std::cout << "  Student " << j << " : " << hours_teachers.at(i).at(j) << std::endl;
            }
        }
    }

    auto makespan()
    {
        generate();

        auto max_end = 0;
        for (auto const &jury_and_schedule : hours_teachers)
        {
            auto jury = jury_and_schedule.first;
            auto schedule = jury_and_schedule.second;

            for (auto const &student_and_hour : schedule)
            {
                auto student = student_and_hour.first;
                auto hour = student_and_hour.second;

                auto exam_end = hour + durations_[jury];

                if (exam_end > max_end)
                    max_end = exam_end;
            }
        }

        return max_end;
    }

    const auto &get_schedule()
    {
        generate();
        return hours_teachers;
    }
};

#endif
