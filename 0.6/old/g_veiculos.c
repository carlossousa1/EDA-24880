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
int existeVeiculos(Veiculos array_veiculos[], int quant_veiculos, int valor)
{
    int i;
    for(i=0;i<quant_veiculos;i++)
    {
        if (array_veiculos[i].id == valor) return(i);
    }
    return(-1);
}

// Guardar estrutura veículos na primeira celula livre da base de dados
int adicionarVeiculos(Veiculos array_veiculos[], int posicao, Veiculos a)  
{   
    if ((posicao>=0) && (posicao<TAM) && (existeVeiculos(array_veiculos,posicao,a.id)==-1))
    {
        array_veiculos[posicao] = a;
        return(1);
    }
    else return(0);
}

// Inserção de um novo registo
Veiculos inserirVeiculos()
{
    Veiculos a;
    int cont;
		
	do
	{
		cont=0;
		printf("ID?\n"); cont += scanf("%d",&a.id); while ((getchar()) != '\n');
		printf("Tipo?\n"); cont += scanf("%[^\n]",a.tipo); while ((getchar()) != '\n');
		printf("Bateria?\n"); cont += scanf("%f",&a.bateria); while ((getchar()) != '\n');
		printf("Autonomia?\n"); cont += scanf("%f",&a.autonomia); while ((getchar()) != '\n');
		printf("Geocode?\n"); cont += scanf("%[^\n]",a.geocode); while ((getchar()) != '\n');
			
		if (cont==5) return(a); else printf("Dados inválidos!\n\n");
	}
	while(cont!=5);
}

// Listar veículos
Veiculos listarVeiculos(Veiculos array_veiculos[], int quant_veiculos)
{
    int i=0;

    while(i<quant_veiculos)
    {
        printf("%d %s %f %f %s\n", array_veiculos[i].id, array_veiculos[i].tipo, array_veiculos[i].bateria, array_veiculos[i].autonomia, array_veiculos[i].geocode);
        i++;
    }
    
    Veiculos a;
    int res;
    return(a);
}

// Remover uma linha da base de dados veículos
int removerVeiculos(Veiculos array_veiculos[], int quant_veiculos, int b)
{
    if(b>0 && b<=quant_veiculos)
    {
        for(int i=b-1; i<quant_veiculos-1; i++)
        {
            array_veiculos[i] = array_veiculos[i + 1];
        }
        return(0);
    }
    else return(-1);

}

// Alterar um linha da base de dados veículos
int editarVeiculos(Veiculos array_veiculos[], int quant_veiculos, int b)
{   
    if(b>0 && b<=quant_veiculos)
    {
        for(int i=0; i<quant_veiculos; i++)
        {
            if(b == (i+1))
            array_veiculos[i] = inserirVeiculos();
        }
        return(0);
    }
    else return(-1);
}

// Listar veiculos por autonomia de forma decrescente
int decrescenteVeiculos(Veiculos array_veiculos[], int quant_veiculos)
{
    Veiculos b[quant_veiculos];
    float a;

    // definir na lista "b" os dados de "array_veiculos";
    for (int z=0; z<quant_veiculos; ++z)
    {
        b[z] = array_veiculos[z];
    }
    
    for (int i=0; i<quant_veiculos; ++i) 
    {
        for (int j=i+1; j<quant_veiculos; ++j) 
        {
            if (b[j].autonomia > b[i].autonomia) 
            {
                a = b[i].autonomia;
                b[i].autonomia = b[j].autonomia;
                b[j].autonomia = a;
            }
        }
    }
    
    for(int i=0; i<quant_veiculos; i++)
    {
        printf("%d %s %f %f %s\n", b[i].id, b[i].tipo, b[i].bateria, b[i].autonomia, b[i].geocode);
    }
    return(0);
}

// Listar veiculos por determinado geocodigo
int geocodigoVeiculos(Veiculos array_veiculos[], int quant_veiculos, char b[])
{   
    int c=0;
    for(int i=0; i<quant_veiculos; i++)
    {
        if(strcmp(b, array_veiculos[i].geocode) == 0)
        {
            printf("%d %s %f %f %s\n", array_veiculos[i].id, array_veiculos[i].tipo, array_veiculos[i].bateria, array_veiculos[i].autonomia, array_veiculos[i].geocode);
            c++;
        }
    }
    return(c);
}

/*
    Gestao de ficheiros
*/

// Ler lista de veiculos no ficheiro "veiculos.txt"
int lerVeiculos(Veiculos array_veiculos[])
{   
    FILE* fp;
    int i=0;
    fp = fopen("veiculos.txt","rt");  // rt = read text

    if (fp != NULL)
    {
        do
        {
            
            fscanf(fp,"%d;%[^;];%f;%f;%[^\n]\n", &array_veiculos[i].id, array_veiculos[i].tipo, &array_veiculos[i].bateria, &array_veiculos[i].autonomia, array_veiculos[i].geocode);
            i++;
        } while(!feof(fp));  // end of file  feof ==> >0
        
        fclose(fp);
        return(i);
    }
    else return(-1);
}

// Armazenar informacao dos veiculos em um ficheiro .bin
int guardarVeiculosBin(Veiculos array_veiculos[], int quant_veiculos)
{
    FILE* fp;
    int i=0;
    fp = fopen("veiculos.bin","wb");  // wt = write binary

    if (fp != NULL)
    {
        fwrite(array_veiculos, sizeof(Veiculos), quant_veiculos, fp);
        fclose(fp);

        return(1);
    }
    else return(0);
}

// Ler lista de veiculos no ficheiro "veiculos.bin"
int lerVeiculosBin(Veiculos array_veiculos[])
{   
    FILE* fp;
    int i=0;
    fp = fopen("veiculos.bin","rb");  // rb = read binary

    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fread(&array_veiculos[i], sizeof(Veiculos), 1, fp);
            i++;
        }

        fclose(fp);
        return(i-1);
    }
    else return(-1);
}