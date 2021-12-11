# Executable names:
EXE = project
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o src/graph.o src/edge.o src/vertex.o src/betweenness.o src/bfs.o src/dijkstras.o src/utils.o src/argument_parser.o

data: 
	curl https://storageaccountrgfuna61f.blob.core.windows.net/cs225/data.csv --output data/data.csv
	curl https://storageaccountrgfuna61f.blob.core.windows.net/cs225/mini_data.csv --output data/mini_data.csv
	curl https://storageaccountrgfuna61f.blob.core.windows.net/cs225/tiny_data.csv --output data/tiny_data.csv
	curl https://storageaccountrgfuna61f.blob.core.windows.net/cs225/10mb_data.csv --output data/10mb_data.csv
	curl https://storageaccountrgfuna61f.blob.core.windows.net/cs225/30mb_data.csv --output data/30mb_data.csv

# Use the cs225 makefile template:
include cs225/make/cs225.mk
