#include <algorithm>
#include <ctime>
#include <array>
#include <iostream>
#include <vector>
#include <random>
#include <map>

#ifndef MODEL_HPP
#define MODEL_HPP

class Order
{
  private:
    const unsigned int size_;
    unsigned int *order_;

  public:
    Order(const unsigned int size) : size_(size)
    {
        order_ = new unsigned int[size];

        for (unsigned int i = 0; i < size_; i++)
            order_[i] = i;
    }

    Order(const Order &from) : size_(from.size_)
    {
        order_ = new unsigned int[size_];
        for (unsigned int i = 0; i < size_; i++)
            order_[i] = from.order_[i];
    }

    auto shuffle()
    {
        std::srand(std::time(nullptr));

        auto random_variable = std::rand();

        
    }

    auto begin()
    {
        return order_;
    }

    auto end()
    {
        return order_ + size_;
    }

    ~Order() { delete[] order_; }
};

auto make_order(unsigned int length)
{
    Order o(length);
    o.shuffle();
    return o;
}

class Solution
{
  private:
    Order teacher_order;
    std::vector<Order> chromosomes;
    std::map<unsigned int, unsigned int> durations_;

    const unsigned int teachers_;
    const unsigned int students_;

  public:
    Solution(const unsigned int teachers, const unsigned int students, const unsigned int *durations)
        : teachers_(teachers), students_(students),
          teacher_order(make_order(teachers))
    {
        for (unsigned int i = 0; i < teachers_; i++)
            durations_.insert(i, durations[i]);
    }

    auto makespan()
    {
        for (const auto teacher_id : teacher_order)
        {
            std::cout << "Teacher " << teacher_id << std::endl;
            for (const auto &student_id : chromosomes.at(teacher_id))
                std::cout << "\tStudent " << student_id << std::endl;
        }
    }
};

#endif