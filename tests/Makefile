all:
	make pq_test
	make dstr_test

pq_test: pq_test.c ../pq.h ../pq.c
	gcc -Wall -I../ -o pq_test pq_test.c ../pq.c 
	@./pq_test

dstr_test: dstr_test.c ../dstr.h ../dstr.c
	gcc -Wall -I../ -o dstr_test dstr_test.c ../dstr.c 
	@./dstr_test
	
clean:
	@rm *_test

.PHONY: clear
