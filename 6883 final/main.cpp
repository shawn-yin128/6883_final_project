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

int main(int argc, const char * argv[]) {
    int selection;
    const string MENU = string("Menu\n")
    + "====================\n"
    + "1 - Enter N to retrieve 2N+1 days of historical price data for all stocks.\n"
    + "2 - Pull information for one stock from one group.\n"
    + "3 - Show AAR, AAR-STD, CAAR and CAAR-STD for one group.\n"
    + "4 - Plot Avg CAAR for 3 groups.\n"
    + "5 - Plot STD CAAR for 3 groups.\n"
    + "6 - Plot Avg AAR for 3 groups.\n"
    + "7 - Plot STD AAR for 3 groups.\n"
    + "8 - Exit.\n\n";
    
    cout << MENU;
    
    map<string, Stock> stocks;
    map<string, Stock> validStocks;

    bool run = 1;
    while (run) {
        cout << "Please enter your choice and press return: ";
        cin >> selection;
        switch (selection) {
            case 1: {
                int N;
                cout << "Please enter N: ";
                cin >> N;
                Parser parser(CONFIG);
                parser.LoadSymbol(ANNOUNCEMENT);
                parser.DownloadData();
                stocks = parser.PopulateDate(ANNOUNCEMENT);
                for (map<string, Stock>::iterator itr = stocks.begin(); itr != stocks.end(); itr++) {
                    if (itr->second.computeUsedData(N)) {
                        validStocks[itr->second.getSymbol()] = itr->second;
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
