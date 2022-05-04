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
            int N;
            bool enough = false;
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
        
            void setN(int N_) {N = N_;}
        
            void addTrade(const Trade& aTrade);

            const vector<Trade>& getTrade(void) const;
    };
}


#endif /* Stock_hpp */
