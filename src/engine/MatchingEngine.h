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
    [[nodiscard]] std::set<Trade> processOrder(Order& order);

private:
    void addRestingOrder(const Order& aggressor) noexcept;

    // executes trades between aggressor and the opposing side
    // buy orders are matched to the lowest sell prices (ascending)
    // sell orders are matched to the highest buy prices (descending)
    template <typename OwnBook, typename OpposingBook>
    [[nodiscard]] std::set<Trade> executeTrades(Order& aggressor, OpposingBook& opposingBook, OwnBook& aggressorBook)
    {
        std::set<Trade> trades;

        auto isMatchPossible = [&] {
            auto bestPriceOpt = opposingBook.bestPrice();
            return bestPriceOpt && aggressorBook.isPriceMatchable(aggressor.price, *bestPriceOpt);
        };

        while (aggressor.isActive() && isMatchPossible()) {
            Order* bestOrder = opposingBook.getBestOrder();
            if (!bestOrder) break;
            Quantity tradeQuantity = std::min(aggressor.quantity, bestOrder->quantity);
            processTrade(aggressor, *bestOrder, tradeQuantity, trades);
            opposingBook.removeInactiveOrders();
        }

        if (aggressor.isActive()) {
            addRestingOrder(aggressor);
        }
        return trades;
    }
    
    // process a trade between two orders and record the trades
    void processTrade(Order& aggressor, Order& restingOrder, Quantity tradeQuantity, std::set<Trade>& trades);
    
    void insertOrMerge(std::set<Trade>& trades, const Trade& newTrade);
    
private:
    OrderBook buys{std::greater<Price>{}};
    OrderBook sells{std::less<Price>{}};
};

} // namespace engine


