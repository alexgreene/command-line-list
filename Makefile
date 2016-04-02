make:
	gcc -o list -g list.c

valgrind: 
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./list print
