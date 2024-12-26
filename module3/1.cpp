#include <iostream>
#include <functional>
// #include <utility>
#include <vector>
#include <set>
#include <cassert>
#include <queue>
#include <deque>

struct IGraph {
    virtual ~IGraph() {}
        
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

//__________________________________________________ListGraph___________________________________________________


struct ListGraph : public IGraph {
public:
    ListGraph(int size) : adjacencyLists(size) {};
    ListGraph(const IGraph& graph) : adjacencyLists(graph.VerticesCount()) {
        for (int i = 0; i < graph.VerticesCount(); ++i) {
            adjacencyLists[i] = graph.GetNextVertices(i);
        }
    }

    void AddEdge(int from, int to) override {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
    }
    int VerticesCount() const override {
        return adjacencyLists.size();
    }
    std::vector<int> GetNextVertices(int vertex) const override {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }
    std::vector<int> GetPrevVertices(int vertex) const override {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;

        for (int from = 0; from < adjacencyLists.size(); ++from) {
            for (int to : adjacencyLists[from]) {
                if (to == vertex) {
                    prevVertices.push_back(from);
                }
            }
        }
        return prevVertices;
    }
private:
    std::vector<std::vector<int>> adjacencyLists;
};

//______________________________________________MatrixGraph___________________________________________________

struct MatrixGraph : public IGraph {
public:
    MatrixGraph(int size) : adjacencyMatrix(size, std::vector<bool>(size, false)) {}
    MatrixGraph(const IGraph& graph) 
    : adjacencyMatrix(graph.VerticesCount(), std::vector<bool>(graph.VerticesCount(), false)) {
        for (int i = 0; i < graph.VerticesCount(); ++i) {
            for (int vertex : graph.GetNextVertices(i)) {
                AddEdge(i, vertex);
            }
        }
    }

    void AddEdge(int from, int to) override {
        assert(0 <= from && from < adjacencyMatrix.size());
        assert(0 <= to && to < adjacencyMatrix.size());
        adjacencyMatrix[from][to] = true;
    }

    int VerticesCount() const override {
        return adjacencyMatrix.size();
    }
    std::vector<int> GetNextVertices(int vertex) const override {
        assert(0 <= vertex && vertex < adjacencyMatrix.size());
        std::vector<int> nextVertices;
        for (int i = 0; i < adjacencyMatrix.size(); ++i) {
            if (adjacencyMatrix[vertex][i]) {
                nextVertices.push_back(i);
            }
        }
        return nextVertices;
    }
    std::vector<int> GetPrevVertices(int vertex) const override {
        assert(0 <= vertex && vertex < adjacencyMatrix.size());
        std::vector<int> prevVertices;
        for (int i = 0; i < adjacencyMatrix.size(); ++i) {
            if (adjacencyMatrix[i][vertex]) {
                prevVertices.push_back(i);
            }
        }
        return prevVertices;
    }

private:
    std::vector<std::vector<bool>> adjacencyMatrix;
};

//_____________________________________________________SetGraph__________________________________________________
struct SetGraph : public IGraph {
public:
    SetGraph(int size) : adjacencySets(size) {}
    SetGraph(const IGraph& graph) : adjacencySets(graph.VerticesCount()) {
        for (int i = 0; i < graph.VerticesCount(); ++i) {
            for (int vertex : graph.GetNextVertices(i)) {
                AddEdge(i, vertex);
            }
        }
    }

