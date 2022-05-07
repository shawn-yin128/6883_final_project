#include "Parser.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "curl/curl.h"
#include "Utils.hpp"
#include "../Models/Stock.hpp"

using namespace std;
using namespace fre;

namespace fre {
    int Parser::loadConfig(string configFile) {
        map<string, string> configMap = processConfigFile(configFile);
        apiToken = configMap["api_token"];
        if (!apiToken.empty() && apiToken[apiToken.length() - 1] == '\r') {
            apiToken.erase(apiToken.size() - 1);
        }
        urlCommon = configMap["url_common"];
        if (!urlCommon.empty() && urlCommon[urlCommon.length() - 1] == '\r') {
            urlCommon.erase(urlCommon.size() - 1);
        }
        startDate = configMap["start_date"];
        if (!startDate.empty() && startDate[startDate.length() - 1] == '\r') {
            startDate.erase(startDate.size() - 1);
        }
        endDate = configMap["end_date"];
        if (!endDate.empty() && endDate[endDate.length() - 1] == '\r') {
            endDate.erase(endDate.size() - 1);
        }
        return 0;
    }

    int Parser::loadSymbol(string configFile) {
        annMap = processAnnouncementFile(configFile);
        for (map<string, vector<string>>::iterator itr = annMap.begin(); itr != annMap.end(); itr++) {
            symbolVector.push_back(itr->first);
        }
        symbolVector.push_back("IWV");
        return 0;
    }

    int Parser::loadSymbol(vector<string> symbols) {
        symbolVector = symbols;
        return 0;
    }

    int Parser::downloadData() {
        curl_global_init(CURL_GLOBAL_ALL);
        CURL * handle;
        CURLcode result;
        handle = curl_easy_init();
        if (!handle) {
            cout << "curl_easy_init failed" << endl;
            return -1;
        }
        for (int i = 0; i < symbolVector.size(); i++) {
            string urlRequest = urlCommon + symbolVector[i] + ".US?" + "from=" + startDate + "&to=" + endDate + "&api_token=" + apiToken + "&period=d";
            string readBuffer;
            curl_easy_setopt(handle, CURLOPT_URL, urlRequest.c_str());
            curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, &readBuffer);
            result = curl_easy_perform(handle);
            plainData[symbolVector[i]] = readBuffer;
            cout << symbolVector[i] << " has been downloaded." << endl;
        }
        curl_easy_cleanup(handle);
        return 0;
    }

    map<string, Stock> Parser::populateDate() {
        map<string, Stock> Stocks;
        for (string str : symbolVector) {
            Stock stock(str);
            vector<string> dailyData = split(plainData[str], '\n'); // daily
            if (str != "IWV") {
                stock.setAnnouncementDate(annMap[str][0]);
            }
            int count = 0;
            for (string data : dailyData) {
                if (count == 0) {
                    count++;
                    continue;
                }
                vector<string> fields = split(data, ',');
                if (fields.size() == 1) {
                    continue;
                }
                string date = fields[0];
                float open = stof(fields[1]);
                float high = stof(fields[2]);
                float low = stof(fields[3]);
                float close = stof(fields[4]);
                float adjClose = stof(fields[5]);
                int volume = stoi(fields[6]);
                Trade trade(date, open, high, low, close, adjClose, volume);
                stock.addTrade(trade);
                count++;
            }
            if (str == "IWV") {
                IWV = stock;
            } else {
                Stocks[str] = stock;
            }
        }
        return Stocks;
    }

    // setter
    void Parser::setData(map<string, string> data) {
        plainData = data;
    }
}
