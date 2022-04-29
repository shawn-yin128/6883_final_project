#ifndef Trade_hpp
#define Trade_hpp

#include <iostream>
#include <string>

using namespace std;

namespace fre {
    class Trade {
        protected:
            string Date;
            float Open;
            float High;
            float Low;
            float Close;
            float AdjClose;
            int Volume;
        public:
            Trade(string date_, float open_, float high_, float low_, float close_, float adjusted_close_, int volume_): Date(date_), Open(open_), High(high_), Low(low_), Close(close_), AdjClose(adjusted_close_), Volume(volume_) {}
            ~Trade() {}
        
            // getter
            float GetOpen() const;
            float GetHigh() const;
            float GetLow() const;
            float GetClose() const;
            int GetVolume() const;
            string GetDate() const;
            float GetAdjustedClose() const;
    };
}


#endif /* Trade_hpp */
