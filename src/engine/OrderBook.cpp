#include "OrderBook.h"

namespace engine {

void OrderBook::addRestingOrder(const Order& order) {
    if (!order.isActive()) return;
    priceLevels[order.price].push_back(order);
}

Order* OrderBook::getBestOrder() {
    while (!priceLevels.empty()) {
        auto& deque = priceLevels.begin()->second;
        if (deque.empty()) {
            priceLevels.erase(priceLevels.begin());
            continue;
        }
        if (!deque.front().isActive()) {
            deque.pop_front();
            continue;
        }
        return &deque.front();
    }
    return nullptr;
}

std::optional<Price> OrderBook::bestPrice() const {
    if (priceLevels.empty()) {
        return std::nullopt;
    }
    return priceLevels.begin()->first;
}

bool OrderBook::isPriceMatchable(const Price& aggressorPrice, const Price& bookPrice) const {
    auto compareFunc = priceLevels.key_comp();
    return aggressorPrice == bookPrice || compareFunc(aggressorPrice, bookPrice);
}

void OrderBook::removeInactiveOrders() noexcept {
    while (!priceLevels.empty()) {
        auto& bestOrders = priceLevels.begin()->second;
        while (!bestOrders.empty() && !bestOrders.front().isActive()) {
            bestOrders.pop_front();
        }
        if (bestOrders.empty()) {
            priceLevels.erase(priceLevels.begin());
        } else {
            break; // best level is valid
        }
    }
}

void OrderBook::print() const noexcept {
    std::cout << "{" << std::endl;
    for (const auto& [price, orders] : priceLevels) {
        std::cout << "    ";
        for (const auto& order : orders) {
            std::cout << order << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "}" << std::endl;
}

} // namespace engine


