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
// * Matrícula: 2024104505 0480                                *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
#include "imagem.h"  // Inclui o arquivo de cabeçalho que contém a definição da estrutura PGM e funções auxiliares.
#include <stdio.h>    // Biblioteca padrão para entrada e saída.
#include <stdlib.h>   // Biblioteca padrão para alocação de memória e outras funções utilitárias.
#include <string.h>   // Biblioteca para manipulação de strings.
#include <dirent.h>   // Biblioteca para manipulação de diretórios.

/**
 * Função que ignora comentários no arquivo PGM.
 * Comentários em arquivos PGM começam com '#' e continuam até o fim da linha.
 */
void ignorarComentarios(FILE *arquivo) {
    int c;
    while ((c = fgetc(arquivo)) == '#') { // Verifica se o caractere lido é '#'.
        while ((c = fgetc(arquivo)) != '\n' && c != EOF); // Ignora todos os caracteres até o final da linha.
    }
    fseek(arquivo, -1, SEEK_CUR); // Retorna um caractere para trás para não perder dados úteis.
}

/**
 * Função que lê uma imagem no formato PGM (P5 - binário) e retorna uma estrutura PGM.
 * @param caminho Caminho do arquivo PGM a ser lido.
 * @return Estrutura PGM contendo os dados da imagem.
 */
PGM lerPGM(const char *caminho) {
    FILE *arquivo = fopen(caminho, "rb"); // Abre o arquivo em modo binário de leitura.
    if (!arquivo) { // Verifica se o arquivo foi aberto com sucesso.
        printf("Erro ao abrir arquivo: %s\n", caminho);
        return (PGM){NULL, 0, 0, 0}; // Retorna uma estrutura PGM vazia caso ocorra erro.
    }

    char tipo[3];
    // Lê o tipo do arquivo (deve ser "P5") e verifica se está correto.
    if (fscanf(arquivo, "%2s", tipo) != 1 || strcmp(tipo, "P5")) {
        printf("Formato inválido (esperado P5): %s\n", caminho);
        fclose(arquivo);
        return (PGM){NULL, 0, 0, 0};
    }

    ignorarComentarios(arquivo); // Chama a função para ignorar possíveis comentários no cabeçalho.

    PGM pgm;
    // Lê as dimensões da imagem (largura, altura) e a intensidade máxima dos pixels.
    if (fscanf(arquivo, "%d %d %d", &pgm.largura, &pgm.altura, &pgm.max_intensidade) != 3) {
        printf("Erro ao ler cabeçalho PGM: %s\n", caminho);
        fclose(arquivo);
        return (PGM){NULL, 0, 0, 0};
    }

    fgetc(arquivo); // Lê o caractere de nova linha após o cabeçalho para posicionar corretamente o ponteiro no início dos pixels.

    // Aloca memória para armazenar os pixels da imagem.
    pgm.imagem = malloc(pgm.largura * pgm.altura);
    if (!pgm.imagem) { // Verifica se a alocação de memória foi bem-sucedida.
        printf("Erro ao alocar memória para imagem: %s\n", caminho);
        fclose(arquivo);
        return (PGM){NULL, 0, 0, 0};
    }

    // Lê os pixels da imagem e armazena no vetor `pgm.imagem`.
    if (fread(pgm.imagem, 1, pgm.largura * pgm.altura, arquivo) != (size_t)(pgm.largura * pgm.altura)) {
        printf("Erro ao carregar pixels da imagem: %s\n", caminho);
        free(pgm.imagem); // Libera a memória alocada antes de sair.
        fclose(arquivo);
        return (PGM){NULL, 0, 0, 0};
    }

    fclose(arquivo); // Fecha o arquivo após a leitura bem-sucedida.
    return pgm; // Retorna a estrutura contendo a imagem lida.
}

/**
 * Função que libera a memória alocada para a imagem.
 * @param pgm Ponteiro para a estrutura PGM.
 */
void liberarImagem(PGM *pgm) {
    free(pgm->imagem); // Libera a memória alocada para os pixels da imagem.
}

/**
 * Função que salva a imagem PGM após a clusterização.
 * @param pgm Estrutura PGM contendo a imagem processada.
 * @param k Número de clusters utilizado na segmentação.
 * @param pasta_destino Diretório onde a imagem será salva.
 * @param nome_imagem Nome base do arquivo de saída.
 */
void salvarImagem(const PGM *pgm, int k, const char *pasta_destino, const char *nome_imagem) {
    char caminho_saida[256];
    // Cria o caminho do arquivo de saída, incluindo o diretório e o nome do arquivo.
    snprintf(caminho_saida, sizeof(caminho_saida), "%s/%s_clustered.pgm", pasta_destino, nome_imagem);

    FILE *arquivo = fopen(caminho_saida, "wb"); // Abre o arquivo em modo binário para escrita.
    if (!arquivo) { // Verifica se o arquivo foi aberto corretamente.
        printf("Erro ao abrir arquivo para escrita: %s\n", caminho_saida);
        return;
    }

    // Escreve o cabeçalho do arquivo PGM.
    fprintf(arquivo, "P5\n%d %d\n%d\n", pgm->largura, pgm->altura, pgm->max_intensidade);

    // Escreve os pixels da imagem no arquivo.
    // Cada pixel é ajustado com base no número de clusters `k`.
    for (int i = 0; i < pgm->largura * pgm->altura; i++) {
        fputc(pgm->imagem[i] * (pgm->max_intensidade / k), arquivo);
    }
    
    fclose(arquivo); // Fecha o arquivo após a escrita.
}