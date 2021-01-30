#include <stdio.h>
#include <stdlib.h>

#include <stddef.h>
#include <string.h>

char* ReverseSentence(char* src);
void Mirror(char* str_start, char* str_end);


int main()
{
    char string1[] = "Have a nice day";
    ReverseSentence(string1);
    printf("the new string is \n%s\n", string1);

    return (0);
}

char* ReverseSentence(char* src)
{
    char* str_ptr1 = src;
    char* str_ptr2 = src;
    while (*str_ptr2 != '\0')
    {
        if (*str_ptr2 == ' ') 
        {
            Mirror(str_ptr1, str_ptr2-1);
            str_ptr1 = str_ptr2 +1;            
        }            
        
        ++str_ptr2;
    }
    Mirror(str_ptr1,str_ptr2 - 1);
    Mirror(src,str_ptr2 - 1);
    return(src);
}

void Mirror(char* str_start, char* str_end)
{
    char temp_char = 0;
    char *str_end_ptr = str_end;
    while (str_start < str_end_ptr)
    {
     temp_char = *str_start;
     *str_start = *str_end_ptr;   
     *str_end_ptr = temp_char;   
     ++str_start;
     --str_end_ptr;
    }
}