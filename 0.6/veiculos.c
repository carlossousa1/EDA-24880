/**
 * @author Carlos Sousa (a24880@alunos.ipca.pt)
 * @brief Estrutuacao dos dados do trabalho
 * @version 0.6
 * @date 2023-04-19
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes.h"

/*
    Manipulacao da base de dados
*/

//Verificar se um veiculo existe pelo seu id
int ExisteVeiculo(Veiculos* Inicio, int id) 
{
	while (Inicio != NULL) {
		if (Inicio->id == id) return(1);
		Inicio = Inicio->seguinte;
	}
	return(0);
}

//Inserir veículos
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

//Listar veiculos
void ListarVeiculos(Veiculos* Inicio) 
{
	while (Inicio != NULL) 
    {
		printf("%d %s %f %f %s\n", Inicio->id, Inicio->tipo, Inicio->bateria, Inicio->autonomia, Inicio->geocode);
		Inicio = Inicio->seguinte;
	}
}

//Remover um veiculo
Veiculos* RemoverVeiculo(Veiculos* Inicio, int id) 
{
	Veiculos* anterior = Inicio, * atual = Inicio, * aux;
    if (atual == NULL) return(NULL);
    else if (atual->id == id) //remoção do 1º registo
    {
        aux = atual->seguinte;
        free(atual);
        return(aux);
    }
    else
    {
        while ((atual != NULL) && (atual->id != id))
        {
            anterior = atual;
            atual = atual->seguinte;
        }
        if (atual == NULL) return(Inicio);
        else
        {
            anterior->seguinte = atual->seguinte;
            free(atual);
            return(Inicio);
        }
    }
}

//Editar dados de um veiculo
Veiculos* EditarVeiculo(Veiculos* Inicio, int id, char tipo[], float bateria, float autonomia, char geocode[])
{
    if (ExisteVeiculo(Inicio, id) == 1)
    {
        while (Inicio != NULL)
        {
            if (Inicio->id == id)
            {
                Inicio->id = id;
			    strcpy(Inicio->tipo, tipo);
                Inicio->bateria = bateria;
                Inicio->autonomia = autonomia;
                strcpy(Inicio->geocode, geocode);
            }
            Inicio = Inicio->seguinte;
        }
        return(Inicio);
    }
    else
    printf("Cliente nao encontrado!\n");
}

//Devolver número de veículos
int QuantVeiculos(Veiculos* Inicio)
{
	Veiculos* aux = Inicio;
	int quant = 0;
	if (aux == NULL) return(0);
	else {
		while (aux != NULL) {
			quant++;
			aux = aux->seguinte;
		}
	}
	return(quant);
}

void DescrescenteVeiculos(Veiculos* Inicio)
{
    Veiculos* atual = Inicio;
    Veiculos* temp = NULL;
    float temp_autonomia = 0;

    // lista temporária dos veículos
    while (atual != NULL)
    {
        Veiculos* novo_veiculo = (Veiculos*)malloc(sizeof(Veiculos));
        novo_veiculo->id = atual->id;
        strcpy(novo_veiculo->tipo, atual->tipo);
        novo_veiculo->bateria = atual->bateria;
        novo_veiculo->autonomia = atual->autonomia;
        strcpy(novo_veiculo->geocode, atual->geocode);
        novo_veiculo->seguinte = temp;
        temp = novo_veiculo;
    }

    // ordenar lista temporária por ordem decrescente de autonomia
    for (Veiculos* i=temp; i!=NULL; i=i->seguinte)
    {
        for (Veiculos* j=i->seguinte; j!=NULL; j=j->seguinte)
        {
            if(j->autonomia > i->autonomia)
            {
                temp_autonomia = i->autonomia;
                i->autonomia = j->autonomia;
                j->autonomia = temp_autonomia;
            }
        }
    }

    // imprimir nova infomacao
    for (Veiculos* i = temp; i != NULL; i = i->seguinte)
    {
        printf("%d %s %f %f %s\n", Inicio->id, Inicio->tipo, Inicio->bateria, Inicio->autonomia, Inicio->geocode);
    }

    // liberar memória da lista temporária
    while (temp != NULL)
    {
        Veiculos* proximo = temp->seguinte;
        free(temp);
        temp = proximo;
    }
}

/*
    Manipulacao de ficheiros
*/

//Ler ficheiro ".txt" dos veículos
Veiculos* LerVeiculos()
{
    FILE* fp;
    int id;
    float bateria, autonomia;
    char tipo[40], geocode[40];

    Veiculos* aux = NULL;
    fp = fopen("veiculos.txt", "r");
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

//Ler ficheiro ".bin" dos veículos
Veiculos* LerVeiculosBin()
{
	FILE* fp;
    int id;
    float bateria, autonomia;
    char tipo[40], geocode[40];

    Veiculos* aux=NULL;
    fp = fopen("veiculos.bin","rb"); // "rb" read binary
    if (fp!=NULL)
    {
        while (!feof(fp))
        {
            fread(&id, sizeof(int), 1, fp);
            fread(tipo, sizeof(char), 20, fp);
            fread(&bateria, sizeof(float), 1, fp);
            fread(&autonomia, sizeof(float), 1, fp);
            fread(geocode, sizeof(char), 20, fp);
            aux = InserirVeiculo(aux, id, tipo, bateria, autonomia, geocode);
        }
        fclose(fp);
    }
    return(aux);
}

//Guardar veiculos em um ficheiro ".bin"
int guardarVeiculosBin(Veiculos* Inicio)
{
	FILE* fp;
    fp = fopen("veiculos.bin","wb"); // "wb" write binary

    if (fp!=NULL)
    {
        Veiculos* aux= Inicio; // aux referencia o início da lista ligada
        while (aux != NULL)
        {
            fwrite(&aux->id, sizeof(int), 1, fp);
            fwrite(aux->tipo, sizeof(char), 20, fp);
            fwrite(&aux->bateria, sizeof(float), 1, fp);
            fwrite(&aux->autonomia, sizeof(float), 1, fp);
            fwrite(aux->geocode, sizeof(char), 20, fp);
            aux = aux->seguinte;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}