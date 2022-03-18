void mx_printchar(char c);
void mx_printstr(const char *s);
char *mx_strchr(const char *s, int c);
int mx_strlen(const char *s);


int main (int argc, char *argv[])
{
    argc = 0;
    int slashes_pos = 0;
    int i = 0;
    char *c = argv[0];
    while(i < mx_strlen(c))
    {
        if(c[i] == '/')
        {
            slashes_pos = i;
        }
        i++;
    }
    slashes_pos++;
    for(int i = slashes_pos; c[i] != '\0'; i++)
    {
        mx_printchar(c[i]);
    }
    mx_printchar('\n');

}


