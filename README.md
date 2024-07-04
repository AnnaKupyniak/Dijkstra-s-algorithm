# Dijkstra's algorithm in C++

This repository contains implementations of Dijkstra's algorithm for finding the shortest path in a graph.

## Introduction

This project provides a `Graph` class that supports operations like adding edges, removing edges, and finding the shortest path using Dijkstra's algorithm. It uses an adjacency matrix representation for simplicity.

## Features

- **Graph Class**: Implements basic operations on a graph such as adding edges, removing edges, and finding shortest paths.
- **Dijkstra's Algorithm**: Utilizes Dijkstra's algorithm to compute the shortest path from a starting vertex to a target vertex.
- **Unit Tests**: Includes unit tests using Google Test framework to verify the correctness of graph operations and algorithms.

## Usage

To use the `Graph` class and Dijkstra's algorithm in your project:

1. **Include the Source Files**: Add the `Graph.cpp` and `Graph.h` files to your project.
   
2. **Instantiate the Graph**: Create a `Graph` object with a specified number of vertices.

    ```cpp
    Graph g(5); // Create a graph with 5 vertices
    ```

3. **Add Edges**: Use the `addEdge` method to add edges between vertices.

    ```cpp
    g.addEdge(0, 1, 1); // Add an undirected edge between vertices 0 and 1 with weight 1
    ```

4. **Run Dijkstra's Algorithm**: Use the `AlgorithmDijkstra` method to find the shortest path between vertices.

    ```cpp
    string shortestPath = g.AlgorithmDijkstra(0, 4); // Find the shortest path from vertex 0 to vertex 4
    cout << "Shortest path: " << shortestPath << endl;
    ```

5. **Compile and Run**: Compile your project and run the executable to see the results.

## Running Tests

To run the unit tests for the `Graph` class:

1. **Compile with Google Test**: Make sure you have Google Test installed. Compile your project with Google Test linked.

2. **Execute Tests**: Run the executable to execute all the unit tests.

## Examples

Check the `main.cpp` file for example usage of the `Graph` class and Dijkstra's algorithm.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please create an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
