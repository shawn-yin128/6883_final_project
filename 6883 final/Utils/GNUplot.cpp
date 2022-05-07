//#include "GNUplot.h"
//
//using namespace std;
//namespace fre {
//	void plotResults(Vector& xData, Vector& y1Data, Vector& y2Data, Vector& y3Data,
//		string y1_name, string y2_name, string y3_name) {
//        FILE* gnuplotPipe, * tempDataFile;
//        const char* tempDataFileName1 = "tempData1";
//        const char* tempDataFileName2 = "tempData2";
//        double x, y, x2, y2;
//        int i;
//        // gnuplotPipe = popen("/opt/local/bin/gnuplot","w");       for MAC
//        gnuplotPipe = _popen("C:\\PROGRA~1\\gnuplot\\bin\\gnuplot.exe", "w");
//        if (gnuplotPipe) {
//            fprintf(gnuplotPipe, "plot \"%s\" with lines, \"%s\" with lines\n", tempDataFileName1, tempDataFileName2);
//            fflush(gnuplotPipe);
//            tempDataFile = fopen(tempDataFileName1, "w");
//            for (i = 0; i <= dataSize; i++) {
//                x = xData[i];
//                y = yData[i];
//                fprintf(tempDataFile, "%lf %lf\n", x, y);
//            }
//            fclose(tempDataFile);
//            tempDataFile = fopen(tempDataFileName2, "w");
//            for (i = 0; i <= dataSize; i++) {
//                x2 = xData[i];
//                y2 = yData2[i];
//                fprintf(tempDataFile, "%lf %lf\n", x2, y2);
//            }
//            fclose(tempDataFile);
//            printf("press enter to continue...");
//            getchar();
//            remove(tempDataFileName1);
//            remove(tempDataFileName2);
//
//            cout << 'test' << endl;
//            tempDataFile = fopen(tempDataFileName1, "w");
//            for (i = 0; i <= dataSize; i++) {
//                x = xData[i];
//                y = yData[i] + 0.1;
//                fprintf(tempDataFile, "%lf %lf\n", x, y);
//            }
//            printf("press enter to continue...");
//            getchar();
//            fclose(tempDataFile);
//
//            fprintf(gnuplotPipe, "exit \n");
//        }
//        else {
//            printf("gnuplot not found...");
//        }
//	}
//
//}
//
