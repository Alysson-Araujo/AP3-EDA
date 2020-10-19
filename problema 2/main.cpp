

/*      Turma: Estrutura de dados avançada 2020.1   
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Aluno: Alysson Alexandre de Oliveira Araújo               |
Matricula: 474084                                         |
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Aluno: João Almir da Costa Junior                         |
Matricula: 470034                                         |
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include "graph.h"
#include "graphm.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

//Definicoes para o DFS
#define BRANCO 0
#define CINZA 1
#define PRETO 2
// Implementacao simples de BFS sem
// os vetores filho [] e d[]

void DFS_VISIT(Graph &G, int v, int *temp_Descoberta, int *temp_Finalizacao, int &tempo) {
    tempo++;
    temp_Descoberta[v] = tempo;
    G.setMark(v, CINZA);

    // cout << v << " "<<Filho[v] << endl;

    cout << " \tVertex " << v << " visited " << endl;

    cout << "\nCHEFE = " << G.getChefes(v) << " Filho = " << G.getFilho(v) << endl
         << endl;

    for (int &i : G.neighbors(v)) {
/*
        if(G.getConvidados(G.getChefes(v))==1){
                G.setConvidados(v,false);
        }
        else if(G.getChefes(v)==0){
            G.setConvidados(v,true);
        }


        if( G.getFilho()==v{
            G.setConvidados(i, true);
            G.setConvidados(G.getChefes(v),false);
        }
        
        
        /*if(G.getChefes(v)== G.getFilho(v)){
            cout << "\nCHEFE E FILHO TA IGUAl\n";
            G.setConvidados(v, true);
            G.setConvidados(G.getChefes(v),false);
        }*/
        /*
        if(G.getChefes(i) != -1 && G.getConvidados(G.getChefes(i)) == false){
            G.setConvidados(i, true);
        }
        */

        if (G.getMark(i) == BRANCO) {

            DFS_VISIT(G, i, temp_Descoberta, temp_Finalizacao, tempo);
        }
    }
    
    if(G.getChefes(v) != -1){
        if(G.getConvidados(v) == true)
            G.setConvidados(G.getChefes(v),false);
        else
            G.setConvidados(G.getChefes(v),true);
    }
    else{
        if(G.getConvidados(0) == true)
            for (int i = 0; i < G.n(); i++){
                if(G.getChefes(i) == 0 && G.getConvidados(i) == true){
                    G.setConvidados(0,false);
                    break;
                }

        }
    }
    
    G.setMark(v, PRETO);
    tempo++;
    temp_Finalizacao[v] = tempo;
}

void DFS(Graph &G) {

    int temp_Descoberta[G.n()];
    int temp_Finalizacao[G.n()];

    int tempo = 0;

    //o dono da empresa n tem pai, logo n tem chefe

    for (int i = 0; i < G.n(); i++)
        G.setMark(i, BRANCO);

    for (int x = 0; x < G.n(); x++)
        for (int &i : G.neighbors(x)) {
            G.setFilho(x, i);
        }

    /*for (int   i = 0; i < G.n(); i++)
    {
        //cout <<  i <<"->"<<Filho[i] <<endl;
    }*/

    for (int i = 0; i < G.n(); i++) {
        if (G.getMark(i) == BRANCO)
            DFS_VISIT(G, i, temp_Descoberta, temp_Finalizacao, tempo);
    }

    
}

