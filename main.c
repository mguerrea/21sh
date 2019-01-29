void hello(char **test)
{
	*test[0] = 'h';
	*test[1] = 'e';
	*test[2] = '\0';
}

int main(void)
{
	char *test;

	test = malloc(6);
	hello(&test);
	printf("%s\n", test);
	return 0;
}
