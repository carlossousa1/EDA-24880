#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct adjacente *Adjacente;
typedef struct node *Node;

struct adjacente 
{
    Node PtDestino;
    Adjacente seguinte;
};

struct node 
{
    int *PtID;
    char *PtCidade;
    Adjacente PtAdjacente;
    Node seguinte;
};

// Função para criar um novo vértice no grafo
Node CriarNode(int ID, const char *cidade) 
{
    Node novoNode = (Node)malloc(sizeof(struct node));
    if (novoNode == NULL) {
        printf("Erro: Falha ao alocar memória para o novo nó.\n");
        return NULL;
    }

    novoNode->PtID = (int *)malloc(sizeof(int));
    if (novoNode->PtID == NULL) {
        printf("Erro: Falha ao alocar memória para o identificador do nó.\n");
        free(novoNode);
        return NULL;
    }

    *(novoNode->PtID) = ID;

    novoNode->PtCidade = (char *)malloc((strlen(cidade) + 1) * sizeof(char));
    if (novoNode->PtCidade == NULL) {
        printf("Erro: Falha ao alocar memória para o nome da cidade do nó.\n");
        free(novoNode->PtID);
        free(novoNode);
        return NULL;
    }

    strcpy(novoNode->PtCidade, cidade);
    novoNode->PtAdjacente = NULL;
    novoNode->seguinte = NULL;

    return novoNode;
}

// Função para adicionar uma adjacência entre dois vértices no grafo
void CriarAdjacente(Node origem, Node destino) 
{
    if (origem == NULL || destino == NULL) {
        printf("Erro: Vértice de origem ou destino inválido.\n");
        return;
    }

    Adjacente novoAdjacente = (Adjacente)malloc(sizeof(struct adjacente));
    if (novoAdjacente == NULL) {
        printf("Erro: Falha ao alocar memória para a nova adjacência.\n");
        return;
    }

    novoAdjacente->PtDestino = destino;
    novoAdjacente->seguinte = origem->PtAdjacente;
    origem->PtAdjacente = novoAdjacente;
}

// Função para exibir as informações dos vértices no grafo
void PrintGrafo(Node grafo) 
{
    Node currentNode = grafo;
    while (currentNode != NULL) {
        printf("Identificador: %d, Cidade: %s\n", *(currentNode->PtID), currentNode->PtCidade);
        Adjacente currentAdjacente = currentNode->PtAdjacente;
        while (currentAdjacente != NULL) {
            printf("Adjacente: %s\n", currentAdjacente->PtDestino->PtCidade);
            currentAdjacente = currentAdjacente->seguinte;
        }
        printf("\n");
        currentNode = currentNode->seguinte;
    }
}

// Função para liberar a memória alocada pelo grafo
void FreeGrafo(Node grafo) 
{
    Node currentNode = grafo;
    while (currentNode != NULL) {
        Adjacente currentAdjacente = currentNode->PtAdjacente;
        while (currentAdjacente != NULL) {
            Adjacente nextAdjacente = currentAdjacente->seguinte;
            free(currentAdjacente);
            currentAdjacente = nextAdjacente;
        }
        Node nextNode = currentNode->seguinte;
        free(currentNode->PtCidade);
        free(currentNode->PtID);
        free(currentNode);
        currentNode = nextNode;
    }
}

int main() 
{
    Node grafo = NULL;

    // Criando alguns vértices
    Node node1 = CriarNode(1, "Cidade A");
    Node node2 = CriarNode(2, "Cidade B");
    Node node3 = CriarNode(3, "Cidade C");

    // Adicionando adjacências
    CriarAdjacente(node1, node2);
    CriarAdjacente(node1, node3);
    CriarAdjacente(node2, node1);
    CriarAdjacente(node3, node2);

    // Adicionando vértices ao grafo
    node1->seguinte = grafo;
    grafo = node1;
    node2->seguinte = grafo;
    grafo = node2;
    node3->seguinte = grafo;
    grafo = node3;

    // Exibindo informações do grafo
    PrintGrafo(grafo);

    // Liberando a memória alocada pelo grafo
    FreeGrafo(grafo);

    return 0;
}

