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

//Verificar se um aluguer existe pelo seu id
int ExisteAluguer(Alugueis* Inicio, int id) 
{
	while (Inicio != NULL) {
		if (Inicio->id == id) return(1);
		Inicio = Inicio->seguinte;
	}
	return(0);
}

//Inserir alugueis
Alugueis* InserirAluguer(Alugueis * Inicio, int id, int ini_dia, int ini_mes, int ini_ano, int fim_dia, int fim_mes, int fim_ano, float valor, int id_veiculos, int id_utilizador)
{
	if (ExisteAluguer(Inicio, id) == 0) 
    {
		Alugueis* novo = malloc(sizeof(Alugueis));
		if (novo != NULL) 
        {
			novo->id = id;
            novo->ini_dia = ini_dia;
            novo->ini_mes = ini_mes;
            novo->ini_ano = ini_ano;
            novo->fim_dia = fim_dia;
            novo->fim_mes = fim_mes;
            novo->fim_ano = fim_ano;
            novo->valor = valor;
            novo->id_veiculos = id_veiculos;
            novo->id_utilizador = id_utilizador;

			novo->seguinte = Inicio;
			return(novo);
        }
	}
	else return(Inicio);
}

//Listar Alugueis
void ListarAlugueis(Alugueis* Inicio) 
{
	while (Inicio != NULL) 
    {
		printf("%d %d %d %d %d %d %d %.2f %d %d\n", Inicio->id, Inicio->ini_dia, 
        Inicio->ini_mes, Inicio->ini_ano, Inicio->fim_dia, Inicio->fim_mes, 
        Inicio->fim_ano, Inicio->valor, Inicio->id_veiculos, Inicio->id_utilizador);
		Inicio = Inicio->seguinte;
	}
}

//Remover um aluguer
Alugueis* removerAluguer(Alugueis* Inicio, int id) 
{
	Alugueis* anterior = Inicio, * atual = Inicio, * aux;
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

//Editar dados de um aluguer
Alugueis* EditarAluguer(Alugueis* Inicio, int id, int ini_dia, int ini_mes, int ini_ano, int fim_dia, int fim_mes, int fim_ano, float valor, int id_veiculos, int id_utilizador)
{
    if (ExisteAluguer(Inicio, id) == 1)
    {
        while (Inicio != NULL)
        {
            if (Inicio->id == id)
            {
                Inicio->id = id;
                Inicio->ini_dia = ini_dia;
                Inicio->ini_mes = ini_mes;
                Inicio->ini_ano = ini_ano;
                Inicio->fim_dia = fim_dia;
                Inicio->fim_mes = fim_mes;
                Inicio->fim_ano = fim_ano;
                Inicio->valor = valor;
                Inicio->id_veiculos = id_veiculos;
                Inicio->id_utilizador = id_utilizador;
            }
            Inicio = Inicio->seguinte;
        }
        return(Inicio);
    }
    else
    printf("Cliente nao encontrado!\n");
}

//Devolver número de alugueres
int QuantAlugueis(Alugueis* Inicio)
{
	Alugueis* aux = Inicio;
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

// Registo do aluguer de um determinado veiculo
int VeiculoAlugueis(Alugueis* Inicio, int id_veiculos)
{
    Alugueis* atual = Inicio;
    while(atual != NULL)
    {
        if(atual->id_veiculos == id_veiculos)
        {
            printf("%d %d %d %d %d %d %d %.2f %d %d\n", atual->id, atual->ini_dia, 
        atual->ini_mes, atual->ini_ano, atual->fim_dia, atual->fim_mes, 
        atual->fim_ano, atual->valor, atual->id_veiculos, atual->id_utilizador);
        }
        atual = atual->seguinte;
    }
}

/*
    Manipulacao de ficheiros
*/

//Ler ficheiro ".txt" dos alugueis
Alugueis* LerAlugueis()
{
    FILE* fp;
    int id, ini_dia, ini_mes, ini_ano, fim_dia, fim_mes, fim_ano, id_veiculos, id_utilizador;
    float valor;

    Alugueis* aux = NULL;
    fp = fopen("aluguer.txt", "r");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%d;%d;%d;%d;%d;%d;%d;%f;%d;%d\n", &id, &ini_dia, &ini_mes, &ini_ano, &fim_dia, &fim_mes, &fim_ano, &valor, &id_veiculos, &id_utilizador);
            aux = InserirAluguer(aux, id, ini_dia, ini_mes, ini_ano, fim_dia, fim_mes, fim_ano, valor, id_veiculos, id_utilizador);
        }
        fclose(fp);
    }
    return(aux);
}

//Ler ficheiro ".bin" dos alugueis
Alugueis* LerAlugueisBin()
{
	FILE* fp;
    int id, ini_dia, ini_mes, ini_ano, fim_dia, fim_mes, fim_ano, id_veiculos, id_utilizador;
    float valor;

    Alugueis* aux=NULL;
    fp = fopen("aluguer.bin","rb"); // "rb" read binary
    if (fp!=NULL)
    {
        while (!feof(fp))
        {
            fread(&id, sizeof(int), 1, fp);
            fread(&ini_dia, sizeof(int), 1, fp);
            fread(&ini_mes, sizeof(int), 1, fp);
            fread(&ini_ano, sizeof(int), 1, fp);
            fread(&fim_dia, sizeof(int), 1, fp);
            fread(&fim_mes, sizeof(int), 1, fp);
            fread(&fim_ano, sizeof(int), 1, fp);
            fread(&valor, sizeof(float), 1, fp);
            fread(&id_veiculos, sizeof(int), 1, fp);
            fread(&id_utilizador, sizeof(int), 1, fp);
            aux = InserirAluguer(aux, id, ini_dia, ini_mes, ini_ano, fim_dia, fim_mes, fim_ano, valor, id_veiculos, id_utilizador);
        }
        fclose(fp);
    }
    return(aux);
}

//Guardar alugueis em um ficheiro ".bin"
int guardarAlugueisBin(Alugueis* Inicio)
{
	FILE* fp;
    fp = fopen("aluguer.bin","wb"); // "wb" write binary

    if (fp!=NULL)
    {
        Alugueis* aux= Inicio; // aux referencia o início da lista ligada
        while (aux != NULL)
        {
            fwrite(&aux->id, sizeof(int), 1, fp);
            fwrite(&aux->ini_dia, sizeof(int), 1, fp);
            fwrite(&aux->ini_mes, sizeof(int), 1, fp);
            fwrite(&aux->ini_ano, sizeof(int), 1, fp);
            fwrite(&aux->fim_dia, sizeof(int), 1, fp);
            fwrite(&aux->fim_mes, sizeof(int), 1, fp);
            fwrite(&aux->fim_ano, sizeof(int), 1, fp);
            fwrite(&aux->valor, sizeof(float), 1, fp);
            fwrite(&aux->id_veiculos, sizeof(int), 1, fp);
            fwrite(&aux->id_utilizador, sizeof(int), 1, fp);
            aux = aux->seguinte;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}