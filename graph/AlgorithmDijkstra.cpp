#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <gtest/gtest.h>

using namespace std;

class Graph {
private:
    int V;              // Number of vertices in the graph
    int** adj_matrix;   // Adjacency matrix

    // Helper function to get the path using the predecessor array
    string getPath(const vector<int>& prev, int vertex) {
        if (vertex == -1) {
            return "";  // Base case: reached the start of the path
        }
        // Recursively build the path by appending the current vertex
        return getPath(prev, prev[vertex]) + " " + char('A' + vertex);
    }
public:
    // Constructor for the graph with a specified number of vertices
    Graph(int V) : V(V) {
        adj_matrix = new int* [V];
        for (int i = 0; i < V; ++i) {
            adj_matrix[i] = new int[V];
            for (int j = 0; j < V; ++j) {
                adj_matrix[i][j] = INT_MAX;  // Initialize all edges with maximum value (no connection)
            }
        }
    }

    // Destructor to free dynamically allocated memory
    ~Graph() {
        for (int i = 0; i < V; ++i) {
            delete[] adj_matrix[i];
        }
        delete[] adj_matrix;
    }

    // Method to add an undirected edge between vertices u and v with weight w
    void addEdge(int u, int v, int w) {
        adj_matrix[u][v] = w;
        adj_matrix[v][u] = w;
    }

    // Method to add a directed edge from vertex u to vertex v with weight w
    void addEdgeDirecte(int u, int v, int w) {
        adj_matrix[u][v] = w;
    }

    // Method to remove an undirected edge between vertices u and v
    void removeEdge(int u, int v) {
        adj_matrix[u][v] = INT_MAX;
        adj_matrix[v][u] = INT_MAX;
    }

    // Method to remove a directed edge from vertex u to vertex v
    void removeEdgeDirected(int u, int v) {
        adj_matrix[u][v] = INT_MAX;
    }

    // Method to get the weight of the edge between vertices u and v
    int getWeight(int u, int v) {
        return adj_matrix[u][v];
    }

    // Dijkstra's algorithm to find the shortest path from start to target vertex
    string AlgorithmDijkstra(int start, int target) {
        vector<int> dist(V, INT_MAX);   // Distance from start to each vertex
        vector<int> prev(V, -1);        // Previous vertex in the shortest path
        vector<bool> visited(V, false); // Visited vertices
        dist[start] = 0;                // Distance from start to itself is 0

        // Iterate V-1 times to find shortest paths to all vertices
        for (int count = 0; count < V - 1; ++count) {
            int u = -1;
            // Find the vertex with the smallest distance that hasn't been visited
            for (int i = 0; i < V; ++i) {
                if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                    u = i;
                }
            }
            visited[u] = true;  // Mark the vertex as visited

            // Update distances to adjacent vertices of u
            for (int v = 0; v < V; ++v) {
                int weight = adj_matrix[u][v];
                if (weight != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u; // Update predecessor
                }
            }
        }

        // Build the result string based on whether a path exists to the target vertex
        if (dist[target] == INT_MAX) {
            return "No path exists from " + string(1, 'A' + start) + " to " + string(1, 'A' + target);
        }
        else {
            return "Shortest path from " + string(1, 'A' + start) + " to " + string(1, 'A' + target) + " is " + to_string(dist[target]) + "\nPath:" + getPath(prev, target);
        }
    }
};

// Unit tests for the Graph class using Google Test framework

// Test case for when there's no path from A to E
TEST(GraphTest, NoPathExists) {
    Graph g(5);
    g.addEdge(0, 1, 1);
    string result = g.AlgorithmDijkstra(0, 4);
    EXPECT_EQ("No path exists from A to E", result);
}

// Test case for when there's a path from A to C
TEST(GraphTest, PathExists) {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 10);
    string result = g.AlgorithmDijkstra(0, 2);
    EXPECT_EQ("Shortest path from A to C is 3\nPath: A B C", result);
}

// Test case for path from A to itself
TEST(GraphTest, PathToSelf) {
    Graph g(1);
    string result = g.AlgorithmDijkstra(0, 0);
    EXPECT_EQ("Shortest path from A to A is 0\nPath: A", result);
}

// Test case for a small graph
TEST(GraphTest, SmallGraph) {
    Graph g(2);
    g.addEdge(0, 1, 1);
    string result = g.AlgorithmDijkstra(0, 1);
    EXPECT_EQ("Shortest path from A to B is 1\nPath: A B", result);
}

// Test case for an empty graph
TEST(GraphTest, EmptyGraph) {
    Graph g(3);
    string result = g.AlgorithmDijkstra(0, 2);
    EXPECT_EQ("No path exists from A to C", result);
}

// Test case for a large graph
TEST(GraphTest, LargeGraph) {
    Graph g(10);
    for (int i = 0; i < 9; ++i) {
        g.addEdge(i, i + 1, 1);
    }
    string result = g.AlgorithmDijkstra(0, 9);
    EXPECT_EQ("Shortest path from A to J is 9\nPath: A B C D E F G H I J", result);
}

// Test case for a graph with loops
TEST(GraphTest, GraphWithLoops) {
    Graph g(3);
    g.addEdge(0, 0, 1);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    string result = g.AlgorithmDijkstra(0, 2);
    EXPECT_EQ("Shortest path from A to C is 3\nPath: A B C", result);
}

// Test case for removing an edge
TEST(GraphTest, RemoveEdge) {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.removeEdge(0, 1);
    EXPECT_EQ(INT_MAX, g.getWeight(0, 1)); // Check if the edge weight is set to INT_MAX
}

// Test case for a directed graph
TEST(GraphTest, DirectedGraph) {
    Graph g(3);
    g.addEdgeDirecte(0, 1, 1);
    string resultForward = g.AlgorithmDijkstra(0, 1);
    EXPECT_EQ("Shortest path from A to B is 1\nPath: A B", resultForward);

    string resultBackward = g.AlgorithmDijkstra(1, 0);
    EXPECT_EQ("No path exists from B to A", resultBackward);
}

// Main function to run all the tests
int main() {
    Graph g(5);

    g.addEdge(0, 3, 1); // A-D
    g.addEdge(0, 1, 6); // A-B
    g.addEdge(1, 2, 5); // B-C
    g.addEdge(1, 3, 2); // B-D
    g.addEdge(1, 4, 2); // B-E
    g.addEdge(3, 4, 1); // D-E
    g.addEdge(2, 4, 5); // C-E

    // Print the result of Dijkstra's algorithm from vertex 0 to vertex 2
    cout << g.AlgorithmDijkstra(0, 2) << endl;
    cout << "-----------------" << endl;

    // Initialize Google Test and run all tests
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
