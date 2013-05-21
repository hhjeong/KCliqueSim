#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>

#include "BruteForce.h"
#include "BruteForceBySort.h"
#include "BruteForceBySortNoIterator.h"
#include "BruteForceByLittlePrune.h"
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

	fprintf( stderr, "fileName : %s\n", testDataName);
	fprintf( stderr, "target K : %d\n", K );
	fprintf( stderr, "graph size : %d\n", graph.size() );

	BruteForce bt(graph);

	vector<Base *> methods;
	methods.push_back( new BruteForce(graph) );
	methods.push_back( new BruteForceBySort(graph) );
	methods.push_back( new BruteForceBySortNoIterator(graph) );
	methods.push_back( new BruteForceByLittlePrune(graph) );

	for( int i = 0 ; i < methods.size() ; ++i ) {
		pair<double,int> ret = run(*methods[i], K);
		cerr << typeid(*methods[i]).name() << " " << ret.first << " " << ret.second << endl;
	}
}
int main() {
	for( int k = 1 ; k <= 4 ; ++k ) {
		for( int testno = 1 ; testno <= 4 ; ++testno ) {
			char fname[100];
			sprintf( fname, "testdata/test%d.txt", testno );
			testSingleCase(fname, k );
		}
	}
}