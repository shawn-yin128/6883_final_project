#ifndef Stock_hpp
#define Stock_hpp

#include <string>
#include <vector>
#include "Trade.hpp"

using namespace std;
using namespace fre;

namespace fre {
    class Stock {
        private:
            string symbol;
            string announcementDate;
            vector<Trade> trades;
            vector<Trade> validTrades;
            vector<double> AR;
            vector<Trade>::iterator itr_Day0;
            bool valid = false;

            bool findDay0(const string& annDate);
            bool _computeUsedData(int N, const string& annDate);

        public:
            Stock() : symbol("") {
                trades.clear();
            }
            Stock(string symbol_) : symbol(symbol_) {
                trades.clear();
            }
            Stock(const Stock& stock) {
                symbol = stock.symbol;
                announcementDate = stock.announcementDate;
                validTrades = stock.validTrades;
                trades = stock.trades;
                AR = stock.AR;
                valid = stock.valid;
                itr_Day0 = stock.itr_Day0;
            }
            ~Stock() {}
        
            void addTrade(const Trade& aTrade);
        
            bool computeUsedData(int N);
            bool computeUsedData(int N, const string& annDate);
            void computeAR(int N,Stock& benchmark);

            // setter
            void setAnnouncementDate(string date);
        
            // getter
            const string getSymbol(void) const;
            const string getAnnouncementDate(void) const { return announcementDate; };
            const vector<Trade>& getTrades(void) const;
            const vector<Trade>& getValidTrade(void) const;
            const vector<double>& getAR(void) const;
            void printValidTrades()const;
            void printTrades()const;
            void printInfo() const;
    };
}


#endif /* Stock_hpp */
