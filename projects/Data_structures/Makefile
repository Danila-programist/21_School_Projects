all : list_test 

list_test : list_test.o list.o
	gcc list_test.o list.o -o Quest_2

list_test.o : list_test.c
	gcc -c -Wextra -Werror -Wall list_test.c

list.o : list.c
	gcc -c -Wextra -Werror -Wall list.c

clean : 
	rm -rf *.o Quest_2

rebuild : clean all