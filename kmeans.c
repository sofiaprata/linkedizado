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
#include <stdio.h>      // Biblioteca padrão para entrada e saída de dados.
#include "kmeans.h"     // Arquivo de cabeçalho com a definição da função k-means.
#include <stdlib.h>     // Biblioteca para alocação de memória e funções utilitárias.
#include <string.h>     // Biblioteca para manipulação de strings e memória.
#include <math.h>       // Biblioteca para operações matemáticas (exemplo: abs()).
#include <time.h>       // Biblioteca para manipulação de tempo (usada para seed do rand()).
#include "imagem.h"     // Arquivo de cabeçalho que contém a estrutura PGM e funções relacionadas.

#define MAX_ITER 100    // Define o número máximo de iterações para o algoritmo k-means.

/**
 * Função que aplica o algoritmo k-means para clusterizar os pixels de uma imagem PGM.
 * @param pgm Estrutura contendo a imagem a ser clusterizada.
 * @param k Número de clusters a serem formados.
 * @param clusters Vetor que armazenará o cluster atribuído a cada pixel.
 */
void kmeans(PGM *pgm, int k, int *clusters) {
    // Alocação dinâmica de memória para os centroides e variáveis auxiliares.
    int *centroides = (int *)malloc(k * sizeof(int)); // Vetor que armazena os centroides atuais.
    int *soma = (int *)malloc(k * sizeof(int));       // Vetor para somar os valores dos pixels atribuídos a cada cluster.
    int *count = (int *)malloc(k * sizeof(int));      // Vetor para contar quantos pixels pertencem a cada cluster.

    // Verifica se a alocação de memória foi bem-sucedida.
    if (centroides == NULL || soma == NULL || count == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com base no tempo atual.

    // Escolhe os centroides iniciais aleatoriamente a partir dos pixels da imagem.
    for (int i = 0; i < k; i++) {
        centroides[i] = pgm->imagem[rand() % (pgm->largura * pgm->altura)];
    }
    
    // Loop principal do k-means, com no máximo MAX_ITER iterações.
    for (int iter = 0; iter < MAX_ITER; iter++) {
        memset(soma, 0, k * sizeof(int));   // Zera os valores do vetor soma.
        memset(count, 0, k * sizeof(int));  // Zera os valores do vetor count.

        // Aloca memória para armazenar os centroides antigos para comparação.
        int *centroides_antigos = (int *)malloc(k * sizeof(int));
        if (centroides_antigos == NULL) {
            printf("Erro ao alocar memória para centroides antigos.\n");
            free(centroides);
            free(soma);
            free(count);
            return;
        }

        // Copia os centroides atuais para os antigos antes de atualizá-los.
        memcpy(centroides_antigos, centroides, k * sizeof(int));

        // Etapa de atribuição: associa cada pixel ao cluster mais próximo.
        for (int i = 0; i < pgm->largura * pgm->altura; i++) {
            int pixel = pgm->imagem[i]; // Obtém o valor do pixel atual.
            int cluster = 0;            // Índice do cluster mais próximo.
            int min_dist = abs(pixel - centroides[0]); // Calcula a distância ao primeiro centroide.

            // Percorre os k clusters para encontrar o centroide mais próximo.
            for (int c = 1; c < k; c++) {
                int dist = abs(pixel - centroides[c]); // Calcula a distância do pixel ao centroide c.
                if (dist < min_dist) {  // Se a distância for menor que a mínima encontrada até agora:
                    min_dist = dist;    // Atualiza a menor distância.
                    cluster = c;        // Atualiza o índice do cluster correspondente.
                }
            }
            clusters[i] = cluster; // Atribui o cluster ao pixel atual.
            soma[cluster] += pixel; // Acumula o valor do pixel no somatório do cluster correspondente.
            count[cluster]++;       // Incrementa a contagem de pixels no cluster correspondente.
        }

        // Etapa de atualização: recalcula os centroides com base na média dos pixels atribuídos.
        for (int c = 0; c < k; c++) {
            // Se houver pixels no cluster, recalcula o centroide como a média dos pixels atribuídos a ele.
            centroides[c] = count[c] ? soma[c] / count[c] : centroides[c];
        }

        // Verificação de convergência: se os centroides não mudaram, finaliza o loop.
        int centroides_iguais = 1;
        for (int c = 0; c < k; c++) {
            if (centroides[c] != centroides_antigos[c]) { // Se ao menos um centroide mudou:
                centroides_iguais = 0; // Indica que ainda não convergiu.
                break;
            }
        }

        free(centroides_antigos); // Libera a memória dos centroides antigos.

        // Se os centroides permaneceram inalterados, o algoritmo convergiu e podemos sair do loop.
        if (centroides_iguais) {
            break;
        }
    }

    // Libera a memória das variáveis alocadas dinamicamente.
    free(centroides);
    free(soma);
    free(count);
}
