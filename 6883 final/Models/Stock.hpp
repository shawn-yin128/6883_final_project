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
            vector<Trade> AR;

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
                trades = stock.trades;
                validTrades = stock.validTrades;
            }
            ~Stock() {}
        
            void addTrade(const Trade& aTrade);
        
            bool computeUsedData(int N);
            
            // setter
            void setAnnouncementDate(string date);
        
            // getter
            const string getSymbol(void) const;
<<<<<<< HEAD
            const vector<Trade>& getTrades(void) const;
            const vector<Trade>& getValidTrade(void) const;
            const vector<Trade>& getAR(void) const;
=======
            const vector<Trade> getTrades(void) const;
            const vector<Trade> getValidTrade(void) const;
>>>>>>> a7da60818e7c719a4ba530cfff941e3a82ef2af5
    };
}


#endif /* Stock_hpp */
