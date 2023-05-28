#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_VERTICES 50

typedef struct adjacente* Adjacente;
typedef struct node* Node;

struct adjacente {
    Node PtDestino;
    int peso;
    Adjacente seguinte;
};

struct node {
    int ID;
    char* Cidade;
    float Latitude;
    float Longitude;
    Adjacente PtAdjacente;
    Node seguinte;
} Cidade;

Node criarNode(int ID, char* Cidade, float Latitude, float Longitude) {
    Node novoNode = (Node)malloc(sizeof(struct node));
    novoNode->ID = ID;
    novoNode->Cidade = strdup(Cidade);
    novoNode->Latitude = Latitude;
    novoNode->Longitude = Longitude;
    novoNode->PtAdjacente = NULL;
    novoNode->seguinte = NULL;
    return novoNode;
}

Adjacente criarAdjacente(Node PtDestino, int peso) {
    Adjacente novoAdjacente = (Adjacente)malloc(sizeof(struct adjacente));
    novoAdjacente->PtDestino = PtDestino;
    novoAdjacente->peso = peso;
    novoAdjacente->seguinte = NULL;
    return novoAdjacente;
}

void adicionarAdjacente(Node node, Node adjacente, int peso) {
    Adjacente novoAdjacente = criarAdjacente(adjacente, peso);

    if (node->PtAdjacente == NULL) {
        node->PtAdjacente = novoAdjacente;
    } else {
        Adjacente ultimoAdjacente = node->PtAdjacente;
        while (ultimoAdjacente->seguinte != NULL) {
            ultimoAdjacente = ultimoAdjacente->seguinte;
        }
        ultimoAdjacente->seguinte = novoAdjacente;
    }
}

void lerVertices(Node* grafo) {
    FILE* arquivo = fopen("vertices.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de vertices.\n");
        return;
    }

    int ID;
    char Cidade[100];
    float Latitude, Longitude;
    Node novoNode, ultimoNode = NULL;

    while (fscanf(arquivo, "%d %s %f %f", &ID, Cidade, &Latitude, &Longitude) == 4) {
        novoNode = criarNode(ID, Cidade, Latitude, Longitude);

        if (*grafo == NULL) {
            *grafo = novoNode;
        } else {
            ultimoNode->seguinte = novoNode;
        }
        ultimoNode = novoNode;
    }

    fclose(arquivo);
}

void lerAdjacencias(Node grafo) {
    FILE* arquivo = fopen("adjacencias.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de adjacencias.\n");
        return;
    }

    int IDOrigem, IDAdjacente, peso;

    while (fscanf(arquivo, "%d %d %d", &IDOrigem, &IDAdjacente, &peso) == 3) {
        Node node = grafo;
        Node adjacente = NULL;

        while (node != NULL) {
            if (node->ID == IDOrigem) {
                adjacente = node;
                break;
            }
            node = node->seguinte;
        }

        if (adjacente != NULL) {
            Node nodeAdjacente = grafo;

            while (nodeAdjacente != NULL) {
                if (nodeAdjacente->ID == IDAdjacente) {
                    adicionarAdjacente(adjacente, nodeAdjacente, peso);
                    break;
                }
                nodeAdjacente = nodeAdjacente->seguinte;
            }

            if (nodeAdjacente == NULL) {
                printf("Cidade adjacente nao encontrada.\n");
            }
        } else {
            printf("Cidade de origem nao encontrada.\n");
        }
    }

    fclose(arquivo);
}

void imprimirGrafo(Node grafo) {
    Node node = grafo;
    while (node != NULL) {
        printf("Cidade: %s (%.2f,%.2f)\n", node->Cidade, node->Latitude, node->Longitude);

        Adjacente adjacente = node->PtAdjacente;
        while (adjacente != NULL) {
            printf("  Adjacente: %s, Peso: %d\n", adjacente->PtDestino->Cidade, adjacente->peso);
            adjacente = adjacente->seguinte;
        }

        node = node->seguinte;
    }
}

