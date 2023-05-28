/**
 * @author Carlos Sousa (a24880@alunos.ipca.pt)
 * @brief Estrutuacao dos dados do trabalho
 * @version 0.8
 * @date 2023-05-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "includes.h"

// Número máximo de vertices aceites
#define MAX_VERTICES 100

/*
=====================================================================    
    Manipulacao da base de dados
=====================================================================
*/

/*
    Inserir nodes (Vértices)
*/
Node InserirNode(int ID, char* Cidade, float Latitude, float Longitude) 
{
    Node novoNode = (Node)malloc(sizeof(struct registo_node));
    novoNode->ID = ID;
    novoNode->Cidade = strdup(Cidade);
    novoNode->Latitude = Latitude;
    novoNode->Longitude = Longitude;
    novoNode->PtAdjacente = NULL;
    novoNode->seguinte = NULL;
    return novoNode;
}

/*
    Criar adjacencias
    (Funcao auxeiliar para "AdicinarAdjacente")
*/
Adjacente CriarAdjacente(Node PtDestino, int peso) 
{
    Adjacente novoAdjacente = (Adjacente)malloc(sizeof(struct registo_adjacente));
    novoAdjacente->PtDestino = PtDestino;
    novoAdjacente->peso = peso;
    novoAdjacente->seguinte = NULL;
    return novoAdjacente;
}

/*
    Inserir adjacencias
*/
void InserirAdjacente(Node node, Node adjacente, int peso) 
{
    Adjacente novoAdjacente = CriarAdjacente(adjacente, peso);

    if (node->PtAdjacente == NULL) 
    {
        node->PtAdjacente = novoAdjacente;
    } else 
    {
        Adjacente ultimoAdjacente = node->PtAdjacente;
        while (ultimoAdjacente->seguinte != NULL) 
        {
            ultimoAdjacente = ultimoAdjacente->seguinte;
        }
        ultimoAdjacente->seguinte = novoAdjacente;
    }
}

/*
    Listar grafo
*/
void ListarGrafos(Node grafo) 
{
    Node node = grafo;
    while (node != NULL) 
    {
        printf("Cidade: %s (%.2f,%.2f)\n", node->Cidade, node->Latitude, node->Longitude);

        Adjacente adjacente = node->PtAdjacente;
        while (adjacente != NULL) 
        {
            printf("  Adjacente: %s, Peso: %d\n", adjacente->PtDestino->Cidade, adjacente->peso);
            adjacente = adjacente->seguinte;
        }

        node = node->seguinte;
    }
}

/*
    Liberar dados do grafo
*/
void LiberarGrafo(Node grafo) 
{
    Node nodeAtual = grafo;
    while (nodeAtual != NULL) 
    {
        Node nodeProximo = nodeAtual->seguinte;

        Adjacente adjacenteAtual = nodeAtual->PtAdjacente;
        while (adjacenteAtual != NULL) 
        {
            Adjacente adjacenteProximo = adjacenteAtual->seguinte;
            free(adjacenteAtual);
            adjacenteAtual = adjacenteProximo;
        }

        free(nodeAtual->Cidade);
        free(nodeAtual);

        nodeAtual = nodeProximo;
    }
}

