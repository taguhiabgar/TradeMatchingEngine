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
    
    bool isBuy() const noexcept { return side == Side::Buy; }
    bool isSell() const noexcept { return side == Side::Sell; }
    bool isActive() const { return quantity > 0; }
};

std::istream& operator>>(std::istream& is, Order& order);
std::ostream& operator<<(std::ostream& os, const Order& order);

} // namespace engine


