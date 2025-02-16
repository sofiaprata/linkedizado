//∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ /
//∗ Aluno : Joao de Souza ∗/
//∗ M a t ri c ul a : 12345 ∗/
//∗ A v ali a c a o 0 4: Trabalho Fi n al ∗/
//∗ 0 4. 5 0 5. 2 3 − 2 0 2 4. 2 − P r o f . D a ni el F e r r e i r a ∗/
//∗ Compilador : . . . ( DevC++ ou gcc ) v e r s a o . . . ∗/
//∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ 
//∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ /
//∗ Aluno : Joao de Souza ∗/
//∗ M a t ri c ul a : 12345 ∗/
//∗ A v ali a c a o 0 4: Trabalho Fi n al ∗/
//∗ 0 4. 5 0 5. 2 3 − 2 0 2 4. 2 − P r o f . D a ni el F e r r e i r a ∗/
//∗ Compilador : . . . ( DevC++ ou gcc ) v e r s a o . . . ∗/
//∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ 
//∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ /
//∗ Aluno : Joao de Souza ∗/
//∗ M a t ri c ul a : 12345 ∗/
//∗ A v ali a c a o 0 4: Trabalho Fi n al ∗/
//∗ 0 4. 5 0 5. 2 3 − 2 0 2 4. 2 − P r o f . D a ni el F e r r e i r a ∗/
//∗ Compilador : . . . ( DevC++ ou gcc ) v e r s a o . . . ∗/
//∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ 
#include <stdio.h>
#include <time.h>
#include "processamento.h"

int main() {
    clock_t begin = clock();

    // Caminho genérico, ajustado para ser mais portátil
    const char *inputPath = "dataset"; // Diretório relativo
    const char *outputPath = "out"; // Diretório relativo de saída

    // Processar imagens
    processarImagens(inputPath, outputPath);

    // Calcular o tempo de execução
    clock_t end = clock();
    double tempo = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo total: %.2lf segundos\n", tempo);

    return 0;
}