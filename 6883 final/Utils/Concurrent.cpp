#include "Concurrent.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "Parser.hpp"
#include "Utils.hpp"

using namespace std;

namespace fre {
    void ConcurrentDownloader::parse(string configFile, vector<string> symbols) {
        thread parser1(ConcurrentParser(), configFile, slicing(symbols, 0, symbols.size()/THREAD_NUMBER), &dataMap[0],false);
        thread parser2(ConcurrentParser(), configFile, slicing(symbols, symbols.size()/THREAD_NUMBER + 1, 2 * symbols.size()/THREAD_NUMBER), &dataMap[1],false);
        thread parser3(ConcurrentParser(), configFile, slicing(symbols, 2 * symbols.size()/THREAD_NUMBER + 1, symbols.size() - 1), &dataMap[2], true);
        
        parser1.join();
        parser2.join();
        parser3.join();
    }

    map<string, Stock> ConcurrentDownloader::populate(string configFile, string annFile) {
        plainData = dataMap[0];
        for (int i = 1; i < THREAD_NUMBER; i++) {
            plainData.insert(dataMap[i].begin(), dataMap[i].end());
        }
        Parser parser(configFile);
        parser.loadSymbol(annFile);
        parser.setData(plainData);
        map<string, Stock> stocks = parser.populateDate();
        return stocks;
    }
}
