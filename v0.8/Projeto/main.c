/**
 * @author Carlos Sousa (a24880@alunos.ipca.pt)
 * @brief Estrutuacao dos dados do trabalho
 * @version 0.8
 * @date 2023-05-25
 */

// IMPORTANTE!!!!!
/*
    Para compilar com o GCC em Linux e garantir o bom funcionamento da func. math, 
    deve-se seguir o seguinte exemplo!

    exemplo: gcc *.c -o programa -lm
*/

// include das funcionalidades extraídas dos outros arquivos ".c"
#include "includes.h"
// include da biblioteca para escrita e leitura de dados no "main.c"
#include <stdio.h>
// include da biblioteca para liberar memória no "main.c"
#include "stdlib.h"

int menu(int grupo, int login, float quantia)
{
    int opcao;
    if (login == -1)
    {

        if(grupo != 4)
        {
            printf("\n-- M E N U --\n");
            printf("1 Inserir Meio\n");
            printf("2 Listar Meios\n");
            printf("3 Remover Meio\n");
            printf("4 Editar Meios\n");
            printf("5 Guardar Meios\n");
            printf("6 Ler Meios\n");
            if(grupo == 1)
            {
                printf("7 Listar Veiculos\n");
                printf("8 Listagem Geocodigo\n");
            }
            else if(grupo == 3)
            {
                printf("7 Veiculos por Aluguer\n");
            }
        }
        else
        {
            printf("1 Guardar Grafo\n");
            printf("2 Ler Grafo\n");
            printf("3 Listar Grafo\n");
            printf("4 Distancia Grafo\n");
            printf("5 Percurso Coleta Grafo\n");
        }
        printf("9 Trocar\n");

    }
    else
    {
        printf("id:%d / saldo:%.2f\n", login, quantia);
        printf("-- M E N U --\n");
        printf("1 Depositar Quantia\n");
        printf("2 Novo Aluguer\n");
        printf("3 Remover Aluguer\n");
        printf("4 Listar Alugueres\n");

    }
    printf("0 Sair\n");
    printf("Opcao: ");
    scanf("%d",&opcao);
    return(opcao);
}

