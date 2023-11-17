comp:
	gcc -g $$PROGRAMA.c -o $$PROGRAMA.out 
exe:
	./$$PROGRAMA.out 
comxe:
	make comp
	make exe
zipa:
	mkdir lista
	cp *.c lista/
	zip -r lista.zip lista/
	rm -r lista
debug:
	gdb $$PROGRAMA.out  
ray:
	gcc $$PROGRAMA.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $$PROGRAMA.out 
rayexe:
	make ray
	make exe