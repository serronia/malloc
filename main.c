#include "includes/ft_malloc.h"

int main(int a, char **b)
{
    if (a != 1)
        write(1, b, 1);
    char *str;
    char *str2;
    char *str3;
//    str = (char*)malloc(1);



    int p = 0;
    while (p < 1)
    {
        p += 1;
        printf("%d : \n", p);
    }
    str3 = malloc(1180);    printf("\n");
//    str = malloc(1);    printf("\n");
//    str = malloc(1);    printf("\n");
//    str = malloc(55);    printf("\n");
//    str = malloc(1);    printf("\n");

    printf("je sors\n");

    size_t i = getpagesize() * 3;
    printf("\nla taille des pages sont %zu\n", i);
    printf("hmmm %p", &str[0]);


    return(0);
}