int main()
{
    int opcao, opcao2=2, opcao3=-1;
    int login; // variável que verifica se é cliente ou gestor
    float quantia; // variável que mostra a quantia do cliente logado
    
    Veiculos *veiculos=NULL;
    int id, gestor;
    char nome[TAM], morada[TAM];
    float saldo;

    Clientes *clientes=NULL;
    char tipo[TAM], geocode[TAM];
    float bateria, autonomia;

    Alugueis *alugueis=NULL;
    int ini_dia, ini_mes, ini_ano, fim_dia, fim_mes, fim_ano, id_veiculos, id_utilizador;
    float valor;

    Node grafo = NULL;
    char tipo_veiculo[TAM];
    float latitude, longitude, distancia;
    int id_inicio, id_fim;

    /*
    =====================================================================
        Processos de inicializacao
    =====================================================================
    */
    //Obter dados do ficheiro "veiculos.txt"
    veiculos = LerVeiculos();
    //Obter dados do ficheiro "clientes.txt"
    clientes = LerClientes();
    //Obter dados do ficheiro "aluguer.txt"
    alugueis = LerAlugueis();
    //Obter dados do ficheiro "vertices.txt e adjacencias.txt"
    LerVertices(&grafo);
    LerAdjacencias(grafo);

    /*
    =====================================================================
        Seccao para definir se é cliente ou gestor
    =====================================================================
    */
    while (ExisteCliente(clientes, opcao3) == 0)
    {
        printf("ID de utilizador: ");
        scanf("%d", &opcao3);
    }
    login = VerificaUtilizador(clientes, opcao3);

    // le dado dos ficheiros binários caso seja um cliente logado
    // Substitui os dados lidos dos ficheiros .txt para os .bin
    if (login != -1)
    {
        veiculos = LerVeiculosBin();
        clientes = LerClientesBin();
        alugueis = LerAlugueisBin();
    }

    /*
    =====================================================================
        Comandos do cliente/gestor
    =====================================================================
    */
    if (login == -1)
    {
        do
        {
            opcao = menu(opcao2, login, 0);
            
            if(opcao2 == 1)
            {
                switch(opcao)
            {
                // Inserir Veiculo
                case 1:
                        printf("\nCodigo: ");
                        scanf("%d", &id);
                        printf("Tipo: ");
                        scanf("%s", tipo);
                        printf("Bateria: ");
                        scanf("%f", &bateria);
                        printf("Autonomia: ");
                        scanf("%f", &autonomia);
                        printf("Geocode: ");
                        scanf("%s", geocode);

                        veiculos = InserirVeiculo(veiculos, id, tipo, bateria, autonomia, geocode);
                    break;

                // Listar Veículos
                case 2:
                        ListarVeiculos(veiculos);
                    break;

                // Remover Veículo
                case 3:
                        printf("\nCódigo: ");
                        scanf("%d",&opcao3);
                        veiculos = RemoverVeiculo(veiculos, opcao3);
                    break;

                // Editar Veículo
                case 4:
                        printf("\nCodigo: ");
                        scanf("%d", &id);
                        printf("Tipo: ");
                        scanf("%s", tipo);
                        printf("Bateria: ");
                        scanf("%f", &bateria);
                        printf("Autonomia: ");
                        scanf("%f", &autonomia);
                        printf("Geocode: ");
                        scanf("%s", geocode);

                        EditarVeiculo(veiculos, id, tipo, bateria, autonomia, geocode);
                    break;

                // Guardar Veículos em um ficheiro ".bin"
                case 5:
                        guardarVeiculosBin(veiculos);
                    break;

                // Ler Veiculos em um ficheiro ".bin"
                case 6:
                        veiculos = LerVeiculosBin();
                    break;
                
                // Listagem decrescente dos veículos por sua autonomia
                case 7:
                        DescrescenteVeiculos(veiculos);
                    break;
                
                // Listagem de veículos por seu geocódigo
                case 8:
                        printf("Geocode: ");
                        scanf("%s", geocode);

                        GeocodigoVeiculos(veiculos, geocode);
                    break;
            }

            }

            if(opcao2 == 2)
            {
                switch(opcao)
            {
                // Inserir Cliente
                case 1:
                        printf("\nCodigo: ");
                        scanf("%d", &id);
                        printf("Nome: ");
                        scanf("%s", nome);
                        printf("Saldo: ");
                        scanf("%f", &saldo);
                        printf("Morada: ");
                        scanf("%s", morada);
                        printf("Gestor: ");
                        scanf("%d", &gestor);

                        clientes = InserirCliente(clientes, id, nome, saldo, morada, gestor);
                    break;

                // Listar Clientes
                case 2:
                        ListarClientes(clientes);
                    break;

                // Remover Cliente
                case 3:
                        printf("\nCódigo: ");
                        scanf("%d",&opcao3);
                        clientes = RemoverCliente(clientes, opcao3);
                    break;

                // Editar Cliente
                case 4:
                        printf("\nCodigo: ");
                        scanf("%d", &id);
                        printf("Novo Nome: ");
                        scanf("%s", nome);
                        printf("Novo Saldo: ");
                        scanf("%f", &saldo);
                        printf("Nova Morada: ");
                        scanf("%s", morada);
                        printf("Novo Gestor: ");
                        scanf("%d", &gestor);

                        EditarCliente(clientes, id, nome, saldo, morada, gestor);
                    break;

                // Guardar Clientes em um ficheiro ".bin"
                case 5:
                        guardarClientesBin(clientes);
                    break;

                // Ler Clientes em um ficheiro ".bin"
                case 6:
                        clientes = LerClientesBin();
                    break;

            }

            }

            if(opcao2 == 3)
            {
                switch(opcao)
            {
                // Inserir Aluguer
                case 1:
                        printf("\nCodigo: ");
                        scanf("%d", &id);
                        printf("Dia, Mes, Ano de Inicio: ");
                        scanf("%d %d %d", &ini_dia, &ini_mes, &ini_ano);
                        printf("dia, Mes, Ano de Fim: ");
                        scanf("%d %d %d", &fim_dia, &fim_mes, &fim_ano);
                        printf("Valor: ");
                        scanf("%f", &valor);
                        printf("ID do veículo: ");
                        scanf("%d", &id_veiculos);
                        printf("ID do utilizador: ");
                        scanf("%d", &id_utilizador);

                        alugueis = InserirAluguer(alugueis, id, ini_dia, ini_mes, ini_ano, fim_dia, fim_mes, fim_ano, valor, id_veiculos, id_utilizador);
                    break;

                // Listar Alugueis
                case 2:
                        ListarAlugueis(alugueis);
                    break;

                // Remover Aluguer
                case 3:
                        printf("\nCódigo: ");
                        scanf("%d",&opcao3);
                        alugueis = removerAluguer(alugueis, opcao3);
                    break;

                // Editar Aluguer
                case 4:
                        printf("\nCodigo: ");
                        scanf("%d", &id);
                        printf("Dia, Mes, Ano de Inicio: ");
                        scanf("%d %d %d", &ini_dia, &ini_mes, &ini_ano);
                        printf("dia, Mes, Ano de Fim: ");
                        scanf("%d %d %d", &fim_dia, &fim_mes, &fim_ano);
                        printf("Valor: ");
                        scanf("%f", &valor);
                        printf("ID do veículo: ");
                        scanf("%d", &id_veiculos);
                        printf("ID do utilizador: ");
                        scanf("%d", &id_utilizador);

                        EditarAluguer(alugueis, id, ini_dia, ini_mes, ini_ano, fim_dia, fim_mes, fim_ano, valor, id_veiculos, id_utilizador);
                    break;

                // Guardar Alugueis em um ficheiro ".bin"
                case 5:
                        guardarAlugueisBin(alugueis);
                    break;

                // Ler Alugueis em um ficheiro ".bin"
                case 6:
                        alugueis = LerAlugueisBin();
                    break;
                case 7:
                        printf("\nCódigo: ");
                        scanf("%d",&opcao3);
                        VeiculoAlugueis(alugueis, opcao3);
                    break;
            }

            }

            if(opcao2 == 4)
            {
                switch(opcao)
            {
                // Guardar Grafo em binário
                case 1:
                        guardarVerticesBin(grafo);
                        guardarAdjacenciasBin(grafo);
                    break;
                // Ler Grafo em binário
                case 2:
                        grafo = NULL;
                        LerVertices(&grafo);
                        LerAdjacencias(grafo);
                    break;
                // Listar Grafo
                case 3:
                        ListarGrafos(grafo);
                    break;
                // Distancia Grafo/Veiculos
                case 4:
                        printf("\nLatitude: ");
                        scanf("%f", &latitude);
                        printf("\nLongitude: ");
                        scanf("%f", &longitude);
                        printf("\nDistancia Máxima: ");
                        scanf("%f", &distancia);
                        printf("\nTipo do veículo: ");
                        scanf("%s", tipo_veiculo);

                        printf("\n");
                        listarVeiculosRaio(grafo, veiculos, latitude, longitude, distancia, tipo_veiculo);
                    break;
                // Menor Caminho Grafo/Veiculos
                case 5:
                        printf("\nTipo do veículo: ");
                        scanf("%s", tipo_veiculo);
                        printf("\nID do vértice inicial: ");
                        scanf("%d", &id_inicio);
                        printf("\nID do vértice final: ");
                        scanf("%d", &id_fim);

                        menorCaminhoVeiculos(grafo, veiculos, tipo_veiculo, id_inicio, id_fim);
                    break;
            }

            }

            // Trocar entre menu veiculo(1), cliente(2) e aluguer(3)
            if(opcao == 9)
            {
                do
                {
                    printf("Opcao? (1=veiculos, 2=clientes, 3=alugueis, 4=grafo)\n");
                    scanf("%d",&opcao2);
                } while (opcao2 < 0 && opcao2 > 4);
            }
         
        } while (opcao!=0);
    }
    else
    {
        do
        {
             quantia = LerSaldo(clientes, login);
             opcao = menu(opcao2, login, quantia);

            switch(opcao)
            {
                // Depositar Valor na Quantia de um Cliente
                case 1:
                        printf("Valor: ");
                        scanf("%f",&saldo);
                        DepositarQuantia(clientes, login, saldo);
                        printf("\n");
                        guardarClientesBin(clientes);
                    break;
 
                // Inserir Aluguer de um Cliente
                case 2:
                        printf("\nCodigo: ");
                        scanf("%d", &id);
                        printf("Dia, Mes, Ano de Inicio: ");
                        scanf("%d %d %d", &ini_dia, &ini_mes, &ini_ano);
                        printf("dia, Mes, Ano de Fim: ");
                        scanf("%d %d %d", &fim_dia, &fim_mes, &fim_ano);
                        printf("Valor: ");
                        scanf("%f", &valor);
                        printf("ID do veículo: ");
                        scanf("%d", &id_veiculos);

                        if (valor <= quantia)
                        {
                            printf("Aluguer Inserido!\n");
                            RemoverQuantia(clientes, login, valor);
                            alugueis = InserirAluguer(alugueis, id, ini_dia, ini_mes, ini_ano, fim_dia, fim_mes, fim_ano, valor, id_veiculos, login);
                            guardarClientesBin(clientes);
                            guardarAlugueisBin(alugueis);
                        }
                    break;

                // Remover Aluguer de um Cliente
                case 3:
                        printf("\nCódigo: ");
                        scanf("%d",&opcao3);
                        alugueis = removerAluguerCliente(alugueis, opcao3, login);
                        guardarAlugueisBin(alugueis);
                    break;

                // Listar Veiculos de um Cliente
                case 4:
                        if (ListarAlugueisCliente(alugueis, login) == 0)
                            printf("Nenhum Veículo Encontrado!\n");
                        printf("\n"); 
                    break;
            }
        } while (opcao!=0);
    }

    // Liberar memória alocada
    free(clientes);
    free(veiculos);
    free(alugueis);
    LiberarGrafo(grafo);
 return(0);
}