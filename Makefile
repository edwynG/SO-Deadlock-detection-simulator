SRCDIR = src
OBJDIR = obj
BINDIR = bin

CFLAGS = -Wall -I ./include  # Agrega el directorio de las cabeceras
SOURCE = $(wildcard $(SRCDIR)/*.c) # Lista de achivos fuentes
OBJ = $(SOURCE:$(SRCDIR)/%.c=$(OBJDIR)/%.o) # Aplica un map en SOURCE y crea archivos objetos

FILE = prevencion
NAMEFILE = "tests/caso_2.txt"

all: prepare $(BINDIR)/$(FILE)

clean:
	rm -rf $(OBJDIR) $(BINDIR) || true

prepare:
	mkdir -p $(OBJDIR) $(BINDIR)

$(BINDIR)/$(FILE): $(OBJ)
	gcc $(CFLAGS) -o $@ $^
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	gcc $(CFLAGS) -c $< -o $@

execute: $(BINDIR)/$(FILE)
	./$(BINDIR)/$(FILE) $(NAMEFILE)
 
# Ejecutar: ./bin/prevencion <nombre del archivo>