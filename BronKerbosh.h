#include "Base.h"
#include <list>
#include <algorithm>
#include <set>
class BronKerbosh : public Base {

public:
	const int N;
	int K;
	vector<bool> seen;
	set< list<int> > cliques;

	BronKerbosh( vector< vector<int> > &g ) : Base(g), N(g.size()), seen(g.size(),false) {
	} 

	int NCR( int N, int R ) {
		int ret = 1;
		for( int i = N, j = 1 ; i > R ; --i, ++j ) {
			ret *= i;
			ret /= j;
		}
		return ret;
	}
	bool nomore( list<int> &candidates, list<int> &alreadyFound ) {

		for( auto af = begin(alreadyFound) ; af != end(alreadyFound) ; ++af ) {
			int edgeCounter = 0;
			const int szCandidates = candidates.size();
			const vector< int > &edges = graph[*af];
			for( auto cand = begin(candidates) ; cand != end(candidates) ; ++cand ) {
				edgeCounter += binary_search( begin(edges), end(edges), *cand );
			}
			if( szCandidates == edgeCounter ) return true;
		}

		return false;
	}
	int solve( list<int> &potentialClique, list<int> &candidates, list<int> &alreadyFound ) {
		list<int> candidatesArray = candidates;

		if( nomore(candidates,alreadyFound) ) return 0;
		for( auto cand = begin(candidatesArray) ; cand != end(candidatesArray) ; ++cand ) {
			list<int> newCandidates;
			list<int> newAlreadyFound;

			potentialClique.push_back(*cand);
			candidates.remove(*cand);

			const vector<int> &edges = graph[*cand];

			for( auto newCand = begin(candidates) ; newCand != end(candidates) ; ++newCand ) {
				if( binary_search(begin(edges),end(edges),*newCand) ) {
					newCandidates.push_back(*newCand);
				}
			}
				
			for( auto newFound = begin(alreadyFound) ; newFound != end(alreadyFound) ; ++newFound ) {
				if( binary_search(begin(edges),end(edges),*newFound) ) {
					newAlreadyFound.push_back(*newFound);
				}
			}

			if( newCandidates.empty() && newAlreadyFound.empty() ) {
				cliques.insert( potentialClique );
				// cerr << "maximal cliques found. size is " << potentialClique.size() << endl;
			}
			else {
				solve( potentialClique, newCandidates, newAlreadyFound );
			}

			alreadyFound.push_back(*cand);
			potentialClique.remove(*cand);
		}
		return 0;
	}

	virtual int findClique( const int K ) {
		
		this->K = K;
		list<int> potentialClique;
		list<int> candidates;
		list<int> alreadyFound;
		
		for( int i = 0 ; i < N ; ++i ) candidates.push_back(i);
		solve( potentialClique, candidates, alreadyFound );

		int ret = 0;
		for( auto c = begin(cliques) ; c != end(cliques) ; ++c ) {
			for( auto d = begin(*c) ; d != end(*c) ; ++d ) {
				cerr << *d << " ";
			}
			cerr << endl;
			ret += NCR(c->size(),K);
		}
		return ret;

		return NCR(10,1);
	}

};
