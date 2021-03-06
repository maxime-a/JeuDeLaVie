CC = gcc             # le compilateur à utiliser
CFLAGS = -Wall  # les options du compilateur
LDFLAGS = -lsx      # les options pour l'éditeur de liens
SRC = donnees.c vue.c grille.c modele.c rappels.c main.c  # les fichiers sources
PROG = JeuDeLaVie          # nom de l'exécutable
OBJS =  $(SRC:.c=.o) # les .o qui en découlent
.SUFFIXES: .c .o     # lien entre les suffixes

all: $(PROG)

# étapes de compilation et d'édition de liens
# $@ la cible  $^ toutes les dépendances	
$(PROG): $(OBJS)
	$(CC)  -o $@ $^ $(LDFLAGS)

rappels.o: modele.h
modele.o: grille.h
main.o: vue.h
# le lien entre .o et .c
# $< dernière dépendance	
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# pour faire propre
.PHONY: clean
clean:
	rm -f *.o *~ core $(PROG)
