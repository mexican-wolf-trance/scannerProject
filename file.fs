func add(int a, int b);

int main()
{
	if (add(22, 44) == 66)
		printf("It works!");
	else
		printf("It failed!");
	return 0;
}

func add(int a, int b)
{
        return a + b;
}
