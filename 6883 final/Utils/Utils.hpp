#ifndef Utils_hpp
#define Utils_hpp

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace fre {
    bool cmp(pair<string, float> a, pair<string, float> b);
    vector<string> sort(map<string, float> M);

    string converTime(string date);
    vector<string> split(string text, char delim);

    size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);

    map<string, string> processConfigFile(string configFile);
    vector<string> processSymbolFile(string configFile);
    map<string, vector<string>> processAnnouncementFile(string configFile);

    vector<string> bootstrapping(vector<string> symbols, int size);
}

#endif /* Utils_hpp */
