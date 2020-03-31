#include "includes/ft_malloc.h"

int main(int a, char **b)
{
    if (a != 1)
        myfunct(b[1]);
    char *str;
    char *str2;
    char *str3;
    str = (char*)malloc(1);



    int p = 0;
    while (p < 1)
    {
        p += 1;
        printf("%d : ", p);
    str = malloc(1);
    printf("\n");
    }
//    str2 = malloc(55);
    printf("\n");
    str3 = malloc(55);    printf("\n");
//    str3 = malloc(55);    printf("\n");
//    str3 = malloc(55);    printf("\n");

//    printf("\n");
    str = malloc(1);    printf("\n");
    str = malloc(1);    printf("\n");
    str = malloc(12);    printf("\n");
//    str = malloc(1);    printf("\n");
//////
//////
//    str = malloc(1);    printf("\n");
//    str = malloc(1);    printf("\n");
//    str = malloc(1);    printf("\n");
//    str = malloc(1);    printf("\n");
//    str = malloc(1);    printf("\n");
//    str = malloc(1);    printf("\n");

//    str = malloc(1);    printf("\n");
////
//    str = malloc(10);    printf("\n");
//    str = malloc(10);    printf("\n");
//    str = malloc(1);    printf("\n");
//    str = malloc(10);    printf("\n");

    printf("je sors\n");

//int j = 0;
//    while ( j < 54)
//    {
//        str2[j] = 'd';
//        j++;
//
//    }
//    j = 0;
//    while ( j < 10)
//    {
//        str[j] = 'u';
//        j++;
//
//    }
//    j = 0;
//    while ( j < 20)
//    {
//        str3[j] = 't';
//        j++;
//
//    }
//

//    str = malloc(20);
//    printf("\n");
//    str = malloc(80);
//    printf("\n");
//    str = malloc(20);
//    printf("\n");
//    str = malloc(20);
//    printf("\n");
//    str = malloc(20);


//    str = malloc(1);
    size_t i = getpagesize() * 3;
    printf("\nla taille des pages sont %zu\n", i);
    printf("hmmm %p", &str[0]);

//    printf("str  : %s\n", str);
//    printf("str2 : %s\n", str2);
//    printf("str3 : %s\n", str3);

    return(0);
}
