#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure for the Node
struct GraphNode {
    int vertex_node;
    int Weight;

//overloding > to compare b/w nodes
    bool operator>(const GraphNode &node) const {
        return Weight > node.Weight; 
    }
};


// DijkstraAlgo function , pass function and source and des
void DijkstraAlgo(const vector<vector<pair<int, int>>> &graph_verti, int source, int desti) {
    int n = graph_verti.size();
    vector<int> Weight(n, INT_MAX);
    vector<int> parent_node(n, -1);
    priority_queue<GraphNode, vector<GraphNode>, greater<GraphNode>> queue;

    Weight[source] = 0;
    queue.push({source, 0});


  // loop priority queue
    while (!queue.empty()) {
        GraphNode present_node = queue.top();
        queue.pop();

        int currentNode = present_node.vertex_node;
        int dist = present_node.Weight;

      // Looping through the adjacent nodes of the current node
        auto neighbor_node = graph_verti[currentNode].begin();
        while (neighbor_node != graph_verti[currentNode].end()) {
            int v_first = neighbor_node->first;
            int weight_cost = neighbor_node->second;

          // Checking if the Weight of the adjacent node is greater than the current Weight
            if (dist + weight_cost < Weight[v_first]) {
                Weight[v_first] = dist + weight_cost;
                parent_node[v_first] = currentNode;
                queue.push({v_first, Weight[v_first]});
            }

            ++neighbor_node;
        }
    }

  // Printing the path from source to desti
    cout << "Shortest Path from " << source << " to " << desti << ":\n";
    cout << "Cost: " << Weight[desti] << "\nPath: ";

    int i = desti;
    vector<int> path_traversal;
    while (i != -1) {
        path_traversal.push_back(i);
        i = parent_node[i];
    }

    for (int j = path_traversal.size() - 1; j >= 0; --j) {
        cout << path_traversal[j];
        if (j != 0) cout << " -> ";
    }
}


// main function defination
int main() {
    int num_of_Nodes;

  // Prompting the user to enter number of nodes
    cout << "Enter the number of nodes : ";
    cin >> num_of_Nodes;

    if (num_of_Nodes <= 0) {
        cout << "Enter atleast one node.\n";
        return 1;
    }

    vector<vector<pair<int, int>>> graph_verti(num_of_Nodes);
  cout << "If there is no connection enter -999:\n ";
 
    // Letting the user to enter the weights between nodes
    for (int node1 = 0; node1 < num_of_Nodes; ++node1) {
        for (int node2 = node1 + 1; node2 < num_of_Nodes; ++node2) {
            int weight_in_between;

            cout << "Enter weight from node " << node1 << " to " << node2 << ": ";
            cin >> weight_in_between;

            if (weight_in_between == -999) {
                continue;
            }

            // Check if the same edge already exists with a different weight
            for (const auto &edge_path : graph_verti[node1]) {
                if (edge_path.first == node2 && edge_path.second != weight_in_between) {
                    cout << "Different weights found between same nodes.\n";
                    return 1;
                }
            }
            // Pushing the edge and weight to the graph
            graph_verti[node1].push_back({node2, weight_in_between});
            graph_verti[node2].push_back({node1, weight_in_between});
        }
    }

    int start, end;

    cout << "Enter the start node: ";
    cin >> start;

    cout << "Enter the end node: ";
    cin >> end;

    DijkstraAlgo(graph_verti, start, end); // Calling DijkstraAlgo's function

    return 0;
}
