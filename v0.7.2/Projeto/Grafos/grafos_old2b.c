#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define TAM 50
#define MAX_VERTICES 100

#include <math.h>

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

typedef struct registo_veiculos {
    int id;
    char tipo[TAM];
    float bateria;
    float autonomia;
    char geocode[TAM];
    struct registo_veiculos* seguinte;
} Veiculos;

int ExisteVeiculo(Veiculos* Inicio, int id) 
{
	while (Inicio != NULL) {
		if (Inicio->id == id) return(1);
		Inicio = Inicio->seguinte;
	}
	return(0);
}

Veiculos* InserirVeiculo(Veiculos * Inicio, int id, char tipo[], float bateria, float autonomia, char geocode[]) 
{
	if (ExisteVeiculo(Inicio, id) == 0) 
    {
		Veiculos* novo = malloc(sizeof(Veiculos));
		if (novo != NULL) 
        {
			novo->id = id;
			strcpy(novo->tipo, tipo);
            novo->bateria = bateria;
            novo->autonomia = autonomia;
            strcpy(novo->geocode, geocode);

			novo->seguinte = Inicio;
			return(novo);
        }
	}
	else return(Inicio);
}

Veiculos* LerVeiculos()
{
    FILE* fp;
    int id;
    float bateria, autonomia;
    char tipo[40], geocode[40];

    Veiculos* aux = NULL;
    fp = fopen("../veiculos.txt", "r");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%d;%[^;];%f;%f;%[^\n]\n", &id, tipo, &bateria, &autonomia, geocode);
            aux = InserirVeiculo(aux, id, tipo, bateria, autonomia, geocode);
        }
        fclose(fp);
    }
    return(aux);
}

void ListarVeiculos(Veiculos* Inicio) 
{
	while (Inicio != NULL) 
    {
		printf("%d %s %f %f %s\n", Inicio->id, Inicio->tipo, Inicio->bateria, Inicio->autonomia, Inicio->geocode);
		Inicio = Inicio->seguinte;
	}
}

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

void listarVeiculosNoRaio(struct node* grafo, Veiculos* Inicio, float clienteLat, float clienteLon, float raio, int cidadeAlvo, char tipoVeiculo[]) {
    // Inicialização das estruturas de dados
    int* visitado = (int*)malloc(sizeof(int) * MAX_VERTICES);
    memset(visitado, 0, sizeof(int) * MAX_VERTICES);

    float* distancia = (float*)malloc(sizeof(float) * MAX_VERTICES);
    memset(distancia, -1, sizeof(float) * MAX_VERTICES);

    struct node** fila = (struct node**)malloc(sizeof(struct node*) * MAX_VERTICES);
    int frente = 0, tras = 0;

    int geocode;
    while (Inicio != NULL)
    {
    // Localização do vértice inicial (cliente)
    struct node* verticeAtual = grafo;
    while (verticeAtual != NULL) {
        // Verifica se há veículo associado à cidade atual
        if (verticeAtual->PtAdjacente != NULL) {
            // Cálculo da distância euclidiana entre o cliente e o veículo
            float lat1 = clienteLat;
            float lon1 = clienteLon;
            float lat2 = verticeAtual->Latitude;
            float lon2 = verticeAtual->Longitude;
            float distanciaAtual = sqrt(pow(lat2 - lat1, 2) + pow(lon2 - lon1, 2));

            // Verifica se o veículo está dentro do raio de busca e pertence à cidade alvo
            
                geocode = atoi(Inicio->geocode);
                if (!visitado[verticeAtual->ID] && distanciaAtual <= raio && verticeAtual->ID == geocode && strcmp(Inicio->tipo, tipoVeiculo) == 0) {
                    printf("- %s / %s (Distância: %.2f)\n", verticeAtual->Cidade, Inicio->tipo, distanciaAtual);
                    visitado[verticeAtual->ID] = 1;
                    distancia[verticeAtual->ID] = distanciaAtual;
                    fila[tras++] = verticeAtual;
                }
        }

        verticeAtual = verticeAtual->seguinte;
    }

    // BFS adaptado para calcular a distância acumulada com base em latitude e longitude
    while (frente != tras) {
        struct node* noAtual = fila[frente++];
        struct adjacente* adjacente = noAtual->PtAdjacente;
        while (adjacente != NULL) {
            struct node* noAdjacente = adjacente->PtDestino;

            // Verifica se há veículo associado à cidade adjacente
            if (noAdjacente->PtAdjacente != NULL) {
                // Cálculo da distância euclidiana entre os pontos geográficos
                float lat1 = noAtual->Latitude;
                float lon1 = noAtual->Longitude;
                float lat2 = noAdjacente->Latitude;
                float lon2 = noAdjacente->Longitude;
                float distanciaAtual = sqrt(pow(lat2 - lat1, 2) + pow(lon2 - lon1, 2));

                // Verifica se o veículo está dentro do raio de busca e pertence à cidade alvo
                    geocode = atoi(Inicio->geocode);
                    if (!visitado[noAdjacente->ID] && distanciaAtual <= raio && noAdjacente->ID == geocode && strcmp(Inicio->tipo, tipoVeiculo) == 0) {
                        printf("- %s / %s (Distância: %.2f)\n", noAdjacente->Cidade, Inicio->tipo, distancia[noAtual->ID] + distanciaAtual);
                        visitado[noAdjacente->ID] = 1;
                        distancia[noAdjacente->ID] = distancia[noAtual->ID] + distanciaAtual;
                        fila[tras++] = noAdjacente;
                    }
            }

            adjacente = adjacente->seguinte;
        }
    }
    Inicio = Inicio->seguinte;
    }

    // Liberar memória alocada
    free(visitado);
    free(distancia);
    free(fila);
}

