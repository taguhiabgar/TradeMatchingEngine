#include <iostream>
#include "engine/MatchingEngine.h"
#include "engine/Order.h"

using engine::MatchingEngine;
using engine::Order;

int main() {
    MatchingEngine engine;
    Order order;
    
    while (std::cin >> order) {
        engine.processOrder();
    }
    
    return 0;
}

