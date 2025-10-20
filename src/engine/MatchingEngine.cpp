#include "MatchingEngine.h"

namespace engine {

void MatchingEngine::printTrades(const std::set<Trade>& trades) const noexcept {
    if (trades.empty()) {
        return;
    }
    for (const auto& trade: trades) {
        std::cout << trade << ' ';
    }
    std::cout << std::endl;
}

void MatchingEngine::processOrder(Order& aggressor) {
    if (aggressor.isBuy()) {
        auto trades = executeTrades(aggressor, sells, buys);
        printTrades(trades);
    } else {
        auto trades = executeTrades(aggressor, buys, sells);
        printTrades(trades);
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


} // namespace engine
