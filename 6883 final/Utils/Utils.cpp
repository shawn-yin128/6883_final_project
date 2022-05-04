#include "Utils.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace fre {
    string converTime(string date) {
        vector<string> dmy = split(date, '-');
        map<string, string> monthMap = {{"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, {"Apr", "04"}, {"May", "05"}, {"Jun", "06"}, {"Jul", "07"}, {"Aug", "08"}, {"Sep", "09"}, {"Oct", "10"}, {"Nov", "11"}, {"Dec", "12"}};
        string day = dmy[0].size() == 1 ? "0"+dmy[0] : dmy[0];
        string month = monthMap[dmy[1]];
        string year = "20"+dmy[2];
        return year + "-" + month + "-" + day;
    }

    vector<string> split(string text, char delim) {
        string line;
        vector<string> vec;
        stringstream ss(text);
        while (std::getline(ss, line, delim)) {
            vec.push_back(line);
        }
        return vec;
    }

    size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    map<string, string> ProcessConfigFile(string config_file_name) {
        map<string, string> config_map;
        ifstream fin;
        fin.open(config_file_name, ios::in);
        string line, name, value;
        while (!fin.eof()) {
            getline(fin, line);
            stringstream sin(line);
            getline(sin, name, ':');
            getline(sin, value);
            config_map.insert(pair<string, string>(name, value));
        }
        return config_map;
    }

    vector<string> ProcessSymbolFile(string symbol_file_name) {
        vector<string> symbol_vector;
        ifstream fin;
        fin.open(symbol_file_name, ios::in);
        string line, symbol, description;
        while (!fin.eof()) {
            getline(fin, line);
            stringstream sin(line);
            getline(sin, symbol, ',');
            getline(sin, description);
            symbol_vector.push_back(symbol);
        }
        return symbol_vector;
    }

    map<string, vector<string>> ProcessAnnouncementFile(string announcement_file_name) {
        map<string, vector<string>> announcement_map;
        ifstream fin;
        fin.open(announcement_file_name, ios::in);
        string line, symbol, date, period_ending, estimate, reported, surprise, surprise_pct;
        getline(fin, line);
        while (!fin.eof()) {
            vector<string> factors;
            getline(fin, line);
            stringstream sin(line);
            getline(sin, symbol, ',');
            getline(sin, date, ',');
            factors.push_back(date);
            getline(sin, period_ending, ',');
            factors.push_back(period_ending);
            getline(sin, estimate, ',');
            factors.push_back(estimate);
            getline(sin, reported, ',');
            factors.push_back(reported);
            getline(sin, surprise, ',');
            factors.push_back(surprise);
            getline(sin, surprise_pct);
            factors.push_back(surprise_pct);
            if (symbol.empty()) {
                continue;
            }
            announcement_map[symbol] = factors;
        }
        return announcement_map;
    }

    vector<string> Bootstrapping(vector<string> symbols, int size) {
        vector<string> bootstrapping_symbols;
        for (int i = 0; i < size; i++) {
            bootstrapping_symbols.push_back(symbols[rand() % symbols.size()]);
        }
        return bootstrapping_symbols;
    }
}
