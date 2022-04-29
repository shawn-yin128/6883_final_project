#include "Trade.hpp"


namespace fre {
    float Trade::GetOpen() const { return Open; }
    float Trade::GetHigh() const { return High; }
    float Trade::GetLow() const { return Low; }
    float Trade::GetClose() const { return Close; }
    int Trade::GetVolume() const { return Volume; }
    string Trade::GetDate() const { return Date; }
    float Trade::GetAdjustedClose() const { return AdjClose; }
}
