using System;

class Complex<T> : IComparable, IFormattable where T : IComparable, IFormattable
{
    public T Real { get; set; }
    public T Imaginary { get; set; }

    public Complex()
    {
        this.Real = this.Imaginary = default(T);
    }

    public Complex(T r)
    {
        this.Real = r;
        this.Imaginary = default(T);
    }

    public Complex(T r, T i)
    {
        this.Real = r;
        this.Imaginary = i;
    }

    public static Complex<T> operator -(Complex<T> z)
    {
        dynamic re = z.Real;
        dynamic im = z.Imaginary;
        return new Complex<T>(-re, -im);
    }

    public static Complex<T> operator +(Complex<T> z1, Complex<T> z2)
    {
        dynamic re1 = z1.Real;
        dynamic re2 = z2.Real;
        dynamic im1 = z1.Imaginary;
        dynamic im2 = z2.Imaginary;
        return new Complex<T>(re1 + re2, im1 + im2);
    }

    public static Complex<T> operator -(Complex<T> z1, Complex<T> z2)
    {
        return z1 + (-z2);
    }

    public static Complex<T> operator *(Complex<T> z1, Complex<T> z2)
    {
        dynamic re1 = z1.Real;
        dynamic re2 = z2.Real;
        dynamic im1 = z1.Imaginary;
        dynamic im2 = z2.Imaginary;
        return new Complex<T>(re1*re2 - im1*im2, re1*im1 + re2*im2);
    }

    public string ToString(string format, IFormatProvider formatProvider)
    {
        dynamic Im = Imaginary;
        dynamic Re = Real;

        if (Im == 0) {
            return Real.ToString();
        }

        var oper = "+";

        if (Im < 0) {
            oper = "-";
            Im = -Im;
        }

        if (Im == 1) {
            Im = "";
        }

        var rel = (Re == 0 ? (oper == "-" ? "-" : "") : $"{Re} {oper} ");
        return $"{rel}{Im}i";

    }

    public int CompareTo(Object obj)
    {
        dynamic ob = obj;
        if (this.Real != ob.Real || this.Imaginary != ob.Imaginary)
        {
            throw new Exception("Cannot compare this two complex numbers");
        }
        return 0;
    }
}

/*
class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine(new Complex<int>(2, 0));
        Console.WriteLine(new Complex<int>(-2, 1));
        Console.WriteLine(new Complex<int>(0, -1));
        Console.WriteLine(new Complex<int>(0, -2));
        Console.WriteLine(new Complex<int>(12, 4));
    }
}
*/
