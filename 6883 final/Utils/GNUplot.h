#pragma once
#include "Utils.hpp"
#include "Parser.hpp"
#include "../Models/Model.h"

using namespace std;
namespace fre {
	class GNU {
	private:
		const string EXE_PATH_PC = "C:\\PROGRA~1\\gnuplot\\bin\\gnuplot.exe";
		const string EXE_PATH_MAC = "/opt/local/bin/gnuplot";

		
		Vector xData;

		void _plotResults(const Vector& xData, map<string, Vector>& yData);
		//void plotResults_test(const Vector& xData, const Matrix& yData_val, const vector<string>& yData_name);

	public:

		Vector& create_xData(int N);
		Vector& get_xData();

		void plotResults(Vector& xData, map<string, Vector>& yData);
		void plotResults(Vector& xData, const Matrix& yData_val,const vector<string>& yData_name);

		void plotResults(Vector& xData, Vector& y1Data, Vector& y2Data, Vector& y3Data,
			string y1_name, string y2_name, string y3_name);

		void plotResults(Vector& xData, Vector& y1Data, Vector& y2Data, Vector& y3Data, Vector& y4Data,
			string y1_name, string y2_name, string y3_name, string y4_name);

	};


}
