#include "../Utils/Utils.hpp"
#include "../Utils/Parser.hpp"
#include "Trade.hpp"
#include "Stock.hpp"
#include "Model.h"
#include <map>
#include <vector>
#include <string>
#include <vector>
#include <time.h>
#include <cmath>


using namespace std;

namespace fre {
	// operator overloading
	Vector& operator-=(Vector& V, const Vector& U) {
		// assume same size	
		for (int i = 0; i < V.size(); i++) {
			V[i] -= U[i];
		}
		return V;
	}
	Vector& operator+=(Vector& V, const Vector& U) {
		// assume same size	
		for (int i = 0; i < V.size(); i++) {
			V[i] += U[i];
		}
		return V;
	}
	Vector& operator/=(Vector& V, const int c) {
		for (int i = 0; i < V.size(); i++) {
			V[i]/=c;
		}
		return V;
	}
	Vector& operator/=(Vector& V, const double c) {
		for (int i = 0; i < V.size(); i++) {
			V[i] /= c;
		}
		return V;
	}
	Vector& operator*=( Vector& V, const int c) {
		for (int i = 0; i < V.size(); i++) {
			V[i] *= c;
		}
		return V;
	}
	Vector& operator*=(Vector& V, const double c) {
		for (int i = 0; i < V.size(); i++) {
			V[i] *= c;
		}
		return V;
	}
	Vector operator^(const Vector& V, const double x) {
		Vector Vx(V.size());
		for (int i = 0; i < V.size(); i++) {
			Vx[i] = (x == 0.5) ? sqrt(V[i]) : pow(V[i], x);	// sqrt is faster than pow(x,0.5)
		}
		return Vx;
	}
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

	// Bootstrapping Class
	Vector& Bootstrapping::calAAR(vector<string>& group, Vector& AAR) {
		vector<string> stocks;
		stocks = sampling_NoReplace<vector<string>>(group, M);

		if (AAR.size() != 2 * N) AAR.resize(2 * N);		// restrict the size to be 2N
		fill(AAR.begin(), AAR.end(), 0);			
		for (string stk : stocks) {
			AAR += validStocks[stk].getAR();
		}
		AAR /= M;
		return AAR;
	}
	Vector& Bootstrapping::calCAAR(Vector& AAR, Vector& CAAR) {
		double cumAAR = 0;

		if (CAAR.size() != 2 * N) CAAR.resize(2 * N);		// restrict the size to be 2N

		for (int i = 0; i < 2*N; i++) {
			cumAAR += AAR[i];
			CAAR[i] = cumAAR;
		}
		return CAAR;

	}
	void Bootstrapping::run_BtStp() {
		map<string, Matrix> result;		// key:group, value:[mean-AAR,std-AAR,mean-CAAR, std-CAAR] 
		vector<string>* group_ptr =nullptr ;
		string gp;

		for (int i = 0; i < 3; i++) {
			// loop through 3 groups, can change to multithread later
			switch (i)
			{
				case group_enum:: miss_0: {
					group_ptr = &miss;
					gp = "miss";
					break;
				}
				case group_enum:: meet_1: {
					group_ptr = &meet;
					gp = "meet";
					break;
				}
				case group_enum::beat_2: {
					group_ptr = &beat;
					gp = "beat";
					break;
				}
			}
			Matrix temp(4,Vector (2*N,0));		// [mean - AAR, std - AAR, mean - CAAR, std - CAAR]
			result[gp] = temp;

			for (int k = 0; k < K; k++) {
				// loop through 40 bootstraps, can change to multithread later
				Vector AAR(2 * N, 0);
				result[gp][0] += calAAR(*group_ptr, AAR);		// mean-AAR (sum AAR)

				Vector CAAR(2 * N, 0);
				result[gp][2] += calCAAR(AAR, CAAR);			// mean-CAAR (sum CAAR)

				result[gp][1] += AAR ^ 2;						// std-AAR	(sum AAR^2)
				result[gp][3] += CAAR ^ 2;						// std-AAR	(sum CAAR^2)
			}
			result[gp][0] /= K;									// mean-AAR
			result[gp][2] /= K;									// mean-CAAR
			// std-AAR
			result[gp][1] /= K;									// Hsq
			result[gp][1] -= result[gp][0] ^ 2;					// Hsq- H*H
			result[gp][1] = result[gp][1] ^ 0.5;				// std = sqrt(Hsq- H*H)
			// std-CAAR
			result[gp][3] /= K;									// Hsq
			result[gp][3] -= result[gp][2] ^ 2;					// Hsq- H*H
			result[gp][3] = result[gp][3] ^ 0.5;				// std = sqrt(Hsq- H*H)
		}
	}
	ostream& Bootstrapping::printResult(ostream& out) {
		return out;
	}

}
