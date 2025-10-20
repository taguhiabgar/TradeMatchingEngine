#pragma once

#include "CommonTypes.h"
#include <iostream>
#include <string>

namespace engine {

struct Trade {
    std::string traderId;
    Side side;
    Quantity quantity;
    Price price;
    
    [[nodiscard]] bool isBuy() const noexcept { return side == Side::Buy; }
    [[nodiscard]] bool isSell() const noexcept { return side == Side::Sell; }
};

std::ostream& operator<<(std::ostream& os, const Trade& trade);

} // namespace engine


