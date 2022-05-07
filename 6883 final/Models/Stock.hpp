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
            float estimatedEarnings;
            float reportedEarnings;
            float suprise;
            float suprise_pct;
            string group;

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
                estimatedEarnings = stock.estimatedEarnings;
                reportedEarnings = stock.reportedEarnings;
                suprise = stock.suprise;
                suprise_pct = stock.suprise_pct;
                group = stock.group;

                trades = stock.trades;
                validTrades = stock.validTrades;
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
            void setEstimatedEarnings(float estimatedEarnings_) { estimatedEarnings = estimatedEarnings_; }
            void setReportedEarnings(float reportedEarnings_) { reportedEarnings = reportedEarnings_; }
            void setSuprise(float suprise_) { suprise = suprise_; }
            void setSuprise_pct(float suprise_pct_) { suprise_pct = suprise_pct_; }
            void setGroup(string group_) { group = group_; }

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
