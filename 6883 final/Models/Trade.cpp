#include "Trade.hpp"

namespace fre {
    float Trade::getOpen() const { return open; }
    float Trade::getHigh() const { return high; }
    float Trade::getLow() const { return low; }
    float Trade::getClose() const { return close; }
    int Trade::getVolume() const { return volume; }
    string Trade::getDate() const { return date; }
    float Trade::getAdjustedClose() const { return adjClose; }
}
