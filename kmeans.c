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
// *********************************************************#include <stdio.h>
#include "kmeans.h" // Header file para funções relacionadas ao K-Means
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "imagem.h" // Header file para manipulação de imagens PGM

#define MAX_ITER 100 // Número máximo de iterações do K-Means
#define NIVEIS_CINZA 256 // Total de níveis de cinza possíveis em uma imagem PGM

// Função para calcular o histograma de uma imagem PGM
void calcularHistograma(PGM *pgm, int *histograma) {
    // Inicializa o histograma com zeros
    memset(histograma, 0, NIVEIS_CINZA * sizeof(int));
    
    // Itera sobre todos os pixels da imagem para calcular as ocorrências de cada nível de cinza
    for (int i = 0; i < pgm->largura * pgm->altura; i++) {
        histograma[pgm->imagem[i]]++;
    }
}

// Função para inicializar os centroides de forma distribuída ao longo do histograma
void inicializarCentroides(int *centroides, int k, int *histograma) {
    int valores[NIVEIS_CINZA], n = 0;

    // Coleta os níveis de cinza que estão presentes na imagem
    for (int i = 0; i < NIVEIS_CINZA; i++) {
        if (histograma[i] > 0) {
            valores[n++] = i;
        }
    }

    // Caso existam menos tons distintos do que o número de clusters \(k\)
    if (n < k) {
        fprintf(stderr, "Aviso: Menos tons distintos do que k. Ajustando...\n");
        for (int i = 0; i < k; i++) {
            centroides[i] = valores[i % n]; // Repete os valores disponíveis
        }
        return;
    }

    // Distribui os centroides uniformemente ao longo dos níveis de cinza
    for (int i = 0; i < k; i++) {
        centroides[i] = valores[(n * i) / k];
    }
}

// Função principal do algoritmo K-Means
void kmeans(PGM *pgm, int k, int *clusters) {
    // Alocação dinâmica para armazenar centroides, soma de valores e contagem de pixels por cluster
    int *centroides = (int *)malloc(k * sizeof(int));
    int *soma = (int *)malloc(k * sizeof(int));
    int *count = (int *)malloc(k * sizeof(int));

    // Verifica se a memória foi alocada com sucesso
    if (!centroides || !soma || !count) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        return;
    }

    // Calcula o histograma da imagem
    int histograma[NIVEIS_CINZA];
    calcularHistograma(pgm, histograma);

    // Inicializa os centroides com base no histograma
    inicializarCentroides(centroides, k, histograma);

    // Loop principal do K-Means (máximo de \(MAX_ITER\) iterações)
    for (int iter = 0; iter < MAX_ITER; iter++) {
        // Inicializa os acumuladores de soma e contagem para os clusters
        memset(soma, 0, k * sizeof(int));
        memset(count, 0, k * sizeof(int));

        // Salva os centroides antigos para verificar a convergência
        int centroides_antigos[k];
        memcpy(centroides_antigos, centroides, k * sizeof(int));

        // Atribui cada pixel ao cluster mais próximo
        for (int i = 0; i < pgm->largura * pgm->altura; i++) {
            int pixel = pgm->imagem[i];
            int cluster = 0;
            int min_dist = abs(pixel - centroides[0]); // Calcula a distância ao primeiro centroide

            // Calcula a distância do pixel a todos os centroides e encontra o mais próximo
            for (int c = 1; c < k; c++) {
                int dist = abs(pixel - centroides[c]);
                if (dist < min_dist) {
                    min_dist = dist;
                    cluster = c;
                }
            }

            clusters[i] = cluster; // Atribui o cluster ao pixel
            soma[cluster] += pixel; // Acumula o valor do pixel no cluster correspondente
            count[cluster]++; // Incrementa a contagem de pixels no cluster
        }

        // Atualiza os centroides com a média aritmética dos pixels atribuídos a cada cluster
        for (int c = 0; c < k; c++) {
            if (count[c] > 0) {
                centroides[c] = soma[c] / count[c];
            }
        }

        // Verifica se os centroides mudaram em relação à iteração anterior
        int convergiu = 1; // Assume que convergiu inicialmente
        for (int c = 0; c < k; c++) {
            if (centroides[c] != centroides_antigos[c]) {
                convergiu = 0; // Caso algum centroide tenha mudado, ainda não convergiu
                break;
            }
        }

        // Interrompe o loop se o algoritmo convergiu
        if (convergiu) break;
    }

    // Atualiza os pixels da imagem para os valores exatos dos centroides
    for (int i = 0; i < pgm->largura * pgm->altura; i++) {
        pgm->imagem[i] = centroides[clusters[i]];
    }

    // Libera a memória alocada dinamicamente
    free(centroides);
    free(soma);
    free(count);
}