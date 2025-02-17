#include "kmeans.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "imagem.h"

#define MAX_ITER 100

void kmeans(PGM *pgm, int k, int *clusters) {
    int centroides[k];
    int soma[k], count[k];
    
    srand(time(NULL));
    
    // Inicializa os centroides com valores aleatórios dos pixels da imagem
    for (int i = 0; i < k; i++) {
        centroides[i] = pgm->imagem[rand() % (pgm->largura * pgm->altura)];
    }
    
    for (int iter = 0; iter < MAX_ITER; iter++) {
        memset(soma, 0, k * sizeof(int));
        memset(count, 0, k * sizeof(int));

        // Armazenar os centroides antigos
        int centroides_antigos[k];
        memcpy(centroides_antigos, centroides, k * sizeof(int));

        // Calculando a atribuição dos clusters
        for (int i = 0; i < pgm->largura * pgm->altura; i++) {
            int pixel = pgm->imagem[i];
            int cluster = 0, min_dist = abs(pixel - centroides[0]);

            for (int c = 1; c < k; c++) {
                int dist = abs(pixel - centroides[c]);
                if (dist < min_dist) {
                    min_dist = dist;
                    cluster = c;
                }
            }
            clusters[i] = cluster;
            soma[cluster] += pixel;
            count[cluster]++;
        }

        // Atualizando os centroides
        for (int c = 0; c < k; c++) {
            centroides[c] = count[c] ? soma[c] / count[c] : centroides[c];
        }

        // Verificar se os centroides mudaram. Se não, quebrar o loop.
        int centroides_iguais = 1;
        for (int c = 0; c < k; c++) {
            if (centroides[c] != centroides_antigos[c]) {
                centroides_iguais = 0;
                break;
            }
        }

        // Se os centroides não mudaram, sai do loop
        if (centroides_iguais) {
            break;
        }
    }
}
