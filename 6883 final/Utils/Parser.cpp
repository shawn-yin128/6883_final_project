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
        Symbol = ProcessSymbolFile(symbol_file_name);
        return 0;
    }

    int Parser::DownloadData() {
        for (int i = 0; i < Symbol.size(); i++) {
            cout << i << endl;
            string url_request = URL_common + Symbol[i] + ".US?" + "from=" + Start + "&to=" + End + "&api_token=" + API_token + "&period=d";
            string read_buffer;
            curl_global_init(CURL_GLOBAL_ALL);
            CURL * handle;
            CURLcode result;
            handle = curl_easy_init();
            if (!handle) {
                cout << "curl_easy_init failed" << endl;
                return -1;
            }
            curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
            curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, &read_buffer);
            result = curl_easy_perform(handle);
            if (result != CURLE_OK) {
                return -1;
            }
            curl_easy_cleanup(handle);
            Data[Symbol[i]] = read_buffer;
        }
        return 0;
    }

    vector<Stock> Parser::PopulateDate() {
        vector<Stock> Stocks;
        return Stocks;
    }

    void Parser::ShowData() {
        for (map<string, string>::iterator itr = Data.begin(); itr != Data.end(); itr++) {
            cout << itr -> first << endl << itr -> second << endl;
        }
    }
}
