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

	for(int i = 0; i < kstrlen(str_literal);i++){
		if(str_literal[i] == '%'){
			va_start(vars,str_literal);
			switch(str_literal[i + 1]) {
				case('d'):
					int decn = va_arg(vars, int);
					char *dec = kitoa(decn,10);
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
				case('x'):
					int hexn = va_arg(vars, int);
                                        char *hex = kitoa(hexn,16);
                                        write(1,hex,kstrlen(hex));
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
	kprintf("hex: %x\n", 0x100);
	return 0;
	
}
