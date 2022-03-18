#include <stdbool.h>
bool mx_isdigit(int c);
bool mx_isspace(char c);
int mx_atoi(const char *str) {
    int sign = 0;
    int plus = 0;
    int digit = 0;
    for (unsigned int i = 0; str[i]; ++i) {
        if (!mx_isspace(str[i])) {
            if (mx_isdigit(str[i])) {
                digit = digit * 10 + (str[i] - '0');
            }
            else if (mx_isspace(str[i + 1]) && str[i] == '-') {
                return 0;
            }
            else {
                if (str[i] == '-') {
                    if (!str[i + 1]) {
                        return 0;
                    }
                    else if (sign == 0 && plus == 0) {
                        sign = 1;
                    }
                    else {
                        return 0;
                    }
                }
                else if (str[i] == '+') {
                    if (!str[i + 1]) {
                        return 0;
                    }
                    else if (plus == 0 && sign == 0) {
                        plus = 1;
                    }
                    else {
                        return 0;
                    }
                }
                else {
                    return 0;
                }
            }
        }
    }
    if (sign == 1) {
       return -digit;
    }
    else {
        return digit;
    }
}



