#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct adjacente *Adjacente;
typedef struct node *Node;

struct adjacente 
{
    Node PtDestino;
    int peso; // Novo campo de peso
    Adjacente seguinte;
};


struct node 
{
    int ID;
    char *Cidade;
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

    novoNode->ID = ID;

    novoNode->Cidade = (char *)malloc((strlen(cidade) + 1) * sizeof(char));
    if (novoNode->Cidade == NULL) {
        printf("Erro: Falha ao alocar memória para o nome da cidade do nó.\n");
        free(novoNode);
        return NULL;
    }

    strcpy(novoNode->Cidade, cidade);
    novoNode->PtAdjacente = NULL;
    novoNode->seguinte = NULL;

    return novoNode;
}

// Função para adicionar uma adjacência entre dois vértices no grafo
void CriarAdjacente(Node origem, Node destino, int peso) {
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
    novoAdjacente->peso = peso; // Atribuir o peso
    novoAdjacente->seguinte = origem->PtAdjacente;
    origem->PtAdjacente = novoAdjacente;
}


// Função para exibir as informações dos vértices no grafo
void PrintGrafo(Node grafo) {
    Node currentNode = grafo;
    while (currentNode != NULL) {
        printf("Identificador: %d, Cidade: %s\n", currentNode->ID, currentNode->Cidade);
        Adjacente currentAdjacente = currentNode->PtAdjacente;
        while (currentAdjacente != NULL) {
            printf("Adjacente: %s\n", currentAdjacente->PtDestino->Cidade);
            currentAdjacente = currentAdjacente->seguinte;
        }
        printf("\n");
        currentNode = currentNode->seguinte;
    }
}

// Função para liberar a memória alocada pelo grafo
void LiberaGrafo(Node grafo) {
    Node currentNode = grafo;
    while (currentNode != NULL) {
        Adjacente currentAdjacente = currentNode->PtAdjacente;
        while (currentAdjacente != NULL) {
            Adjacente nextAdjacente = currentAdjacente->seguinte;
            free(currentAdjacente);
            currentAdjacente = nextAdjacente;
        }
        Node nextNode = currentNode->seguinte;
        free(currentNode->Cidade);
        free(currentNode);
        currentNode = nextNode;
    }
}

// Função para ler os dados do grafo de um arquivo de texto
Node LerGrafoDeArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro: Não foi possível abrir o arquivo '%s'.\n", nomeArquivo);
        return NULL;
    }

    Node grafo = NULL;
    int ID;
    char linha[100];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *token = strtok(linha, ";"); // Dividir a linha em campos com base no delimitador ";"
        sscanf(token, "%d", &ID);

        token = strtok(NULL, ";");
        char cidade[100];
        sscanf(token, "%s", cidade);

        Node novoNode = CriarNode(ID, cidade);
        if (novoNode != NULL) {
            novoNode->seguinte = grafo;
            grafo = novoNode;
        }
    }

    fclose(arquivo);
    return grafo;
}


// Função para encontrar um vértice pelo seu ID
Node EncontrarVertice(Node grafo, int ID) {
    Node currentNode = grafo;
    while (currentNode != NULL) {
        if (currentNode->ID == ID) {
            return currentNode;
        }
        currentNode = currentNode->seguinte;
    }
    return NULL;
}

// Função para ler as adjacências do grafo a partir de um arquivo de texto
void LerAdjacencias(Node grafo, FILE *arquivo) {
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int idOrigem, idDestino, peso;
        sscanf(linha, "%d", &idOrigem);

        Node origem = EncontrarVertice(grafo, idOrigem);

        char *token = strtok(linha, ";"); // Ignorar o ID da origem
        while ((token = strtok(NULL, ";")) != NULL) {
            sscanf(token, "%d:%d", &idDestino, &peso);

            Node destino = EncontrarVertice(grafo, idDestino);
            if (destino != NULL) {
                CriarAdjacente(origem, destino, peso);
            }
        }
    }
}


int main() {
    Node grafo = NULL;

    // Abrir o arquivo de texto
    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: Não foi possível abrir o arquivo 'dados.txt'.\n");
        return 1;
    }

    // Ler os dados do grafo do arquivo de texto
    grafo = LerGrafoDeArquivo("dados.txt");
    if (grafo == NULL) {
        printf("Erro: Não foi possível ler o grafo do arquivo.\n");
        fclose(arquivo);
        return 1;
    }

    // Ler as adjacências do arquivo
    LerAdjacencias(grafo, arquivo);

    fclose(arquivo);

    // Exibir informações do grafo
    PrintGrafo(grafo);

    // Liberar a memória alocada pelo grafo
    LiberaGrafo(grafo);

    return 0;
}

