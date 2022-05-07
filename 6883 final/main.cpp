#include <iostream>
#include <map>
#include <vector>
#include <time.h>
#include "Utils/Utils.hpp"
#include "Utils/Parser.hpp"
#include "Utils/Concurrent.hpp"
#include "Models/Model.h"
#include "Models/Stock.hpp"
#include "Models/Trade.hpp"

using namespace std;
using namespace fre;

const string CONFIG = "config_mac.csv";
const string SYMBOL = "Russell_3000_component_stocks.csv";
const string ANNOUNCEMENT = "Russell3000EarningsAnnouncements.csv";
// const string ANNOUNCEMENT = "Russell3000EarningsAnnouncements_test.csv";

int main(void) {
    srand((unsigned)time(NULL));
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
    + "8 - Exit.\n"
    + "9 - Print stock list of specific group with surprise.\n";
    
    
/*    map<string, Stock> beat;
    map<string, Stock> miss;
    map<string, Stock> meet;  */  
    vector<string> beat;
    vector<string> miss;
    vector<string> meet;
    Stock IWV;
    map<string, Stock> stocks;
    map<string, Stock> validStocks;
    map<string, vector<string>> annMap;
    map<string, float> surpriseMap;
    int N,M, K;

    bool run = 1;
    while (run) {
        cout << MENU;
        cout << "===========================================================================\nPlease enter your choice and press return: ";
        cin >> selection;
        switch (selection) {
            case 1: {
                
                cout << "Please enter N: ";
                cin >> N;
                
                // parse all data and 2N+1 interval data
                Parser parser(CONFIG);
                vector<string> iwv;
                iwv.clear();
                iwv.push_back("IWV");
                parser.loadSymbol(iwv);
                parser.downloadData();
                parser.populateDate();         // change from string to Stock
                IWV = parser.getIWV();
                
                ConcurrentDownloader concurrentDownloader;
                vector<string> symbols = processSymbolFile(SYMBOL);
                concurrentDownloader.parse(CONFIG, symbols);
                stocks = concurrentDownloader.populate(CONFIG, ANNOUNCEMENT);
                
                for (map<string, Stock>::iterator itr = stocks.begin(); itr != stocks.end(); itr++) {
                    if (itr->second.computeUsedData(N)) {
                        itr->second.computeAR(N, IWV);
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
                int size_oStk = orderedStocks.size();
                cout << "Total number of stocks: " << size_oStk << endl;
                miss.clear();
                meet.clear();
                beat.clear();
                miss.assign(orderedStocks.begin(), orderedStocks.begin() + size_oStk / 3 );
                meet.assign(orderedStocks.begin() + size_oStk / 3 , orderedStocks.begin() + size_oStk / 3 * 2 );
                beat.assign(orderedStocks.begin() + size_oStk / 3 * 2 , orderedStocks.end());
                //for (int i = 0; i < orderedStocks.size(); i++) {
                //    if (i < orderedStocks.size()/3) {
                //        miss[orderedStocks[i]] = validStocks[orderedStocks[i]];
                //    } else if (i >= orderedStocks.size()/3 && i < 2*orderedStocks.size()/3) {
                //        meet[orderedStocks[i]] = validStocks[orderedStocks[i]];
                //    } else {
                //        beat[orderedStocks[i]] = validStocks[orderedStocks[i]];
                //    }
                //}

                break;
            }
            case 2: {
            Peak1Stock:

                string ticker;
                cout << "Please enter Ticker or enter 0 to return Menu: ";
                cin >> ticker;
                if (ticker == "0") break;
                stringCapitalize(ticker);           // Ensure user input in uppercase
                try {
                    if (ticker == "IWV") {
                        IWV.printTrades();
                    }
                    else {
                        validStocks.at(ticker).printInfo();
                        validStocks.at(ticker).printValidTrades();
                    }
                }
                catch (const out_of_range& oor) {
                    cout <<ticker << " is not a valid stock. " << endl;
                    goto Peak1Stock;
                }

                break;
            }
            case 3: {
                // Model calculation
                cout << "Please enter M - number of stocks picked in each group or enter 0 to return Menu: ";
                cin >> M;
                if (M == 0) break;

                cout << "Please enter K - number of times of bootstrapping or enter 0 to return Menu: ";
                cin >> K;
                if (K == 0) break;

                Bootstrapping model(N, M, K, beat, miss, meet, IWV, validStocks);
                model.run_BtStp();

            VisuliseResult:
                cout << "Please enter group 1-miss, 2-meet, 3-beat or enter 0 to return Menu: ";
                int gp;
                cin >> gp;
                if (gp == 0) break;
                model.printResult(gp - 1);
                goto VisuliseResult;
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
            case 9: {
            PrintStockList:
                int gp;
                cout << "Please enter group 1-miss, 2-meet, 3-beat or enter 0 to return Menu: ";
                cin >> gp;
                if (gp == 0) break;
                switch (gp-1) {
                case miss_0: {
                    cout << "Total number of stock in Group miss: " << miss.size() << endl;
                    for (int i = 0; i < miss.size(); i++) {
                        cout << miss[i] << endl;
                    }
                    break;
                }
                case meet_1: {
                    cout << "Total number of stock in Group meet: " << meet.size() << endl;
                    for (int i = 0; i < meet.size(); i++) {
                        cout << meet[i] << endl;
                    }
                    break;
                }
                case beat_2: {
                    cout << "Total number of stock in Group meet: " << beat.size() << endl;
                    for (int i = 0; i < beat.size(); i++) {
                        cout << beat[i] << endl;
                    }
                    break;
                }
                }
                goto PrintStockList;
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
