#ifndef graphm_h
#define graphm_h
#include "graph.h"
#include <list>
#include <queue>
#include <stdexcept>


#define INFI 0x3f3f3f3f

using namespace std;

//enum Color {  WHITE   , BLACK };
//             #FFFFFF  #000000

/**
 * Class GraphM: implementation of a graph as an adjacency matrix 
 */
class GraphM : public Graph {
private:
    int N; //quantidade de vertices
    int M; //quantidade de arestas
    int *pai; //pai do vertice (-1 para o start)
    int *distancia; //distacia do start do bfs
    int **matrix; //matriz de vertices
    int *mark;  //marcas no percurso bfs
    int *color; // 1 = vermelho --- 2 = preto

    // Check if a vertex v is valid ( 0 <= v <= N-1 )
    void checkVertex(int v) {
        if (v < 0 || v > N - 1)
            throw std::runtime_error("Intervalo de valor de vertice invalido");
    }

public:
    // Constructor
    GraphM(int n) {
        if (n <= 0)
            throw std::runtime_error("Tamanho invalido");
        N = n;
        M = 0;
        // Aloccate memory for mark array
        mark = new int[n];
        // Allocate memory for a matrix n x n
        matrix = new int *[n];
        // Aloca memoria para o vetor pai
        pai = new int[n];
        // Aloca memoria para o vetor distancia
        distancia = new int[n];

        color = new int[n];

        for (int i = 0; i <= n - 1; ++i) {
            matrix[i] = new int[n];
        }
        // Initialize matrix with 0's
        for (int i = 0; i <= n - 1; ++i) {
            color[i] = -1;
            for (int j = 0; j <= n - 1; ++j)
                matrix[i][j] = 0;
        }
    }

    // Destructor
    ~GraphM() {
        delete[] pai;
        delete[] distancia;
        delete[] mark;
        for (int i = 0; i < N; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    // Return: the number of vertices and edges respectively
    int n() { return N; }
    int m() { return M; }

    // Return a list containing v's incident edges
    std::list<Edge> &incidentEdges(int v) {
        std::list<Edge> *lst = new std::list<Edge>();
        for (int i = 0; i < N; ++i) {
            if (matrix[v][i] != 0) {
                lst->push_back(Edge(i, matrix[v][i]));
            }
        }
        return *lst;
    }

    // Return a list containing vertex v's neighbors
    std::list<int> &neighbors(int v) {
        std::list<int> *lst = new std::list<int>();

        for (int i = 0; i < N; ++i) {
            if (matrix[v][i] != 0) {
                lst->push_back(i);
            }
        }
        return *lst;
    }

    void setEdgeWeight(int v1, int v2, int wgt) {
        if (wgt <= 0)
            throw std::runtime_error("Peso negativo ou igual a zero");
        if (!isEdge(v1, v2))
            ++M;
        matrix[v1][v2] = wgt;
    }

    // Add an edge
    void addEdge(int v1, int v2) {
        setEdgeWeight(v1, v2, 1);
    }

    // Delete an edge
    void delEdge(int v1, int v2) {
        if (isEdge(v1, v2)) {
            M--;
            matrix[v1][v2] = 0;
        }
    }

    // Determine if an edge is in the graph
    bool isEdge(int v1, int v2) {
        return (matrix[v1][v2] > 0);
    }

    int weight(int v1, int v2) {
        checkVertex(v1);
        checkVertex(v2);
        if (isEdge(v1, v2))
            return matrix[v1][v2];
        else
            return 0;
    }


    //gets
    int getMark(int v) {
        checkVertex(v);
        return mark[v];
    }

    int getCor(int v){
        checkVertex(v);
        return color[v];
    }

    int getPai(int v) {
        checkVertex(v);
        return pai[v];
    }
    int getDistancia(int v) {
        checkVertex(v);
        return distancia[v];
    }
    int getMatrix(int x, int y) {
        checkVertex(x);
        checkVertex(y);
        return matrix[x][y];
    }
    int getN() {
        return N;
    }
    //sets
    void setMark(int v, int value) {
        checkVertex(v);
        mark[v] = value;
    }

    void setDistancia(int v, int distancia) {
        checkVertex(v);
        this->distancia[v] = distancia;
    }

    void setPai(int f, int p) {
        checkVertex(f);
        this->pai[f] = p;
    }

    void setCor(int v, int x) {
        checkVertex(v);
        this->color[v] = x;
    }
    
    void imprimeCores() {
        string cor;
        for (int i = 0; i < N; i++) {
            if(color[i] == 1)
                cout << i << " " << "R" << endl;
            else
                cout << i << " " << "B" << endl;
        }
    }
    
};
#endif