void liberarGrafo(Node grafo) {
    Node nodeAtual = grafo;
    while (nodeAtual != NULL) {
        Node nodeProximo = nodeAtual->seguinte;

        Adjacente adjacenteAtual = nodeAtual->PtAdjacente;
        while (adjacenteAtual != NULL) {
            Adjacente adjacenteProximo = adjacenteAtual->seguinte;
            free(adjacenteAtual);
            adjacenteAtual = adjacenteProximo;
        }

        free(nodeAtual->Cidade);
        free(nodeAtual);

        nodeAtual = nodeProximo;
    }
}

// =======================================================================

// ler ficheiros bin

void escreverVerticesBinario(Node grafo) {
    FILE* arquivo = fopen("vertices.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de vertices.\n");
        return;
    }

    Node node = grafo;
    while (node != NULL) {
        fwrite(&node->ID, sizeof(int), 1, arquivo);
        fwrite(node->Cidade, sizeof(char), 100, arquivo);
        fwrite(&node->Latitude, sizeof(float), 1, arquivo);
        fwrite(&node->Longitude, sizeof(float), 1, arquivo);

        node = node->seguinte;
    }

    fclose(arquivo);
}

void escreverAdjacenciasBinario(Node grafo) {
    FILE* arquivo = fopen("adjacencias.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de adjacencias.\n");
        return;
    }

    Node node = grafo;
    while (node != NULL) {
        Adjacente adjacente = node->PtAdjacente;
        while (adjacente != NULL) {
            fwrite(&node->ID, sizeof(int), 1, arquivo);
            fwrite(&adjacente->PtDestino->ID, sizeof(int), 1, arquivo);
            fwrite(&adjacente->peso, sizeof(int), 1, arquivo);
            adjacente = adjacente->seguinte;
        }
        node = node->seguinte;
    }

    fclose(arquivo);
}

void lerVerticesBinario(Node* grafo) {
    FILE* arquivo = fopen("vertices.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de vertices.\n");
        return;
    }

    int ID;
    char Cidade[100];
    float Latitude, Longitude;
    Node novoNode, ultimoNode = NULL;

    while (fread(&ID, sizeof(int), 1, arquivo) == 1) {
        fread(Cidade, sizeof(char), 100, arquivo);
        fread(&Latitude, sizeof(float), 1, arquivo);
        fread(&Longitude, sizeof(float), 1, arquivo);

        novoNode = criarNode(ID, Cidade, Latitude, Longitude);

        if (*grafo == NULL) {
            *grafo = novoNode;
        } else {
            ultimoNode->seguinte = novoNode;
        }
        ultimoNode = novoNode;
    }

    fclose(arquivo);
}

void lerAdjacenciasBinario(Node grafo) {
    FILE* arquivo = fopen("adjacencias.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de adjacencias.\n");
        return;
    }

    int IDOrigem, IDAdjacente, peso;

    while (fread(&IDOrigem, sizeof(int), 1, arquivo) == 1) {
        fread(&IDAdjacente, sizeof(int), 1, arquivo);
        fread(&peso, sizeof(int), 1, arquivo);

        Node node = grafo;
        Node adjacente = NULL;

        while (node != NULL) {
            if (node->ID == IDOrigem) {
                adjacente = node;
                break;
            }
            node = node->seguinte;
        }

        if (adjacente != NULL) {
            Node nodeAdjacente = grafo;

            while (nodeAdjacente != NULL) {
                if (nodeAdjacente->ID == IDAdjacente) {
                    adicionarAdjacente(adjacente, nodeAdjacente, peso);
                    break;
                }
                nodeAdjacente = nodeAdjacente->seguinte;
            }

            if (nodeAdjacente == NULL) {
                printf("Cidade adjacente nao encontrada.\n");
            }
        } else {
            printf("Cidade de origem nao encontrada.\n");
        }
    }

    fclose(arquivo);
}

// =======================================================================