// =========

void menorCaminho(Node grafo, int origem, int destino) {
    int dist[MAX_VERTICES];
    int visitado[MAX_VERTICES];
    int anterior[MAX_VERTICES];
    int i, menorDist, proximoNo;

    // Inicialização
    Node noAtual = grafo;
    while (noAtual != NULL) {
        dist[noAtual->ID] = INT_MAX;
        visitado[noAtual->ID] = 0;
        anterior[noAtual->ID] = -1;
        noAtual = noAtual->seguinte;
    }

    dist[origem] = 0;

    for (i = 0; i < MAX_VERTICES; i++) {
        menorDist = INT_MAX;

        // Encontra o nó com a menor distância
        noAtual = grafo;
        while (noAtual != NULL) {
            if (!visitado[noAtual->ID] && dist[noAtual->ID] < menorDist) {
                menorDist = dist[noAtual->ID];
                proximoNo = noAtual->ID;
            }
            noAtual = noAtual->seguinte;
        }

        visitado[proximoNo] = 1;

        // Atualiza as distâncias dos nós adjacentes ao nó atual
        noAtual = grafo;
        while (noAtual != NULL) {
            Adjacente adjacente = noAtual->PtAdjacente;
            while (adjacente != NULL) {
                if (adjacente->PtDestino->ID == proximoNo) {
                    int distancia = dist[proximoNo] + adjacente->peso;
                    if (distancia < dist[noAtual->ID]) {
                        dist[noAtual->ID] = distancia;
                        anterior[noAtual->ID] = proximoNo;
                    }
                    break;
                }
                adjacente = adjacente->seguinte;
            }
            noAtual = noAtual->seguinte;
        }
    }

    // Imprime o menor caminho
    if (dist[destino] == INT_MAX) {
        printf("Não há caminho entre os nós %d e %d.\n", origem, destino);
    } else {
        printf("Menor caminho entre os nós %d e %d:\n", origem, destino);
        int caminho[MAX_VERTICES];
        int tamanhoCaminho = 0;
        int no = destino;
        while (no != -1) {
            caminho[tamanhoCaminho++] = no;
            no = anterior[no];
        }

        for (i = tamanhoCaminho - 1; i >= 0; i--) {
            printf("%d ", caminho[i]);
        }
        printf("\n");
        printf("Distância total: %d\n", dist[destino]);
    }
}

// =======================================================================

int main() {
    Veiculos *veiculos=NULL;
    int id, gestor;
    char nome[TAM], morada[TAM];
    float saldo;
    
    veiculos = LerVeiculos();

    ListarVeiculos(veiculos);

    // =====
    printf("\n\n\n");
    // =====
    
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

    //listarVeiculosNoRaio(novoGrafo, veiculos, 10, 10, 100, 1, "1");
    menorCaminho(novoGrafo, 1, 3);

    // Limpar o novo grafo
    liberarGrafo(novoGrafo);

    return 0;
}