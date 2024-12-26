#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <utility>

using namespace std;

// Требуется отыскать самый короткий маршрут между городами.
// Из города может выходить дорога, которая возвращается в этот же город.

// Требуемое время работы O((N + M)log N),
// где N – количество городов, M – известных дорог между ними.

// Формат ввода
// Первая строка содержит число N – количество городов, 3 ≤ N ≤ 10000.
// Вторая строка содержит число M - количество дорог, 1 ≤ M ≤ 250000.
// Каждая следующая строка содержит три числа u, v, w – описание дороги:
// откуда, куда, время в пути. 0 ≤ u < N, 0 ≤ v < N, 1 ≤ w ≤ 10000. Между любыми двумя городами может быть больше одной дороги.
// Последняя строка содержит два числа: s и t – маршрут (откуда и куда нужно доехать). 0 ≤ s < N, 0 ≤ t < N.

// Формат вывода
// Вывести длину самого короткого маршрута.

int dijkstra(int n, const vector<vector<pair<int, int>>> &graph, int start, int end) {
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (current_dist <= dist[u]) {
            for (auto [v, weight] : graph[u]) {
                int new_dist = current_dist + weight;
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    pq.emplace(new_dist, v);
                }
            }
        }
    }

    return dist[end] != INT_MAX ? dist[end] : -1;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    int s, t;
    cin >> s >> t;

    cout << dijkstra(n, graph, s, t) << endl;
    return 0;
}


