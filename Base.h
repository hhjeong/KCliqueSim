#ifndef __BASE_H__
#define __BASE_H_

#include <vector>
#include <utility>
#include <Windows.h>
using namespace std;

class Base {

public:
	const vector< vector<int> > &graph;

	Base( vector< vector<int> > &g ) : graph(g) {} 
	virtual int findClique( const int K ) {
		return 0;
	}
};

#endif