/*
//Grafos: Lista de Adjac�ncias
//
// Procura em Profundidade: Stack
// Procura em Largura:		Queue
//lufer
*/
#pragma once

#ifndef GRF
#define GRF

//=========================================================
//H1 : grafo orientado, n�o pesado, com Matriz Fixa
//=========================================================
#define TOTALVERTICES 8

//Vertice
typedef struct item {
	int valor;			//n�mero de adjacentes ou valor do vertice
	struct item* prox;	//lista de adjacentes
}ITEM;



bool CriaGraph(ITEM *gr, int tot);
void MostraGrafo(ITEM *lista);
bool InsereAresta(ITEM *lista, int a, int b);
void printGraph(struct Graph* graph);
void printGraphWeight(struct Graph* graph, bool pesado);
void CreateGraphTable(Node *graph, int position, char cityName[]);
void CreateAdjacent(Node *graph, int origin, int destiny);
void ListGraph(Node graph);


//=========================================================
//H2 - Grafo orientado e pesado - Matriz calculada
//=========================================================

// nodo da Lista de Adjac�ncias
struct AdjListNode
{
	int valor;			//1 ou 0
	float peso;			//grafo pesado
	struct AdjListNode* next;
};

// Lista de Adjac�ncias
struct AdjList
{
	struct AdjListNode *head;  // head da Lista
};

// Um Grafo. Um array de Lista de Adjac�ncias!!!
// Array = numero de v�rtices do Grafo
struct Graph
{
	int v;				//total de vertices
	struct AdjList* array;	//"lista" de adjacencias
};

//prototipos fun��es

struct Graph* createGraph(int nVertices);
//Insere em grafo n�o orientado e pesado
bool addEdgeWeight(struct Graph* graph, int src, int dest, float p);
//insere em grafo n�o orientado e n�o pesado
bool addEdge(struct Graph* graph, int src, int dest);
//Menor Dist�ncia
float ShorterDistance(struct Graph* graph, int v);

//=========================================================
//H3
//S� estruturas din�micas
////=========================================================

typedef struct adjacent *Adjacent;
typedef struct node *Node;

struct adjacent {
	Node Ptdestiny;
	Adjacent PtNext;
};

struct node
{
	int *PtIdentifier;
	char *PtCity;
	Adjacent PtAdjacent;
	Node PtNext;
};

#endif // !GRF

