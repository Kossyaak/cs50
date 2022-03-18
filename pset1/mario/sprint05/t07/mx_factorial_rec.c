int mx_factorial_iter(int n);
int mx_factorial_rec(int n)
{
    if(n > 0)
    {
        long fac = 1;
        fac = mx_factorial_rec(n - 1) * n;
        if (fac > 2147483647)
        {
            return 0;
        }
        return fac; 
    }
    else if(n == 0)
    {
        return 1;
    }
    else
    {
        return 0;        
    }
    
}












