#ifndef Trade_hpp
#define Trade_hpp

#include <iostream>
#include <string>

using namespace std;

namespace fre {
    class Trade {
        protected:
            string date;
            float open;
            float high;
            float low;
            float close;
            float adjClose;
            int volume;
        public:
            Trade(string date_, float open_, float high_, float low_, float close_, float adjustedClose_, int volume_): date(date_), open(open_), high(high_), low(low_), close(close_), adjClose(adjustedClose_), volume(volume_) {}
            ~Trade() {}
        
            // getter
            float getOpen() const;
            float getHigh() const;
            float getLow() const;
            float getClose() const;
            int getVolume() const;
            string getDate() const;
            float getAdjustedClose() const;
    };
}


#endif /* Trade_hpp */
