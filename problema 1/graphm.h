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
    int N;
    int M;
    int *pai;
    int *distancia;
    int **matrix;
    int *mark;
    int *color; // 1 = vermelho --- 2 = preto --- 3 = preto

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
    // N == tamanho do grafo
    /*
    void correctColoring() {
        // vamos alterar as cores para algumas situações. Um exemplo que explicaria isso seria o seguinte
        /** 
         * suponha que temos um vértice 0 com filhos 3 4 5
         * Por padrão decidimos colocar as cores do vértice que tivessem cor -1
         * sendo vermelho, mas isso só vale o vértice que estamos pegando para
         * para ver os seus vizinhos e olhar suas cores. Logo 0 terá cor vermelha. Consequentemente, os seus vizinhos terão a cor preta para seguir a
         * regra dita no problema. Já que foi Pintado de preto para o 0, o próximo vértice v com cor inexistente (-1)
         * vai ser pintado de preto, pela regra que eu e o João pomos para esse problema. EX:
         * 
         *  (R)0 vizinhos ->3(P) 4(P) 5(P)
            (R) 1 vizinhos ->3(P) 4(P) 5(P)
            (R) 2 vizinhos ->3(P) 4(P) 5(P) 
            (P) 3 vizinhos ->0(R) 1(R) 2(R)
            (P) 4 vizinhos ->0(R) 1(R) 2(R)
            (P) 5 vizinhos ->0(R) 1(R) 2(R)
         * 
         * 
         * 
         * Indo para o próximo vértice, que seria o 1 que contém vizinhos 8 4 10 14. Como o vértice 1 não era vizinho
         * do 0, então sua cor ainda é inexistente (-1), logo pintariamos de vermelho pela regra, correto? Na verdade
         * não! Se fizéssemos isso, a regra das duas cores não iria funcionar já que o vértice 4, que é vizinho tanto do 1
         * quanto do 0, foi pintado de preto 
        */
       /*

        queue<int> fila;
        queue<int> aux_fila;

        color[0] = "R";

        bool vetor_cor_nao_cheio = true;
        bool falha_detectada = false;
        int vetor_olhado = 0;

        bool ja_visitado[N - 1];
        for (int i = 0; i < N; i++)
            ja_visitado[i] = false;

        while (vetor_cor_nao_cheio && !falha_detectada) {
            cout << "olhando o vertice: " << vetor_olhado << endl;

            for (int vizinhos2 : neighbors(vetor_olhado)) {

                if(ja_visitado[vizinhos2] == false){

                    cout << "\ninserindo o vizinho: " << vizinhos2 << " na fila\n";
                    fila.push(vizinhos2);
                    aux_fila.push(vizinhos2);

                    while (!aux_fila.empty()) {
                        if (color[aux_fila.front()] == "-1" && color[vetor_olhado] == "B") {
                            cout << ">>>>" << aux_fila.size() << "<<<<" << endl;
                            color[aux_fila.front()] = "R";
                            aux_fila.pop();
                            cout << " CASO 1 \n";
                            cout << ">>>>" << aux_fila.size() << "<<<<" << endl;

                        } else if (color[aux_fila.front()] == "-1" && color[vetor_olhado] == "R") {
                            cout << ">>>>" << aux_fila.size() << "<<<<" << endl;
                            color[aux_fila.front()] = "B";
                            aux_fila.pop();
                            cout << " CASO 2 \n";
                            cout << ">>>>" << aux_fila.size() << "<<<<" << endl;

                        } else if (color[aux_fila.front()] == "R" && color[vetor_olhado] == "R") {

                            //cout << "FALHA, VERMELHO LIGANDO COM VERMELHO";
                            falha_detectada = true;
                        } else if (color[aux_fila.front()] == "B" && color[vetor_olhado] == "B") {

                            //cout << "FALHA, PRETO LIGANDO COM PRETO";
                            falha_detectada = true;
                        }

                        else {

                            aux_fila.pop();
                            cout << ">>>>" << aux_fila.size() << "<<<<" << endl;
                        }
                    }

                    for (int i = 0; i <= N - 1; ++i) {
                        if (color[i] == "-1") {
                            vetor_cor_nao_cheio = true;
                            break;
                        } else
                            vetor_cor_nao_cheio = false;
                    }

                }

                ja_visitado[vetor_olhado] = true;
                if (ja_visitado[fila.front()] == false) {
                    vetor_olhado = fila.front();
                    fila.pop();
                } else {
                    fila.pop();
                    vetor_olhado = fila.front();
                }
            }
        }
    }
    */
    
    
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
