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
    int Parser::LoadConfig(string config_file_name) {
        map<string, string> config_map = ProcessConfigFile(config_file_name);
        API_token = config_map["api_token"];
        URL_common = config_map["url_common"];
        Start = config_map["start_date"];
        End = config_map["end_date"];
        return 0;
    }

    int Parser::LoadSymbol(string symbol_file_name) {
        map<string, vector<string>> annMap = ProcessAnnouncementFile(symbol_file_name);
        for (map<string, vector<string>>::iterator itr = annMap.begin(); itr != annMap.end(); itr++) {
            Symbol.push_back(itr->first);
        }
        return 0;
    }

    int Parser::multithreadLoadSymbol(vector<string> symbols) {
        Symbol = symbols;
        return 0;
    }

    int Parser::DownloadData() {
        curl_global_init(CURL_GLOBAL_ALL);
        CURL * handle;
        CURLcode result;
        handle = curl_easy_init();
        if (!handle) {
            cout << "curl_easy_init failed" << endl;
            return -1;
        }
        for (int i = 0; i < Symbol.size(); i++) {
            string url_request = URL_common + Symbol[i] + ".US?" + "from=" + Start + "&to=" + End + "&api_token=" + API_token + "&period=d";
            string read_buffer;
            curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
            curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, &read_buffer);
            result = curl_easy_perform(handle);
            Data[Symbol[i]] = read_buffer;
            cout << Symbol[i] << " has been downloaded." << endl;
        }
        curl_easy_cleanup(handle);
        return 0;
    }

    map<string, Stock> Parser::PopulateDate(string symbol_file_name) {
        map<string, Stock> Stocks;
        map<string, vector<string>> annMap = ProcessAnnouncementFile(symbol_file_name);
        for (string str : Symbol) {
            cout << str << endl;
            Stock stock(str);
            vector<string> dailyData = split(Data[str], '\n'); // daily
            stock.setAnnouncementDate(annMap[str][1]);
            for (string data : dailyData) {
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
            }
            Stocks[str] = stock;
        }
        return Stocks;
    }

    void Parser::ShowData() {
        for (map<string, string>::iterator itr = Data.begin(); itr != Data.end(); itr++) {
            cout << itr -> first << endl << itr -> second << endl;
        }
    }
}
