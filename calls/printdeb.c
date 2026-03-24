#include <stdarg.h>
#include <unistd.h>

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
	if(n == 0){
		res[i] = '0';
		res[i++];
		return res;	
	}
	if(base == 10){
		if(isNegative == 1){
                                n * -1;
                }
		while(n != 0){
			rem = n % 10;
			n /= 10;
			string[i] = rem + '0';
			i++;
		}
	}
	else if(base == 16){
		if(isNegative == 1){
			n * -0x1;
		}
		while(n != 0){
                        rem = n % 16;
                        n /= 16;
                        string[i] = (rem-10) + 'a';
                        i++;
                }
	
	}

	int len = kstrlen(string);
	
	if(base == 10){
		if(isNegative == 1){
			string[i++] = '-';
			for(int j = 0; j < len; j++){
                		res[j] = string[len - j - 1]; 
        		}
		}
		else{
			for(int j = 0; j < len; j++){
				res[j] = string[len - j - 1];
			}
		}
	}
	else if(base == 16){
		res[0] = '0';
		res[1] = 'x';
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
			va_start(vars,str_literal);
			switch(str_literal[i + 1]) {
				case('d'):
					int num = va_arg(vars, int);
					char *dec = kitoa(num,10);
				        write(1,dec,kstrlen(dec));
					i++;
					break;
				case('s'):
					char *str = va_arg(vars, char *);
					write(1,str,kstrlen(str));
					i++;
					break;
				case('c'):
					char *c = va_arg(vars, char *);
					write(1,c, 1);
					i++;
					break;

			}
		}
		else{
			char l[1] = {str_literal[i]};
			write(1,l,1);
		}
	}
}

int main(void){
	kprintf("hello world %d\n", 45);
	kprintf("hi %s\n", "red");
	kprintf("negative: %d\n", -54);
	kprintf("hex: %x\n", 200);
	return 0;
	
}
