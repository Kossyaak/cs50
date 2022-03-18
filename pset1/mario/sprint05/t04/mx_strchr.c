char *mx_strchr(const char *s, int c) 
{
    for(;*s != '\0';) 
    {
        if (*s == c)
        {
            return (char *)s;
        }
        s++;
    }
    return 0;
}   






