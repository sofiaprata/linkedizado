#include "processamento.h"
#include "imagem.h"
#include "kmeans.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void criarPasta(const char *pasta) {
    struct stat st;
    if (stat(pasta, &st) == -1) {
        mkdir(pasta);
    }
}

void processarImagens(const char *pasta_origem, const char *pasta_destino) {
    DIR *dir = opendir(pasta_origem);
    if (!dir) {
        printf("Erro ao abrir a pasta: %s\n", pasta_origem);
        return;
    }

    criarPasta(pasta_destino);
    struct dirent *entrada;
    int imagens_processadas = 0;

    while ((entrada = readdir(dir)) != NULL) {
        if (strstr(entrada->d_name, ".pgm")) {
            char caminho[256];
            snprintf(caminho, sizeof(caminho), "%s/%s", pasta_origem, entrada->d_name);

            PGM pgm = lerPGM(caminho);
            if (!pgm.imagem) {
                printf("Erro ao carregar imagem: %s\n", caminho);
                continue;
            }

            int *clusters = malloc(pgm.largura * pgm.altura * sizeof(int));
            if (!clusters) {
                printf("Erro ao alocar memória para clusters\n");
                liberarImagem(&pgm);
                continue;
            }

            int k = 10;
            kmeans(&pgm, k, clusters);
            salvarImagem(&pgm, k, pasta_destino, entrada->d_name);

            free(clusters);
            liberarImagem(&pgm);
            imagens_processadas++;
        }
    }

    closedir(dir);
    printf("Total de imagens processadas: %d\n", imagens_processadas);
}
