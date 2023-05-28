/**
 * @author Carlos Sousa (a24880@alunos.ipca.pt)
 * @brief Estrutuacao dos dados do trabalho
 * @version 0.8
 * @date 2023-05-25
 */
/*
    AVISO!
    Este ficheiro contém as funcoes de todos ficheiros com "g" na frente
*/
#include "estruturas.h"

/*
    Funcoes do ficheiro clientes.c
*/
int ExisteCliente(Clientes* Inicio, int id);
Clientes* InserirCliente(Clientes * Inicio, int id, char nome[], float saldo, char morada[], int gestor);
void ListarClientes(Clientes* Inicio);
Clientes* RemoverCliente(Clientes* Inicio, int id);
Clientes* EditarCliente(Clientes* Inicio, int id, char nome[40], float saldo, char morada[40], int gestor);
int QuantClientes(Clientes* Inicio);

Clientes* LerClientes();
Clientes* LerClientesBin();
int guardarClientesBin(Clientes* Inicio);

/*
    Funcoes do ficheiro veiculos.c
*/

int ExisteVeiculo(Veiculos* Inicio, int id);
Veiculos* InserirVeiculo(Veiculos* Inicio, int id, char tipo[], float bateria, float autonomia, char geocode[]);
void ListarVeiculos(Veiculos* Inicio);
Veiculos* RemoverVeiculo(Veiculos* Inicio, int id);
Veiculos* EditarVeiculo(Veiculos* Inicio, int id, char tipo[], float bateria, float autonomia, char geocode[]);
int QuantVeiculos(Veiculos* Inicio);

void DescrescenteVeiculos(Veiculos* Inicio);
void GeocodigoVeiculos(Veiculos* Inicio, char geocode[]);

Veiculos* LerVeiculos();
Veiculos* LerVeiculosBin();
int guardarVeiculosBin(Veiculos* Inicio);


/*
    Funcoes do ficheiro aluguer.c
*/

int ExisteAluguer(Alugueis* Inicio, int id);
Alugueis* InserirAluguer(Alugueis* Inicio, int id, int ini_dia, int ini_mes, int ini_ano, int fim_dia, int fim_mes, int fim_ano, float valor, int id_veiculos, int id_utilizador);
void ListarAlugueis(Alugueis* Inicio);
Alugueis* removerAluguer(Alugueis* Inicio, int id);
Alugueis* EditarAluguer(Alugueis* Inicio, int id, int ini_dia, int ini_mes, int ini_ano, int fim_dia, int fim_mes, int fim_ano, float valor, int id_veiculos, int id_utilizador);
int QuantAlugueis(Alugueis* Inicio);

int VeiculoAlugueis(Alugueis* Inicio, int id_veiculos);

Alugueis* LerAlugueis();
Alugueis* LerAlugueisBin();
int guardarAlugueisBin(Alugueis* Inicio);

/*
    Funcoes do ficheiro grafos.c
*/

Node InserirNode(int ID, char* Cidade, float Latitude, float Longitude);
void InserirAdjacente(Node node, Node adjacente, int peso);
Adjacente CriarAdjacente(Node PtDestino, int peso);
void ListarGrafos(Node grafo);
void LiberarGrafo(Node grafo);
void listarVeiculosRaio(struct registo_node* grafo, Veiculos* Inicio, float clienteLat, float clienteLon, float raio, char tipoVeiculo[]);
void menorCaminhoVeiculos(Node grafo, Veiculos* listaVeiculos, char* tipoVeiculo, int origem, int destino);

void LerVertices(Node* grafo);
void LerVerticesBin(Node* grafo);
void LerAdjacencias(Node grafo);
void LerAdjacenciasBin(Node grafo);
void guardarVerticesBin(Node grafo);
void guardarAdjacenciasBin(Node grafo);

/*
    Funcoes do ficheiro utilizador.c
*/

int VerificaUtilizador(Clientes* cliente, int id);
int LerSaldo(Clientes* Inicio, int id);
Clientes* DepositarQuantia(Clientes* Inicio, int id, float saldo);
Clientes* RemoverQuantia(Clientes* Inicio, int id, float saldo);
int ListarAlugueisCliente(Alugueis* Inicio, int id);
Alugueis* removerAluguerCliente(Alugueis* Inicio, int id, int id_utilizador);