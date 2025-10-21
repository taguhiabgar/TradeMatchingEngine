#include "MatchingEngine.h"

namespace engine {

std::set<Trade> MatchingEngine::processOrder(Order& aggressor) {
    if (aggressor.isBuy()) {
        return executeTrades(aggressor, sells, buys);
    } else {
        return executeTrades(aggressor, buys, sells);
    }
}

void MatchingEngine::addRestingOrder(const Order& order) noexcept {
    if (order.isBuy()) {
        buys.addRestingOrder(order);
    } else {
        sells.addRestingOrder(order);
    }
}

void MatchingEngine::insertOrMerge(std::set<Trade>& trades, const Trade& newTrade) {
    auto it = trades.find(newTrade);
    if (it != trades.end()) {
        Quantity combinedQuantity = it->quantity + newTrade.quantity;
        it = trades.erase(it);
        trades.emplace_hint(it, Trade{newTrade.traderId, newTrade.side, combinedQuantity, newTrade.price});
    } else {
        trades.emplace(newTrade);
    }
}

void MatchingEngine::processTrade(Order& aggressor, Order& restingOrder, Quantity tradeQuantity, std::set<Trade>& trades) {
    aggressor.quantity -= tradeQuantity;
    restingOrder.quantity -= tradeQuantity;
    // record trade for both counterparties
    insertOrMerge(trades, Trade{aggressor.traderId, aggressor.side, tradeQuantity, restingOrder.price});
    insertOrMerge(trades, Trade{restingOrder.traderId, restingOrder.side, tradeQuantity, restingOrder.price});
}

} // namespace engine
