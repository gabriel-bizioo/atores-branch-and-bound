PROG = elenco
OBJS = main.o problema.o branch_bound.o util.o
DIR = src
CC = gcc

all: $(PROG)

problema.o: $(DIR)/problema.c $(DIR)/problema.h
	$(CC) -c $(CFLAGS) -o $@ $<

util.o: $(DIR)/util.c $(DIR)/util.h
	$(CC) -c $(CFLAGS) -o $@ $<

branch_bound.o: $(DIR)/branch_bound.c $(DIR)/branch_bound.h
	$(CC) -c $(CFLAGS) -o $@ $<

main.o: $(DIR)/main.c
	$(CC) $(MAINFLAGS) -c $(CFLAGS)  -o $@ $<

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)
	@rm -f $(OBJS)

clean:
	@echo "Limpando..."
	@rm -f elenco
