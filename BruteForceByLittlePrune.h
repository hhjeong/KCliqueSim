#include "Base.h"
#include <algorithm>

/* No iterator + some prune*/
class BruteForceByLittlePrune : public Base {

public:
	const int N;
	int K;
	vector<bool> seen;
	vector<bool> pruned;
	vector< pair<int,int> > degree;
	BruteForceByLittlePrune( vector< vector<int> > &g ) : Base(g), N(g.size()), seen(g.size(),false) {
	} 

	int solve( int pos, vector<int> &lst ) {
		if( lst.size() == K ) return 1;

		int ret = 0;

		for( int wh = pos ; wh < degree.size() ; ++wh ) {
			int next = degree[wh].second;
			if( pruned[next] ) continue;
			const vector<int> &edges = graph[next];
			int nmatch = 0;
			for( int i = 0 ; i < edges.size() ; ++i ) {
				int other = edges[i];
				if( seen[other] ) ++nmatch;
			}
			if( nmatch == lst.size() ) {
				seen[next] = true;
				lst.push_back( next );
				ret += solve( wh+1, lst );
				lst.pop_back();
				seen[next] = false;
			}
		}
		return ret;
	}

	virtual int findClique( const int K ) {
		this->K = K;
		degree.clear();
		pruned.clear();
		pruned.resize(N,false);
		for( int i = 0 ; i < N ; ++i ) {
			
			if( graph[i].size() >= K ) {
				degree.push_back( make_pair( -(int)graph[i].size(), i ) );
			}
			else {
				pruned[i] = true;
			}
		}
		sort( begin(degree), end(degree) );
		vector<int> lst;
		
		return solve(0,lst);
		
	}

};
