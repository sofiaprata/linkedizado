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

