
#include <stdio.h>
#include <stdlib.h>

char	*to_base(unsigned int nb)
{
	char	*str;
	int		j;
    char    *base;

    base = "0123456789ABCDEF";
	j = 0;
	str = malloc(sizeof(char) * 3);
	str[1] = base[nb % 16];
	nb = nb / 16;
    if (nb < 10)
        str[0] = nb + '0';
    else
        str[0] = nb - 10 + 'A';
	str[2] = '\0';
    return (str);
}

int main()
{  
    char    *str;
    str = to_base(2);
    printf("%s\n", str);
}