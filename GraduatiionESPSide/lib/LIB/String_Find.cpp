#include "String_Find.h"

char find_string(const char *string, const char* string_find)
{
	int matched = 0;
	int index_string = 0;
	int length_of_string = 0;
	int length_of_string_find = 0;

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


void find_get_string(const char *string, const char* from, const char _from, const char* to, const char _to, char *get_text)
{
	char *p1;
	char *p2;
	char length = 0;

	p1 = strstr(string, from) + _from;
	p2 = strstr(p1, to) + _to;
	length = p2 - p1;

	strncpy(get_text, p1, length);
	get_text[length] = '\0';
}
