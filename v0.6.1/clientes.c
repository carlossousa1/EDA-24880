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
    Manipulacao de listas
*/

//Verificar se um cliente existe pelo seu id
int ExisteCliente(Clientes* Inicio, int id) 
{
	while (Inicio != NULL) {
		if (Inicio->id == id) return(1);
		Inicio = Inicio->seguinte;
	}
	return(0);
}

//Inserir clientes
Clientes* InserirCliente(Clientes * Inicio, int id, char nome[], float saldo, char morada[], int gestor) 
{
	if (ExisteCliente(Inicio, id) == 0) 
    {
		Clientes* novo = malloc(sizeof(Clientes));
		if (novo != NULL) 
        {
			novo->id = id;
			strcpy(novo->nome, nome);
			novo->saldo = saldo;
			strcpy(novo->morada, morada);
            novo->gestor = gestor;

			novo->seguinte = Inicio;
			return(novo);
        }
	}
	else return(Inicio);
}

//Listar clientes
void ListarClientes(Clientes* Inicio) 
{
	while (Inicio != NULL) 
    {
		printf("%d %s %.2f %s %d\n", Inicio->id, Inicio->nome, Inicio->saldo, Inicio->morada, Inicio->gestor);
		Inicio = Inicio->seguinte;
	}
}

//Remover um cliente
Clientes* RemoverCliente(Clientes* Inicio, int id) 
{
	Clientes* anterior = Inicio, * atual = Inicio, * aux;
	if (atual == NULL) return(NULL);
	else if (atual->id == id) //remoção do 1º registo
    {
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else {
		while ((atual != NULL) && (atual->id != id)) {
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL) return(Inicio);
		else {
			anterior->seguinte = atual->seguinte;
			free(atual);
			return(Inicio);
		}
	}
}

//Editar dados de um cliente
Clientes* EditarCliente(Clientes* Inicio, int id, char nome[40], float saldo, char morada[40], int gestor)
{
    if (ExisteCliente(Inicio, id) == 1) 
    {
        while (Inicio != NULL)
        {
            if (Inicio->id == id) 
            {
                strcpy(Inicio->nome, nome);
                Inicio->saldo = saldo;
                strcpy(Inicio->morada, morada);
                Inicio->gestor = gestor;
            }
            Inicio = Inicio->seguinte;
        }
        return(Inicio);
    }
    else
    printf("Cliente nao encontrado!\n");
}

//Devolver número de clientes
int QuantClientes(Clientes* Inicio) 
{
	Clientes* aux = Inicio;
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

/*
    Manipulacao de ficheiros
*/

//Ler ficheiro ".txt" dos clientes
Clientes* LerClientes()
{
	FILE* fp;
	int id, gestor;
    char nome[40], morada[40];
    float saldo;

	Clientes* aux = NULL;
	fp = fopen("clientes.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%f;%[^;];%d\n", &id, nome, &saldo, morada, &gestor);
			aux = InserirCliente(aux, id, nome, saldo, morada, gestor);
		}
		fclose(fp);
	}
	return(aux);
}

//Ler ficheiro ".bin" dos clientes
Clientes* LerClientesBin()
{
	FILE* fp;
	int id, gestor;
	char nome[40], morada[40];
	float saldo;

 	Clientes* aux=NULL;
 	fp = fopen("clientes.bin","rb"); // "rb"  read binary
 	if (fp!=NULL)
 	{
		while (!feof(fp))
  		{ 
			fread(&id, sizeof(int), 1, fp);
			fread(nome, sizeof(char), 20, fp);
			fread(&saldo, sizeof(float), 1, fp);
			fread(morada, sizeof(char), 20, fp);
			fread(&gestor, sizeof(int), 1, fp);
    		aux = InserirCliente(aux, id, nome, saldo, morada, gestor);
  		}
  		fclose(fp);
 	}
 	return(aux);
}

//Guardar clientes em um ficheiro ".bin"
int guardarClientesBin(Clientes* Inicio)
{
	FILE* fp;
	fp = fopen("clientes.bin","wb");  // "wb" write binary

	if (fp!=NULL)
	{
 		Clientes* aux= Inicio; // aux referencia o início da lista ligada
 		while (aux != NULL)
 		{
  			fwrite(&aux->id, sizeof(int), 1, fp);
			fwrite(aux->nome, sizeof(char), 20, fp);
			fwrite(&aux->saldo, sizeof(float), 1, fp);
			fwrite(&aux->morada, sizeof(char), 20, fp);
			fwrite(&aux->gestor, sizeof(int), 1, fp);
  			aux = aux->seguinte;
 		}
		fclose(fp);
		return(1);
 	}
 	else return(0);
}

//---------------------------------
