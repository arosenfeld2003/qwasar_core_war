#include "asm_utils.h"

/*
 * asm_utils.c
 */

int my_atoi(char *str)
{
    int i = 0;
    int sign = 1;
    int nb = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9')
            nb = (nb * 10) + (str[i] - 48);
        i++;
    }
    return (sign * nb);
}

int my_strlen(char *str)
{
    int i = 0;

    if (!str)
        return 0;

    while (str[i] != '\0')
        i++;
    return i;
}

int	my_strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] == s2[i])
	{
		i++;
		if (s1[i] == '\0' || s2[i] == '\0')
			break ;
	}
	return (s1[i] - s2[i]);
}

char *my_strcpy(char *dest, char *src)
{
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
        i++;
    }
	dest[i] = '\0';
	return dest;
}

/*
 * note: remember to free the returned string
 */
char *my_itoa_base(long long num, int base) {
    int is_neg = num < 0 && base == 10;
    int num_length = num == 0;
    int digit, i = 0;
    num = my_abs(num);
    long long rem = num;

    if (base < 2) return NULL;
    
    while (rem > 0) {
        num_length++;
        rem /= base;
    }
    char *str = (char*)malloc(sizeof(char) * (num_length + is_neg + 1));
    if (!str) return NULL;
    
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    while (num != 0) {
        digit = num % base;
        str[i++] = (digit > 9) ? (digit - 10) + 'a' : digit + '0';
        num /= base;
    }
    if (is_neg) str[i++] = '-';

    str[i] = '\0';
    return reverse_string(str);
}