void buscarVerticesAlcance(struct node* grafo, int verticeInicial, int distanciaLimite) {
    // Inicialização das estruturas de dados
    int* visitado = (int*)malloc(sizeof(int) * MAX_VERTICES);
    memset(visitado, 0, sizeof(int) * MAX_VERTICES);

    float* distancia = (float*)malloc(sizeof(float) * MAX_VERTICES);
    memset(distancia, -1, sizeof(float) * MAX_VERTICES);

    struct node** fila = (struct node**)malloc(sizeof(struct node*) * MAX_VERTICES);
    int frente = 0, tras = 0;

    // Localização do vértice inicial
    struct node* verticeAtual = grafo;
    while (verticeAtual != NULL) {
        if (verticeAtual->ID == verticeInicial) {
            break;
        }
        verticeAtual = verticeAtual->seguinte;
    }

    // Verificação se o vértice inicial foi encontrado
    if (verticeAtual == NULL) {
        printf("Vértice inicial não encontrado.\n");
        return;
    }

    // Marcar o vértice inicial como visitado e com distância 0
    visitado[verticeAtual->ID] = 1;
    distancia[verticeAtual->ID] = 0;
    fila[tras++] = verticeAtual;

    printf("Vértices no alcance de %s (Distância limite: %d):\n", verticeAtual->Cidade, distanciaLimite);

    // BFS adaptado para calcular a distância acumulada com base em latitude e longitude
    while (frente != tras) {
        struct node* noAtual = fila[frente++];
        struct adjacente* adjacente = noAtual->PtAdjacente;
        while (adjacente != NULL) {
            struct node* noAdjacente = adjacente->PtDestino;
            float lat1 = noAtual->Latitude;
            float lon1 = noAtual->Longitude;
            float lat2 = noAdjacente->Latitude;
            float lon2 = noAdjacente->Longitude;

            // Cálculo da distância euclidiana entre dois pontos geográficos
            float distanciaAtual = sqrt(pow(lat2 - lat1, 2) + pow(lon2 - lon1, 2));

            if (!visitado[noAdjacente->ID]) {
                visitado[noAdjacente->ID] = 1;
                distancia[noAdjacente->ID] = distancia[noAtual->ID] + distanciaAtual;

                if (distancia[noAdjacente->ID] <= distanciaLimite) {
                    printf("- %s (Distância: %.2f)\n", noAdjacente->Cidade, distancia[noAdjacente->ID]);
                    fila[tras++] = noAdjacente;
                }
            }
            adjacente = adjacente->seguinte;
        }
    }

    // Liberar memória alocada
    free(visitado);
    free(distancia);
    free(fila);
}

// =======================================================================

int main() {
    Node grafo = NULL;
    lerVertices(&grafo);
    lerAdjacencias(grafo);
    
    // Definindo nós e adjacências manualmente
    
    /*Node cidadeA = criarNode(1, "Cidade A");
    Node cidadeB = criarNode(2, "Cidade B");
    Node cidadeC = criarNode(3, "Cidade C");

    adicionarAdjacente(cidadeA, cidadeB, 10);
    adicionarAdjacente(cidadeA, cidadeC, 15);
    adicionarAdjacente(cidadeB, cidadeC, 5);
    
    // Definindo o grafo
    grafo = cidadeA;
    cidadeA->seguinte = cidadeB;
    cidadeB->seguinte = cidadeC;*/
    imprimirGrafo(grafo);
    
    // =====
    printf("\n\n\n");
    // =====
    
    // Escrever os dados em arquivos binários
    escreverVerticesBinario(grafo);
    escreverAdjacenciasBinario(grafo);

    // Limpar o grafo
    //liberarGrafo(grafo);

    // Ler os dados dos arquivos binários e recriar o grafo
    Node novoGrafo = NULL;
    lerVerticesBinario(&novoGrafo);
    lerAdjacenciasBinario(novoGrafo);
    imprimirGrafo(novoGrafo);

    // =====
    printf("\n\n\n");
    // =====

    buscarVerticesAlcance(novoGrafo, 1, 40);

    // Limpar o novo grafo
    liberarGrafo(novoGrafo);

    return 0;
}