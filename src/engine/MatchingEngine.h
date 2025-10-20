#pragma once

#include "Order.h"
#include "OrderBook.h"
#include "Trade.h"

#include <set>
#include <vector>

namespace engine {

// Central class coordinating buy/sell order processing

class MatchingEngine {
public:
    void processOrder(Order& order);

private:
    void addRestingOrder(const Order& aggressor) noexcept;
    
    template <typename OwnBook, typename OpposingBook>
    [[nodiscard]] std::set<Trade> executeTrades(Order& aggressor, OpposingBook& opposingBook, OwnBook& aggressorBook)
    {
        std::set<Trade> trades;
        
        if (opposingBook.empty()) {
            addRestingOrder(aggressor);
            return trades;
        }
        
        auto bestPriceOpt = opposingBook.bestPrice();
        if (bestPriceOpt == std::nullopt) {
            return trades;
        }
        Price bestPrice = bestPriceOpt.value();
        
        while (aggressor.isActive() && aggressorBook.isPriceMatchable(aggressor.price, bestPrice)) {
            Order* bestOrder = opposingBook.getBestOrder();
            if (bestOrder == nullptr) {
                return trades;
            }
            
            auto tradeQuantity = std::min(aggressor.quantity, bestOrder->quantity);
            // make trade
            aggressor.quantity -= tradeQuantity;
            bestOrder->quantity -= tradeQuantity;
            
            insertOrMerge(trades, Trade{aggressor.traderId, aggressor.side, tradeQuantity, bestOrder->price});
            insertOrMerge(trades, Trade{bestOrder->traderId, bestOrder->side, tradeQuantity, bestOrder->price});
            
            opposingBook.removeInactiveOrders();
            
            bestPriceOpt = opposingBook.bestPrice();
            if (bestPriceOpt == std::nullopt) {
                return trades;
            }
            bestPrice = bestPriceOpt.value(); // recalculate best price
        }
        
        if (aggressor.isActive()) {
            addRestingOrder(aggressor);
        }
        
        return trades;
    }
    
    void insertOrMerge(std::set<Trade>& trades, const Trade& newTrade);
    
    void printTrades(const std::set<Trade>& trades) const noexcept;
    
private:
    OrderBook buys{std::greater<Price>{}};
    OrderBook sells{std::less<Price>{}};
};

} // namespace engine


