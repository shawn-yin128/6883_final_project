#include <iostream>
#include "Utils/Utils.hpp"
#include "Utils/Parser.hpp"

using namespace std;
using namespace fre;

int main(int argc, const char * argv[]) {
    Parser parser("config_mac.csv");
    parser.LoadSymbol("Russell_3000_component_stocks.csv");
    parser.DownloadData();
    return 0;
}
