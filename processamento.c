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
/**
 * Função para imprimir o histograma da imagem.
 */
#include "processamento.h"
#include "imagem.h"
#include "kmeans.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define NIVEIS_CINZA 256

/**
 * Função para imprimir o histograma da imagem.
 */
void imprimirHistograma(int *histograma, const char *const caminho) {
  printf("Histograma da imagem %s: \n", caminho);
  for (int i = 0; i < NIVEIS_CINZA;i++) {
    if (histograma[i] > 0) {
      printf("Nível %d: %d\n", i, histograma[i]);
    }
  }
}

/**
 * Função para processar todas as imagens PGM em uma pasta de origem,
 * aplicar o algoritmo de clusterização k-means e salvar os resultados
 * na pasta de destino.
 *
 * @param pasta_origem Diretório contendo as imagens PGM originais.
 * @param pasta_destino Diretório onde as imagens processadas serão salvas.
 */
void processarImagens(const char *pasta_origem, const char *pasta_destino) {
    // Abre o diretório especificado como pasta de origem
    DIR *dir = opendir(pasta_origem);
    if (!dir) {
        printf("Erro ao abrir a pasta: %s\n", pasta_origem);
        return;
    }

    struct dirent *entrada;
    int imagens_processadas = 0;

    // Percorre os arquivos do diretório
    while ((entrada = readdir(dir)) != NULL) {
        if (strstr(entrada->d_name, ".pgm")) {
        char caminho[FILENAME_MAX];
        snprintf(caminho, sizeof(caminho), "%s/%s", pasta_origem, entrada->d_name);

        // Lê a imagem PGM do arquivo
        PGM pgm = lerPGM(caminho);
        if (!pgm.imagem) {
            printf("Erro ao carregar imagem: %s\n", caminho);
            continue;
        }

        // Calcula e imprime o histograma da imagem antes do K-Means
        int histograma[NIVEIS_CINZA];
        calcularHistograma(&pgm, histograma);
        imprimirHistograma(histograma, caminho);

        // Aloca memória para os clusters
        int *clusters = malloc(pgm.largura * pgm.altura * sizeof(int));
        if (!clusters) {
            printf("Erro ao alocar memória para clusters\n");
            liberarImagem(&pgm);
            continue;
        }

        int k = 10; // Define o número de clusters
        kmeans(&pgm, k, clusters);

        // Salva a imagem processada na pasta de destino
        salvarImagem(&pgm, k, pasta_destino, entrada->d_name);

        // Libera memória
        free(clusters);
        liberarImagem(&pgm);

        imagens_processadas++;
        printf("\n");
        }
    }

    closedir(dir);
    printf("Total de imagens processadas: %d\n", imagens_processadas);
}