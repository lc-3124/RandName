CC = g++
FLAGS = -g -static -std=c++17 -lraylib 
MAIN = main.cpp
BIN = main.exe
all: making running 

making : *.cpp 
	${CC} ${MAIN} -o ${BIN} ${FLAGS}


	
