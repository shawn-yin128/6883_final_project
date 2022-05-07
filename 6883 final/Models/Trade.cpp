#include "Trade.hpp"
#include <iomanip>                                                                              

namespace fre {
    float Trade::getOpen() const { return open; }
    float Trade::getHigh() const { return high; }
    float Trade::getLow() const { return low; }
    float Trade::getClose() const { return close; }
    int Trade::getVolume() const { return volume; }
    string Trade::getDate() const { return date; }
    float Trade::getAdjustedClose() const { return adjClose; }

    // Overload cout for trade
    ostream& operator<<(ostream& out, const Trade& trade) {
        out << fixed << setprecision(2);
        out << setw(13) << trade.date << "|" ;
        out << setw(10) << trade.open << "|" ;
        out << setw(10) << trade.high << "|";
        out << setw(10) << trade.low << "|";
        out << setw(10) << trade.close << "|";
        out << setw(10) << trade.adjClose << "|";
        if (trade.cumDailyRet != 99.99) {
            out << setw(15) << trade.cumDailyRet << "|";
        }
        out << setw(15) << trade.volume << endl;
        return out;
    }

}
