#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

// Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. 
// Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).

// Формат ввода
// v: кол-во вершин (макс. 50000),
// n: кол-во ребер(макс. 200000),
// n пар реберных вершин,
// пара вершин (u, w) для запроса.

// Формат вывода
// Количество кратчайших путей от v к w.

using namespace std;

int find_num_paths(int num_vertices, vector<pair<int, int>>& edges, int from, int to) {
    vector<vector<int>> graph(num_vertices + 1);
    for (auto& edge : edges) {
        int a = edge.first, b = edge.second;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> dist(num_vertices + 1, INT_MAX);
    vector<int> path_count(num_vertices + 1, 0);

    queue<int> q;

    dist[from] = 0;
    path_count[from] = 1;
    q.push(from);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : graph[node]) {
            if (dist[neighbor] == INT_MAX) {
                dist[neighbor] = dist[node] + 1;
                path_count[neighbor] = path_count[node];
                q.push(neighbor);
            } else if (dist[neighbor] == dist[node] + 1) {
                path_count[neighbor] += path_count[node];
            }
        }
    }

    return path_count[to];
}

int main() {
    int num_vertices, num_edges;
    cin >> num_vertices >> num_edges;

    vector<pair<int, int>> edges(num_edges);
    for (int i = 0; i < num_edges; i++) {
        int a, b;
        cin >> a >> b;
        edges.push_back({a, b});
    }

    int from, to;
    cin >> from >> to;

    int result = find_num_paths(num_vertices, edges, from, to);
    cout << result << endl;

    return 0;
}
