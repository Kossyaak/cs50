double mx_pow_rec(double n, unsigned int pow);
double mx_pow_rec(double n, unsigned int pow)
{
    double temp = n;
    if(pow == 0)
    {
        return 1;
    }
    else if(pow > 0)
    {
        return n * mx_pow_rec(n, pow - 1);
    }
}





