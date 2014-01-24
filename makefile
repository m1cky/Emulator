# Only recompile if there are changes within Pri_Main
all: Pri_Main

# Only recompile if there are changes to main.c or pri.h
Pri_Main: main.c pri.h
	gcc -o main main.c -lm
