#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50

struct adjacente {
    struct node* PtDestino;
    int peso;
    struct adjacente* seguinte;
};

struct node {
    int ID;
    char* Cidade;
    float Latitude;
    float Longitude;
    struct adjacente* PtAdjacente;
    struct node* seguinte;
};

typedef struct registo_veiculos {
    int id;
    char tipo[TAM];
    float bateria;
    float autonomia;
    char geocode[TAM];
    struct registo_veiculos* seguinte;
} Veiculos;

float calcularDistancia(float lat1, float lon1, float lat2, float lon2) {
    // Cálculo simplificado da distância entre dois pontos (latitude, longitude)
    // Você pode substituir essa função pelo cálculo real da distância se necessário
    return abs(lat2 - lat1) + abs(lon2 - lon1);
}

void listarVeiculosECalcularDistancias(struct node* vertices, Veiculos* veiculos) {
    Veiculos* veiculoAtual = veiculos;
    while (veiculoAtual != NULL) {
        struct node* cidadeAtual = vertices;
        while (cidadeAtual != NULL) {
            if (cidadeAtual->ID == atoi(veiculoAtual->geocode)) {
                // Cálculo da distância simplificado
                float distancia = abs(cidadeAtual->Latitude - cidadeAtual->Latitude) +
                                  abs(cidadeAtual->Longitude - cidadeAtual->Longitude);
                printf("Veículo ID: %d\n", veiculoAtual->id);
                printf("Distância: %.2f\n", distancia);
                printf("------------\n");
                break; // Saímos do loop interno quando encontramos a correspondência
            }
            cidadeAtual = cidadeAtual->seguinte;
        }
        veiculoAtual = veiculoAtual->seguinte;
    }
}

int main() {
    struct node cidade1 = { 1, "Cidade1", 12.34, 56.78, NULL, NULL };
    struct node cidade2 = { 2, "Cidade2", 23.45, 67.89, NULL, NULL };
    struct node cidade3 = { 3, "Cidade3", 34.56, 78.90, NULL, NULL };

    Veiculos veiculo1 = { 1, "Carro", 80.0, 600.0, "1", NULL };
    Veiculos veiculo2 = { 2, "Moto", 60.0, 400.0, "3", NULL };
    Veiculos veiculo3 = { 3, "Bicicleta", 0.0, 0.0, "2", NULL };

    listarVeiculosECalcularDistancias(&cidade1, &Veiculos);


    return 0;
}

