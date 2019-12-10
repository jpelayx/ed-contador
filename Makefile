CC=gcc

contador: contador.c
	$(CC) contador.c descritor.c abp.c avl.c abf.c -o contador
