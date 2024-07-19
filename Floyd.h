#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <string>

using namespace std;

const int INF = INT_MAX;

class Floyd {
private:
    vector<vector<int>> graph;
public:
    Floyd(string fileName);
    void printPath(vector<vector<int>>& next, int u, int v);
    void Solve();
};