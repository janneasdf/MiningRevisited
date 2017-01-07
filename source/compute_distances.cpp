#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <deque>
#include <chrono>
#include <algorithm>

using namespace std;

int main() 
{
	cout << "Reading input/output filenames" << endl;
	string input_file, output_file;
	cin >> input_file >> output_file;

	// Read file describing the edges of the connected component graph
	cout << "Reading input file" << endl;
	ifstream cc_input;
	cc_input.open(input_file.c_str());
	map<string, int> node_numbers;
	vector<vector<int>> neighbor_lists;
	int node_count = 0;
	if (cc_input.is_open()) 
	{
		string line;
		while (getline(cc_input, line))
		{
			istringstream edge(line);
			string source_node_name;
			string target_node_name;
			getline(edge, source_node_name, ' ');
			getline(edge, target_node_name, ' ');
			auto init_map_element = [&](string node_name) -> int 
			{
				if (node_numbers.count(node_name) < 1)
				{
					node_numbers[node_name] = node_count;
					neighbor_lists.push_back(vector<int>());
					node_count++;
				}
				return node_numbers[node_name];
			};
			int source_node = init_map_element(source_node_name);
			int target_node = init_map_element(target_node_name);
			auto& source_neighbors = neighbor_lists[source_node]; 
			if (find(source_neighbors.begin(), source_neighbors.end(), target_node) == source_neighbors.end())
			{
				source_neighbors.push_back(target_node);
			}
		}
		cc_input.close();
	}
	else
	{
		cout << "Unable to open file: " << input_file << endl;
	}
	cout << "Found " << node_count << " nodes" << endl;

	vector<int> distance_histogram(node_count, 0);
	struct QueuedNode
	{
		int node;
		int distance;
		QueuedNode(int node, int distance) : node(node), distance(distance) {}
	};
	// Performs BFS from source_node and counts distances from source
	auto BFS_add_distances = [&distance_histogram, &neighbor_lists, node_count](int source_node) -> void
	{
		vector<bool> visited(node_count, false);
		deque<QueuedNode> nodes_to_visit;
		nodes_to_visit.push_back(QueuedNode(source_node, 0));
		visited[source_node] = true;
		while (!nodes_to_visit.empty())
		{
			QueuedNode current_node = nodes_to_visit.front();
			nodes_to_visit.pop_front();
			#pragma omp atomic
			distance_histogram[current_node.distance]++;
			for (int neighbor_node : neighbor_lists[current_node.node])
			{
				if (!visited[neighbor_node])
				{
					visited[neighbor_node] = true;
					nodes_to_visit.push_back(QueuedNode(neighbor_node, current_node.distance + 1));
				}
			}
		}
	};
	auto start_time = chrono::steady_clock::now();
	#pragma omp parallel for
	for (int source_node = 0; source_node < node_count; ++source_node)
	{
		/*if (source_node % 1000 == 0) 
		{
			cout << "Processed " << source_node << " nodes" << endl;
		}*/
		BFS_add_distances(source_node);
	}
	auto duration_millis = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start_time).count();

	// Count edges in the graph
	int edge_count = 0;
	for (auto& neighbor_list : neighbor_lists)
	{
		edge_count += neighbor_list.size();
	}

	// Helper function for writing output into a stream
	auto write_output = [&](ostream& out) -> void
	{
		out << "Time: " << duration_millis * 0.001 << endl;
		out << "Iters: None" << endl;
		out << "Nodes: " << node_count << endl;
		out << "Edges: " << edge_count << endl;
		if (node_count > 0)
		{
			out << distance_histogram[0];
			for (auto it = distance_histogram.begin() + 1; it != distance_histogram.end(); ++it)
			{
				out << " " << *it;
			}
			out << endl;
		}
	};

	// Write output to file
	ofstream output;
	output.open(output_file.c_str());
	write_output(output);
	output.close();

	// Print the output file to standard output
	write_output(cout);

	return 0;
}
