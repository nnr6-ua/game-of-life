# Macros

MAIN = main/
MAIN_FILE = $(MAIN)main.cpp
SRC = src/
SRC_FILES = $(SRC)cell_t.cpp $(SRC)board_t.cpp
OUT = bin/
OUT_FILE = $(OUT)juego-vida

# Tus 3 documentos distintos en la carpeta input
IN = input/
IN_FILE1 = $(IN)tablero1.txt
IN_FILE2 = $(IN)tablero2.txt
IN_FILE3 = $(IN)tablero3.txt
IN_FILE4 = $(IN)tablero4.txt
IN_FILE5 = $(IN)tablero5.txt

# Reglas explícitas

default:
	g++ $(MAIN_FILE) $(SRC_FILES) -o $(OUT_FILE)

manual:
	$(OUT_FILE)

file:
	$(OUT_FILE) $(IN_FILE1) $(IN_FILE2) $(IN_FILE3) $(IN_FILE4) $(IN_FILE5)

run: default manual

run-file: default file
run-file: default file

clean: 
	rm -rf $(OUT)
