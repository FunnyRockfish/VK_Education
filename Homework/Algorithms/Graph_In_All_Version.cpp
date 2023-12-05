/*
Необходимо написать несколько реализаций интерфейса:
ListGraph, хранящий граф в виде массива списков смежности,
MatrixGraph, хранящий граф в виде матрицы смежности,
SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
ArcGraph, хранящий граф в виде одного массива пар {from, to}.
Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.

*/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <functional>
#include <cassert>

using namespace ::std;

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;
    virtual int EdgesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

struct ListGraph: public IGraph
{
public:
    ListGraph(int size)
            : adjacencyLists(size)
    {
    }

    ListGraph(const IGraph &graph)
            : adjacencyLists(graph.VerticesCount())
    {
        for (int i = 0; i < graph.VerticesCount(); i++)
        {
            adjacencyLists[i] = graph.GetNextVertices(i);
        }
    }

    ~ListGraph()
    {
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
    }

    int VerticesCount() const override
    {
        return static_cast<int>(adjacencyLists.size());
    }

    int EdgesCount() const override{
        int counter= 0;
        for (int i = 0; i < adjacencyLists.size(); i++){
            counter += adjacencyLists[i].size();
        }
        return counter;
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;

        for (int from = 0; from < adjacencyLists.size(); from++)
        {
            for (int to: adjacencyLists[from])
            {
                if (to == vertex)
                {
                    prevVertices.push_back(from);
                }
            }
        }
        return prevVertices;
    }

private:
    std::vector<std::vector<int>> adjacencyLists;
};
///////////////
struct ArcGraph : public IGraph
{
public:
    struct edge{
        int from;
        int to;
    };

    ArcGraph(int size)
            : edges(size)
    {
    }

    ArcGraph(const IGraph &graph)
            : edges(0)
    {
        vector<bool> usedVerts(5);
        for (int i = 0; i < graph.VerticesCount(); i++)
        {
            vector<int > verts = graph.GetNextVertices(i);
            for (int j = 0; j < verts.size(); j++)
            {
                edges.push_back({i, verts[j]});
                //edges[i].from = i;
                //edges[i].to = verts[j];
                while((i > usedVerts.size()) || (verts[j] > usedVerts.size())){
                    vector<bool> newUsedVerts(usedVerts.size() * 2);
                    for (int i = 0; i < usedVerts.size(); i++){
                        newUsedVerts[i] = usedVerts[i];
                    }
                    usedVerts = newUsedVerts;
                }
                if (usedVerts[i] == false){
                    verCounter++;
                    usedVerts[i] = true;
                }
                if (usedVerts[verts[j]] == false){
                    verCounter++;
                    usedVerts[verts[j]] = true;
                }
                cout << "New Ver: " << i << " " << verts[j] << endl;
            }
        }
        for (int i= 0; i < edges.size(); i++){
            cout << edges[i].from << " -> " << edges[i].to << endl;
        }
        cout << endl;
    }

    ~ArcGraph()
    {
    }

    void AddEdge(int from, int to) override
    {
        edges.push_back({from, to});
    }

    int VerticesCount() const override
    {
        return verCounter - 1;
    }

    int EdgesCount() const override{
        return edges.size();
    }

    vector<int> GetNextVertices(int vertex) const override
    {
       // cout << "len of edges = " << edges.size() << endl;
        assert(0 <= vertex && vertex < verCounter);
        vector<int> NextVertices;
        for (int i = 0; i < edges.size(); i++){
            if (edges[i].from == vertex){
               // cout << "found the cheold for " << vertex << " = " << edges[i].to << endl;
                NextVertices.push_back(edges[i].to);
            }
        }
        return NextVertices;
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < edges.size());
        std::vector<int> prevVertices;
        for (int i = 0; i < edges.size(); i++){
            if (edges[i].to == vertex){
                prevVertices.push_back(edges[i].from);
            }
        }

        return prevVertices;
    }

private:
    int verCounter = 0;
    vector<edge> edges;
};

/////////////////
struct MatrixGraph : public IGraph
{
public:
    MatrixGraph(int size)
            : Matr(size)
    {
    }

    MatrixGraph(const IGraph &graph)
            : Matr(graph.VerticesCount())
    {
        for (int i = 0; i < graph.VerticesCount(); i++){
            Matr[i] = vector<int>(graph.VerticesCount());
        }
        for (int i = 0; i < graph.VerticesCount(); i++){
            vector<int> nextVerts = graph.GetNextVertices(i);
            vector<int> prevVerts = graph.GetPrevVertices(i);
            for (int j = 0; j < nextVerts.size(); j++){
                int elem = nextVerts[j]; /// i -> elem
                Matr[elem][i] = 1;
                cout << i << " -> " << elem << endl;
                edgeCounter++;
            }
            for (int j = 0; j < prevVerts.size(); j++){
                int elem = prevVerts[j]; /// elem -> i
                //Matr[i][elem] = 1;
                //cout << elem << " -> " << i << endl;
                //edgeCounter++;
            }
        }
    }

    ~MatrixGraph()
    {
    }

    void AddEdge(int from, int to) override
    {
        Matr[to][from] = 1;
    }

