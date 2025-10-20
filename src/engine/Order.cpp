#include "Order.h"

namespace engine {

std::istream& operator>>(std::istream& is, Order& order) {
    std::string sideStr;
    if (is >> order.traderId >> sideStr >> order.quantity >> order.price) {
        if (sideStr == "B") {
            order.side = Side::Buy;
        } else if (sideStr == "S") {
            order.side = Side::Sell;
        } else {
            is.setstate(std::ios::failbit); // invalid side string
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    const char side = (order.isBuy() ? 'B' : 'S');
    os << order.traderId << ' ' << side << ' ' << order.quantity << ' ' << order.price;
    return os;
}

} // namespace engine


