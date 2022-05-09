#include "Utils.hpp"
#include "../Models/Stock.hpp"
#include "../Models/Model.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

namespace fre {

    bool cmp(pair<string, float> a, pair<string, float> b) {
        return a.second < b.second;
    }

    vector<string> sort(map<string, float> M) {
        vector<pair<string, float> > A;
        for (auto& it : M) {
            A.push_back(it);
        }
        sort(A.begin(), A.end(), cmp);
        vector<string> res;
        for (auto& it : A) {
            res.push_back(it.first);
        }
        return res;
    }

    string converTime(string date) {
        vector<string> dmy = split(date, '-');
        map<string, string> monthMap = {{"JAN", "01"}, {"FEB", "02"}, {"MAR", "03"}, {"APR", "04"}, {"MAY", "05"}, {"JUN", "06"}, {"JUL", "07"}, {"AUG", "08"}, {"SEP", "09"}, {"OCT", "10"}, {"NOV", "11"}, {"DEC", "12"}};
        string day = dmy[0].size() == 1 ? "0"+dmy[0] : dmy[0];
        string month = monthMap[stringCapitalize(dmy[1])];
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

    size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    map<string, string> processConfigFile(string configFile) {
        map<string, string> configMap;
        ifstream fin;
        fin.open(configFile, ios::in);
        string line, name, value;
        while (!fin.eof()) {
            getline(fin, line);
            stringstream sin(line);
            getline(sin, name, ':');
            getline(sin, value);
            configMap.insert(pair<string, string>(name, value));
        }
        return configMap;
    }

    vector<string> processSymbolFile(string configFile) {
        vector<string> symbolVector;
        map<string, vector<string>> annMap = processAnnouncementFile(configFile);
        for (map<string, vector<string>>::iterator itr = annMap.begin(); itr != annMap.end(); itr++) {
            symbolVector.push_back(itr->first);
        }
        return symbolVector;
    }

    map<string, vector<string>> processAnnouncementFile(string configFile) {
        map<string, vector<string>> annMap;
        ifstream fin;
        fin.open(configFile, ios::in);
        string line, symbol, date, periodEnding, estimate, reported, surprise, surprisePct;
        getline(fin, line);
        while (!fin.eof()) {
            vector<string> factors;
            getline(fin, line);
            stringstream sin(line);
            getline(sin, symbol, ',');
            getline(sin, date, ',');
            factors.push_back(date);
            getline(sin, periodEnding, ',');
            factors.push_back(periodEnding);
            getline(sin, estimate, ',');
            factors.push_back(estimate);
            getline(sin, reported, ',');
            factors.push_back(reported);
            getline(sin, surprise, ',');
            factors.push_back(surprise);
            getline(sin, surprisePct);
            factors.push_back(surprisePct);
            if (symbol.empty()) {
                continue;
            }
            stringCapitalize(symbol);       // Ensure all symbol are in upper case
            annMap[symbol] = factors;
        }
        return annMap;
    }

    string& stringCapitalize(string& str) {
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }

    vector<string> slicing(vector<string>& arr, int X, int Y) {
        auto start = arr.begin() + X;
        auto end = arr.begin() + Y + 1;
     
        vector<string> result(Y - X + 1);
        copy(start, end, result.begin());

        return result;
    }
}
