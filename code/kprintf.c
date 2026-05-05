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

void reverse(char str[], int length)
{
    	int start = 0;
    	int end = length - 1;
    	while (start < end) {
        	char temp = str[start];
        	str[start] = str[end];
        	str[end] = temp;
        	end--;
        	start++;
    	}
}

char * kitoa(int num, int base){
	int i = 0;
    	int isNegative = 0;
    	
	if (num == 0) {
        	res[i++] = '0';
        	res[i] = '\0';
        	return res;
    	}

    	if (num < 0 && base == 10) {
        	isNegative = 1;
        	num = -num;
    	}
    	while (num != 0) {
        	int rem = num % base;
        	res[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        	num = num / base;
    	}
    	if (isNegative == 1)
        	res[i++] = '-';

   		res[i] = '\0';

    	reverse(res, i);

    	return res;
}

void kprintf(char *str_literal,...){
	char *vga = (char *)0xB8000;
	int vgap = 0;
	va_list vars;
	va_start(vars, str_literal);
	for(int i = 0; i < kstrlen(str_literal);i++){
		if(str_literal[i] == '%'){
			switch(str_literal[i + 1]) {
				case('d'):
					int num = va_arg(vars, int);
					char *res = kitoa(num,10);
				        for(int j = 0; j < kstrlen(res);j++){
						vga[vgap + j * 2] = res[j];	
						vga[vgap + 1 + j * 2] = 0x07;
					}
					i++;
					vgap += kstrlen(res) * 2;
					continue;
				case('s'):
					char *str = va_arg(vars, char *);
					for(int j = 0; j < kstrlen(str); j++){
						vga[vgap + j * 2] = str[j];
						vga[vgap + 1 + j * 2] = 0x07;
					}
					i++;
					vgap += kstrlen(str) * 2;
					continue;
				case('c'):
					vga[vgap] = (char)va_arg(vars, int);
					vga[vgap + 1] = 0x07;
					i++;
					vgap += 2;
					continue;
				case('x'):
					int hex = va_arg(vars, int);
                                        char *resx = kitoa(hex,16);
                                        for(int j = 0; j < kstrlen(resx);j++){
                                                vga[vgap + j * 2] = resx[j];
                                                vga[vgap + 1 + j * 2] = 0x07;
                                        }
					i++;
					vgap += kstrlen(resx) * 2;
					continue;

			}


		}
		else{
			vga[vgap] = str_literal[i];
			vga[vgap + 1] = 0x07;
			vgap += 2;
		}
	}
}

int kernel_main(void){
	kprintf("hello world %d", 123);
	while(1);
	return 0;
}
