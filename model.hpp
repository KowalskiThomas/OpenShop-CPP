#include <vector>
#include <algorithm>

#ifndef ORDER_TEMPLATE_IMPLEMENTATION
class Order {
    private:
        const unsigned int size_;
        unsigned int* order_;

    public:
        Order(const unsigned int size) : size_(size)
        {
            order_ = new unsigned int[size];
        }

        Order(const Order& from) : size_(from.size_)
        {
            order_ = new unsigned int[size_];
            for(unsigned int i = 0; i < size_; i++)
                order_[i] = from.order_[i];
        }

        ~Order()
        {
            delete[] order_;
        }
};
#endif

Order make_order(unsigned int length)
{
    Order o(length);
}

class Solution {
    private:
        Order teacher_order;
        std::vector<Order> chromosomes;

        const unsigned int teachers_;
        const unsigned int students_;

    public:
        Solution(const unsigned int teachers, const unsigned int students) : teachers_(teachers), students_(students)
        {
            
        }
};