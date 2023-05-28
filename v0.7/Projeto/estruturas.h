/**
 * @author Carlos Sousa (a24880@alunos.ipca.pt)
 * @brief Estrutuacao dos dados do trabalho
 * @version 0.7
 * @date 2023-05-18
 */

/*
    Header responsável por definir as variáveis tipo struct para o programa.
*/

typedef struct registo_clientes
{
    int id;
    char nome[TAM];
    float saldo;
    char morada[TAM];
    int gestor; // 1=gestor, resto=cliente

    struct registo_clientes* seguinte;
} Clientes;

typedef struct registo_veiculos
{
    int id;
    char tipo[TAM];
    float bateria;
    float autonomia;
    char geocode[TAM];

    struct registo_veiculos* seguinte;
} Veiculos;

typedef struct registo_alugueis
{
    int id;
    int ini_dia; // (data inicio: dias)
    int ini_mes; // (data inicio: mes)
    int ini_ano; // (data inicio: ano)
    int fim_dia; // (data fim: dias)
    int fim_mes; // (data fim: mes)
    int fim_ano; // (data fim: ano)
    float valor; // (valor pago em euros)
    int id_veiculos; // (id do veiculo ligado ao aluguer)
    int id_utilizador; // (id do utilizador ligado ao aluguer)

    struct registo_alugueis* seguinte;
} Alugueis;