# Project: cinema

OBJ  = sem_op.o shm_op.o aleatoire_place.o aleatoire_traitement.o
LINKOBJ  = $(OBJ)
BIN  = cinema caisse display
CFLAGS = -g #-Wall

all: cinema caisse display

cinema: $(LINKOBJ) shm_const.h cinema.c
	$(CC) cinema.c $(LINKOBJ) -o cinema $(CFLAGS)

display: $(LINKOBJ) shm_const.h display.c
	$(CC) display.c $(LINKOBJ) -o display $(CFLAGS)

caisse: $(LINKOBJ) shm_const.h caisse.c
	$(CC) caisse.c $(LINKOBJ) -o caisse $(CFLAGS)

shm_op.o: shm_op.c shm_const.h
	$(CC) -c shm_op.c $(CFLAGS)

sem_op.o: sem_op.c shm_const.h
	$(CC) -c sem_op.c $(CFLAGS)

aleatoire_place.o: aleatoire_place.c
	$(CC) -c aleatoire_place.c $(CFLAGS)

aleatoire_traitement.o: aleatoire_traitement.c
	$(CC) -c aleatoire_traitement.c $(CFLAGS)

clean: 
	rm -f $(OBJ) $(BIN)

re: clean all
