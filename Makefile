run: input.o input_processing.o db_operations.o
	gcc -g input.o input_processing.o db_operations.o -o segmn && ./segmn db3.csv

input.o: input.c
	gcc -g -c input.c 

input_processing.o: input_processing.c
	gcc -g -c input_processing.c

db_operations.o: db_operations.c
	gcc -g -c db_operations.c

gdb:
	gdb --args ./segmn db.csv

clean:
	rm -f *.o 