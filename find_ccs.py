import networkx as nx
import sys

def main():
	assert(len(sys.argv) == 4)
	graph_path = sys.argv[1]
	lscc_path = sys.argv[2]
	lwcc_path = sys.argv[3]
	G_directed = nx.DiGraph(nx.read_edgelist(graph_path, create_using=nx.DiGraph()))
	G_undirected = nx.read_edgelist(graph_path)
	LSCC = max(nx.strongly_connected_component_subgraphs(G_directed), key=len)
	LWCC = max(nx.connected_component_subgraphs(G_undirected), key=len)
	nx.write_edgelist(LSCC, lscc_path)
	nx.write_edgelist(LWCC, lwcc_path)
	print('Wrote LSCC file', lscc_path)
	print('Wrote LWCC file', lwcc_path)

if __name__ == '__main__':
	main()