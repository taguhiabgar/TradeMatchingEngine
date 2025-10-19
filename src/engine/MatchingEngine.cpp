#include "MatchingEngine.h"

namespace engine {

void MatchingEngine::processOrder(const Order& order) {
    std::cout << "process order: " << order << std::endl;
    if (order.isBuy()) {
        matchBuyOrder(order);
    } else {
        matchSellOrder(order);
    }
}

// TODO: replace int with Trade object
std::vector<int> MatchingEngine::matchBuyOrder(const Order& aggressor) noexcept {
    // TODO: replace int with Trade object
    // std::vector<int> trades = matchOrderInternal(aggressor, sells);
    return matchOrderInternal(aggressor, sells);
    
}

// TODO: replace int with Trade object
std::vector<int> MatchingEngine::matchSellOrder(const Order& aggressor) noexcept {
    // TODO: replace int with Trade object
    //std::vector<int> trades = matchOrderInternal(aggressor, buys);
    return matchOrderInternal(aggressor, buys);
    
}

// TODO: replace int with Trade object
template <typename Map>
std::vector<int> MatchingEngine::matchOrderInternal(const Order& aggressor, Map& restingOrders)
{
    if (restingOrders.empty()) {
        addRestingOrder(aggressor);
        return {};
    }
    
    auto [bestPrice, bestOrder] = *restingOrders.begin();
    
    auto compareFunc = restingOrders.key_comp();
    if (compareFunc(aggressor.price, bestPrice)) { // match was made
        std::cout << "trade" << std::endl;
        return {0};
    } else { // no match
        std::cout << "no trade - make resting order" << std::endl;
        restingOrders[aggressor.price] = aggressor;
    }
    
    std::cout << "bestPrice: " << bestPrice << ", bestOrder: " << bestOrder << std::endl;
    
    for (const auto& [price, order] : restingOrders) {
        std::cout << order << '\n';
    }
    
    if (aggressor.quantity > 0) {
        addRestingOrder(aggressor);
        
    }
    
    return {};
}

void MatchingEngine::addRestingOrder(const Order& order) noexcept {
    std::cout << "add resting order: " << order << std::endl;
    
    if (order.isBuy()) {
        buys.emplace(order.price, order);
    } else {
        sells.emplace(order.price, order);
    }
}


} // namespace engine
