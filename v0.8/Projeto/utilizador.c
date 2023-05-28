/**
 * @author Carlos Sousa (a24880@alunos.ipca.pt)
 * @brief Estrutuacao dos dados do trabalho
 * @version 0.8
 * @date 2023-05-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes.h"

/*
=====================================================================    
    Manipulacao da base de dados
    Comandos exclusivos para os clientes
=====================================================================
*/

/*
    Verificar se o Utilizador é Cliente ou Gestor
*/
int VerificaUtilizador(Clientes* Inicio, int id) 
{
    Clientes* atual = Inicio;
    
    while (atual != NULL) {
        if (atual->id == id && atual->gestor == 1) 
        {
            printf("Logado como Gestor!\n\n");
            return -1;
        }
        else if (atual->id == id)
        {
            printf("Logado como Cliente!\n\n");
            return atual->id;
        }

        atual = atual->seguinte;
    }
}

/*
    Ler saldo de um Cliente
*/
int LerSaldo(Clientes* Inicio, int id)
{
    Clientes* atual = Inicio;

    while (atual != NULL)
    {
        if (atual->id == id) 
            return atual->saldo;
		atual = atual->seguinte;
    }
}

/*
    Depositar quantia no saldo de um Cliente
*/
Clientes* DepositarQuantia(Clientes* Inicio, int id, float saldo)
{
    if (ExisteCliente(Inicio, id) == 1) 
    {
        while (Inicio != NULL)
        {
            if (Inicio->id == id) 
            {
                Inicio->saldo = saldo+Inicio->saldo;
            }
            Inicio = Inicio->seguinte;
        }
        return(Inicio);
    }
    else
    printf("Erro ao depositar quantia!\n");
}

/*
    Depositar quantia no saldo de um Cliente
*/
Clientes* RemoverQuantia(Clientes* Inicio, int id, float saldo)
{
    if (ExisteCliente(Inicio, id) == 1) 
    {
        while (Inicio != NULL)
        {
            if (Inicio->id == id) 
            {
                Inicio->saldo = Inicio->saldo-saldo;
            }
            Inicio = Inicio->seguinte;
        }
        printf("Aluguer removido!\n");
        return(Inicio);
    }
    else
    printf("Erro ao remover quantia!\n");
}

/*
    Listar aluguer de um Cliente
*/
int ListarAlugueisCliente(Alugueis* Inicio, int id)
{
	Alugueis* atual = Inicio;
    int cont=0;
    
    while (atual != NULL) 
    {
		if (atual->id_utilizador == id)
        {
            printf("%d %d %d %d %d %d %d %.2f %d %d\n", atual->id, atual->ini_dia, atual->ini_mes, atual->ini_ano, atual->fim_dia, atual->fim_mes, atual->fim_ano, atual->valor, atual->id_veiculos, atual->id_utilizador);
        }
        cont++;
        atual = atual->seguinte;
	}
    if (cont == 0)
    {
        return 0;
    }
    else return 1;
}

/*
    Remover Aluguer de um Cliente
*/
Alugueis* removerAluguerCliente(Alugueis* Inicio, int id, int id_utilizador)
{
	Alugueis* anterior = Inicio, * atual = Inicio, * aux;
    if (atual == NULL) return(NULL);
    else if (atual->id == id && atual->id_utilizador == id_utilizador) //remoção do 1º registo
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
        if (atual == NULL && atual->id_utilizador == id_utilizador) return(Inicio);
        else
        {
            anterior->seguinte = atual->seguinte;
            if (atual->id_utilizador == id_utilizador)
                free(atual);
            return(Inicio);
        }
    }
}