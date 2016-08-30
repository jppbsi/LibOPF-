LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

CC=gcc
FLAGS= -O3 -Wall

all: libOPF

libOPF: $(LIB)/libOPF.a
	echo "libOPF.a built..."

$(LIB)/libOPF.a: \
$(OBJ)/graph.o \
$(OBJ)/common.o \

	ar csr $(LIB)/libOPF.a \
$(OBJ)/graph.o \
$(OBJ)/common.o \

$(OBJ)/common.o: $(SRC)/common.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/common.c -o $(OBJ)/common.o
$(OBJ)/graph.o: $(SRC)/graph.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/graph.c -o $(OBJ)/graph.o


## Cleaning-up
clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o 
