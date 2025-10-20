#include "MatchingEngine.h"

namespace engine {

void MatchingEngine::printBuysSells() const noexcept {
//    std::cout << std::endl << "Buys:" << std::endl;
//    
//    buys.print();
//    
//    std::cout << "Sells:" << std::endl;
//    
//    sells.print();
//    
//    std::cout << std::endl << std::endl;
}

void MatchingEngine::printTrades(const std::multiset<Trade>& trades) const noexcept {
    // TODO: should combine trades if necessary?
    for (const auto& trade: trades) {
        std::cout << trade << ' ';
    }
    std::cout << std::endl;
}

void MatchingEngine::processOrder(Order& aggressor) {
//    std::cout << "process order: " << aggressor << std::endl;
    
    if (aggressor.isBuy()) {
        auto trades = executeTrades(aggressor, sells, buys);
        printTrades(trades);
    } else {
        auto trades = executeTrades(aggressor, buys, sells);
        printTrades(trades);
    }
    
    printBuysSells();
    
}

void MatchingEngine::addRestingOrder(const Order& order) noexcept {
//    std::cout << "add resting order: " << order << std::endl;
    
    if (order.isBuy()) {
        buys.addRestingOrder(order);
    } else {
        sells.addRestingOrder(order);
    }
}


} // namespace engine
