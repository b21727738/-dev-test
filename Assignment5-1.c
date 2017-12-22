#include <stdio.h>

int main() {
	int secpos;
	int inp = 4;
	char pristri[inp*2] ;
	char rc = '/',rr = '\\';
	for (int i=0; i<(inp*2) ;i++) {
		for (int j=0;j<(inp*2);j++){
			pristri[j] = ' ';
		}
		if (i < inp) {
			pristri[((inp - i)-1)] = rc;
			pristri[(inp + i)] = rr;
			pristri[(inp + i+1)] = '\0';
			printf("%s\n",&pristri);
		} else {
			pristri[(i - inp)] = rr;
			pristri[((inp *2) + inp - 1) - i] = rc;
			printf("%s\n",&pristri);
		}
	}
	return 0;
	
}
