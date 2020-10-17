#include "graph.h"
#include "graphm.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Implementacao simples de BFS sem
// os vetores pai [] e d[]

void bfs(Graph *G, int start) {

    for (int i = 0; i < G->getN(); i++) {
        G->setMark(i, 1);         //todo mundo é branco. Logo, não foram visitados
        G->setDistancia(i, 0); //maior inteiro que cabe em um int
        G->setPai(i, -1);
    }
    G->setDistancia(start, 0);
    queue<int> Q;
    Q.push(start);

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
       // cout << "Vertice " << v << " visitado" << endl;
       // cout << "cor = " << G->getCor(v) << " pai = " << G->getPai(v) << " distancia = " << G->getDistancia(v) << endl;
        for (int &w : G->neighbors(v)) {
            if (G->getMark(w) == 1) {
                G->setMark(w, 2);

                G->setPai(w, v);
                Q.push(w);

                if (G->getPai(w) != -1)
                    G->setDistancia(w, G->getDistancia(G->getPai(w)) + 1);

            }
        }
        //cout << "cor = " << G->getCor(v) << " pai = " << G->getPai(v) << " distancia = " << G->getDistancia(v) << endl;

        G->setMark(v, 3);
    }
}

int main() {

    fstream arq;
    arq.open("grafos.txt", ios::in);

    Graph *grafo;
    //grafo = new GraphM(N);
    //vértice 1 e 2
    int v1, v2;

    string linha;
    int tamanho = 10;

    /* pega o tamanho do grafo*/

    getline(arq, linha);

    cout << "linha:" << linha << endl;

   // tamanho = std::stoi(linha);
    
    grafo = new GraphM(10);
    int tamanho_aux = 0;
    bool falha = false;
    cout << "TAMANHO:" << tamanho << endl;
    
    
    while (tamanho > 0) {
         getline(arq, linha);

        while (tamanho_aux > 0) {

            int index = 1;

            getline(arq,linha);
            std::stringstream s_stream(linha);

            string substr;
            getline(s_stream, substr, ' ');

            //v1 = std::stoi(substr);

            getline(s_stream, substr, ' ');
            //v2 = std::stoi(substr);

            //cout << "v1: " << v1 << endl;
            //cout << "v2: " << v2 << endl;

            grafo->addEdge(v1, v2);
            grafo->addEdge(v2, v1);

            tamanho_aux--;
        }

        bfs(grafo, 0);
        bool folha[tamanho];
        for(int i = 0; i < tamanho; i++)
            folha[i] = true;


        for(int i = 0; i < tamanho; i++){ //para encontrar os que não são chefes de ninguem
            for(int j = 0; j < tamanho; j++){
                if(i != j)
                    if(grafo->getPai(i) == j){
                        folha[i] = false;                      
                    }
                        
            }

        }
        
        getline(arq, linha);
        tamanho = std::stoi(linha);
        //cout << "tamanho é : " << tamanho << endl;

        if (tamanho > 0) {
            grafo->~Graph();
            grafo = new GraphM(tamanho);
        }

    }



    grafo->~Graph();

    return 0;
}
