SHELL_SOURCE = my_shell.c ioredirect.o
all: $(SHELL_SOURCE)
	$(cc) $(CFLAGS) $(SHELL_SOURCE) -o my_shell

clean:
	rm product my_shell ioredirect.o

strip: $(SHELL_SOURCE) $(PRODUCT_SOURCE)
	gcc $(SHELL_SOURCE) -o my_shell
	gcc $(PRODUCT_SOURCE) -o product
