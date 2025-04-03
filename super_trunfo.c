#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>


struct cartaTrunfo {
    char estado[3];
    int cod;
    char cidade[34];
    unsigned long int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidade;
    float pibPerCapita;
    float superPoder; // area + pib + pontosTuristicos + pibPerCapita + populacao + 1/densidade
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

void to_upper(char *str) {
    while (*str) {
        *str = toupper((unsigned char) *str);
        str++;
    }
}

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
            
            char estadoUpper[3];
            to_upper(estado);
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
        getchar();
        char cidade_temp[34];

        printf("Insira o nome da cidade..... ");
        if (fgets(cidade_temp,33,stdin) != NULL){
            cidade_temp[strcspn(cidade_temp, "\n")] = '\0';
            if (strlen(cidade_temp) > 33) {
                printf("Erro: Cidade excede o tamanho máximo de 33 caracteres.\n");
                return baralho; // Retorna o baralho sem modificações
            }
    
            // Copiar a cidade para o baralho e converter para maiúsculas
            strcpy(baralho.cartas[i].cidade, cidade_temp);
            to_upper(baralho.cartas[i].cidade);
        }else{
            printf("Erro ao ler cidade\n");
            return baralho;
        }
        fflush(stdin);

        printf("Insira a populacao..... ");
        if(scanf("%d", &baralho.cartas[i].populacao) != 1){
            printf("Erro ao ler a populacao\n");
            return baralho;
        }
        fflush(stdin);
        printf("Insira a area da cidade(em km²)..... ");
        if(scanf("%f", &baralho.cartas[i].area) != 1){
            printf("Erro ao ler a area\n");
            return baralho;
        }
        fflush(stdin);
        printf("Insira o PIB da cidade..... ");
        if(scanf("%f", &baralho.cartas[i].pib) != 1){
            printf("Erro ao ler o PIB\n");
            return baralho;
        }
        fflush(stdin);
        printf("Insira a quantidade de pontos turisticos..... ");
        if(scanf("%d", &baralho.cartas[i].pontosTuristicos) != 1){
            printf("Erro ao ler os pontos turisticos\n");
            return baralho;
        }  
        fflush(stdin);
        
        printf("===================================================\n");
        //calcular pib per capita e densidade
        baralho.cartas[i].densidade = (float)baralho.cartas[i].populacao / baralho.cartas[i].area;
        baralho.cartas[i].pibPerCapita = (baralho.cartas[i].pib) /(float)baralho.cartas[i].populacao;

        //canculando super-poder
        baralho.cartas[i].superPoder = baralho.cartas[i].populacao + baralho.cartas[i].area + baralho.cartas[i].pib + baralho.cartas[i].pontosTuristicos + baralho.cartas[i].pibPerCapita + (1/baralho.cartas[i].densidade);


        baralho.qtdCartas++;
    }
    return baralho;
}



void mostrarCarta(struct cartaTrunfo carta) {
    printf("===================================================\n");
    printf("SUEPER PODER : %d\n", carta.superPoder);
    printf("===================================================\n");
    printf("Codigo : %d\n", carta.cod);
    printf("Estado : %s\n", carta.estado);
    printf("Cidade : %s\n", carta.cidade);
    printf("Populacao : %d\n", carta.populacao);
    printf("Pontos Turisticos : %d\n", carta.pontosTuristicos);
    printf("Area : %.2f km2\n", carta.area);
    printf("PIB : R$ %.2f \n", carta.pib);
    printf("Densidade populacional : %.2f hab/km2\n",carta.densidade);
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
    if(qtdA > 32){
        printf("Erro, quantidade de cartas supera a capacidade do baralho(32)");
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