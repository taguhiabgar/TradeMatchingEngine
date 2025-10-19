#include <iostream>
#include "engine/MatchingEngine.h"
#include "engine/Order.h"

using engine::MatchingEngine;
using engine::Order;

int main() {
    MatchingEngine engine;
    Order order;
    
    int counter = 0;
    
    while (std::cin >> order) {
        std::cout << std::endl << "  ------  " << ++counter << "  ------  " << std::endl << std::endl;
        
        engine.processOrder(order);
        
        std::cout << std::endl;
    }
    
    return 0;
}

