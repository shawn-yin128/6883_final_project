#include <iostream>
#include <map>
#include <vector>
#include <time.h>
#include "Utils/Utils.hpp"
#include "Utils/Parser.hpp"

using namespace std;
using namespace fre;

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

    bool run = 1;
    while (run) {
        cout << "Please enter your choice and press return: ";
        cin >> selection;
        switch (selection) {
            case 1: {
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
