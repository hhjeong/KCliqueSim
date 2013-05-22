#include "Base.h"

class BruteForce : public Base {

public:
	const int N;
	int K;
	vector<bool> seen;
	BruteForce( vector< vector<int> > &g ) : Base(g), N(g.size()), seen(g.size(),false) {
	} 

	int solve( vector<int> &lst ) {
		if( lst.size() == K ) {
			/*
			ofstream oup("Logs/bruteforce.txt", ios::app);
			for( int i = 0 ; i < lst.size() ; ++i ) oup << lst[i] << " ";
			oup << endl;
			oup.close();*/
			return 1;
		}

		int ret = 0;

		int last = lst.empty() ? 0 : lst.back() + 1;

		for( int next = last ; next < N ; ++next ) {
			const vector<int> &edges = graph[next];
			
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
		vector<int> lst;
		
		return solve( lst );
		
	}

};
