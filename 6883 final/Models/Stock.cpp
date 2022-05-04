#include "Stock.hpp"
#include <string>
#include <vector>
#include "Trade.hpp"
#include "../Utils/Utils.hpp"

using namespace std;

namespace fre {
    void Stock::addTrade(const Trade& aTrade) {
        trades.push_back(aTrade);
    }

    const string Stock::getSymbol(void) const {
        return symbol;
    }

    const vector<Trade>& Stock::getTrades(void) const {
        return trades;
    }

    const vector<Trade>& Stock::getValidTrade(void) const {
        return validTrades;
    }

    const vector<Trade>& Stock::getAR(void) const {
        return AR;
    }

    void Stock::setAnnouncementDate(string date) {
        announcementDate = converTime(date);
    }

    bool Stock::computeUsedData(int N) {
        for (vector<Trade>::iterator itr = trades.begin(); itr != trades.end(); itr++) {
            if (itr->getDate() == announcementDate) {
                if (itr - trades.begin() < N || trades.end() - itr < N) {
                    return false;
                } else {
                    for (auto itr2 = itr - N; itr2 <= itr + N; itr2++) {
                        validTrades.push_back(*itr2);
                    }
                    return true;
                }
            }
        }
        return false;
    }
}
