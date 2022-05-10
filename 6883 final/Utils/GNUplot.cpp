#include "GNUplot.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <chrono>
#include <thread>


using namespace std;
namespace fre {
    Vector& GNU::create_xData(int N) {
        xData.clear();
        for (int i = -N + 1; i <= N; i++) {
            xData.push_back(i);
        }
        return xData;
    }
    Vector& GNU::get_xData() { return xData; }

    void GNU::_plotResults(const Vector& xData, map<string, Vector>& yData) {
        double x, y;
        FILE* gnuplotPipe, * tempDataFile;

        #ifdef _WIN32						// Checking for windows OS with _WIN32 macro
            gnuplotPipe = _popen(EXE_PATH_PC.c_str(), "w");
        #elif __APPLE__						// Checking for mac OS with __APPLE__ macro
            gnuplotPipe = popen(EXE_PATH_MAC.c_str(), "w"); // for MAC
        #endif


        if (gnuplotPipe) {
            string command = "plot ";
            for (map<string, Vector>::iterator itr = yData.begin(); itr != yData.end(); itr++) {
                command += "\"" + itr->first + "\" with lines,";
            }
            command += "\n";
            fprintf(gnuplotPipe, command.c_str());
            fflush(gnuplotPipe);
            for (map<string, Vector>::iterator itr = yData.begin(); itr != yData.end(); itr++) {
                tempDataFile = fopen((itr->first).c_str(), "w");
                for (int i = 0; i < xData.size(); i++) {
                    x = xData[i];
                    y = itr->second[i];
                    fprintf(tempDataFile, "%lf %lf\n", x, y);
                }
                fclose(tempDataFile);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(2000));    // sleep for 2 second to wait for GNU plot engine

            //printf("press enter to continue...");
            //getchar();

            for (map<string, Vector>::iterator itr = yData.begin(); itr != yData.end(); itr++) {
                remove((itr->first).c_str());
            }

            fprintf(gnuplotPipe, "exit \n");
        }
        else {
            printf("gnuplot not found...");
        }
    }

    void GNU::plotResults(Vector& xData, map<string, Vector>& yData) {
        _plotResults(xData, yData);
    }

    void GNU::plotResults(Vector& xData, const Matrix& yData_val, const vector<string>& yData_name) {
        map<string, Vector> yData;
        for (int i = 0; i < yData_val.size(); i++) {
            yData[yData_name[i]] = yData_val[i];
        }
        _plotResults(xData, yData);
        //plotResults_test(xData, yData_val, yData_name);
    }

	void GNU::plotResults(Vector& xData, Vector& y1Data, Vector& y2Data, Vector& y3Data,
		string y1_name, string y2_name, string y3_name) {
        map<string, Vector> yData;
        yData[y1_name] = y1Data;
        yData[y2_name] = y2Data;
        yData[y3_name] = y3Data;
        _plotResults(xData, yData);
    }

    void GNU::plotResults(Vector& xData, Vector& y1Data, Vector& y2Data, Vector& y3Data, Vector& y4Data,
        string y1_name, string y2_name, string y3_name, string y4_name) {
        map<string, Vector> yData;
        yData[y1_name] = y1Data;
        yData[y2_name] = y2Data;
        yData[y3_name] = y3Data;
        yData[y4_name] = y4Data;
        _plotResults(xData, yData);

    }
}
