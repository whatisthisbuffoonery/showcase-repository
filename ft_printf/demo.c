#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

int main(void)
{

	ft_printf("% .6d\n", -3);
	printf("% .6d\n", -3);
/*
	ft_printf("%c\n", 'a');
	ft_printf("%s\n", "hello");
	ft_printf("%p\n", (void *) 0x123);
	ft_printf("%d\n", 42);
	ft_printf("%i\n", -123);
	ft_printf("%u\n", 4294967295U);
	ft_printf("%x\n", 255);
	ft_printf("%X\n", 255);


	ft_printf("%s\n", "");
	ft_printf("%s\n", NULL);
	ft_printf("%c\n", '\0');
	ft_printf("%d\n", INT_MIN);
	ft_printf("%d\n", INT_MAX);
	ft_printf("%u\n", 0);
	ft_printf("%u\n", UINT_MAX);
	ft_printf("%x\n", 0);
	ft_printf("%x\n", 0xDEADBEEF);
	ft_printf("%X\n", 0XDEADBEEF);


	ft_printf("%s %% %d %% %x %% %c\n", "test", 42, 255, '!');
	ft_printf("%X %X %X\n", (void *) 0xface, (void *) 0xa, (void *) 0xbed);

	ft_printf("%%");
	ft_printf("\n%%\n");
	ft_printf("%%\n");
	ft_printf("%%%%%%%%");
	ft_printf("\n%%%%%%%%\n");
	ft_printf("%%%%%%%%\n");


	ft_printf("%%%d", 42);
	ft_printf("\n%%%d\n%d", 43, 44);
	ft_printf("%d%%\n", 45);
	ft_printf("%%%%%%%%");
	ft_printf("\n%%%%%%%%\n");
	ft_printf("%%%%%%%%\n");


	ft_printf("");
	ft_printf("%");
	ft_printf("%t");
	ft_printf("%d %% w%\n", 2);


	ft_printf("%c%c%c%c", 'a', 'a', 0, 0);
	ft_printf("%c%c%c%c", '\n', 0, 0, '\n');
	ft_printf("\nhere --> %c\n", 0);


	write(1, "mine\n", 5);
	ft_printf("|%+8d|%+8d|%+.3d|\n", 42, -42, 42);
	write(1, "theirs\n", 7);
	printf("|%+8d|%+8d|%+.3d|\n", 42, -42, 42);
	write(1, "mine\n", 5);
	ft_printf("|%-8d|%-8d|%-.3d|\n", 42, -42, 42);
	write(1, "theirs\n", 7);
	printf("|%-8d|%-8d|%-.3d|\n", 42, -42, 42);
	write(1, "mine\n", 5);
	ft_printf("|%08d|%08d|%0.3d|\n", 42, -42, 42);
	write(1, "theirs\n", 7);
	printf("|%08d|%08d|%0.3d|\n", 42, -42, 42);
	write(1, "mine\n", 5);
	ft_printf("|% 8d|% 8d|% .3d|\n", 42, -42, 42);
	write(1, "theirs\n", 7);
	printf("|% 8d|% 8d|% .3d|\n", 42, -42, 42);


	write(1, "mine\n", 5);
	ft_printf("|%+8.3d| |%-+8.3i| |%8.3u| |%#8.3x| |%#8.3X| |%8p|\n",42, 42, 42, 42, 42, (void*)0xABCD);
	write(1, "theirs\n", 7);
	printf("|%+8.3d| |%-+8.3i| |%8.3u| |%#8.3x| |%#8.3X| |%8p|\n",42, 42, 42, 42, 42, (void*)0xABCD);


	write(1, "mine\n", 5);
	ft_printf("|%8.3s| |%-8.3s| |%8c| |%-8c|\n","hi","hi", 'A', 'A');
	write(1, "theirs\n", 7);
	printf("|%8.3s| |%-8.3s| |%8c| |%-8c|\n","hi","hi", 'A', 'A');


	write(1, "mine\n", 5);
	ft_printf("|%.0d| |%+.0d| |%#0.0x| |%.1s| |%.0s|\n", 0, 0, 0, "hi", "hi");
	write(1, "theirs\n", 7);
	printf("|%.0d| |%+.0d| |%#0.0x| |%.1s| |%.0s|\n", 0, 0, 0, "hi", "hi");


	ft_printf("|%#0.0x|\n", 0);

	ft_printf("%-9p, %-10p", LONG_MIN, LONG_MAX);
	write(1, "\n", 1);
	printf("%-9p, %-10p\n", (void *) LONG_MIN, (void *) LONG_MAX);


	ft_printf("%.5s\n", NULL);
	printf("%.5s\n", (char *) NULL);
	ft_printf("%.6s\n", NULL);
	printf("%.6s\n", (char *) NULL);
	ft_printf("%.5p\n", NULL);
	printf("%p\n", NULL);
	ft_printf("%.4p\n", NULL);
	printf("%p\n", NULL);
*/
//	ft_printf("%#x\n", 0);
//	ft_printf("%#x\n", LONG_MIN);
//	ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
//	ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
//	ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
//	ft_printf("-->|%-16p|<-- ", (void*)0x1900);
//	write(1, "\n", 1);
//	printf("-->|%-16p|<-- ", (void*)0x1900);
/*
	ft_printf("%08.5p", (void *) 34);
	write(1, "\n", 1);
	printf("%8p\n", (void *) 34);
//	ft_printf("%%\n");
	ft_printf("%08.5i", 43);
	write(1, "\n", 1);
	printf("%08.5i\n", 43);
*/

//	ft_printf("%5.0i", 0);
//	write(1, "\n", 1);
//	printf("%5.0i\n", 0);

/*
	ft_printf("%p\n", (void *) 0);
	ft_printf("%#x\n", 0);
	ft_printf("%x\n", 0);
*/
	int a = INT_MIN;
//	unsigned int c = 0 - a;
	int b = 0 - a;
	ft_printf("%u\n", UINT_MAX);
	printf("%d\n", b);
	//ft_printf("%p", (void *) ULONG_MAX);
}
