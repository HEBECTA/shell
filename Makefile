shelas: main.o shell.o
	gcc main.o shell.o -o shelas

main.o: main.c
	gcc -Wall main.c -c

shell.o: shell.c
	gcc -Wall shell.c -c

clean:
	rm *.o shelas