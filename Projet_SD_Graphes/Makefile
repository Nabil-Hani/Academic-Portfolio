CC = gcc
CFLAGS = -Wall -c
LDFLAGS =
OBJ = Projet.o

all: Projet

Projet: $(OBJ)
	$(CC) $(LDFLAGS) -o Projet $(OBJ)

Projet.o: Projet.c graphe.h sommet.h arc.h chemin.h
	$(CC) $(CFLAGS) Projet.c

clean:
	rm -f *.o Projet
