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
    G->setCor(start, 1); //primeiro é vermelho
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

                if (G->getDistancia(w) % 2 == 0) {
                    G->setCor(w, 1); //coloca os pares em vermelhor
                } else {
                    G->setCor(w, 2); //coloca os impares em preto
                }
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
    int tamanho;

    /* pega o tamanho do grafo*/

    getline(arq, linha);
    tamanho = std::stoi(linha);
    //cout << "tamanho é : " << tamanho << endl;
    grafo = new GraphM(tamanho);
    bool falha = false;
    //cout << "TAMANHO:" << tamanho << endl;
    while (tamanho > 0) {
        
        while (linha[0] != '0' || linha[2] != '0') {
            getline(arq,linha);
            std::stringstream s_stream(linha);

            string substr;
            getline(s_stream, substr, ' ');

            v1 = std::stoi(substr);

            getline(s_stream, substr, ' ');
            v2 = std::stoi(substr);

            if (v1 == 0 && v2 == 0)
                break;

            //cout << "v1: " << v1 << endl;
            //cout << "v2: " << v2 << endl;

            grafo->addEdge(v1, v2);
            grafo->addEdge(v2, v1);
        }

        bfs(grafo, 0);
    
        bool teste = true;  //testa se tem irmãos de cor diferente
       

        int tem_vermelho[tamanho-1], tem_preto[tamanho-1]; // vetor de inteiros para guardar a quantidade de vermelhos e pretos em cada camada
        

        for (int i = 0; i < tamanho-1; i++) {
            tem_vermelho[i] = 0;         //zera os vetores
            tem_preto[i] = 0;
        }

        for (int i = 0; i < tamanho-1; i++) {
            if(grafo->getCor(i) == 1){
                tem_vermelho[grafo->getDistancia(i)]++;
            }
            else{
                tem_preto[grafo->getDistancia(i)]++;
            }
        }
        /*
        cout << "tem vermelho ";
        for (int i = 0; i < tamanho-1; i++){
            cout <<  tem_vermelho[i];
        }
        cout << endl;
        cout << "tem preto ";
        for (int i = 0; i < tamanho-1; i++){
            cout << tem_preto[i];
        }
        cout << endl;
        */

        for(int i = 0; i < tamanho-1; i++) {
            if(tem_vermelho[i] > 0 && tem_preto[i] > 0){
                teste = false;
                break;
            }

        }
    
        

        bool teste2 = true;  //testa se tem ligação entre irmãos

        for(int i = 0; i < tamanho; i++){  //laço testando testando se tem ligação entre vertices da mesma camada 
            for(int j = 0; j < tamanho; j++){
                if( i != j && grafo->getDistancia(i) == grafo->getDistancia(j) && grafo->isEdge(i,j)){
                    teste2 = false;
                    break;
                }
            }
        }

        bool teste3 = true; // se existe um pai que é cor igual ao filho

        for(int i = 0; i < tamanho; i++){
            if(grafo->getPai(i) != -1)
                if(grafo->getCor(i) == grafo->getCor(grafo->getPai(i))){
                    teste3 = false;
                    break;
                }
        }

        if(teste == false || teste2 == false || teste3 == false)
            cout << "NAO\n";
        else{
            cout << "SIM\n";
            grafo->imprimeCores();
        }

        getline(arq, linha);
        tamanho = std::stoi(linha);
        //cout << "tamanho é : " << tamanho << endl;

        if (tamanho > 0) {
            grafo->~Graph();
            grafo = new GraphM(tamanho);
        }   
    }

    //grafo->correctColoring();

    //grafo->imprimeCores();
    /*
    for (int i = 0; i <= grafo->n() - 1; ++i) {
        cout << "Vizinhos do " << i << ": ";
        for (int vizinho : grafo->neighbors(i)) {
            cout << vizinho << " ";
        }
        cout << endl;
    }
    */

    grafo->~Graph();

    return 0;
}
