#include "Base.h"
#include <algorithm>

class BruteForceBySort : public Base {

public:
	const int N;
	int K;
	vector<bool> seen;
	vector< pair<int,int> > degree;
	BruteForceBySort( vector< vector<int> > &g ) : Base(g), N(g.size()), seen(g.size(),false) {
	} 

	int solve( vector< pair<int,int> >::iterator it, vector<int> &lst ) {
		if( lst.size() == K ) return 1;

		int ret = 0;

		for( vector< pair<int,int> >::iterator who = it ; who != end(degree) ; ++who ) {
			int next = who->second;
			const vector<int> &edges = graph[next];
			int nmatch = 0;
			for( int i = 0 ; i < edges.size() ; ++i ) {
				int other = edges[i];
				if( seen[other] ) ++nmatch;
			}
			if( nmatch == lst.size() ) {
				seen[next] = true;
				lst.push_back( next );
				ret += solve( who, lst );
				lst.pop_back();
				seen[next] = false;
			}
		}
		return ret;
	}

	virtual int findClique( const int K ) {
		this->K = K;
		degree.clear();
		degree.resize(N);

		for( int i = 0 ; i < N ; ++i ) degree[i] = make_pair( -(int)graph[i].size(), i );
		sort( begin(degree), end(degree) );
		vector<int> lst;
		
		return solve(begin(degree),lst);
		
	}

};
