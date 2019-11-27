CC=gcc

contador: contador.c 
	$(CC) contador.c descritor.c abp.c -o contador
