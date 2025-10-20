#include "Trade.h"

namespace engine {

std::ostream& operator<<(std::ostream& os, const Trade& trade) {
    const char side = (trade.isBuy() ? '+' : '-');
    os << trade.traderId << side << trade.quantity << '@' << trade.price;
    return os;
}

} // namespace engine


