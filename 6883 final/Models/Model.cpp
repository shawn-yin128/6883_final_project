#include <string>
#include <vector>
#include "Trade.hpp"
#include "Stock.hpp"
#include "Model.h"
#include <map>
#include <vector>
#include <time.h>
#include "../Utils/Utils.hpp"
#include "../Utils/Parser.hpp"


using namespace std;

namespace fre {
	Vector& operator+=(Vector& V, const Vector& U) {
		// assume same size	
		for (int i = 0; i < V.size(); i++) {
			V[i] += U[i];
		}
		return V;
	}
	Vector& operator/=(Vector& V, const int c) {
		// assume same size	
		for (int i = 0; i < V.size(); i++) {
			V[i]/=c;
		}
		return V;
	}
	Vector& operator/=(Vector& V, const double c) {
		// assume same size	
		for (int i = 0; i < V.size(); i++) {
			V[i] /= c;
		}
		return V;
	}
	Vector& operator*=( Vector& V, const int c) {
		// assume same size	
		for (int i = 0; i < V.size(); i++) {
			V[i] *= c;
		}
		return V;
	}
	Vector& operator*=(Vector& V, const double c) {
		// assume same size	
		for (int i = 0; i < V.size(); i++) {
			V[i] *= c;
		}
		return V;
	}
	//Vector& operator^(const Vector& V);
	ostream& operator<<(ostream& out, const Vector& V) {
		for (int i = 0; i < V.size(); i++) {
			out << V[i];
		}
		out << endl;
		return out;
	}
	ostream& operator<<(ostream& out, Matrix& W) {
		for (int i = 0; i < W.size(); i++) {
			out << W[i];
		}
		return out;
	}

	Vector& Bootstrapping::calAAR(vector<string>& group) {
		vector<string> stocks;
		stocks = sampling_NoReplace<vector<string>>(group, M);
		//= sampling_NoReplace<vector<string>>(group, M);
		Vector AAR(2*N,0);
		for (string stk : stocks) {
			AAR += validStocks[stk].getAR();
		}
		AAR /= M;
		return AAR;
	}
	Vector& Bootstrapping::calCAAR(Vector& AAR) {
		double cumAAR = 0;
		Vector CAAR(2 * N, 0);
		for (int i = 0; i < 2 * N; i++) {
			cumAAR += AAR[i];
			CAAR[i] = cumAAR;
		}
		return CAAR;

	}
	//void Bootstrapping::run_BtStp() {
	//	map<string, vector<Matrix>> result;
	//	vector<string>* group_ptr =nullptr ;

	//	for (int i = 0; i < 3; i++) {
	//		switch (i)
	//		{
	//			case 0: {
	//				group_ptr = &miss;
	//				break;
	//			}
	//			case 1: {
	//				group_ptr = &meet;
	//				break;
	//			}
	//			case 2: {
	//				group_ptr = &beat;
	//				break;
	//			}
	//		}
	//		for (int k = 0; k < K; k++) {
	//			//Vector AAR = calAAR(*group_ptr);
	//			//Vector CAAR = calCAAR(AAR);
	//		}
	//	}
	//}

}
