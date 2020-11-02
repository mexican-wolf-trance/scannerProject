#This is a test comment
func add(int a, int b);

#This is the maine function
int main()
{
	if (add(22, 44) == 66)
		printf("It works!");
	else
		printf("It failed!");
	return 0;
}

#Function definition
func add(int a, int b)
{
        return a + b;
}
