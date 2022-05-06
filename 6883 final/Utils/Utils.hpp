#ifndef Utils_hpp
#define Utils_hpp

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

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


    template <typename VEC>
    VEC sampling_NoReplace(VEC& group, int k) {
        if (k <= 0)
            cerr << "sampling_NoReplace: Invalid value k" << endl;

        srand((unsigned)time(NULL));
        int n = group.size();
        vector<int> ind(n);
        for (int i = 0; i < n; i++)
            ind[i] = i;

        int pos;
        VEC stocks;
        for (int i = 0; i < k; i++) {
            pos = rand() % (n - i);
            if (pos != 0)
                iter_swap(ind.begin() + i, ind.begin() + i + pos);
            stocks.push_back(*(group.begin() + ind[i]));
        }
        return stocks;
    }

    string& stringCapitalize(string& str);
}

#endif /* Utils_hpp */