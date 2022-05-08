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
    const int THREAD_NUMBER = 3;
    class ConcurrentParser {
    public:
        void operator()(string configFile, vector<string> symbols, map<string, string>* dataMap, bool print) {
            Parser parser(configFile);
            parser.loadSymbol(symbols);
            parser.downloadData(print);
            *dataMap = parser.getData();
        }
    };

    class ConcurrentDownloader {
    public:
        map<string, string> dataMap[THREAD_NUMBER];
        map<string, string> plainData;
        void parse(string configFile, vector<string> symbols);
        map<string, Stock> populate(string configFile, string annFile);
    };
}

#endif /* ConcurrentParser_hpp */
