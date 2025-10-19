#pragma once

#include "Order.h"

#include <map>
#include <vector>

namespace engine {

// Central class coordinating buy/sell order processing

class MatchingEngine {
public:
    void processOrder(const Order& order);

private:
    std::vector<int> matchBuyOrder(const Order& aggressor) noexcept;
    std::vector<int> matchSellOrder(const Order& aggressor) noexcept;
    void addRestingOrder(const Order& aggressor) noexcept;
    
    // TODO: replace int with Trade object
    template <typename Map>
    std::vector<int> matchOrderInternal(const Order& aggressor, Map& restingOrders);
    
private:
    std::map<unsigned, Order, std::greater<unsigned>> buys;
    std::map<unsigned, Order, std::less<unsigned>> sells;
};

} // namespace engine


