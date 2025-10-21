#include "engine/MatchingEngine.h"
#include "engine/Order.h"
#include "utils/Printer.h"
#include <iostream>

using engine::MatchingEngine;
using engine::Order;
using utils::Printer;

int main() {
    MatchingEngine engine;
    Order order;
    
    while (std::cin >> order) {
        const auto& trades = engine.processOrder(order);
        Printer::printTrades(trades);
    }
    
    return 0;
}

