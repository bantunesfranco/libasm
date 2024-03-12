#include <stdio.h>
#include <string.h>

extern int ft_strlen(char *str);
extern char *ft_strcpy(char *dest, char *src);

int main() {
	char *strr = "Hello, World!";
	int len = ft_strlen(strr);
	printf("Length of string is: %d\n", len);

	char lmao[10] = "lmao000000";
	char str[4] = "lol";
	ft_strcpy(lmao, str);
	printf("%s\n", lmao);
	char str2[16] = "aaaaaa";
	ft_strcpy(lmao, str2);
	printf("%s\n", lmao);
	return 0;
}
