int mx_factorial_iter(int n);
int mx_factorial_iter(int n)
{
    if(n > 0)
    {
        long fac = 1;
        for(int i = 1; i <= n; i++)
        {
            fac *= i;  
        }
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









