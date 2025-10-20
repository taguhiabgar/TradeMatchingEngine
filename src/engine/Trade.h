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
    
    auto operator<=>(const Trade& other) const noexcept {
        if (auto cmp = traderId <=> other.traderId; cmp != 0) return cmp;
        if (auto cmp = side <=> other.side; cmp != 0) return cmp;
        return price <=> other.price;
    }
    
    bool operator==(const Trade& other) const = default;
};

std::ostream& operator<<(std::ostream& os, const Trade& trade);

} // namespace engine


