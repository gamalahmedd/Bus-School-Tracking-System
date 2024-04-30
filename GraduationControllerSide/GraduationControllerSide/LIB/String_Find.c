#include "String_Find.h"
#include <string.h>

unsigned char find_string(unsigned char *string, unsigned char* string_find)
{
	unsigned int matched = 0;
	unsigned int index_string = 0;
	unsigned int length_of_string = 0;
	unsigned int length_of_string_find = 0;

	length_of_string_find = strlen(string_find);
	length_of_string = strlen(string);

	if(length_of_string_find > length_of_string)
	{
		return 0;
	}
	else
	{
		for(index_string = 0; index_string < length_of_string; index_string++)
		{
			if(string[index_string] == string_find[matched])
			{
				matched++;
				if(length_of_string_find == matched)
					return 1;
			}
			else
			{
				matched = 0;
			}
		}
		return 0;
	}
}

void find_get_string(unsigned char *string, unsigned char* from, unsigned char _from, unsigned char* to, unsigned char _to, unsigned char *get_text)
{
	unsigned char *p1;
	unsigned char *p2;
	unsigned char length = 0;

	p1 = strstr(string, from) + _from;
	p2 = strstr(p1, to) + _to;
	length = p2 - p1;

	strncpy(get_text, p1, length);
	get_text[length] = '\0';
}
