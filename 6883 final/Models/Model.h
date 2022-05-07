#ifndef Model_hpp
#define Model_hpp
#pragma once

#include <string>
#include <vector>
#include "Trade.hpp"
#include "Stock.hpp"
#include <map>
#include <vector>
#include <time.h>
#include "../Utils/Utils.hpp"
#include "../Utils/Parser.hpp"

using namespace std;

namespace fre {
	typedef vector<double> Vector;
	typedef vector<Vector> Matrix;
	Vector& operator+=(Vector& V, const Vector& U);
	Vector& operator-=(Vector& V, const Vector& U);
	Vector& operator/=(Vector& V, const int c);
	Vector& operator/=(Vector& V, const double c);
	Vector& operator*=(Vector& V, const int c);
	Vector& operator*=(Vector& V, const double c);
	Vector operator^(const Vector& V, const double x);
	ostream& operator<<(ostream& out, const Vector& V); // Overload cout for Vector
	ostream& operator<<(ostream& out, const vector<string>& V); // Overload cout for Vector
	ostream& operator<<(ostream& out, const Matrix& W); // Overload cout for Matrix
	


	class Bootstrapping {
	private:
		map<group_enum, string> group_str{ {miss_0,"miss"}, {meet_1,"meet"}, {beat_2,"beat"} };
		vector<string> metrics_Name{ "Mean-AAR","Std-AAR","Mean-CAAR","Std-CAAR" };
		int N;					// number of observation days before/after Day0
		int M;					// number of stocks picked in each group
		int K;					// number of times of bootstrapping
		vector<string> beat;
		vector<string> miss;
		vector<string> meet;
		Stock benchmark;
		map<string, Stock> validStocks;
		map<group_enum, Matrix> result;		// key:group, value:[mean-AAR,std-AAR,mean-CAAR, std-CAAR] 

		Vector& calAAR(vector<string>& group, Vector& AAR);
		Vector& calCAAR(Vector& AAR, Vector& CAAR);

	public:
		Bootstrapping() :N(60),M(80), K(40) {}
		Bootstrapping(int N_, int M_, int K_,
			vector<string>& beat_, vector<string>& miss_, vector<string>& meet_, 
			Stock& benchmark_, map<string, Stock>& validStocks_) :
			N(N_), M(M_), K(K_), beat(beat_), miss(miss_), meet(meet_), benchmark(benchmark_), validStocks(validStocks_) {}

		void run_BtStp();
		void printResult(int gp);

		const Matrix& getMetrics(int gp);
		map<string,Vector> getStdCAAR();
		map<string,Vector> getMeanCAAR();
		map<string,Vector> getMeanAAR();
		map<string,Vector> getStdAAR();
		string getGroupName(int gp) { return group_str[group_enum(gp)]; }
		vector<string> getMetricsName() { return metrics_Name; }
	};
}


#endif /* Model_hpp */
