#ifndef IMAGEM_H
#define IMAGEM_H

typedef struct {
    unsigned char *imagem;
    int largura;
    int altura;
    int max_intensidade;
} PGM;

PGM lerPGM(const char *caminho);
void salvarImagem(const PGM *pgm, int k, const char *pasta_destino, const char *nome_imagem);
void liberarImagem(PGM *pgm);

#endif