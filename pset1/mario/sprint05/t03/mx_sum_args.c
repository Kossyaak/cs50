#include <stdbool.h>
int mx_atoi(const char *str);
void mx_printint(int n);
bool mx_isdigit(int c);
bool mx_isspace(char c);
void mx_printchar(char c);

int main(int argc, char *argv[])
{

    int args[argc];
    int count = 0;
    int flag = 0; 
    if(argc > 1)
    {  
        for(int i = 0; i < argc; i++)
        {
            for(int j = 0; argv[i][j] != '\0'; j++)
            {
                if(mx_isspace(argv[i][j]) == 1)
                {    
                    break;
                }
                else if(mx_atoi(argv[i]) && argv[i][j + 1] == '\0')
                {
                    args[count] = mx_atoi(argv[i]);
                    count++;
                    flag++;
                    break;
                }
                else if(mx_atoi(argv[i]) && mx_isspace(argv[i][j + 1]) == 1)
                {
                    break;
                }
            } 
        }
        if(flag > 0)
        {
            int sum = 0;
            for(int i = 0; i < count; i++)
            {       
                sum += args[i];   
            }
            mx_printint(sum);
            mx_printchar('\n');
        }
        else
        {
            mx_printint(0);
            mx_printchar('\n');
        }
        
    }
    return 0;
}








