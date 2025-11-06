# --- Nomes de Arquivo e Diretórios ---
TARGET      = jogo-pif
SRCDIR      = src
INCDIR      = include
BUILDDIR    = build

# Encontra todos os arquivos .c na pasta src/
SRC         = $(wildcard $(SRCDIR)/*.c)
# Converte a lista de arquivos .c para uma lista de arquivos .o na pasta build/
OBJ         = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRC))

# --- Configurações do Compilador ---
CC          = gcc
# Inclui o diretório de cabeçalhos e as flags comuns
CFLAGS      = -I$(INCDIR) -Wall -Wextra -std=c99
# Flags de Otimização e Debug (Troque -O2 por -g para debug)
CFLAGS     += -O2

# --- Configurações da Raylib (Linux/WSL) ---
# Flags para linkar a biblioteca raylib e suas dependências no Linux
LDFLAGS     = -lraylib -lGL -lm -lpthread -ldl -lrt

# --- Regra Principal: Compilação Completa ---
.PHONY: all clean

all: $(BUILDDIR) $(TARGET)

# Cria a pasta 'build' se ela não existir
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

# Linka todos os arquivos .o para criar o executável final
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# --- Regra de Compilação: Arquivos .c para .o ---
# Esta regra compila cada arquivo .c em um arquivo .o e o coloca na pasta build/
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Regras Auxiliares ---

# Executa o jogo
run: $(TARGET)
	./$(TARGET)

# Limpa o projeto (remove a pasta build/ e o executável)
clean:
	@rm -rf $(BUILDDIR) $(TARGET)
	@echo "Projeto limpo!"