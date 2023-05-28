/*
//Grafos: Lista de Adjac�ncias
//
// Procura em Profundidade: Stack
// Procura em Largura:		Queue
//lufer
*/
#include <stdio.h>
#include <stdbool.h>
#include "LAGraph.h"
#include "assert.h"
#include <string.h>
#include <stdlib.h>	//malloc
// Lidar com "exce��es"
// assert(x>=10) - stderror output caso x<10

//Ver: http://www.geeksforgeeks.org/graph-and-its-representations/
//Exercicio: 
//Analisar http://www.thecrazyprogrammer.com/2014/03/depth-first-search-dfs-traversal-of-a-graph.html

//=========================================================
//H1 - Grafo orientado, n�o pesado, matriz fixa (TOTALVERTICES)
//=========================================================


/*
Cria Grafo
Vertices: 0, 1, 2, 3...
Inicializa vertices com lista de adjacencias=NULL
*/
bool CriaGraph(ITEM *gr, int tot) {
	//se n�mero de vertices n�o for v�lido
	if (tot <= 0 || tot > TOTALVERTICES) return false;
	//incializa
	for (int i = 0; i < tot; i++) {
		gr[i].valor = 0;
		gr[i].prox = NULL;
	}
	return true;
}
/*
Mostra Grafo
*/
void MostraGrafo(ITEM *lista) {
	int i;
	ITEM * tmp;
	for (i = 0; i < TOTALVERTICES; i++) {
		tmp = lista[i].prox;
		printf("Vertice %d: (%d) ==>", i, lista[i].valor);
		while (tmp != NULL) {
			printf("Adjacente: %d  ", tmp->valor);
			tmp = tmp->prox;
		}
		printf("\n");
	}
}

/*
Nova aresta, ordenando adjac�ncias, grafo orientado
Vertice origem:a
Vertice destino:b
*/
bool InsereAresta(ITEM *lista, int a, int b) {
	ITEM *destino;
	ITEM *tmp;

	//Novo vertice para o destino
	destino = (ITEM*)malloc(sizeof(ITEM));
	if (destino == NULL) return false;
	//assert(destion)
	destino->valor = b;
	destino->prox = NULL;

	lista[a].valor++;			// conta adjacentes!

	//Regista vertice destino como adjacente
	if (lista[a].prox == NULL)	// se lista vazia - � �nico adjacente	
		lista[a].prox = destino;
	else {						//insere v�rtices ordenados
		tmp = lista[a].prox;
		//insere inicio da lista
		if (tmp->valor > b) {	//insere inicio da lista
			destino->prox = tmp;
			lista[a].prox = destino;
		} 		          
		else if (tmp->prox == NULL) {
			destino->prox = tmp->prox;
			tmp->prox = destino;
		}
		else {
			while ((tmp->prox != NULL) && (tmp->prox->valor < b))
				tmp = tmp->prox;
			destino->prox = tmp->prox;
			tmp->prox = destino;
		}
	}
	return true;
}

//=========================================================
//H2 - Grafo N�o Orientado, pesado, Matriz calculada
//=========================================================

/*
Novo Nodo
*/
struct AdjListNode* newAdjListNode(int val)
{
	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	assert(newNode);		//lida com invariante ex: assert(x>10) - stderror output
	newNode->valor = val;
	newNode->next = NULL;
	newNode->peso = 0;		//grafo ponderado; (peso=0) por omiss�o!
	return newNode;
}

/*
Cria grafo preparado para conter "nVertices" 
*/
struct Graph* createGraph(int nVertices)
{
	//estrutura para guardar todo o grafo
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
	assert(graph);
	graph->v = nVertices;

	//Cria array de lista de adjacencias de tamanho nVertices
	graph->array = (struct AdjList*) malloc(nVertices * sizeof(struct AdjList));

	// Inicializa cada lista de adjacencias
	int i;
	for (i = 0; i < nVertices; ++i)
		graph->array[i].head = NULL;

	return graph;
}

/*
Adiciona aresta em grafo n�o orientado e n�o pesado
*/
bool addEdge(struct Graph* graph, int src, int dest)
{
	//novo nodo para vertice destino
	struct AdjListNode* newNode = newAdjListNode(dest);
	if (newNode == NULL) return false;
	//Insere � cabe�a da lista de adjac�ncias
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// grafo n�o orientado => addEdgs (graph, dest,src) 
	newNode = newAdjListNode(src);
	if (newNode == NULL) return false;
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
	return true;
}


/*
Insere aresta ponderada, ie, com um peso, em grafo n�o orientado
*/
bool addEdgeWeight(struct Graph* graph, int src, int dest, float p)
{
	//novo nodo para vertice destino
	struct AdjListNode* vdest = newAdjListNode(dest);
	if (vdest == NULL) return false;
	vdest->peso = p;		//pondera��o

	//Insere � cabe�a da lista de adjac�ncias
	vdest->next = graph->array[src].head;
	graph->array[src].head = vdest;

	// grafo n�o orientado => addEdgs (graph, dest,src) 
	struct AdjListNode* vsource = newAdjListNode(src);
	if (vsource == NULL) return false;
	vsource->peso = p;		//pondera��o
	vsource->next = graph->array[dest].head;
	graph->array[dest].head = vsource;

	return true;
}