int main() {


    Graph *grafo;
    grafo = new GraphM(11);
    grafo->addEdge(1, 0); // 1<-----0
    grafo->addEdge(2, 0); // 2<-----1
    grafo->addEdge(3, 1); // 3<-----0
    grafo->addEdge(4, 1); // 4<-----1
    grafo->addEdge(5, 2); // 5<-----3
    grafo->addEdge(6, 3);
    grafo->addEdge(7, 3);
    grafo->addEdge(8, 4);
    grafo->addEdge(9, 6);
    grafo->addEdge(10, 9);


/*

    grafo->setNome("Paulo",0);
    grafo->setNome("Jakson",1);
    grafo->setNome("Karina",2);
    grafo->setNome("Luiza",3);
    grafo->setNome("Joao",4);
    grafo->setNome("Carlos",5);
    grafo->setNome("Santiago",6);
    grafo->setNome("Pedro",7);
    /*
    
    grafo->setNome("0", 0);
    grafo->setNome("1", 1);
    grafo->setNome("2", 2);
    grafo->setNome("3", 3);
    grafo->setNome("4", 4);
    grafo->setNome("5", 5);
    grafo->setNome("6", 6);
    grafo->setNome("7", 7);
    grafo->setNome("8", 8);
    grafo->setNome("9", 9);
    grafo->setNome("10", 10);
*/

    
    bool folha[grafo->n()];
    for (int i = 0; i < grafo->n(); i++){
        folha[i] = true;
    }
    
    for (int i = 0; i < grafo->n(); i++){
        for(int j = 0; j < grafo->n(); j++){
            if(i != j)
                if(i == grafo->getChefes(j)){
                    folha[i] = false;
                        break;
                }
        }
    }

    for (int i = 0; i < grafo->n(); i++){
        if(folha[i] == true)
            grafo->setConvidados(i,true);
    }


    DFS(*grafo);

    /*
    
    Graph *grafo;
    grafo = new GraphM(2);
    grafo->addEdge(1,0);           // 1<-----0
               // 2<-----1
   
    
    
    //bfs(grafo, 0);
    
    
    
    grafo->setNome("Laura",0);
    grafo->setNome("Stephane",1);
  */

    /*
    Graph *grafo;
    grafo = new GraphM(6);
    grafo->addEdge(1,0);           // 1<-----0
    grafo->addEdge(2,1);           // 2<-----1
    grafo->addEdge(3,0);           // 3<-----0
    grafo->addEdge(4,1);           // 4<-----1
    grafo->addEdge(5,3);           // 5<-----3
    
    //bfs(grafo, 0);
    
    
    
    grafo->setNome("Paulo",0);
    grafo->setNome("Jakson",1);
    grafo->setNome("Karina",2);
    grafo->setNome("Luiza",3);
    grafo->setNome("Joao",4);
    grafo->setNome("Carlos",5);
    grafo->imprimeChefes();
    */

    cout << endl;

    cout << "Vertice e seu filho na direita\n";
    for (int i = 0; i < grafo->n(); i++) {
        cout << i << " " << grafo->getFilho(i) << endl;
    }

    cout << "Vertice e seu chefe na direita\n";
    for (int i = 0; i < grafo->n(); i++) {
        cout << i << " " << grafo->getChefes(i) << endl;
    }


    int cont = 0;

    

  


    //grafo->getNome(0,"0");
    //
    //grafo->imprimeChefes();

    

    cout << "folha ";
    for (int i = 0; i < grafo->n(); i++){
        cout << folha[i] << " ";
    }

    cout<< endl;

    cout << "convidados: ";

    for (int i = 0; i < grafo->n(); i++) {
        cout << grafo->getConvidados(i) << " ";
        if(grafo->getConvidados(i))
            cont++;
    }
    
    cout<< endl;
    
    cout << "maior quantidade possivel de pessoas na festa: " <<cont << endl;

    grafo->~Graph();
    // fstream arq;
    // fstream arq2;
    // arq.open("grafos.txt", ios::in);
    // arq2.open("resulTestes.txt", ios::out);

    //Graph *grafo;
    //grafo = new GraphM(N);
    //vértice 1 e 2
    //int v1, v2;

    string linha;
    //int tamanho = 10;

    /* pega o tamanho do grafo*/

    //getline(arq, linha);
    //
    //cout << "linha:" << linha << endl;
    //
    // tamanho = std::stoi(linha);

    //grafo = new GraphM(10);
    //int tamanho_aux = 0;
    //bool falha = false;
    //cout << "TAMANHO:" << tamanho << endl;
    /*
    int posicao = 0; //posicao onde cada funcionario ficara, incluindo o dono
    while(getline(arq,linha)&& linha!="0"){
        
        std::stringstream partes(linha);
        string aux;
        getline(partes,aux, ' ');
        cout << aux << endl;
        arq2 << aux << endl;
        getline(partes, aux, ' ');
        if(!isdigit(aux[0])){grafo->setNome(aux, posicao);}
            
    }
    arq.close();
    arq2.close();
    */
    /*
    while (getline(arq,linha) && linha !="0")
    {
        
        //cout << linha << endl;
        //Verifica se a linha pegou o tamanho do grafo!
        //cout << linha[0]<<endl;
        if(linha >="1"){
            
            // significa que o arquivo chegou ao fim
                cout << linha << endl;
                if()
                grafo = new GraphM(std::stoi(linha));
                arq2 << linha << endl;

                // Vai pegar o nome do dono da empresa
                getline(arq,linha);
                grafo->setNome(linha,posicao);
                posicao++;
                arq2 << linha <<endl;
            }
            
            std::stringstream s_stream(linha);

            string substr;
            getline(s_stream, substr, ' ');

            string v1 = substr;
            cout << v1 << endl;
            grafo->setNome(v1, posicao);
            posicao++;
            getline(s_stream, substr, ' ');
            arq2 << linha <<endl;
        }
    

    */

    //grafo->getNome();

    /*
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
        //bool folha[tamanho];
        for(int i = 0; i < tamanho; i++)
            folha[i] = true;


        for(int i = 0; i < tamanho; i++){ //para encontrar os que não são chefes de ninguem
            for(int j = 0; j < tamanho; j++){
                if(i != j)
                    if(grafo->getFilho(i) == j){
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

*/

    //grafo->~Graph();

    return 0;
}
