#include <stdio.h>
#include <time.h>
#include "processamento.h"

int main() {
    clock_t begin = clock();

    processarImagens("C:/Users/Gleissi/Desktop/TrabalhoFinalLab/Carcinoma",
                     "C:/Users/Gleissi/Desktop/TrabalhoFinalLab/Carcinoma_out16");

    clock_t end = clock();
    double tempo = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo total: %.2lf segundos\n", tempo);

    return 0;
}
