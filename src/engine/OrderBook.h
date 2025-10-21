#pragma once

#include "Order.h"
#include <map>
#include <deque>
#include <optional>
#include <functional>
#include <algorithm>

namespace engine {

class OrderBook {
public:
    using OrderQueue = std::deque<Order>;
    using BookMap = std::map<Price, OrderQueue, std::function<bool(const Price&, const Price&)>>;

    explicit OrderBook(std::function<bool(const Price&, const Price&)> comp)
        : priceLevels(comp) {}

    void addRestingOrder(const Order& order);

    // returns pointer to best active order, nullptr if none
    Order* getBestOrder();

    // optional in case book is empty
    std::optional<Price> bestPrice() const;

    // check if a price is matchable according to this book's comparator
    bool isPriceMatchable(const Price& aggressorPrice, const Price& bookPrice) const;

    bool empty() const noexcept { return priceLevels.empty(); }
    
    // removes empty price levels and orders with zero quantity at the best price
    void removeInactiveOrders() noexcept;
    
private:
    BookMap priceLevels;
};

} // namespace engine


