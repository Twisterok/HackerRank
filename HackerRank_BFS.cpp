#include <iostream>
#include <memory>
#include <list>
#include <limits>
#include <queue>
#include <fstream>
#include <string>


using namespace std;
vector<string> split_string(string input_string);

namespace
{
    enum class EColor
    {
        White,
        Grey,
        Black
    };

    bool HasEdge(const vector<vector<int>>& edges, int from, int to)
    {
        if (from < 0 || from >= (int)edges.size())
            return false;

        if (to < 0 || to >= (int)edges[from].size())
            return false;

        return edges[from][to] > 0;
    }
}


vector<int> bfs(int n, int m, const vector<vector<int>>& edges, int start) {
    std::vector<int> distances(n, -1);
    std::vector<EColor> mark(n, EColor::White);

    queue<int> vertexQueue;

    vertexQueue.push(start);
    distances[start] = 0;
    mark[start] = EColor::Grey;

    while (!vertexQueue.empty())
    {
        int vertex = vertexQueue.front();
        vertexQueue.pop();
        for (int i = 0; i < (int)edges[vertex].size(); ++i)
        {
            if (!HasEdge(edges, vertex, i))
                continue;

            if (mark[i] == EColor::White)
            {
                distances[i] = distances[vertex] + 1;
                mark[i] = EColor::Grey;
                vertexQueue.push(i);
            }
        }
        mark[vertex] = EColor::Black;
    }

    return distances;
}

int main()
{
    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nm_temp;
        getline(cin, nm_temp);

        vector<string> nm = split_string(nm_temp);

        int n = stoi(nm[0]);

        int m = stoi(nm[1]);

        vector<vector<int>> edges(n, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            int startV;
            int endV;
            cin >> startV >> endV;
            startV--;
            endV--;
            edges[startV][endV] = 1;
            edges[endV][startV] = 1;
        }

        int s;
        cin >> s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        s--;

        vector<int> result = bfs(n, m, edges, s);

        for (int i = 0; i < (int)result.size(); i++) {
            if (i == s)
                continue;
            if (result[i] >= 0)
                cout << result[i] * 6;
            else
                cout << result[i];

            if (i != result.size() - 1) {
                cout << " ";
            }
        }

        cout << "\n";
    }

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
}