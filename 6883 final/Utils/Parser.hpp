#ifndef Parser_hpp
#define Parser_hpp

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace fre {
    class Parser {
        private:
            // in config file
            string API_token;
            string URL_common;
            
            // user input
            vector<string> Symbol;
            string Start;
            string End;
            
            // plain data
            map<string, string> Data;
        
            // constructor that should not be used;
            Parser() {}
            Parser(const Parser& parser) {}
            
        public:
            // constructor with config file
            Parser(string config_file) {
                LoadConfig(config_file);
            }
            
            // load config
            // set api and url
            int LoadConfig(string config_file_name);
            // set symbols after bootstrapping
            int LoadSymbol(string symbol_file_name);
        
            // download data
            int DownloadData();
    };
}

#endif /* Parser_hpp */
