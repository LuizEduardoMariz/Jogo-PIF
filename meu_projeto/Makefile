# --- Nomes de Arquivo e Diretórios ---
TARGET      = jogo-pif
SRCDIR      = src
INCDIR      = include
BUILDDIR    = build
ASSETDIR    = assets

# Encontra todos os arquivos .c na pasta src/
SRC         = $(wildcard $(SRCDIR)/*.c)
# Converte .c -> .o dentro da pasta build/
OBJ         = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRC))

# --- Configurações do Compilador ---
CC          = gcc
CFLAGS      = -I$(INCDIR) -Wall -Wextra -std=c99 -O2

# --- Configurações da Raylib (Linux/WSL) ---
LDFLAGS     = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# --- Regras Principais ---
.PHONY: all clean run assets

all: $(BUILDDIR) $(TARGET)

# Cria a pasta build se não existir
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

# Linka os objetos e cria o executável
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)
	@echo "✅ Build completo: ./$(TARGET)"

# Compila os .c individualmente
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executa o jogo (assegurando que o som/imagens sejam encontrados)
run: $(TARGET)
	@echo "🎮 Executando $(TARGET)..."
	@./$(TARGET)

# Limpa o projeto
clean:
	@rm -rf $(BUILDDIR) $(TARGET)
	@echo "🧹 Projeto limpo!"

# Cria as pastas de assets se ainda não existirem
assets:
	@mkdir -p $(ASSETDIR)/sounds
	@mkdir -p $(ASSETDIR)/textures
	@mkdir -p $(ASSETDIR)/fonts
	@echo "📁 Pastas de assets criadas com sucesso!"
