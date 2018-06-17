
#include <kimia/lib/string.h>

/**
 * int_to_str
 * get a integer var and convert it to a string and fill an array of chars
 */
void int_to_str(int32 num,uint8 ret[]){
	//if num is zero(0)
	if(num==0){
		ret[0]='0';
		return;
	}
	Boolean is_neg=false;
	uint16 ind=0;
	//is negative number
	if(num<0){
		is_neg=true;
		num*=-1;
	}
	while(num>0){
		uint8 r=num%10;
		num/=10;		
		ret[ind++]=r+'0';
	}
	//add negative
	if(is_neg)
		ret[ind++]='-';
	//finish array	
	ret[ind]='\0';
	//reverse array 
	str_reverse(ret);
	
}
/**
 * str_reverse
 * reverse a string and return a string
 */
void str_reverse(uint8 s[]){
	uint32 len=str_len(s);
	for(uint32 i=0;i<len/2;i++){
		uint8 tmp=s[i];
		s[i]=s[len-i-1];
		s[len-i-1]=tmp;
	}
}
/**
 * str_len
 * calculate length of a string and return an integer
 */
uint32 str_len(String str){
	uint32 len=0;
	for(;;){
		if(str[len]==0){
			break;
		}
		len++;
	}
	return len;
}
/**
 * str_compare
 * compare two strings together and return true or false
 */
uint8  str_compare(String s1,String s2){
	uint32 len1=str_len(s1);
	if(len1!=str_len(s2))
		return 1;
	for(;;){
		len1--;
		if(s1[len1]!=s2[len1])
			return 2;
		if(len1==0)
			break;
	}

	return 0;
}

void append_char(String buf,uint8 ch){
	//uint8 ret[10];*buf=(String)&ret;
	/**buf=(String)malloc(5);
	buf[1]=ch;
	buf[2]='@';
	buf[3]='|';*/
}

/**
 * 	int strcpy(char *dst,const char *src)
 * 	void strcat(void *dest,const void *src)
 * 
 */