    int VerticesCount() const override
    {
        return Matr.size();
    }

    int EdgesCount() const override{
        //cout << "EDGES COUNT = " << edgeCounter << endl;
        return edgeCounter;
    }

    vector<int> GetNextVertices(int vertex) const override
    {
        // cout << "len of edges = " << edges.size() << endl;
        assert(0 <= vertex && vertex < Matr.size());
        vector<int> NextVertices;
        for (int i = 0; i < Matr.size(); i++){
            if (Matr[i][vertex] == 1){
                NextVertices.push_back(i);
            }
        }
        return NextVertices;
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < Matr.size());
        std::vector<int> prevVertices;
        for (int i = 0; i < Matr.size(); i++){
            if (Matr[vertex][i] == 1){
                prevVertices.push_back(i);
            }
        }

        return prevVertices;
    }

private:
    int edgeCounter = 0;
    vector<vector<int>> Matr;
};
/////////////////


struct SetGraph : public IGraph
{
public:
    SetGraph(int size)
            : edges(size), nodes(size), visited(size)
    {
    }

    struct Node{
        int id;
    };

    SetGraph(const IGraph &graph)
            : nodes(graph.VerticesCount()), edges(graph.EdgesCount()), visited(graph.VerticesCount()), hasElems(graph.VerticesCount())
    {
        for (int i = 0; i < graph.VerticesCount(); i++){
            edges[i] = {};
            if (visited[i] == false){
                vector<int> ver = graph.GetNextVertices(i);
                if (ver.size() != 0){
                    hasElems[i] = true;
                }
                nodes[i].id = i; /// пока не знаю, нужно или нет
                for (int j = 0; j < ver.size(); j++){
                    EdgeCounter++;
                    edges[i].push_back(ver[j]);
                }

            }
        }
    }

    ~SetGraph()
    {
    }

    void AddEdge(int from, int to) override
    {
        edges[from].push_back(to);
    }

    int VerticesCount() const override
    {
        return nodes.size();
    }

    int EdgesCount() const override{
        //cout << "EDGES COUNT = " << edgeCounter << endl;
        return EdgeCounter;
    }

    vector<int> GetNextVertices(int vertex) const override {
        if (vertex < nodes.size()) {
            if (hasElems[vertex] == true) {
                return edges.at(vertex);
            } else {
                return {};
            }
        }
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < nodes.size());
        vector<int> PrevVertices;
        if (vertex < edges.size()) {
            if (hasElems[vertex] == true){
                for (int i = 0; i < edges.size(); i++) {
                    for(int j = 0; j < edges.at(i).size(); j++) {
                        if (edges.at(i).at(j) == vertex) {
                            PrevVertices.push_back(i);
                        }
                    }
                }
            }
        }
        return PrevVertices;
    }

private:
    unordered_map<int, Node> nodes;  // Хеш-таблица для хранения узлов
    unordered_map<int, vector<int>> edges;  // Хеш-таблица для хранения ребер
    int EdgeCounter = 0;
    vector<bool> visited;
    vector<bool> hasElems;
};

////////////////

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, std::function<void(int)> &func)
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

void BFS(const IGraph &graph, std::function<void(int)> func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            BFS(graph, i, visited, func);
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, std::function<void(int)> &func)
{
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
            DFS(graph, nextVertex, visited, func);
    }
}

void DFS(const IGraph &graph, std::function<void(int)> func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            DFS(graph, i, visited, func);
    }
}

void topologicalSort(const IGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted)
{
    visited[vertex] = true;

    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
            topologicalSort(graph, nextVertex, visited, sorted);
    }

    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph &graph)
{
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            topologicalSort(graph, i, visited, sorted);
    }

    return sorted;
}

int main(int argc, const char * argv[])
{
    ListGraph listGraph(9);
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
    listGraph.AddEdge(7, 8);

    ArcGraph arcGraphFromList(listGraph);
    MatrixGraph matrGraph(arcGraphFromList);
    SetGraph setGraphFromMatrix(matrGraph);

    cout << "BFS FOR LIST" << endl;
    BFS(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    cout << "BFS FOR ARC" << endl;
    BFS(arcGraphFromList, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    cout << "BFS FOR MATRIX" << endl;
    BFS(matrGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    cout << "BFS FOR SET" << endl;
    BFS(setGraphFromMatrix, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    cout << "DFS FOR LIST" << endl;
    DFS(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    cout << "DFS FOR ARC" << endl;
    DFS(arcGraphFromList, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    cout << "DFS FOR MATRIX" << endl;
    DFS(matrGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    cout << "DFS FOR SET" << endl;
    DFS(setGraphFromMatrix, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    cout << "SORT FOR LIST" << endl;
    for (int vertex: topologicalSort(listGraph))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    // Нужно продемонстрировать работу конструктора копирования, проинициализировав
    // графы разных классов друг от друга. Далее, показать, что вершины и ребра
    // успешно скопированы: число вершин осталось прежним, произвести BFS и DFS.
    // ArcGraph arcGraph(listGraph);
    // MatrixGraph matrixGraph(arcGraph);
    // SetGraph setGraph(matrixGraph);

    return 0;
}
