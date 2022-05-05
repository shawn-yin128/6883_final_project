#include "Stock.hpp"
#include <string>
#include <vector>
#include "Trade.hpp"
#include "../Utils/Utils.hpp"
#include <iomanip>                                                                              
#include <iostream> 

using namespace std;
using namespace fre;

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

    const vector<double>& Stock::getAR(void) const {
        return AR;
    }

    void Stock::setAnnouncementDate(string date) {
        announcementDate = converTime(date);
    }

    void Stock::findDay0(const string& annDate) {
        for (vector<Trade>::iterator itr = trades.begin(); itr != trades.end(); itr++) {
            if (itr->getDate() == annDate) {
                itr_Day0 = itr;
            }
        }
    }

    bool Stock::computeUsedData(int N) {
        //for (vector<Trade>::iterator itr = trades.begin(); itr != trades.end(); itr++) {
        //    if (itr->getDate() == announcementDate) {
        //        //itr_Day0 = itr;
        //        if (itr - trades.begin() < N || trades.end() - itr -1 < N) {
        //            return false;
        //        } else {
        //            for (auto itr2 = itr - N; itr2 <= itr + N; itr2++) {
        //                validTrades.push_back(*itr2);
        //            }
        //            return true;
        //        }
        //    }
        //}
        //return false;

        return _computeUsedData(N, announcementDate);
    }

    bool Stock::computeUsedData(int N, const string& annDate_) {
        return  _computeUsedData(N, annDate_);
    }

    bool Stock::_computeUsedData(int N, const string& annDate_) {
        findDay0(annDate_);
        if (itr_Day0 - trades.begin() < N || trades.end() - itr_Day0 - 1 < N) {
            return false;
        }
        else {
            for (auto itr2 = itr_Day0 - N; itr2 <= itr_Day0 + N; itr2++) {
                validTrades.push_back(*itr2);
            }
            return true;
        }
        return false;
    }

    void Stock::computeAR(int N, Stock& benchmark) {
        // assume Benchmark has all the date in stk.validTrades

        if (benchmark.computeUsedData(N, announcementDate)) {
            const vector<Trade> validT_BM = benchmark.getValidTrade();
            if (validTrades.size() != validT_BM.size())
                cout << "size of benchmark's historical data does not match the size of " << symbol << "'s data" << endl;

            for (int i = 1; i != validT_BM.size(); i++) {
                double R = validTrades[i].getAdjustedClose() - validTrades[i - 1].getAdjustedClose();
                double R_BM = validT_BM[i].getAdjustedClose() - validT_BM[i - 1].getAdjustedClose();
                AR.push_back(R - R_BM);
;            }
        }
        else {
            // error msg
            cout << "size of benchmark's historical data is not enough" << endl;
        }

    }

    void Stock::printValidTrade()const {
        cout << setw(13) << "Date" << "|";
        cout << setw(10) << "Open" << "|";
        cout << setw(10) << "Hige" << "|";
        cout << setw(10) << "Low" << "|";
        cout << setw(10) << "Close" << "|";
        cout << setw(10) << "Adj. Close" << "|";
        cout << setw(15) << "Volume" << endl;
        for (int i = 0; i < validTrades.size(); i++) {
            cout << validTrades[i];
        }
    }

}
