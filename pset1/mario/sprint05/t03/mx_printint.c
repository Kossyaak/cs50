void mx_printchar(char c);
void mx_printint(int n) 
{
    int buff = 0;
    int count = 0;
    if (n == 0) {
        mx_printchar('0');
        return;
    }
    if (n < 0) {
        n *= -1;
        mx_printchar('-');
    }
    buff = n;
    for (int i = 0; buff > 0; i++) {
        buff /= 10;
        count++;
    }
    buff = 0;
    char x[count];
    for (int i = count-1; i >= 0; i--) {
        buff = n % 10;
        x[i] = buff+48;
        n /= 10;
    }
    for (int i = 0; i < count; i++) {
        mx_printchar(x[i]);
    }
}






