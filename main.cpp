#include <iostream>
#include "graph.h"
#include "graphm.h"
#include <fstream>
#include <string>
#include<sstream>
using namespace std;


// Implementacao simples de BFS sem
// os vetores pai [] e d[]
void BFS(Graph *G, int start)
{
    for (int v = 0; v<G -> n(); ++v)
        G->setMark(v, 1);
    G->setMark(start, 2);
    std ::queue<int> Q;
    Q.push(start);
    // vector<bool> visited( G->n() , false); 

    while (!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        
        cout << " Vertex " << v << " visited " << endl;

        for (int &w : G->neighbors(v))
        {
            
            if (G->getMark(w) == 1)
            {
                G->setMark(w, 2);
                Q.push(w);
            }
        }
        G->setMark(v, 3);
    }
}

int main(){

    fstream arq;
     arq.open("testeGrafos.txt", ios::in);
    
    int N = 4;

    cout << "insira o numero de vertices\n";
    //cin >> N;

    Graph *grafo;
    //grafo = new GraphM(N);
    //vértice 1 e 2 
    int v1, v2;
    int aux = N;
    
    

    string linha;
    
    /* pega o tamanho do grafo*/
    getline(arq,linha);
    int tamanho = std::stoi(linha);
    cout << tamanho << "\n" <<endl;
    grafo = new GraphM(tamanho);
    while( getline(arq, linha)){
        if(linha == "0" || linha == "0 0") break;
        std::stringstream s_stream(linha);
        
        string substr;
        getline(s_stream, substr, ' ');
        v1 = std::stoi(substr);
        getline(s_stream, substr, ' ');
        v2 = std::stoi(substr);
        cout << v1 << " ";
        cout << v2<< endl;
        
        grafo->addEdge(v1, v2);
        grafo->addEdge(v2, v1);
        

    }

/*
    for(int i = 0; i < N-1; ++i) {
		grafo->addEdge(i, i+1);
		grafo->addEdge(i+1, i);
	}
*/
    /*
    grafo->addEdge(0, 1);
    grafo->addEdge(1, 0);

    grafo->addEdge(1, 2);
    grafo->addEdge(2, 1);

    grafo->addEdge(2, 3);
    grafo->addEdge(3, 2);

    grafo->addEdge(0, 3);
    grafo->addEdge(3, 0);

    grafo->addEdge(1, 3);
    grafo->addEdge(3, 1);
    
    grafo->addEdge(0, 2);
    grafo->addEdge(2, 0);
*/
    for(int i = 0; i <= N-1; ++i) {
		cout << "Vizinhos do " << i << ": ";
		for( int vizinho : grafo->neighbors(i) ) {
			cout << vizinho << " ";
		}
		cout << endl;
	}


//BFS(grafo,0);
   return 0;
}