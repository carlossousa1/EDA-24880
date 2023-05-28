#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct adjacent *Adjacent;
typedef struct node *Node;

struct adjacent {
    Node PtDestiny;
    Adjacent PtNext;
};

struct node {
    int *PtIdentifier;
    char *PtCity;
    Adjacent PtAdjacent;
    Node PtNext;
};

// Função para criar um novo vértice no grafo
Node CreateNode(int identifier, const char *city) {
    Node newNode = (Node)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Erro: Falha ao alocar memória para o novo nó.\n");
        return NULL;
    }

    newNode->PtIdentifier = (int *)malloc(sizeof(int));
    if (newNode->PtIdentifier == NULL) {
        printf("Erro: Falha ao alocar memória para o identificador do nó.\n");
        free(newNode);
        return NULL;
    }

    *(newNode->PtIdentifier) = identifier;

    newNode->PtCity = (char *)malloc((strlen(city) + 1) * sizeof(char));
    if (newNode->PtCity == NULL) {
        printf("Erro: Falha ao alocar memória para o nome da cidade do nó.\n");
        free(newNode->PtIdentifier);
        free(newNode);
        return NULL;
    }

    strcpy(newNode->PtCity, city);
    newNode->PtAdjacent = NULL;
    newNode->PtNext = NULL;

    return newNode;
}

// Função para adicionar uma adjacência entre dois vértices no grafo
void AddAdjacent(Node source, Node destiny) {
    if (source == NULL || destiny == NULL) {
        printf("Erro: Vértice de origem ou destino inválido.\n");
        return;
    }

    Adjacent newAdjacent = (Adjacent)malloc(sizeof(struct adjacent));
    if (newAdjacent == NULL) {
        printf("Erro: Falha ao alocar memória para a nova adjacência.\n");
        return;
    }

    newAdjacent->PtDestiny = destiny;
    newAdjacent->PtNext = source->PtAdjacent;
    source->PtAdjacent = newAdjacent;
}

// Função para exibir as informações dos vértices no grafo
void PrintGraph(Node graph) {
    Node currentNode = graph;
    while (currentNode != NULL) {
        printf("Identificador: %d, Cidade: %s\n", *(currentNode->PtIdentifier), currentNode->PtCity);
        Adjacent currentAdjacent = currentNode->PtAdjacent;
        while (currentAdjacent != NULL) {
            printf("Adjacente: %s\n", currentAdjacent->PtDestiny->PtCity);
            currentAdjacent = currentAdjacent->PtNext;
        }
        printf("\n");
        currentNode = currentNode->PtNext;
    }
}

// Função para liberar a memória alocada pelo grafo
void FreeGraph(Node graph) {
    Node currentNode = graph;
    while (currentNode != NULL) {
        Adjacent currentAdjacent = currentNode->PtAdjacent;
        while (currentAdjacent != NULL) {
            Adjacent nextAdjacent = currentAdjacent->PtNext;
            free(currentAdjacent);
            currentAdjacent = nextAdjacent;
        }
        Node nextNode = currentNode->PtNext;
        free(currentNode->PtCity);
        free(currentNode->PtIdentifier);
        free(currentNode);
        currentNode = nextNode;
    }
}

int main() {
    Node graph = NULL;

    // Criando alguns vértices
    Node node1 = CreateNode(1, "Cidade A");
    Node node2 = CreateNode(2, "Cidade B");
    Node node3 = CreateNode(3, "Cidade C");

    // Adicionando adjacências
    AddAdjacent(node1, node2);
    AddAdjacent(node1, node3);
    AddAdjacent(node2, node1);
    AddAdjacent(node3, node2);

    // Adicionando vértices ao grafo
    node1->PtNext = graph;
    graph = node1;
    node2->PtNext = graph;
    graph = node2;
    node3->PtNext = graph;
    graph = node3;

    // Exibindo informações do grafo
    PrintGraph(graph);

    // Liberando a memória alocada pelo grafo
    FreeGraph(graph);

    return 0;
}

