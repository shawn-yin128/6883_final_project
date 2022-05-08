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
#define WIDTH 12
    enum group_enum { miss_0, meet_1, beat_2 };

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

    vector<string> slicing(vector<string>& arr, int X, int Y);

    template<class key, class val>
    vector<key>& get_MapKeys(const map<key, val>& mp, vector<key>& mapKeys) {
        for (auto const& imap : mp)
            mapKeys.push_back(imap.first);
        return mapKeys;
    }
    
    //ostream& progressBar(ostream& out, int k, int N) {
    //    int barWidth = 70;
    //    double progress = (k + 1.0) / N;
    //    out << "[";
    //    int pos = barWidth * progress;
    //    for (int i = 0; i < barWidth; ++i) {
    //        if (i < pos) out << "=";
    //        else if (i == pos) out << ">";
    //        else out << " ";
    //    }
    //    out << "] " << int(progress * 100.0) << " %\r";
    //    out.flush();

    //    return out;
    //}
}

#endif /* Utils_hpp */
