void mx_printchar(char c);
void mx_printstr(const char *s);
int mx_strlen(const char *s);
int mx_strcmp(const char*s1, const char*s2);
int main (int argc, char *argv[])
{
    if(argc > 1)
    {
        
        for(int i = 1; i < argc; i++)
        {
            for(int j = i; j < argc; j++)
            {
                int mx = mx_strcmp(argv[j - 1], argv[j]);
                if(mx > 0)
                {
                    char *buf = argv[j -1];
                    argv[j -1] = argv[j];
                    argv[j] = buf;
                } 
            }
        }
        for(int i = 0; i < argc; i++)
        {
            mx_printstr(argv[i]);
            mx_printchar('\n');
        } 
    }
}












