# Executable names:
EXE = project
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o graph.o edge.o vertex.o betweenness.o bfs.o dijkstras.o

# Generated files
CLEAN_RM = actual-*.png

# Use the cs225 makefile template:
include cs225.mk
