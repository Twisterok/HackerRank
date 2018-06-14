#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;
enum class EColor
{
    White,
    Grey,
    Black
};
using Edges = std::vector<std::vector<int>>;
vector<string> split_string(string);

vector<int> bfs(int n, Edges& edges, int start) {
    if (edges[start].empty())
        return vector<int>();

    std::vector<int> distances(n, -1);
    std::vector<EColor> mark(n, EColor::White);
    std::vector<int> prev(n, -1);
    mark[start] = EColor::Grey;
    prev[start] = start;
    distances[start] = 0;
    queue<int> vertexQueue;
    vertexQueue.push(start);
    while (!vertexQueue.empty()) {
        int vertex = vertexQueue.front();
        vertexQueue.pop();

        for (auto it = edges[vertex].begin(); it != edges[vertex].end(); ++it)
        {
            int v = *it;
            if (mark[v] == EColor::White) {
                mark[v] = EColor::Grey;
                prev[v] = vertex;
                distances[v] = distances[vertex] + 1;
                vertexQueue.push(v);
            }
        }
        mark[vertex] = EColor::Black;
    }

    return distances;
}

// Complete the journeyToMoon function below.
long long journeyToMoon(int n, Edges astronaut) {

    std::unordered_set<int> visited;
    std::vector<int> countrySizes;
    for (int start = 0; start < n; ++start)
    {
        if (visited.find(start) != visited.end())
            continue;

        auto distances = bfs(n, astronaut, start);
        visited.insert(start);
        
        countrySizes.push_back(1);
        
        for (int i = 0; i < (int)distances.size(); ++i)
        {
            if (distances[i] > 0)
            {
                visited.insert(i);
                countrySizes.back()++;
            }
        }
    }

    long long numPairs = 0L;
    long long numPartners = n;
    for (int countrySize : countrySizes) {
        numPairs += countrySize * (numPartners -= countrySize);
    }

    return numPairs;
}

/*int main()
{
    //ofstream fout("out.txt");

    ifstream inFile("D:\\work\\hackerRankTestCase4.txt");
    string np_temp;
    getline(inFile, np_temp);

    vector<string> np = split_string(np_temp);

    int n = stoi(np[0]);

    int p = stoi(np[1]);

    Edges edges(n);

    for (int i = 0; i < p; i++) {
        int startV;
        int endV;
        inFile >> startV >> endV;
        edges[startV].push_back(endV);
        edges[endV].push_back(startV);
    }

    long long result = journeyToMoon(n, edges);

    cout << result << "\n";

    inFile.close();
    //fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
        return x == y && x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}*/
