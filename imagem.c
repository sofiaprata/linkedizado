#include "imagem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ignorarComentarios(FILE *arquivo) {
    int c;
    while ((c = fgetc(arquivo)) == '#') {
        while ((c = fgetc(arquivo)) != '\n' && c != EOF);
    }
    fseek(arquivo, -1, SEEK_CUR);
}

PGM lerPGM(const char *caminho) {
    FILE *arquivo = fopen(caminho, "rb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo: %s\n", caminho);
        return (PGM){NULL, 0, 0, 0};
    }

    char tipo[3];
    if (fscanf(arquivo, "%2s", tipo) != 1 || strcmp(tipo, "P5")) {
        printf("Formato inválido (esperado P5): %s\n", caminho);
        fclose(arquivo);
        return (PGM){NULL, 0, 0, 0};
    }

    ignorarComentarios(arquivo);

    PGM pgm;
    if (fscanf(arquivo, "%d %d %d", &pgm.largura, &pgm.altura, &pgm.max_intensidade) != 3) {
        printf("Erro ao ler cabeçalho PGM: %s\n", caminho);
        fclose(arquivo);
        return (PGM){NULL, 0, 0, 0};
    }

    fgetc(arquivo);

    pgm.imagem = malloc(pgm.largura * pgm.altura);
    if (!pgm.imagem) {
        printf("Erro ao alocar memória para imagem: %s\n", caminho);
        fclose(arquivo);
        return (PGM){NULL, 0, 0, 0};
    }

    if (fread(pgm.imagem, 1, pgm.largura * pgm.altura, arquivo) != (size_t)(pgm.largura * pgm.altura)) {
        printf("Erro ao carregar pixels da imagem: %s\n", caminho);
        free(pgm.imagem);
        fclose(arquivo);
        return (PGM){NULL, 0, 0, 0};
    }

    fclose(arquivo);
    return pgm;
}

void liberarImagem(PGM *pgm) {
    free(pgm->imagem);
}

void salvarImagem(const PGM *pgm, int k, const char *pasta_destino, const char *nome_imagem) {
    char caminho_saida[256];
    snprintf(caminho_saida, sizeof(caminho_saida), "%s/%s_clustered.pgm", pasta_destino, nome_imagem);

    FILE *arquivo = fopen(caminho_saida, "wb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para escrita: %s\n", caminho_saida);
        return;
    }

    fprintf(arquivo, "P5\n%d %d\n%d\n", pgm->largura, pgm->altura, pgm->max_intensidade);
    for (int i = 0; i < pgm->largura * pgm->altura; i++) {
        fputc(pgm->imagem[i] * (pgm->max_intensidade / k), arquivo);
    }
    
    fclose(arquivo);
}
