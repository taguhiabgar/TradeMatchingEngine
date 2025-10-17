#pragma once

namespace engine {

// Central class coordinating buy/sell order processing

class MatchingEngine {
public:
    void processOrder(const Order& order);
};

} // namespace engine


