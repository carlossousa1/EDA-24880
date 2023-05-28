/**
 * @author Carlos Sousa (a24880@alunos.ipca.pt)
 * @brief Estrutuacao dos dados do trabalho
 * @version 0.5
 * @date 2023-03-16
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes.h"

/*
    Manipulacao da base de dados
*/

// Determinar a existencia do id ligada a lista
// 1 = existe, 0 = nao existe
int existeClientes(Clientes* inicio, int valor)
{
    while(inicio!=NULL)
    {
        if (inicio->id == valor) return(1);
        inicio = inicio->seguinte_clientes;
    }
    return(0);
}

// Guardar estrutura clientes em uma celula livre da base de dados
Clientes* inserirClientes(Clientes * inicio, int id, char nome[], float saldo, char morada[], int gestor)
{
    if (!existeClientes(inicio, id))
    {
        Clientes * novo = malloc(sizeof(struct registo_clientes));
        
        if (novo != NULL)
        {
            novo->id = id;
            strcpy(novo->nome,nome);
            novo->saldo = saldo;
            strcpy(novo->morada,morada);
            novo->gestor = gestor;

            return(novo);
        }
    } else return(inicio);
}

// Listar clientes
void listarClientes(Clientes * inicio)
{
    while (inicio != NULL)
    {
        printf("%d %s %f %s %d",inicio->id,inicio->nome,inicio->saldo,inicio->morada,inicio->gestor);
        inicio = inicio->seguinte_clientes;
    }
}

// Remover uma linha da base de dados clientes
Clientes* removerClientes(Clientes* inicio, int id) 
{
    Clientes *anterior=inicio, *atual=inicio, *aux;

    if (atual==NULL) return(NULL);
    else if (atual->id == id) // remoção do 1º registo
    {
        aux = atual->seguinte_clientes;
        free(atual);
        return(aux);
    }
    else
    {
        while ((atual!=NULL)&&(atual->id!=id)) 
        {
            anterior = atual;
            atual = atual->seguinte_clientes;
        }
        if (atual==NULL) return(inicio);
        else
        {
            anterior->seguinte_clientes = atual->seguinte_clientes;
            free(atual);
            return(inicio);
        }
    }
}

// Alterar um linha da base de dados clientes
// (...)

/*
    Gestao de ficheiros
*/

// Ler lista de veiculos no ficheiro "clientes.txt"
Clientes* lerClientes()
{
    FILE* fp;
    int id, gestor;
    float saldo;
    char nome[50], morada[50];

    Clientes* aux=NULL;
    fp = fopen("clientes.txt","r"); // "r"  read
    if (fp!=NULL)
    {
        while (!feof(fp))
        { 
            fscanf(fp, "%d;%[^;];%f;%[^;];%d\n", &id, nome, &saldo, morada, &gestor);
            
            aux = inserirClientes(aux, id, nome, saldo, morada, gestor);
        }
        fclose(fp);
    }
    return(aux);
}

// Armazenar informacao dos clientes em um ficheiro .bin
int guardarClientesBin(Clientes* inicio)
{
    FILE* fp;
    fp = fopen("clientes.bin","wb");  // "w" write
    if (fp!=NULL)
    {
        Clientes* aux= inicio; // aux referencia o início da lista ligada
        while (aux != NULL)
        {
            fwrite(&aux->id, sizeof(int), 1, fp);
            fwrite(aux->nome, sizeof(char), 50, fp);
            fwrite(&aux->saldo, sizeof(float), 1, fp);
            fwrite(aux->morada, sizeof(char), 50, fp);
            fwrite(&aux->gestor, sizeof(int), 1, fp);
            aux = aux->seguinte_clientes;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}

// Ler lista de veiculos no ficheiro "clientes.bin"
Clientes* lerClientesBin()
{
    FILE* fp;
    int id, gestor;
    float saldo;
    char nome[50], morada[50];

    Clientes* aux=NULL;
    fp = fopen("clientes.bin","rb"); // "r"  read
    if (fp!=NULL)
    {
        while (!feof(fp))
        { 
            fread(&id, sizeof(int), 1, fp);
            fread(nome, sizeof(char), 50, fp);
            fread(&saldo, sizeof(float), 1, fp);
            fread(morada, sizeof(char), 50, fp);
            fread(&gestor, sizeof(int), 1, fp);
            
            aux = inserirClientes(aux, id, nome, saldo, morada, gestor);
        }
        fclose(fp);
    }
    return(aux);
}