#include <iostream>
#include <map>
#include <vector>
#include <time.h>
#include "Utils/Utils.hpp"
#include "Utils/Parser.hpp"

using namespace std;
using namespace fre;

const string CONFIG = "config_mac.csv";
const string SYMBOL = "Russell_3000_component_stocks.csv";
const string ANNOUNCEMENT = "Russell3000EarningsAnnouncements.csv";

int main(void) {
    int selection;
    const string MENU = string("Menu\n")
    + "===========================================================================\n"
    + "1 - Enter N to retrieve 2N+1 days of historical price data for all stocks.\n"
    + "2 - Pull information for one stock from one group.\n"
    + "3 - Show AAR, AAR-STD, CAAR and CAAR-STD for one group.\n"
    + "4 - Plot Avg CAAR for 3 groups.\n"
    + "5 - Plot STD CAAR for 3 groups.\n"
    + "6 - Plot Avg AAR for 3 groups.\n"
    + "7 - Plot STD AAR for 3 groups.\n"
    + "8 - Exit.\n";
    
    cout << MENU;
    
    map<string, Stock> beat;
    map<string, Stock> miss;
    map<string, Stock> meet;
    Stock IWV;

    bool run = 1;
    while (run) {
        cout << "===========================================================================\nPlease enter your choice and press return: ";
        cin >> selection;
        switch (selection) {
            case 1: {
                map<string, Stock> stocks;
                map<string, Stock> validStocks;
                map<string, vector<string>> annMap;
                map<string, float> surpriseMap;
                
                int N;
                cout << "Please enter N: ";
                cin >> N;
                
                // parse all data and 2N+1 interval data
                Parser parser(CONFIG);
                parser.loadSymbol(ANNOUNCEMENT);
                parser.downloadData();
                stocks = parser.populateDate();
                IWV = parser.getIWV();
                for (map<string, Stock>::iterator itr = stocks.begin(); itr != stocks.end(); itr++) {
                    if (itr->second.computeUsedData(N)) {
                        validStocks[itr->second.getSymbol()] = itr->second;
                    }
                }
                
                // sort and group
                annMap = parser.getAnnMap();
                for (map<string, Stock>::iterator itr = validStocks.begin(); itr != validStocks.end(); itr++) {
                    string symbol = itr->first;
                    string surprise = annMap[symbol][5];
                    if (!surprise.empty() && surprise[surprise.length() - 1] == '\r') {
                        surprise.erase(surprise.size() - 1);
                    }
                    surpriseMap[symbol] = stod(surprise);
                }
                vector<string> orderedStocks = sort(surpriseMap);
                for (int i = 0; i < orderedStocks.size(); i++) {
                    if (i < orderedStocks.size()/3) {
                        miss[orderedStocks[i]] = validStocks[orderedStocks[i]];
                    } else if (i >= orderedStocks.size()/3 && i < 2*orderedStocks.size()/3) {
                        meet[orderedStocks[i]] = validStocks[orderedStocks[i]];
                    } else {
                        beat[orderedStocks[i]] = validStocks[orderedStocks[i]];
                    }
                }
                break;
            }
            case 2: {
                
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                cout << "Program shut down, bye." << endl;
                run = 0;
                break;
            }
            default: {
                cout << "Input invalid selection, please re-enter." << endl;
                break;
            }
        }
    }
    
    return 0;
}
