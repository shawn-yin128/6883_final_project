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

    bool Stock::findDay0(const string& annDate) {
        for (vector<Trade>::iterator itr = trades.begin(); itr != trades.end(); itr++) {
            if (itr->getDate() == annDate) {
                itr_Day0 = itr;
                return true;
            }
        }
        return false;
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
        valid = false;
        if (findDay0(annDate_)) {
            if (itr_Day0 - trades.begin() < N || trades.end() - itr_Day0 - 1 < N) {
                return false;
            }
            else {
                validTrades.clear();
                for (auto itr2 = itr_Day0 - N; itr2 <= itr_Day0 + N; itr2++) {
                    validTrades.push_back(*itr2);
                }
                valid = true;
                return true;
            }
        }
        return false;
    }

    void Stock::computeAR(int N, Stock& benchmark) {
        // assume Benchmark has all the date in stk.validTrades
        // compute cumulative daily return at the same time

        if (benchmark.computeUsedData(N, announcementDate)) {
            const vector<Trade> validT_BM = benchmark.getValidTrade();
            if (validTrades.size() != validT_BM.size())
                cerr << "size of benchmark's historical data does not match the size of " << symbol << "'s data" << endl;

            AR.clear();
            double init_close = validTrades[0].getAdjustedClose();
            validTrades[0].setcumDailyRet(0.0);
            for (int i = 1; i < validT_BM.size(); i++) {
                if (validTrades[i].getAdjustedClose() <= 0) { cout << symbol << endl; }
                // cumulative daily return
                validTrades[i].setcumDailyRet(validTrades[i].getAdjustedClose() / init_close - 1);

                double R = validTrades[i].getAdjustedClose() / validTrades[i - 1].getAdjustedClose() -1;
                double R_BM = validT_BM[i].getAdjustedClose() / validT_BM[i - 1].getAdjustedClose() -1;
                AR.push_back(R - R_BM);
;            }
        }
        else {
            // error msg
            cerr << "size of benchmark's historical data is not enough" << endl;
        }

    }

    void Stock::printValidTrades()const {
        string line(13 + 10 * 5 + 15+17, '_');
        cout << setw(13) << "Date" << "|";
        cout << setw(10) << "Open" << "|";
        cout << setw(10) << "Hige" << "|";
        cout << setw(10) << "Low" << "|";
        cout << setw(10) << "Close" << "|";
        cout << setw(10) << "Adj. Close" << "|";
        cout << setw(15) << "Cum. Daily Ret" << "|";
        cout << setw(15) << "Volume" << endl;
        cout << line << endl;
        for (int i = 0; i < validTrades.size(); i++) {
            cout << validTrades[i];
        }
    }
    void Stock::printTrades()const {
        string line(13 + 10 * 5 + 15, '_');
        cout << setw(13) << "Date" << "|";
        cout << setw(10) << "Open" << "|";
        cout << setw(10) << "Hige" << "|";
        cout << setw(10) << "Low" << "|";
        cout << setw(10) << "Close" << "|";
        cout << setw(10) << "Adj. Close" << "|";
        cout << setw(15) << "Volume" << endl;
        cout << line << endl;
        for (int i = 0; i < trades.size(); i++) {
            cout << trades[i];
        }
    }

    void Stock::printInfo() const {
        cout << "Stock Info " << endl;
        cout << setw(20) << "Symbol: " << symbol << endl;
        if (symbol != "IWV") {
            cout << setw(20) << "Announcement Date: " << announcementDate << endl;
            cout << setw(20) << "With valid data: " << valid << endl;
        }

    }

}
