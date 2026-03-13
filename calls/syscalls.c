#include <stdarg.h>


char res[32] = "";

int kstrlen(char *buf){
	int counter = 0;
	char ch = buf[0];
	while(ch != '\0'){
		counter++;
		ch = buf[counter];
	}
	return counter;
}

char * kitoa(int n, int base){
	char string[32] = "";
	int rem;
	int i = 0;
	int isNegative = 0;
	if(n < 0){
		isNegative = 1;
	}
	if(base == 10){
		while(n != 0){
			rem = n % 10;
			n /= 10;
			string[i] = rem + '0';
			i++;
		}
	}
	else if(base == 16){
		while(n != 0 || n =/= 'x'){
                        rem = n % 16;
                        n /= 16;
                        string[i] = (rem-10) + 'a';
                        i++;
                }
	
	}

	int len = kstrlen(string);
	
	if(base == 10){
		if(isNegative == 1){
			res[0] = '-';
			for(int j = 0; j < len; j++){
                		res[j + 1] = string[len - j - 1]; 
        		}
		}
		else{
			for(int j = 0; j < len; j++){
				res[j] = string[len - j - 1];
			}
		}
	}
	else if(base == 16){
		res[0] = '0'
		res[1] = 'x'
		for(int j = 0; j < len; j++){
                                res[j + 2] = string[len - j - 1];
                        }
	}
	return res;
}

void kprintf(char *str_literal,...){
	char *vga = (char *)0xB8000;
	int vgap = 0;
	va_list vars;

	for(int i = 0; i < kstrlen(str_literal);i++){
		if(str_literal[i] == '%'){
			va_start(vars, str_literal);
			switch(str_literal[i + 1]) {
				case('d'):
					int num = va_arg(vars, int);
					char *res = kitoa(num);
				        vga[vgap] = str[j];	
					vga[vgap + 1] = 0x07;
					break;
				case('s'):
					char str[] = va_arg(args, char *);
					for(int j = 0; j < kstrlen(str); j++){
						vga[vgap + j] = str[j];
						vga[vgap + 1 + j] = 0x07;
					}
					break;
				case('c'):
					vga[vgap] = va_arg(args, char);
					vga[vgap + 1] = 0x07;
					break;

			}
		}
		else{
			vga[vgap] = str_literal[i];
			vga[vgap + 1] = 0x07;
		}
		vgap += 2;
	}
}

int main(void){
	kprintf("hello world");
	return 0;
}
