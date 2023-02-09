double power(double x, unsigned int n)
{
    return n > 0 ? x * power(x, --n) : 1;
}
