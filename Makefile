# Executable names:
EXE = project
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o src/graph.o src/edge.o src/vertex.o src/betweenness.o src/bfs.o src/dijkstras.o src/utils.o src/argument_parser.o

AZURE_DATA_URL = https://storageaccountrgfuna61f.blob.core.windows.net/cs225
DATA_FILES = data.csv mini_data.csv tiny_data.csv 10mb_data.csv 30mb_data.csv

data:
	@for f in $(DATA_FILES); do curl $(AZURE_DATA_URL)/$${f} --output data/$${f}; done

# Use the cs225 makefile template:
include cs225/make/cs225.mk
