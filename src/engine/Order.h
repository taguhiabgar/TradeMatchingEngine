#pragma once

#include "CommonTypes.h"
#include <iostream>
#include <string>

namespace engine {

struct Order {
    std::string traderId;
    Side side;
    Quantity quantity;
    Price price;
    
    bool isBuy() const noexcept { return side == Side::Buy; }
    bool isSell() const noexcept { return side == Side::Sell; }
    bool isActive() const { return quantity > 0; }
};

std::istream& operator>>(std::istream& is, Order& order);
std::ostream& operator<<(std::ostream& os, const Order& order);

} // namespace engine


