#ifndef TSP_H
#define TSP_H

#include <vector>
#include <fstream>
#include <string>
#include <map>

using namespace std;

struct Path{
	string key;
	int path;
}typedef SelectedPath;

class TSP{
	public:
		TSP();
		void BuildAdjMatrix(const char *fileName);
		void GenerateCombinations(int nBits);
		void BuildMatrixTSP(string combination);
		void CalculateLastColumn(string combination);
		void getAllPath();
		void ShowPath();
		void SolutionTSP();
		~TSP();

	private:
		vector<vector<int> > AdjMatrix_;
		vector<string> Combination_;
		vector<SelectedPath> Path_;
		vector<int> showPath_;
		vector<map<string, int> > MatrixTSP_;
		int size_;
};

#endif
