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
        thread parser1(ConcurrentParser(), configFile, slicing(symbols, 0, symbols.size()/7), &dataMap[0]);
        thread parser2(ConcurrentParser(), configFile, slicing(symbols, symbols.size()/7 + 1, 2*symbols.size()/7), &dataMap[1]);
        thread parser3(ConcurrentParser(), configFile, slicing(symbols, 2*symbols.size()/7 + 1, 3*symbols.size()/7), &dataMap[2]);
        thread parser4(ConcurrentParser(), configFile, slicing(symbols, 3*symbols.size()/7 + 1, 4*symbols.size()/7), &dataMap[3]);
        thread parser5(ConcurrentParser(), configFile, slicing(symbols, 4*symbols.size()/7 + 1, 5*symbols.size()/7), &dataMap[4]);
        thread parser6(ConcurrentParser(), configFile, slicing(symbols, 5*symbols.size()/7 + 1, 6*symbols.size()/7), &dataMap[5]);
        thread parser7(ConcurrentParser(), configFile, slicing(symbols, 6*symbols.size()/7 + 1, symbols.size() - 1), &dataMap[6]);
        
        parser1.join();
        parser2.join();
        parser3.join();
        parser4.join();
        parser5.join();
        parser6.join();
        parser7.join();
    }

    map<string, Stock> ConcurrentDownloader::populate(string configFile, string annFile) {
        plainData = dataMap[0];
        for (int i = 1; i < 7; i++) {
            plainData.insert(dataMap[i].begin(), dataMap[i].end());
        }
        Parser parser(configFile);
        parser.loadSymbol(annFile);
        parser.setData(plainData);
        map<string, Stock> stocks = parser.populateDate();
        return stocks;
    }
}
