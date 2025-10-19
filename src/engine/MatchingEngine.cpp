#include "MatchingEngine.h"

namespace engine {

void MatchingEngine::printBuysSells() const noexcept {
    std::cout << std::endl << "Buys:" << std::endl << "{" << std::endl;

    for (const auto& [price, orders] : buys) {
        std::cout << "    ";
        for (const auto& order : orders) {
            std::cout << order << ", ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "}" << std::endl;
    std::cout << "Sells:" << std::endl << "{" << std::endl;
    
    for (const auto& [price, orders]  : sells) {
        std::cout << "    ";
        for (const auto& order : orders) {
            std::cout << order << ", ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "}" << std::endl << std::endl;
}

void MatchingEngine::processOrder(Order& aggressor) {
    std::cout << "process order: " << aggressor << std::endl;
    
    if (aggressor.isBuy()) {
        executeTrades(aggressor, sells, buys);
    } else {
        executeTrades(aggressor, buys, sells);
    }
    
    printBuysSells();
}

void MatchingEngine::addRestingOrder(const Order& order) noexcept {
    std::cout << "add resting order: " << order << std::endl;
    
    if (order.isBuy()) {
        buys[order.price].push_back(order);
    } else {
        sells[order.price].push_back(order);
    }
}


} // namespace engine
