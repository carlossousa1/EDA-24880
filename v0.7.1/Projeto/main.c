/**
 * @author Carlos Sousa (a24880@alunos.ipca.pt)
 * @brief Estrutuacao dos dados do trabalho
 * @version 0.7
 * @date 2023-05-18
 */

#include <stdio.h>
#include "includes.h"

int menu(int grupo)
{
    int opcao;
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
    printf("9 Trocar\n");
    printf("0 Sair\n");
    printf("Opcao: ");
    scanf("%d",&opcao);
    return(opcao);
}

int main()
{
    int opcao, opcao2=2, opcao3;
    
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
        
    /*
    =====================================================================
        Comandos do cliente/gestor
    =====================================================================
    */
        do
        {
            opcao = menu(opcao2);
            
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

            // Trocar entre menu veiculo(1), cliente(2) e aluguer(3)
            if(opcao == 9)
            {
                do
                {
                    printf("Opcao? (1=veiculos, 2=clientes, 3=alugueis)\n");
                    scanf("%d",&opcao2);
                } while (opcao2 < 0 && opcao2 > 3);
            }
         
        } while (opcao!=0);
    //}

 return(0);
}