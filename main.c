#include "includes/ft_malloc.h"

int main(int a, char **b)
{
	if (a != 1)
		write(1, b, 1);

	char *str3;

	str3 = malloc(12);	printf("EeND\n\n ");

	str3 = malloc(50);	printf("END\n\n");
	str3 = malloc(5000);	printf("END\n\n");
	str3 = malloc(14000);	printf("END\n\n");
	str3 = realloc(str3, 51);	  printf("END\n\n");
	str3 = malloc(2000);	printf("END\n\n");

	str3 = malloc(10);	printf("END\n\n");

	str3 = calloc(50, sizeof(int));

	show_alloc_mem();

	return(0);
}


