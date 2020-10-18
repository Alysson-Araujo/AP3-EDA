#ifndef graphm_h
#define graphm_h 
#include "graph.h"
#include <list>
#include <queue>
#include <stdexcept>
#include <tuple>

#define INFI 0x3f3f3f3f

using namespace std;


/**
 * Class GraphM: implementation of a graph as an adjacency matrix 
 */
class GraphM : public Graph {
private:
    int N;
    int M;
    int *filho;
    int **matrix;
    int *mark;
    int *funcionarios;
    string *nomes;
    bool *convidados;
    int *chefes;

    
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
        // Aloca memoria para o vetor Filho
        filho = new int[n];
        
        
        funcionarios = new int[n];

        nomes = new string[n];

        convidados = new bool[n];

        chefes = new int[n];
        chefes[0] = -1;
        for (int i = 0; i <= n - 1; ++i) {
            matrix[i] = new int[n];
            //por padrao, ninguem esta convidado, logo
            convidados[i] = false;
        }
        // Initialize matrix with 0's
        for (int i = 0; i <= n - 1; ++i) {
            for (int j = 0; j <= n - 1; ++j)
                matrix[i][j] = 0;
        }
    }

    // Destructor
    ~GraphM() {
        delete[] filho;
        delete[] mark;
        for (int i = 0; i < N; i++)
            delete[] matrix[i];
        delete[] matrix;
        delete[] nomes;
        delete[] funcionarios;
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
        matrix[v2][v1] = wgt;
    
    }

    // Add an edge
    void addEdge(int v1, int v2) {
        setEdgeWeight(v1, v2, 1);
        //Coloca quem é chefe de quem
        chefes[v1] = v2;
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

    bool nome_existe(string nome){
        for(int i = 0; i < N; i++){
            if(nome == nomes[i])
                return true;
        }
        return false;
    }


    
    string getNome(int id){
         return nomes[id];
    }

    int getMark(int v) {
        checkVertex(v);
        return mark[v];
    }

    int getFuncionarios(int v){
        checkVertex(v);
        return funcionarios[v];
    }
    int getFilho(int v) {
        checkVertex(v);
        return filho[v];
    }
    int getMatrix(int x, int y) {
        checkVertex(x);
        checkVertex(y);
        return matrix[x][y];
    }
    int getN() {
        return N;
    }

    void setFuncionarios(int v, int x) {
        checkVertex(v);
        funcionarios[v] = x;
    }
        
    void setNomes(int v, string value) {
            checkVertex(v);
            nomes[v] = value;
        }

    void setMark(int v, int value) {
        checkVertex(v);
        mark[v] = value;
    }


    void setFilho(int f, int p) {
        checkVertex(f);
        this->filho[f] = p;
    }
    
    void setNome(std::string pessoa, int pos){
        nomes[pos] = pessoa;
    }

     void imprimeNomes(){
        for(int i =0; i<N;i++){
            cout <<nomes[i]<<endl;
        }
    }
/*
    void getNome(int i){
        cout << nomes[i] << endl;
    }
*/
    void imprimeChefes() {
        for (size_t i = 1; i < N; i++)
        {
            cout << nomes[chefes[i]] << "->" << nomes[i] << endl;
        }
        
    }

     int getChefes(int i){
         return chefes[i];
     }
     bool getConvidados(int i){
         return convidados[i];
     }

    void setConvidados(int i, bool entr){
        convidados[i] = entr;
    }
};
#endif
