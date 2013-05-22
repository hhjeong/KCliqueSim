#include "Base.h"
#include <algorithm>

/* No iterator + some prune*/
class BruteForceByLittlePrune : public Base {

public:
	const int N;
	int K;
	vector<bool> seen;
	vector< pair<int,int> > degree;
	vector< vector<int> > reducedGraph;
	BruteForceByLittlePrune( vector< vector<int> > &g ) : Base(g), N(g.size()), seen(g.size(),false) {
	} 

	int solve( vector<int> &lst ) {

		if( lst.size() == K ) return 1;

		int ret = 0;

		int last = lst.empty() ? 0 : lst.back() + 1;
		for( int next = last ; next < reducedGraph.size() ; ++next ) {
			const vector<int> &edges = reducedGraph[next];
			int nmatch = 0;
			for( int i = 0 ; i < edges.size() ; ++i ) {
				int other = edges[i];
				if( seen[other] ) ++nmatch;
			}
			if( nmatch == lst.size() ) {
				seen[next] = true;
				lst.push_back( next );
				ret += solve( lst );
				lst.pop_back();
				seen[next] = false;
			}
		}
		return ret;
	}

	virtual int findClique( const int K ) {
		this->K = K;
		degree.clear();

		vector<int> label(N,-1);

		for( int i = 0 ; i < N ; ++i ) {
			if( graph[i].size() >= K-1 ) {
				degree.push_back( make_pair( -(int)graph[i].size(), i ) );
			}
		}
		sort( begin(degree), end(degree) );

		for( int i = 0 ; i < degree.size() ; ++i ) label[degree[i].second] = i;

		reducedGraph.clear();

		for( int i = 0 ; i < degree.size() ; ++i ) {
			int here = degree[i].second;
			const vector<int> &edges = graph[here];
			vector<int> newEdges;
			for( int j = 0 ; j < edges.size() ; ++j) {
				int next = edges[j];
				if( label[next] == -1 ) continue;
				newEdges.push_back(label[next]);
			}
			reducedGraph.push_back(newEdges);
		}
		vector<int> lst;
		
		return solve(lst);
		
	}

};
