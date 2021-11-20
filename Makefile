# Executable names:
EXE = project
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o src/graph.o src/edge.o src/vertex.o src/betweenness.o src/bfs.o src/dijkstras.o

# Generated files
CLEAN_RM = actual-*.png

# Use the cs225 makefile template:
include cs225.mk
