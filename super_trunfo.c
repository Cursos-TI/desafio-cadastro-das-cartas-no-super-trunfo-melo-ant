#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>


struct cartaTrunfo {
    char estado[3];
    int cod;
    char cidade[34];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidade;
    float pibPerCapita;
};

struct baralhoTrunfo {
    struct cartaTrunfo cartas[32];
    int qtdCartas;
};

int contarCartasEstado(char sigla[2], struct baralhoTrunfo baralho){
    int qtdb = 0;
    if (baralho.qtdCartas > 0){
        for(int i = 0;i < baralho.qtdCartas;i++){
            if (strcmp(sigla, baralho.cartas[i].estado) == 0){
                qtdb = qtdb + 1;
            };

        };
    return qtdb;
    };
    return 0;
};

struct baralhoTrunfo criarCarta(struct baralhoTrunfo baralho, int qtd) {
    for (int i = 0; i < qtd; i++) {
        int next;
        next = 0;
        while (next == 0){
            int cod;
            char estado[3];
            printf("===================================================\n");
            printf("Insira a sigla do estado (Exp : PB, AM, MA e etc)..... ");
            if(scanf("%2s", estado) != 1){ //tratamento de erro do scanf
                printf("Erro ao ler o estado\n");
                return baralho;
            }
            
            //function to seach the greatest number, and return if the next number are disponible
            cod = contarCartasEstado(estado,baralho);
            printf("[!]( qtd de cartas com esse estado : %d )\n",cod);
            if (cod + 1 > 4){
                next = 0;
                printf("Já existem 4 cartas com o mesmo estado\n");
            }else{
                next = 1;
                baralho.cartas[i].cod = cod + 1;
                strcpy(baralho.cartas[i].estado,estado);
            }
        }


        printf("Insira o nome da cidade..... ");
        if(scanf("%33s", baralho.cartas[i].cidade) != 1){
            printf("Erro ao ler a cidade\n");
            return baralho;
        }

        printf("Insira a populacao..... ");
        if(scanf("%d", &baralho.cartas[i].populacao) != 1){
            printf("Erro ao ler a populacao\n");
            return baralho;
        }

        printf("Insira a area da cidade(em km²)..... ");
        if(scanf("%f", &baralho.cartas[i].area) != 1){
            printf("Erro ao ler a area\n");
            return baralho;
        }

        printf("Insira o PIB da cidade(em bilhões)..... ");
        if(scanf("%f", &baralho.cartas[i].pib) != 1){
            printf("Erro ao ler o PIB\n");
            return baralho;
        }

        printf("Insira a quantidade de pontos turisticos..... ");
        if(scanf("%d", &baralho.cartas[i].pontosTuristicos) != 1){
            printf("Erro ao ler os pontos turisticos\n");
            return baralho;
        }
        


        printf("===================================================\n");
        //calcular pib per capita e densidade
        baralho.cartas[i].densidade = baralho.cartas[i].populacao / baralho.cartas[i].area;
        baralho.cartas[i].pibPerCapita = baralho.cartas[i].pib /baralho.cartas[i].populacao;
        baralho.qtdCartas++;
    }
    return baralho;
}



void mostrarCarta(struct cartaTrunfo carta) {
    printf("===================================================\n");
    printf("Codigo : %d\n", carta.cod);
    printf("Estado : %s\n", carta.estado);
    printf("Cidade : %s\n", carta.cidade);
    printf("Populacao : %d\n", carta.populacao);
    printf("Pontos Turisticos : %d\n", carta.pontosTuristicos);
    printf("Area : %.2f km²\n", carta.area);
    printf("PIB : %.2f bilhões de reais \n", carta.pib);
    printf("Densidade populacional : %.2f hab/km²\n",carta.densidade);
    printf("PIB per capita %.2f PIB/hab \n",carta.pibPerCapita);
    printf("===================================================\n");
}

int main(int argc, char const *argv[]) {
    // Sugestão: Defina variáveis separadas para cada atributo da cidade.
    // Exemplos de atributos: código da cidade, nome, população, área, PIB, número de pontos turísticos.
    
    struct baralhoTrunfo baralhoA;
    baralhoA.qtdCartas = 0;

    int qtdA;
    printf("Digite quantas cartas voce quer criar? ");
    if(scanf("%d", &qtdA) != 1){
        printf("Erro ao ler a quantidade de cartas\n");
        return 1;
    }

    // Cadastro das Cartas:
    // Sugestão: Utilize a função scanf para capturar as entradas do usuário para cada atributo.
    // Solicite ao usuário que insira as informações de cada cidade, como o código, nome, população, área, etc.
    
    baralhoA = criarCarta(baralhoA, qtdA);

    // Exibição dos Dados das Cartas:
    // Sugestão: Utilize a função printf para exibir as informações das cartas cadastradas de forma clara e organizada.
    // Exiba os valores inseridos para cada atributo da cidade, um por linha.

    if (baralhoA.qtdCartas > 0){
        for (int i = 0;i<baralhoA.qtdCartas;i++){
            mostrarCarta(baralhoA.cartas[i]);
        };
    
    };
    

    printf("Value of errno: %d\n", errno);
    return 0;
};