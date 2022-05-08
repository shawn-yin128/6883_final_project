#ifndef Parser_hpp
#define Parser_hpp

#include <string>
#include <vector>
#include <map>
#include "../Models/Stock.hpp"
#include "Utils.hpp"

using namespace std;

namespace fre {
    class Parser {
        private:
            // in config file
            string apiToken;
            string urlCommon;
            
            // user input
            vector<string> symbolVector;
            string startDate;
            string endDate;
            
            // plain data
            map<string, string> plainData;
        
            // IWV
            Stock IWV;
        
            // store announcement data
            map<string, vector<string>> annMap;
            
            // constructor that should not be used;
            Parser() {}
            Parser(const Parser& parser) {}
            
        public:
            // constructor with config file
            Parser(string configFile) {
                loadConfig(configFile);
            }
            ~Parser(){}
            
            // load config
            // set api and url
            int loadConfig(string configFile);
            // set symbols after bootstrapping
            int loadSymbol(string configFile);
            int loadSymbol(vector<string> symbols);
        
            // download data
            int downloadData(bool print);
        
            // populate data
            map<string, Stock> populateDate();
        
            // setter
            void setData(map<string, string> data);
        
            // getter
            map<string, string> getData() {return plainData;}
            vector<string> getSymbol() {return symbolVector;}
            Stock getIWV() {return IWV;}
            map<string, vector<string>> getAnnMap() {return annMap;}
    };
}

#endif /* Parser_hpp */
