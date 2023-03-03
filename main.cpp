#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <stack>
#include <cmath>

#define e 7
#define v 6

#define START 3
#define END 4
using namespace std;
int edges[e][2] = {{0, 1}, {0, 4}, {1, 5}, {1, 2}, {2, 3}, {2, 5}, {3, 4}};
vector <vector<bool>> matrix(v, vector<bool>(v));
bool visited[v] = {false};
bool isPath = false;

void write(vector<double>& ppath, vector<double>& Pall, const string& filename) {
	ofstream out(filename);
	if (!out.is_open())
		throw logic_error("ERROR: CAN NOT OPEN FILE ==>" + filename);
	else {
		for (auto i = 0; i < ppath.size(); i++)
			out << ppath[i] << ' ' << Pall[i] << endl;
	}
}

void DFS(int start) {
	stack <int> s;
	int i = 0;
	s.push(start);
	visited[start] = 1;
	while (!s.empty()) {
		int vert = s.top();
		if (vert == END) {
			isPath = true;
			return;
		}
		for (i; i < v; i++) {
			if (visited[i] == 0 && matrix[vert][i]) {
				s.push(i);
				visited[i] = 1;
				break;
			}
		}
		if (i == v) {
			i = s.top() + 1;
			s.pop();
		}
		else
			i = 0;
	}
}

int main() {
	double Pall = 0;
	vector<double> ppath;
	vector<double> P_all;
	vector<double> P_simple;
	for (double p = 0.0; p <= 1.0; p += 0.1) {
		cout << "P - path = " << p;
		for (int i = 0; i < pow(2, e); ++i) {
			double curEdges = 0;
			bitset<e> b(i);
			for (int k = 0; k < b.size(); ++k) {
				if (b[k] == 1) {
					matrix[edges[k][0]][edges[k][1]] = 1;
					matrix[edges[k][1]][edges[k][0]] = 1;
					++curEdges;
				}
			}
			DFS(START);
			if (isPath) {
				Pall += pow(p, curEdges) * pow(1.0 - p, e - curEdges);
			}
			for (int m = 0; m < matrix.size(); ++m) {
				matrix[m].clear();
				matrix[m].resize(7, 0);
			}
			for (int g = 0; g < v; ++g) {
				visited[g] = false;
			}
			isPath = false;
		}
		cout << endl << "P brute force = " << Pall << endl;
		ppath.push_back(p);
		P_all.push_back(Pall);

		Pall = 0.0;
		double simpleP = p + pow(p, 4) + pow(p, 5);
		P_simple.push_back(simpleP);
		cout << "P decomposition = " << simpleP << endl << endl;
	}
	write(ppath, P_all, "Pall.txt");
	write(ppath, P_simple, "simpleP.txt");
	return 0;
}

