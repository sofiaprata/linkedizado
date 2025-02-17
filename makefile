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
# Definição do compilador
CC = gcc

# Opções de compilação
CFLAGS = -O3

# Lista de arquivos-fonte
SRCS = main.c imagem.c kmeans.c processamento.c

# Nome do executável
OUT = completo

# Regra padrão (executa ao rodar 'make' ou 'make all')
all: $(OUT)

# Regra para compilar o executável
$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(OUT)

