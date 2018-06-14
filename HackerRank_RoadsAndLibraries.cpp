#include <iostream>
#include <memory>
#include <list>
#include <limits>
#include <queue>
#include <fstream>
#include <string>
#include <unordered_set>
#include <stack>
#include <unordered_map>


using namespace std;
vector<string> split_string(string);

enum class EColor
{
    White,
    Grey,
    Black
};

using Edges = std::vector<std::vector<int>>;

std::unordered_map<int, int> bfs(int n, Edges& edges, int start) {
    if (edges[start].empty())
        return std::unordered_map<int, int>();

    std::unordered_map<int, int> distances;
    std::vector<bool> mark(n, false);
    mark[start] = true;
    distances[start] = 0;
    queue<int> vertexQueue;
    vertexQueue.push(start);
    while (!vertexQueue.empty()) {
        int vertex = vertexQueue.front();
        vertexQueue.pop();

        for (auto it = edges[vertex].begin(); it != edges[vertex].end(); ++it)
        {
            int v = *it;
            if (mark[v] == false) {
                mark[v] = true;
                distances[v] = distances[vertex] + 1;
                vertexQueue.push(v);
            }
        }
    }

    return distances;
}

using uLongLong = unsigned long long;
// Complete the roadsAndLibraries function below.
uLongLong roadsAndLibraries(int n, long long c_lib, long long c_road, Edges& edges)
{
    if (c_lib <= c_road)
        return (uLongLong)c_lib * (uLongLong)n;

    
    long long libsCount = 0;
    long long roadsCount = 0;
    std::unordered_set<int> visited;
    for (int start = 0; start < n; ++start)
    {
        if (visited.find(start) != visited.end())
            continue;

        auto distances = bfs(n, edges, start);
        visited.insert(start);
        libsCount++;

        for ( const auto& distancePair : distances)
        {
            if (distancePair.second > 0)
            {
                visited.insert(distancePair.first);
                roadsCount++;
            }
        }
    }

    return (long long)libsCount * (long long)c_lib + (long long)roadsCount * (long long)c_road;
}

int main()
{
    ifstream inFile("D:\\work\\hackerRankTestCase.txt");
    long q;
    //cin >> q;
    inFile >> q;
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {        

        cout << "case:" << q_itr << endl;

        long n, m, c_lib, c_road;
        inFile >> n >> m >> c_lib >> c_road;

        Edges edges(n);

        for (int i = 0; i < m; i++) {
            int startV;
            int endV;
            inFile >> startV >> endV;
            startV--;
            endV--;
            edges[startV].push_back(endV);
            edges[endV].push_back(startV);
        }


        uLongLong result = roadsAndLibraries(n, c_lib, c_road, edges);

        cout << result << "\n";
    }

    inFile.close();
    return 0;
}
