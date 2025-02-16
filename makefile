# Definição do compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall -Wextra -g3 -O3

# Lista de arquivos-fonte
SRCS = main.c imagem.c kmeans.c processamento.c

# Nome do executável
OUT = output/completo.exe

# Regra padrão (executa ao rodar 'make' ou 'make all')
all: cria_pasta $(OUT)

# Criar pasta (compatível com Windows e Linux)
cria_pasta:
	@if not exist output mkdir output

# Regra para compilar o executável
$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(OUT)

# Regra para limpar arquivos compilados
clean:
	rm -f $(OUT) 