//Outra Abordagem: Recursiva
/*
void addEdgeII(struct Graph* graph, int src, int dest, float p)
{
//novo nodo para vertice destino
struct AdjListNode* newNode = newAdjListNode(dest);
//Insere � cabe�a da lista de adjac�ncias
newNode->next = graph->array[src].head;
newNode->peso = p;
graph->array[src].head = newNode;

//Chamada Recursiva
addEdgeII(graph, dest, src, p);

}

void addEdgeWeightII(struct Graph* graph, int src, int dest, float p)
{
addEdgeII(graph, src, dest, p);
addEdgeII(graph, dest, src, p);
}
*/

/*
Mostra Grafo
*/
void printGraph(struct Graph* graph)
{
	int v;
	for (v = 0; v < graph->v; ++v)
	{
		struct AdjListNode* aux = graph->array[v].head;
		printf("\n Lista de Adjacencia do Vertice (%d)", v);
		while (aux)
		{
			printf("-> %d", aux->valor);
			aux = aux->next;
		}
		printf("\n");
	}
}

/*
Mostra grafo pesado ou n�o
*/
void printGraphWeight(struct Graph* graph, bool pesado)
{
	int v;
	for (v = 0; v < graph->v; ++v)
	{
		struct AdjListNode* aux = graph->array[v].head;
		printf("\n Lista de Adjacencia do Vertice (%d)", v);
		while (aux)
		{
			if(pesado==false)
				printf("-> %d", aux->valor);
			else
				printf("-> (%d): Peso= %2.0f", aux->valor, aux->peso);
			
			aux = aux->next;
		}
		printf("\n");
	}
}

/*
Menor dist�ncia saindo de um determinado vertice
*/
float ShorterDistance(struct Graph* graph, int v) {
	float menor = 0;
	//assert (v existe e � v�lido)
	struct AdjListNode* aux = graph->array[v].head;
	while (aux)
	{
		if ((aux->peso > menor) && (aux->peso != 0))
			menor = aux->peso;
		aux = aux->next;
	}
	return menor;
}

//=========================================================
//H3 - Estruturas Din�micas
//=========================================================

Adjacent AdjacentCreate(Node destiny)
{
	Adjacent adjacent;

	adjacent = (Adjacent)malloc(sizeof(struct adjacent));
	if (adjacent == NULL)
	{
		return NULL;
	}

	adjacent->Ptdestiny = destiny;
	adjacent->PtNext = NULL;

	return adjacent;
}

void AdjacentDestroy(Adjacent *ptAdjacent)
{
	free(*ptAdjacent);
	*ptAdjacent = NULL;
}

Node NodeCreate(int identifier, char name[])
{
	Node node;

	node = (Node)malloc(sizeof(struct node));
	if (node == NULL)
	{
		return NULL;
	}

	if ((node->PtIdentifier = (int *)malloc(sizeof(int))) == NULL)
	{
		free(node);
		return NULL;
	}

	if ((node->PtCity = (char *)malloc(strlen(name) + 1)) == NULL) {
		free(node->PtIdentifier);
		free(node);
		return NULL;
	}

	*node->PtIdentifier = identifier;
	strcpy(node->PtCity, name);
	node->PtAdjacent = NULL;
	node->PtNext = NULL;
	return node;
}

void NodeDestroy(Node *ptNode) {
	free((*ptNode)->PtIdentifier);
	free((*ptNode)->PtCity);
	free(*ptNode);
	*ptNode = NULL;
}

void CreateGraphTable(Node *graph, int position, char cityName[])
{
	Node previous = NULL;
	Node inserted = NULL;
	Node current = *graph;

	if ((inserted = NodeCreate(position, cityName)) == NULL)
	{
		return;
	}

	while (current != NULL)
	{
		previous = current;
		current = current->PtNext;
	}

	if (previous == NULL)	//no inicio
	{
		inserted->PtNext = *graph;
		*graph = inserted;
	}
	else // no fim
	{
		previous->PtNext = inserted;
	}
}

void ListGraph(Node graph) {
	Node Current = graph;
	while (Current != NULL) {
		printf("%d-", *Current->PtIdentifier);
		printf("%s\n", Current->PtCity);
		Adjacent CurrentAdjacent = Current->PtAdjacent;
		while (CurrentAdjacent != NULL)
		{
			printf("\t");
			printf("adjacent-%d\n", *CurrentAdjacent->Ptdestiny->PtIdentifier);
			CurrentAdjacent = CurrentAdjacent->PtNext;
		}
		Current = Current->PtNext;
	}
}

void CreateAdjacent(Node *graph, int origin, int destiny)
{
	Node originNode = NULL;
	Node destinyNode = NULL;
	Node current = *graph;

	while (current != NULL)
	{
		if (*current->PtIdentifier == origin)
		{
			originNode = current;
			current = current->PtNext;
			continue;
		}
		if (*current->PtIdentifier == destiny)
		{
			destinyNode = current;
		}

		current = current->PtNext;
	}

	if (originNode == NULL && destinyNode == NULL)
	{
		return;
	}

	Adjacent previous = NULL;
	Adjacent inserted = NULL;
	Adjacent currentAdjacent = originNode->PtAdjacent;
	if ((inserted = AdjacentCreate(destinyNode)) == NULL)
	{
		return;
	}

	while (currentAdjacent != NULL)
	{
		previous = currentAdjacent;
		currentAdjacent = currentAdjacent->PtNext;
	}

	if (previous == NULL)
	{
		inserted->PtNext = originNode->PtAdjacent;
		originNode->PtAdjacent = inserted;
	}
	else
	{
		previous->PtNext = inserted;
	}
}
