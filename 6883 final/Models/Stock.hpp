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
            vector<Trade> Trades;
            vector<Trade> used_trades;
        public:
            Stock() : symbol("") {
                Trades.clear();
            }
            Stock(string symbol_) : symbol(symbol_) {
                Trades.clear();
            }
            Stock(const Stock& stock) {
                memcpy(this, &stock, sizeof(stock));
            }
            ~Stock() {}
        
            void setAnnouncementDate(string date);
        
            void addTrade(const Trade& aTrade);
        
            const string getSymbol(void) const;

            const vector<Trade>& getTrade(void) const;
        
            const vector<Trade>& getUsedTrade(void) const;
        
            bool computeUsedData(int N);
    };
}


#endif /* Stock_hpp */
