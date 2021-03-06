



all:
	rm *.o; rm main; export LD_LIBRARY_PATH="."; gcc -g -c htab*.c -fPIC; gcc *.o -shared -o libhtab.so; gcc -Wall -c -g -o wordcount.o wordcount.c -lm;  gcc -Wall -c -g -o io.o io.c -lm;  gcc -Wall -g -o wordcount wordcount.o io.o -lm -L . -lhtab

clear: 
	rm *.o; rm main; rm libhtab.so

main: main.c
	 gcc -Wall -c -g -o main.o main.c -lm;  gcc -Wall -g -o main main.o -lm -L . -lhtab