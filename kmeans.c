// *********************************************************
// * Aluno:  Sofia Freitas Batista Prata                   *
// * Matrícula: 20241045050448                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
// * Aluno: Pedro Felipe Monteiro Ventura                  *
// * Matrícula: 20241045050294                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
// * Aluno: Miguel Antonio Florencio Felix                 *
// * Matrícula: 2024104505   0480                              *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
#include <stdio.h>      // Biblioteca para entrada e saída de dados
#include "kmeans.h"     // Cabeçalho do algoritmo K-means
#include <stdlib.h>     // Biblioteca para alocação de memória e geração de números aleatórios
#include <string.h>     // Biblioteca para manipulação de memória (memset, memcpy)
#include <math.h>       // Biblioteca matemática (usada para a função abs)
#include <time.h>       // Biblioteca para manipulação de tempo (usada na inicialização do rand)
#include "imagem.h"     // Cabeçalho para manipulação de imagens no formato PGM

#define MAX_ITER 100        // Número máximo de iterações para o algoritmo K-means
#define NIVEIS_CINZA 256    // Número total de níveis de cinza possíveis (0 a 255)

/**
 * Calcula o histograma da imagem PGM, contando a frequência de cada nível de cinza.
 * 
 * @param pgm Ponteiro para a estrutura da imagem PGM.
 * @param histograma Vetor que armazenará a contagem de cada nível de cinza.
 */
void calcularHistograma(PGM *pgm, int *histograma) {
    memset(histograma, 0, NIVEIS_CINZA * sizeof(int));  // Inicializa o histograma com zeros

    // Percorre todos os pixels da imagem e contabiliza os níveis de cinza
    for (int i = 0; i < pgm->largura * pgm->altura; i++) {
        histograma[pgm->imagem[i]]++;  // Incrementa a contagem para o nível de cinza correspondente
    }
}

/**
 * Seleciona os centroides iniciais para o K-means com base nos níveis de cinza mais frequentes.
 * Se não houver centroides suficientes, são escolhidos valores aleatórios.
 * 
 * @param centroides Vetor onde os centroides serão armazenados.
 * @param k Número de clusters.
 * @param histograma Vetor contendo a contagem de cada nível de cinza.
 */
void escolherCentroides(int *centroides, int k, int *histograma) {
    int indicesEscolhidos = 0;

    // Percorre os níveis de cinza e escolhe os mais frequentes como centroides iniciais
    for (int i = 0; i < NIVEIS_CINZA && indicesEscolhidos < k; i++) {
        if (histograma[i] > 0) {
            centroides[indicesEscolhidos++] = i;
        }
    }

    // Caso não tenha encontrado k centroides distintos, preenche os restantes com valores aleatórios
    srand(time(NULL));  // Inicializa a semente para geração de números aleatórios
    while (indicesEscolhidos < k) {
        centroides[indicesEscolhidos++] = rand() % NIVEIS_CINZA;
    }
}

/**
 * Executa o algoritmo K-means para segmentação de uma imagem PGM.
 * 
 * @param pgm Ponteiro para a estrutura da imagem PGM.
 * @param k Número de clusters desejado.
 * @param clusters Vetor que armazenará a atribuição de cada pixel ao seu cluster correspondente.
 */
void kmeans(PGM *pgm, int k, int *clusters) {
    // Aloca memória para armazenar os centroides, a soma dos pixels e a contagem de pixels em cada cluster
    int *centroides = (int *)malloc(k * sizeof(int));
    int *soma = (int *)malloc(k * sizeof(int));
    int *count = (int *)malloc(k * sizeof(int));

    // Verifica se a alocação de memória foi bem-sucedida
    if (centroides == NULL || soma == NULL || count == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    // Calcula o histograma da imagem para auxiliar na escolha dos centroides iniciais
    int histograma[NIVEIS_CINZA];
    calcularHistograma(pgm, histograma);

    // Inicializa os centroides com os níveis de cinza mais frequentes
    escolherCentroides(centroides, k, histograma);

    // Loop principal do algoritmo K-means (até atingir o número máximo de iterações)
    for (int iter = 0; iter < MAX_ITER; iter++) {
        memset(soma, 0, k * sizeof(int));   // Zera o vetor soma
        memset(count, 0, k * sizeof(int));  // Zera o vetor count

        // Aloca memória para armazenar os centroides da iteração anterior
        int *centroides_antigos = (int *)malloc(k * sizeof(int));
        if (centroides_antigos == NULL) {
            printf("Erro ao alocar memória para centroides antigos.\n");
            free(centroides);
            free(soma);
            free(count);
            return;
        }
        memcpy(centroides_antigos, centroides, k * sizeof(int)); // Salva os centroides antigos para comparação

        // Atribui cada pixel ao cluster cujo centroide está mais próximo
        for (int i = 0; i < pgm->largura * pgm->altura; i++) {
            int pixel = pgm->imagem[i];
            int cluster = 0;
            int min_dist = abs(pixel - centroides[0]);  // Calcula a distância inicial

            // Encontra o centroide mais próximo para o pixel
            for (int c = 1; c < k; c++) {
                int dist = abs(pixel - centroides[c]);
                if (dist < min_dist) {
                    min_dist = dist;
                    cluster = c;
                }
            }

            clusters[i] = cluster;  // Atribui o pixel ao cluster correspondente
            soma[cluster] += pixel; // Soma o valor do pixel ao cluster correspondente
            count[cluster]++;       // Incrementa a contagem de pixels do cluster
        }

        // Atualiza os centroides como a média dos pixels atribuídos a cada cluster
        for (int c = 0; c < k; c++) {
            centroides[c] = count[c] ? soma[c] / count[c] : centroides[c];
        }

        // Verifica se os centroides mudaram desde a última iteração
        int centroides_iguais = 1;  // Flag para indicar se os centroides permaneceram iguais
        for (int c = 0; c < k; c++) {
            if (centroides[c] != centroides_antigos[c]) {
                centroides_iguais = 0;
                break;
            }
        }

        free(centroides_antigos); // Libera a memória dos centroides antigos

        // Se os centroides não mudaram, o algoritmo convergiu e pode parar
        if (centroides_iguais) {
            break;
        }
    }

    // Libera a memória alocada para os centroides, soma e contagem de pixels
    free(centroides);
    free(soma);
    free(count);
}

