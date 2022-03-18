void mx_printchar(char c);
void mx_printint(int n);
void mx_printint(int n){
    int size = 0;  int tmp = n;
    for(;tmp > 0;){
        tmp = tmp / 10;
        size++;
        }
    char str[size];
    for(int i = 0; i < size; i++){
        int j;
        j = n % 10;
        str[i] = j + 48;
        n = n / 10;
    }
    for(int i = size -1; i != -1; i--){
        mx_printchar(str[i]);
    }
}











