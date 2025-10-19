#include "Order.h"

namespace engine {

std::istream& operator>>(std::istream& is, Order& order) {
    std::string sideStr;
    if (is >> order.traderId >> sideStr >> order.quantity >> order.price) {
        if (sideStr == "B") {
            order.side = Order::Side::Buy;
        } else if (sideStr == "S") {
            order.side = Order::Side::Sell;
        } else {
            is.setstate(std::ios::failbit); // invalid side string
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    char side = (order.side == Order::Side::Buy ? 'B' : 'S');
    os << order.traderId << ' ' << side << ' ' << order.quantity << ' ' << order.price;
    return os;
}

} // namespace engine


