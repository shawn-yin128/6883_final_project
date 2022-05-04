#ifndef Utils_hpp
#define Utils_hpp

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace fre {
    string converTime(string date);
    vector<string> split(string text, char delim);
    size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    map<string, string> ProcessConfigFile(string config_file_name);
    vector<string> ProcessSymbolFile(string config_file_name);
    map<string, vector<string>> ProcessAnnouncementFile(string announcement_file_name);
    vector<string> Bootstrapping(vector<string> symbols, int size);
}

#endif /* Utils_hpp */
