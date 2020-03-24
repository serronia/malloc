#include "includes/ft_malloc.h"

int main(int a, char **b)
{
    if (a != 1)
        myfunct(b[1]);
    char *str;
    char *str2;
//    str = (char*)malloc(1);



    int p = 0;
    while (p < 200)
    {
        p += 1;
        printf("%d : ", p);
    str = malloc(96);
    printf("\n");
    }

//    str = malloc(1);
    size_t i = getpagesize() * 3;
    printf("\nla taille des pages sont %zu\n", i);
    printf("hmmm %p", &str[0]);


    return(0);
}
