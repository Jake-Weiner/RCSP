// RCSP (Resource Constrained Shortest Path Problem) as illustrated in Lagrangian Relaxation Example
// Author: Jake Weiner 11/07/18

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <bits.h>
#include <vector>
#include <queue>
#include <stack>
#include <Eigen/Dense>
#define INF 0x3f3f3f3f

using namespace std;
using namespace Eigen;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector< pii > vii;


// Global vectors for storing distance from source node and previous node in path

vi Dist;  // for storing the distance of every other node from source.
vi Prev;

/*==========================================*/

class my_graph {

public:
	my_graph(string filename, int nodes) {
		vector<vector<float>> cost_matrix;
		vector<vector<float>> time_matrix(nodes, vector<float>(nodes));
		set_cost_matrix(filename, nodes);
		this->nodes = nodes;
	}

	vector<int> get_dist() {
		return dist;
	}
	vector<int> get_prev() {
		return prev;
	}

	void set_cost_matrix(string filename, int nodes) {

		/* initialise cost_matrix*/
		float value;
		ifstream input_file(filename);
		if (!input_file) {
			cout << "error opening cost matrix file " << endl;
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < nodes; i++) {
			for (int j = 0; j < nodes; j++) {
				input_file >> value;  // accepting the value from standard in
				cost_matrix2(i,j) = value; // pushing back the value into the  temporary vector 
			}
		}
		/*
		for (int i = 0; i < nodes; i++) {
			vector<float> temp;  //  temporary vector to insert

			for (int j = 0; j < nodes; j++) {
				input_file >> value;  // accepting the value from standard in
				temp.push_back(value); // pushing back the value into the  temporary vector 
			}
			cost_matrix.push_back(temp); // pushing back the temporary vector into the main vector 
		}
		*/
	}

	void set_time_matrix(string filename) {

	}

	void set_source(int source) {
		this->source = source;
	}
	void set_end(int end) {
		this->end = end;
	}

	void print_cost_matrix() {
		for (int row = 0; row < cost_matrix.size(); row++) {
			for (int col = 0; col < cost_matrix.size(); col++) {
				cout << cost_matrix[row][col] << " ";
			}
			cout << endl;
		}
	}

	void djikstras(int source, int end_node) {

		// STRUCT TEMPLATE used for comparison operator in priority_queue
		struct mygreater
		{	// functor for operator>
			constexpr bool operator()(const pair<int, int>& _Left, const pair<int, int>& _Right) const
			{	// apply operator> to operands
				return (_Left.second > _Right.second);
			}
		};
		priority_queue<pair<int, int>, vector<pair<int, int>>, mygreater > Q;   // min heap
		dist.assign(nodes, INF);
		prev.assign(nodes, -1);
		dist[source] = 0;
		Q.push({ source,0 });
		while (!Q.empty()) {
			pair<int, int> current_node = Q.top();
			if (current_node.first == end_node) {
				return;
			}
			Q.pop();
			for (int i = 0; i < nodes; i++) {
				if (cost_matrix[current_node.first][i] != -1) {
					int v = i;
					int w = cost_matrix[current_node.first][i];
					if (dist[v] > dist[current_node.first] + w) {
						dist[v] = dist[current_node.first] + w;
						prev[v] = current_node.first;
						Q.push({ v,dist[v] });
					}
				}
			}

		}
	}

	void print_shortest_path(int end_node) {

		int last_node = end_node;

		cout << "Distance to node " << end_node << " from " << this->source << " is " << dist[end_node] << endl;

		cout << "Shortest Path to node " << end_node << " is through " << endl;


		stack<int> sequence;
		while (prev[last_node] != -1) {
			sequence.push(last_node);
			last_node = prev[last_node];
		}
		sequence.push(last_node);

		while (!sequence.empty()) {
			cout << sequence.top() << " ";
			sequence.pop();
		}
		cout << endl;



	}

private:
	vector<vector<float>> cost_matrix;
	Matrix3f cost_matrix2;
	vector<vector<float>> time_matrix;
	vector<int> dist;
	vector<int> prev;
	int source;
	int end;
	int nodes;
	void set_dist(vector<int> dist) {
		this->dist = dist;
	}

	void set_prev(vector<int> prev) {
		this->prev = prev;
	}

};

/*
float sub_gradient(float scaling_factor) {

	float best_objective;
	float relaxed_objective;

}
*/

void test_graph(string filename, int nodes) {

	my_graph g1(filename, nodes);
	g1.print_cost_matrix();
	g1.djikstras(0, 5);
	g1.print_shortest_path(5);

}

void test_ei() {
	MatrixXd m(2, 2);
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);
	cout << m << endl;
}

int main()
{
	/*
	string cost_filename = "C:\\Users\\s3730771\\source\\repos\\SPP\\adjacency_cost.txt";
	string time_filename = "C:\\Users\\s3730771\\source\\repos\\SPP\\adjacency_time.txt";
	test_graph(cost_filename, 6);
	*/
	test_ei();
	return 0;
}

