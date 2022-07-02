# Variable
CC = gcc
CFLAGS = -Wall -g
CFLAGS2 = -I include
CPPFLAGS += -I include -I/usr/include/cairo
LDFLAGS += -lcairo -lX11

EXEC = prog
ARCHIVE = tar -cfJ -f ZarikianHayk-Gol-v4.0.tar.xz
MODECAIROSRC = src/io_cairo.c src/main_cairo.c src/grille.c src/jeu.c
MODETEXTSRC = src/io.c src/main.c src/grille.c src/jeu.c

vpath %.h include
vpath %.c src
vpath %.o obj

OBJ = obj/

# Compilation en MODE TEXTE ou GRAPHIQUE
ifeq (TEXTE, $(MODE))
OBJETS = $(patsubst src/%.c, obj/%.o, $(wildcard $(MODETEXTSRC)))

# Compilation MODE TEXTE
$(EXEC) : $(OBJETS)
	$(CC) $(CFLAGS) -o $@ $? $(CFLAGS2)
	mkdir -p bin
	mv -f $(EXEC) bin/
	mv -f ./grilles bin/

$(OBJ)main.o: main.c grille.h io.h jeu.h
	$(CC) $(CFLAGS) -c $< $(CFLAGS2)
	mkdir -p obj 
	mv -f *.o $(OBJ)

$(OBJ)%.o: %.c %.h 
	mkdir -p obj 
	$(CC) $(CFLAGS) -c $< $(CFLAGS2)
	mv -f *.o $(OBJ)

else
OBJETS = $(patsubst src/%.c, obj/%.o, $(wildcard $(MODECAIROSRC)))

# Compilation MODE GRAPHIQUE
prog_cairo : $(OBJETS)
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS) $(CPPFLAGS)
	mkdir -p bin
	mv -f prog_cairo bin/
	mv -f ./grilles bin/

$(OBJ)main_cairo.o: main_cairo.c grille.h io_cairo.h jeu.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) $(CPPFLAGS)
	mkdir -p obj 
	mv -f *.o $(OBJ)

$(OBJ)%.o: %.c %.h 
	mkdir -p obj 
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) $(CPPFLAGS)
	mv -f *.o $(OBJ)

endif
	

# Commandes complémentaires
docs:
	mkdir doc
	doxygen
	
dist:
	$(ARCHIVE) include src Makefile Doxyfile .gitignore
	
clean : 
	mv ./bin/grilles ./
	rm -rf obj bin *.tar.xz doc
