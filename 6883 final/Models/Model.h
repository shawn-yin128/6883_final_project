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
	Vector& operator/=(Vector& V, const int c);
	Vector& operator/=(Vector& V, const double c);
	Vector& operator*=(Vector& V, const int c);
	Vector& operator*=(Vector& V, const double c);
	//Vector& operator^(const Vector& V);
	ostream& operator<<(ostream& out, const Vector& V); // Overload cout for Vector
	ostream& operator<<(ostream& out, const Matrix& W); // Overload cout for Matrix
	
	class Bootstrapping {
	private:
		int N;					// number of observation days before/after Day0
		int M;					// number of stocks picked in each group
		int K;					// number of times of bootstrapping
		vector<string> beat;
		vector<string> miss;
		vector<string> meet;
		Stock benchmark;
		map<string, Stock> validStocks;

	public:
		Bootstrapping() :N(60),M(80), K(40) {}
		Bootstrapping(int N_, int M_, int K_,
			vector<string>& beat_, vector<string>& miss_, vector<string>& meet_, 
			Stock& benchmark_, map<string, Stock>& validStocks_) :
			N(N_), M(M_), K(K_), beat(beat_), miss(miss_), meet(meet_), benchmark(benchmark_), validStocks(validStocks_) {}

		//void run_BtStp();
		Vector& calAAR(vector<string>& group);
		Vector& calCAAR(Vector& AAR);

	};
}


#endif /* Model_hpp */
