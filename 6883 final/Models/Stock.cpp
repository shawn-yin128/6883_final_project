#include "Stock.hpp"
#include <string>
#include <vector>
#include "Trade.hpp"
#include "../Utils/Utils.hpp"

using namespace std;

namespace fre {
    void Stock::addTrade(const Trade& aTrade) {
        Trades.push_back(aTrade);
    }

    const string Stock::getSymbol(void) const {
        return symbol;
    }

    const vector<Trade>& Stock::getTrade(void) const {
        return Trades;
    }

    const vector<Trade>& Stock::getUsedTrade(void) const {
        return used_trades;
    }

    void Stock::setAnnouncementDate(string date) {
        announcementDate = converTime(date);
    }

    bool Stock::computeUsedData(int N) {
        for (vector<Trade>::iterator itr = Trades.begin(); itr != Trades.end(); itr++) {
            if (itr->GetDate() == announcementDate) {
                if (itr - Trades.begin() < N || Trades.end() - itr < N) {
                    return false;
                } else {
                    for (auto itr2 = itr - N; itr2 <= itr + N; itr2++) {
                        used_trades.push_back(*itr2);
                    }
                    return true;
                }
            }
        }
        return false;
    }
}
