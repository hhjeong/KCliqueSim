import random, sys, getopt, itertools

def output_as_list( graph ):
	return "%d\n%s" % (len(graph),"\n".join( [ "%d %s"%(sum(lst)," ".join([ str(j) for j, edge in enumerate(lst) if edge == 1 ])) for i, lst in enumerate(graph) ]))

def output_as_matrix( graph ):
	return "%d\n%s" % (len(graph),"\n".join( " ".join([ str(edge) for edge in vertex ]) for vertex in graph ))

def random_perms( N, K ):
	ret = range(N)
	random.shuffle(ret)
	return tuple(sorted(ret[:K]))

def generate_graph( N, K, D, minC ):
	graph = [ [ 0 for j in xrange(N) ] for i in xrange(N) ]
	
	nedges = D * N * (N-1) / 2 / 100

	edges = [ (u,v) for u in xrange(0,N) for v in xrange(u+1,N) ]
	random.shuffle(edges)
	edges = edges[:nedges]

	for u, v in edges:
		graph[u][v], graph[v][u] = 1, 1

	seen = set() 
	for it in xrange(minC):
		while True:
			r = random_perms(N,K)
			if not r in seen:
				break
		seen.add(r)
		for comb in itertools.combinations(r,2):
			u, v = list(comb)
			graph[u][v], graph[v][u] = 1, 1
	return graph

def main():
	print output_as_list( generate_graph( 5000, 3, 1, 1 ) )
if __name__ == "__main__":
	main()
