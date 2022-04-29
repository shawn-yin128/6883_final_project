#include "Stock.hpp"
#include <string>
#include <vector>
#include "Trade.hpp"

namespace fre {
    void Stock::addTrade(const Trade& aTrade) {
        Trades.push_back(aTrade);
    }

    const vector<Trade>& Stock::getTrade(void) const {
        return Trades;
    }
}
