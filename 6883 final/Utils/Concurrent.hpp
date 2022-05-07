#ifndef Concurrent_hpp
#define Concurrent_hpp

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "Parser.hpp"
#include "Utils.hpp"

using namespace std;

namespace fre {
    class ConcurrentParser {
    public:
        void operator()(string configFile, vector<string> symbols, map<string, string>* dataMap) {
            Parser parser(configFile);
            parser.loadSymbol(symbols);
            parser.downloadData();
            *dataMap = parser.getData();
        }
    };

    class ConcurrentDownloader {
    public:
        map<string, string> dataMap[7];
        map<string, string> plainData;
        void parse(string configFile, vector<string> symbols);
        map<string, Stock> populate(string configFile, string annFile);
    };
}

#endif /* ConcurrentParser_hpp */
