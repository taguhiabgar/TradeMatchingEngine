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

} // namespace engine


