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
// * Matrícula: 2024104505  0480                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
#include "processamento.h"
#include "imagem.h"
#include "kmeans.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


void processarImagens(const char *pasta_origem, const char *pasta_destino) {
    DIR *dir = opendir(pasta_origem);
    if (!dir) {
        printf("Erro ao abrir a pasta: %s\n", pasta_origem);
        return;
    }

    struct dirent *entrada;
    int imagens_processadas = 0;

    while ((entrada = readdir(dir)) != NULL) {
        if (strstr(entrada->d_name, ".pgm")) {
            char caminho[FILENAME_MAX];
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
