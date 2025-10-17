#pragma once

#include <iostream>
#include <string>

namespace engine {

struct Order {
    enum class Side {
        Buy,
        Sell
    };
    
    std::string traderId;
    Side side;
    unsigned quantity;
    unsigned price;
};

std::istream& operator>>(std::istream& is, Order& order);

} // namespace engine


