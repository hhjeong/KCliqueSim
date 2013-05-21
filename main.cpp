#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>

#include "BruteForce.h"
using namespace std;

void getInput( char *fileName, vector< vector<int> > &graph ) {
	graph.clear();
	
	int n;
	ifstream inp(fileName);

	inp >> n;
	graph.assign( n, vector<int>() );
	for( int i = 0 ; i < n ; ++i ) {
		int m;
		inp >> m;
		for( int j = 0 ; j < m ; ++j ) {
			int t;
			inp >> t;
			graph[i].push_back(t);
		}
	}
	inp.close();
}

pair<double,int> run( Base &method, int K ) {
	LARGE_INTEGER freq;
	LARGE_INTEGER st, ed;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&st);
	int ret = method.findClique(K);
	QueryPerformanceCounter(&ed);
	return make_pair( (double)(ed.QuadPart-st.QuadPart)/(freq.QuadPart),ret );
}

void testSingleCase( char *testDataName, int K ) {
	vector< vector<int> > graph;
	getInput( testDataName, graph );

	BruteForce bt(graph);

	vector<Base *> methods;
	methods.push_back( new BruteForce(graph) );

	for( int i = 0 ; i < methods.size() ; ++i ) {
		pair<double,int> ret = run(*methods[i], K);
		cerr << ret.first << " " << ret.second << endl;
	}
}
int main() {
	for( int k = 1 ; k <= 7 ; ++k ) {
		testSingleCase("testdata/test1.txt", k );
	}
}