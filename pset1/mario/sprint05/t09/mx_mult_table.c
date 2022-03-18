#include <stdbool.h>
void mx_printchar(char c);
void mx_printint(int n);
int mx_atoi(const char *str);
bool mx_isdigit(int c);
bool mx_isspace(char c);
int mx_strlen(const char *s);

int main(int argc, char *argv[])
{
    int is_num = mx_atoi(argv[1]);
    int is_num1 = mx_atoi(argv[2]);
    int temp = 0;
    if(argc == 3 || is_num == 1 || is_num1 == 1)
    {
        if(is_num < 9 && is_num > 1 && is_num1 < 9 && is_num1 > 1)
        {
            if(is_num > is_num1)
            {
                temp = is_num;
                is_num = is_num1;
                is_num1 = temp;
            }
            for(int i = is_num; i <= is_num1; i++)
            {
                for(int j = is_num; j <= is_num1; j++)
                {
                    mx_printint(i * j);
                    if(j < is_num1)
                    {
                        mx_printchar('\t');
                    }
                }mx_printchar('\n');
            }
        }
        else
        {
            return 0;
        }       
    }
    else
    {
        return 0;
    }
}




