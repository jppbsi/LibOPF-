LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

CC=gcc
FLAGS= -O3 -Wall

all: libOPF opf_train txt2opf

libOPF: $(LIB)/libOPF.a
	echo "libOPF.a built..."

$(LIB)/libOPF.a: \
$(OBJ)/opf.o \
$(OBJ)/graph.o \
$(OBJ)/common.o \
$(OBJ)/heap.o \
$(OBJ)/queue.o \

	ar csr $(LIB)/libOPF.a \
$(OBJ)/opf.o \
$(OBJ)/graph.o \
$(OBJ)/common.o \
$(OBJ)/heap.o \
$(OBJ)/queue.o \

$(OBJ)/opf.o: $(SRC)/opf.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/opf.c -o $(OBJ)/opf.o
$(OBJ)/common.o: $(SRC)/common.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/common.c -o $(OBJ)/common.o
$(OBJ)/graph.o: $(SRC)/graph.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/graph.c -o $(OBJ)/graph.o
$(OBJ)/heap.o: $(SRC)/heap.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/heap.c -o $(OBJ)/heap.o
$(OBJ)/queue.o: $(SRC)/queue.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/queue.c -o $(OBJ)/queue.o

opf_train: src/opf_train.c
	$(CC) $(FLAGS) src/opf_train.c -o bin/opf_train -I $(INCLUDE) -L $(LIB) -lOPF -lm;

txt2opf: tools/src/txt2opf.c
	$(CC) $(FLAGS) tools/src/txt2opf.c -o tools/txt2opf -I $(INCLUDE) -L $(LIB) -lOPF -lm;

## Cleaning-up
clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o; rm -rf  bin/*; rm tools/txt2opf
