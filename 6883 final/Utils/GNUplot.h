//#pragma once
//#include "Utils.hpp"
//#include "Parser.hpp"
//#include "../Models/Model.h"
//
//using namespace std;
//namespace fre {
//	class GNU {
//	private:
//		const string EXE_PATH_PC = "C:\\PROGRA~1\\gnuplot\\bin\\gnuplot.exe";
//		const string EXE_PATH_MAC = "/opt/local/bin/gnuplot";
//
//		void _plotResults(const Vector& xData, map<string, Vector>& yData) {
//            double x, y;
//            FILE* gnuplotPipe, * tempDataFile;
//            // gnuplotPipe = popen("/opt/local/bin/gnuplot","w");       for MAC
//            gnuplotPipe = _popen("C:\\PROGRA~1\\gnuplot\\bin\\gnuplot.exe", "w");
//
//
//            //const char* tempDataFileName1 = "tempData1";
//            //const char* tempDataFileName2 = "tempData2";
//            //double x, y, x2, y2;
//            //int i;
//            if (gnuplotPipe) {
//                string command = "plot ";
//                for (map<string, Vector>::iterator itr = yData.begin(); itr != yData.end(); itr++) {
//                    command += "\"" + itr->first + "\" with lines,";
//                }
//                command += "\n";
//                fprintf(gnuplotPipe, command.c_str());
//                fflush(gnuplotPipe);
//                for (map<string, Vector>::iterator itr = yData.begin(); itr != yData.end(); itr++) {
//                    tempDataFile = fopen((itr->first).c_str(), "w");
//                    for (int i = 0; i <= xData.size(); i++) {
//                        x = xData[i];
//                        y = itr->second[i];
//                        fprintf(tempDataFile, "%lf %lf\n", x, y);
//                    }
//                    fclose(tempDataFile);
//                }
//
//                printf("press enter to continue...");
//                getchar();
//                for (map<string, Vector>::iterator itr = yData.begin(); itr != yData.end(); itr++) {
//
//                    remove();
//                }
//
//                cout << 'test' << endl;
//                tempDataFile = fopen(tempDataFileName1, "w");
//                for (i = 0; i <= dataSize; i++) {
//                    x = xData[i];
//                    y = yData[i] + 0.1;
//                    fprintf(tempDataFile, "%lf %lf\n", x, y);
//                }
//                printf("press enter to continue...");
//                getchar();
//                fclose(tempDataFile);
//
//                fprintf(gnuplotPipe, "exit \n");
//            }
//            else {
//                printf("gnuplot not found...");
//            }
//		}
//	public:
//
//		void plotResults(Vector& xData, Vector& y1Data, Vector& y2Data, Vector& y3Data,
//			string y1_name, string y2_name, string y3_name);
//
//		void plotResults(Vector& xData, Vector& y1Data, Vector& y2Data, Vector& y3Data, Vector& y4Data,
//			string y1_name, string y2_name, string y3_name, string y4_name);
//
//	};
//
//
//}
