#pragma once

#include <set>
#include <iostream>
#include "engine/Trade.h"

namespace utils {

class Printer {
public:
    static void printTrades(const std::set<engine::Trade>& trades) noexcept {
        if (trades.empty()) {
            return;
        }
        for (const auto& trade: trades) {
            std::cout << trade << ' ';
        }
        std::cout << std::endl;
    }
};

} // namespace utils


