#include <iostream>
#include <map>
#include <vector>
#include "Utils/Utils.hpp"
#include "Utils/Parser.hpp"

using namespace std;
using namespace fre;

int main(int argc, const char * argv[]) {
    Parser parser("config_mac.csv");
    parser.LoadSymbol("Russell_3000_component_stocks.csv");
    parser.DownloadData();
    map<string, string> data = parser.getData();
    vector<string> symbol = parser.getSymbol();
    for (map<string, string>::iterator itr = data.begin(); itr != data.end(); itr++) {
        cout << itr->first << endl;
    }
    return 0;
}
