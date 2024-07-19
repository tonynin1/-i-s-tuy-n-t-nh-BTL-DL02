#include <iostream>
#include <vector>
#include <climits>
#include "Floyd.h"

using namespace std;


// Constructor of Floyd object
Floyd::Floyd(string fileName) {
    ifstream file(fileName);
    if (!file) {
        cout << "Error: File not found" << endl;
        return;
    }

    int V;
    file >> V;
    this->graph = vector<vector<int>>(V, vector<int>(V, INF));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            string temp = "";
            file >> temp;

            if (temp == "inf")
                graph[i][j] = INF;
            else
                graph[i][j] = stoi(temp);
        }
    }
    file.close();

    return;
}

// Function to print the path from vertex u to vertex v using the predecessor matrix
void Floyd::printPath(vector<vector<int>>& next, int u, int v) {
    if (next[u][v] == -1) {
        cout << "No path\n";
        return;
    }
    vector<int> path;
    for (; u != v; u = next[u][v]) {
        if (u == -1) {
            cout << "No path\n";
            return;
        }
        path.push_back(u);
    }
    path.push_back(v);
    
    for (int i = 0; i < path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << path[i]+1;
    }
    cout << endl;
}


// Implementation of the Floyd-Warshall algorithm
void Floyd::Solve() {
    int V = graph.size();
    cout << "This graph has " << V <<  " vertices" << endl;
    vector<vector<int>> dist = graph;
    vector<vector<int>> next(V, vector<int>(V, -1));
    
    // Initialize the predecessor matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] != INF && i != j) {
                next[i][j] = j;
            }
        }
    }

    // Apply Floyd-Warshall algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Print the shortest distance matrix
    cout << "Shortest distance matrix:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }

    // Print the paths
    cout << "Paths:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j) {
                cout << "Path from " << i+1 << " to " << j+1 << ": ";
                printPath(next, i, j);
            }
        }
    }
}