    void AddEdge(int from, int to) override {
        adjacencySets[from].insert(to);
    }
    int VerticesCount() const override {
        return adjacencySets.size();
    }
    std::vector<int> GetNextVertices(int vertex) const override {
        return std::vector<int>(adjacencySets[vertex].begin(), adjacencySets[vertex].end());
    }
    std::vector<int> GetPrevVertices(int vertex) const override {
        std::vector<int> prevVertices;
        for (int from = 0; from < adjacencySets.size(); ++from) {
            if (adjacencySets[from].find(vertex) != adjacencySets[from].end()) {
                prevVertices.push_back(from);
            }
        }
        return prevVertices;
    }

private:
    std::vector<std::set<int>> adjacencySets;
};


//______________________________________________ArcGraph______________________________________________________
struct ArcGraph : public IGraph {
public:
    explicit ArcGraph(int size) : verticesCount(size) {}
    ArcGraph(const IGraph& graph) : verticesCount(graph.VerticesCount()) {
        for (int i = 0; i < graph.VerticesCount(); ++i) {
            for (int vertex : graph.GetNextVertices(i)) {
                AddEdge(i, vertex);
            }
        }
    }

    void AddEdge(int from, int to) override  {
        edges.push_back({from, to});
    }
    int VerticesCount() const override {
        return verticesCount;
    }
    std::vector<int> GetNextVertices(int vertex) const override {
        std::vector<int> nextVertices;
        for (const auto& edge : edges) {
            if (edge.first == vertex) {
                nextVertices.push_back(edge.second);
            }
        }
        return nextVertices;
    }
    std::vector<int> GetPrevVertices(int vertex) const override {
        std::vector<int> prevVertices;
        for (const auto& edge : edges) {
            if (edge.second == vertex) {
                prevVertices.push_back(edge.first);
            }
        }
        return prevVertices;
    }


private:
    int verticesCount;
    std::vector<std::pair<int, int>> edges;
};


void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;
    
    while (!qu.empty())
    {
        int currentVertex = qu.front();
        qu.pop();
        
        func(currentVertex);
        
        for (int nextVertex: graph.GetNextVertices(currentVertex))
        {
            if (!visited[nextVertex])
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph &graph, const std::function<void(int)> &func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            BFS(graph, i, visited, func);
        }
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
    visited[vertex] = true;
    func(vertex);
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            DFS(graph, nextVertex, visited, func);
        }
    }
}

void mainDFS(const IGraph &graph, const std::function<void(int)> &func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            DFS(graph, i, visited, func);
        }
    }
}

void topologicalSortInternal(const IGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted)
{
    visited[vertex] = true;
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            topologicalSortInternal(graph, nextVertex, visited, sorted);
        }
    }
    
    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph &graph)
{
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            topologicalSortInternal(graph, i, visited, sorted);
        }
    }
    
    return sorted;
}

int main(int argc, const char * argv[]) {
    ListGraph listGraph(7);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);
    

    std::cout << "ListGraph:\n";
    std::cout << "Vertices count: " << listGraph.VerticesCount() << '\n';
    mainBFS(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    
    mainDFS(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    
    for (int vertex: topologicalSort(listGraph))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;


    MatrixGraph MG(listGraph);
    std::cout << "\nMatrixGraph:\n";
    std::cout << "Vertices count: " <<  MG.VerticesCount() << '\n';

    mainBFS(MG, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    
    mainDFS(MG, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    
    for (int vertex: topologicalSort(MG))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    

    SetGraph SG(MG);
    std::cout << "\nSetGraph:\n";
    std::cout << "Vertices count: " <<  SG.VerticesCount() << '\n';

    mainBFS(SG, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    
    mainDFS(SG, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    
    for (int vertex: topologicalSort(SG))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;


    ArcGraph AG(SG);
    std::cout << "\nArcGraph:\n";
    std::cout << "Vertices count: " <<  AG.VerticesCount() << '\n';

    mainBFS(AG, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    
    mainDFS(AG, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    
    for (int vertex: topologicalSort(AG))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    // Нужно продемонстрировать работу конструктора копирования, проинициализировав
    // графы разных классов друг от друга. Далее, показать, что вершины и ребра
    // успешно скопированы: число вершин осталось прежним, произвести BFS и DFS.
    // MatrixGraph matrixGraph(listGraph);
    // ArcGraph arcGraph(matrixGraph);
    // SetGraph setGraph(arcGraph);
    return 0;
}
