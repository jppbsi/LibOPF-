LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj
UTIL=util

CC=gcc

FLAGS=  -O3 -Wall


INCFLAGS = -I$(INCLUDE)

all: libOPF

libOPF: libOPF-build
	echo "libOPF.a built..."

libOPF-build: \
util \
$(OBJ)/OPF.o \

	ar csr $(LIB)/libOPF.a \
$(OBJ)/graph.o \


$(OBJ)/OPF.o: $(SRC)/OPF.c
	$(CC) $(FLAGS) -c $(SRC)/OPF.c $(INCFLAGS) \
	-o $(OBJ)/OPF.o


## Cleaning-up

clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o 
