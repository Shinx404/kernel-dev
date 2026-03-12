#include <stdarg.h>


int kstrlen(char *buf){
	int counter = 0;
	char ch = buf[0];
	while(ch != '\0'){
		counter++;
		ch = buf[counter];
	}
	return counter;
}

int kitoa(int n){
	char string[] = "";
	int rem;
	int i = 0;
	int isNegative = 0;
	if(n < 0){
		isNegative = 1;
	}
	while(n != 0){
		rem = n % 10;
		n /= 10;
		string[i] = rem;
		i++;
	}

	int len = kstrlen(string);
	char res[len] = "";

	if(isNegative == 1){
		res[0] = '-';
		len++;
	}
	for(int j = 1; j < len; j++){
		
	}
}

void kprintf(char *str_literal,...){
	char *vga = (char *)0xB8000;
	int vgap = 0;
	va_list vars;

	for(int i = 0; i < kstrlen(str_literal);i++){
		if(str_literal[i] == '%'){
			va_start(vars);
			switch(str_literal[i + 1]) {
				case('d'):
					int num = va_arg(args, int);
					char res[] = kitoa(num); 
					vga[vgap + 1] = 0x07;
					break;
				case('s'):
					char str[] = va_arg(args, char *);
					for(int j = 0; j < strlen(str); j++;){
						vga[vgap] = str[j];
						vga[vgap + 1] = 0x07;
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
