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
        G->setDistancia(i, INFI); //maior inteiro que cabe em um int
        G->setPai(i, -1);
    }
    G->setDistancia(start, 0);
    G->setCor(start, 1); //primeiro é vermelho
    queue<int> Q;
    Q.push(start);

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        //cout << "Vertice " << v << " visitado" << endl;
        //cout << "cor = " << G->getCor(v) << " pai = " << G->getPai(v) << " distancia = " << G->getDistancia(v) << endl;
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
    arq.open("testeGrafos.txt", ios::in);

    Graph *grafo;
    //grafo = new GraphM(N);
    //vértice 1 e 2
    int v1, v2;

    string linha, linha2;
    int tamanho;

    /* pega o tamanho do grafo*/

    getline(arq, linha);
    tamanho = std::stoi(linha);
    //cout << "tamanho é : " << tamanho << endl;
    grafo = new GraphM(tamanho);
    bool falha = false;

    while (tamanho > 0) {

        while (linha[0] != '0' || linha[2] != '0') {

            std::stringstream s_stream(linha);

            string substr;
            getline(arq, linha);

            v1 = std::stoi(linha);

            
            int espaco;
            int aux = 0;
            for (int i = 0; linha.length() > i; i++) {
                if (linha[i] == ' ')
                    espaco = i;
            }

            linha2[0] = linha[espaco];
            linha2[1] = linha[espaco+1];



            v2 = std::stoi(linha2);
    
            if (v1 == 0 && v2 == 0)
                break;
            


            //cout << linha << " ";

            //cout << linha2 << endl;

            grafo->addEdge(v1, v2);
            grafo->addEdge(v2, v1);
        }

        bfs(grafo, 0);

        /*
        int tem_vermelho[tamanho], tem_preto[tamanho]; // vetor de inteiros para guardar a quantidade de vermelhos e pretos em cada camada
        

        for (int i = 0; i < tamanho; i++) {
            tem_vermelho[i] = 0;
            tem_preto[i] = 0;
        }

        for (int i = 0; i < tamanho; i++) {
            if (grafo->getCor(i) == 1) { // se for vermelho
                tem_vermelho[grafo->getDistancia(i)]++;
            } else{ // se for vermelho
                tem_preto[grafo->getDistancia(i)]++;
            }
        }

        for(int i = 0; i < tamanho; i++) {
            if(tem_vermelho[i] > 0 && tem_preto[i] > 0){
                teste = false;
                break;
            }

        }

        
*/
        bool teste = true;

        for(int i = 0; i < tamanho; i++){  //laço testando testando se tem ligação entre vertices da mesma camada 
            for(int j = 0; j < tamanho; j++){
                if( i != j && grafo->getDistancia(i) == grafo->getDistancia(j) && grafo->isEdge(i,j)){
                    teste = false;
                    break;
                }
            }
        }
        if(teste == false)
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