/*
    Distancia dos Veiculos em um raio
*/
void listarVeiculosRaio(Node grafo, Veiculos* Inicio, float clienteLat, float clienteLon, float raio, char tipoVeiculo[]) 
{
    // Inicialização dos arrays estáticos
    int visitado[MAX_VERTICES] = {0};
    float distancia[MAX_VERTICES];
    Node fila[MAX_VERTICES];
    int frente = 0, tras = 0;

    int geocode;
    while (Inicio != NULL) 
    {
        // Localização do vértice inicial (cliente)
        Node verticeAtual = grafo;
        while (verticeAtual != NULL) 
        {
            // Verifica se há veículo associado à cidade atual
            if (verticeAtual->PtAdjacente != NULL) 
            {
                // Cálculo da distância euclidiana entre o cliente e o veículo
                float lat1 = clienteLat;
                float lon1 = clienteLon;
                float lat2 = verticeAtual->Latitude;
                float lon2 = verticeAtual->Longitude;
                float distanciaAtual = sqrt(pow(lat2 - lat1, 2) + pow(lon2 - lon1, 2));

                // Verifica se o veículo está dentro do raio de busca e pertence à cidade alvo
                geocode = atoi(Inicio->geocode);
                if (!visitado[verticeAtual->ID] && distanciaAtual <= raio && verticeAtual->ID == geocode && strcmp(Inicio->tipo, tipoVeiculo) == 0) 
                {
                    printf("- %s / %s (Distância: %.2f)\n", verticeAtual->Cidade, Inicio->tipo, distanciaAtual);
                    visitado[verticeAtual->ID] = 1;
                    distancia[verticeAtual->ID] = distanciaAtual;
                    fila[tras++] = verticeAtual;
                }
            }

            verticeAtual = verticeAtual->seguinte;
        }

        // BFS adaptado para calcular a distância acumulada com base em latitude e longitude
        while (frente != tras) 
        {
            Node noAtual = fila[frente++];
            Adjacente adjacente = noAtual->PtAdjacente;
            while (adjacente != NULL) 
            {
                Node noAdjacente = adjacente->PtDestino;

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
}

/*
    Percorrer grafo para recolher veiculos com menos de 50% da bateria
*/
void menorCaminhoVeiculos(Node grafo, Veiculos* listaVeiculos, char* tipoVeiculo, int origem, int destino) 
{
    int dist[MAX_VERTICES];
    int anterior[MAX_VERTICES];
    int visitado[MAX_VERTICES];
    int fila[MAX_VERTICES];
    int frente = 0, tras = 0;
    int i, geocode;

    // Inicialização
    for (i = 0; i < MAX_VERTICES; i++) 
    {
        dist[i] = INT_MAX;
        anterior[i] = -1;
        visitado[i] = 0;
    }

    dist[origem] = 0;
    visitado[origem] = 1;
    fila[tras++] = origem;

    while (frente != tras) 
    {
        int verticeAtual = fila[frente++];
        Node noAtual = grafo;
        while (noAtual != NULL) 
        {
            if (noAtual->ID == verticeAtual) 
            {
                Adjacente adjacente = noAtual->PtAdjacente;
                while (adjacente != NULL) 
                {
                    Node noAdjacente = adjacente->PtDestino;
                    int pesoAdjacente = adjacente->peso;

                    if (!visitado[noAdjacente->ID]) 
                    {
                        visitado[noAdjacente->ID] = 1;
                        dist[noAdjacente->ID] = dist[verticeAtual] + pesoAdjacente;
                        anterior[noAdjacente->ID] = verticeAtual;
                        fila[tras++] = noAdjacente->ID;
                    } else if (dist[verticeAtual] + pesoAdjacente < dist[noAdjacente->ID]) 
                    {
                        dist[noAdjacente->ID] = dist[verticeAtual] + pesoAdjacente;
                        anterior[noAdjacente->ID] = verticeAtual;
                    }

                    adjacente = adjacente->seguinte;
                }
                break;
            }
            noAtual = noAtual->seguinte;
        }
    }

    printf("\n");
    // Imprime o menor caminho
    if (dist[destino] == INT_MAX) 
    {
        printf("Não há caminho entre os nós %d e %d.\n", origem, destino);
    } else 
    {
        printf("Menor caminho entre os nós %d e %d:\n", origem, destino);
        int caminho[MAX_VERTICES];
        int tamanhoCaminho = 0;
        int no = destino;
        while (no != -1) 
        {
            caminho[tamanhoCaminho++] = no;
            no = anterior[no];
        }

        printf("Percurso com veículos do tipo '%s': ", tipoVeiculo);
        for (i = tamanhoCaminho - 1; i >= 0; i--) 
        {
            Node noAtual = grafo;
            while (noAtual != NULL) 
            {
                if (noAtual->ID == caminho[i]) 
                {
                    Veiculos* veiculoAtual = listaVeiculos;
                    while (veiculoAtual != NULL) 
                    {
                        geocode = atoi(veiculoAtual->geocode);
                        // verifica e retorna se há veículo no vértice
                        if (geocode == noAtual->ID && strcmp(veiculoAtual->tipo, tipoVeiculo) == 0) 
                        {
                            printf("%d ", caminho[i]);
                            if (veiculoAtual->bateria < 50) 
                            {
                                printf("(%s) ", veiculoAtual->tipo);
                            }
                            break;
                        }
                        veiculoAtual = veiculoAtual->seguinte;
                    }
                    break;
                }
                noAtual = noAtual->seguinte;
            }
        }
        printf("\n");
        printf("Distância total: %d\n", dist[destino]);
    }
}

/*
=====================================================================    
    Manipulacao de ficheiros
=====================================================================    
*/

/*
    Ler ficheiro ".txt" dos Nodes (Vértices)
*/
void LerVertices(Node* grafo) 
{
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
        novoNode = InserirNode(ID, Cidade, Latitude, Longitude);

        if (*grafo == NULL) {
            *grafo = novoNode;
        } else {
            ultimoNode->seguinte = novoNode;
        }
        ultimoNode = novoNode;
    }

    fclose(arquivo);
}

/*
    Ler ficheiro ".bin" dos nodes (Vértices)
*/
void LerVerticesBin(Node* grafo) 
{
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

        novoNode = InserirNode(ID, Cidade, Latitude, Longitude);

        if (*grafo == NULL) {
            *grafo = novoNode;
        } else {
            ultimoNode->seguinte = novoNode;
        }
        ultimoNode = novoNode;
    }

    fclose(arquivo);
}

/*
    Ler ficheiro ".txt" das Adjacencias
*/
void LerAdjacencias(Node grafo) 
{
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
                    InserirAdjacente(adjacente, nodeAdjacente, peso);
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

/*
    Ler ficheiro ".bin" das adjacencias
*/
void LerAdjacenciasBin(Node grafo) 
{
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
                    InserirAdjacente(adjacente, nodeAdjacente, peso);
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

/*
    Guardar nodes (Vertices) em um ficheiro ".bin"
*/
void guardarVerticesBin(Node grafo) 
{
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

/*
    Guardar adjacencias em um ficheiro ".bin"
*/
void guardarAdjacenciasBin(Node grafo) 
{
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