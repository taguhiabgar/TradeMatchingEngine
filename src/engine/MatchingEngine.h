#pragma once

#include "Order.h"

#include <map>
#include <vector>
#include <deque>
#include <algorithm>

namespace engine {

// Central class coordinating buy/sell order processing

class MatchingEngine {
public:
    void processOrder(Order& order);

private:
    void addRestingOrder(const Order& aggressor) noexcept;
    
    // TODO: replace int with Trade object
    template <typename OwnBook, typename OpposingBook>
    std::vector<int> executeTrades(Order& aggressor, OpposingBook& opposingBook, OwnBook& aggressorBook)
    {
        if (opposingBook.empty()) {
            addRestingOrder(aggressor);
            return {};
        }
        
        auto isPriceMatchable = [&](Price aggressorPrice, Price bookPrice) {
            const auto compareFunc = aggressorBook.key_comp();
            return aggressorPrice == bookPrice || compareFunc(aggressorPrice, bookPrice);
        };
        
        auto bestPrice = opposingBook.begin()->first;
        while (aggressor.isActive() && isPriceMatchable(aggressor.price, bestPrice)) {
            std::cout << "-->  TRADE: " << aggressor.price << ", " << bestPrice << std::endl;
            
            auto& bestOrders = opposingBook[bestPrice];
            if (bestOrders.empty()) {
                opposingBook.erase(bestPrice);
                bestPrice = opposingBook.begin()->first; // recalculate best price
                continue;
            }
            
            if (!bestOrders.front().isActive()) {
                bestOrders.pop_front();
                bestPrice = opposingBook.begin()->first; // recalculate best price
                continue;
            }
            
            auto minQuantity = std::min(aggressor.quantity, bestOrders.front().quantity);
            // make trade
            aggressor.quantity -= minQuantity;
            bestOrders.front().quantity -= minQuantity;
            // TODO: add to trades vector
            
            bestPrice = opposingBook.begin()->first; // recalculate best price
        }
        
        if (aggressor.isActive()) {
            addRestingOrder(aggressor);
        }
        
        return {};
    }
    
    // TODO: delete - debug function
    void printBuysSells() const noexcept;
    
private:
    std::map<Price, std::deque<Order>, std::greater<Price>> buys;
    std::map<Price, std::deque<Order>, std::less<Price>> sells;
};

} // namespace engine


