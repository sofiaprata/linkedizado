// kmeans.h
#ifndef KMEANS_H
#define KMEANS_H
#include "imagem.h"

void calcularHistograma(PGM *pgm, int *histograma);
void kmeans(PGM *pgm, int k, int *clusters);

#endif