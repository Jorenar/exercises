using System;

// It already works, because operator overloading

using C = Complex<int>;

class Program
{
    static void Main(string[] args)
    {
        Matrix<C> m1 = new Matrix<C>(new[,] {
            { new C(1,3), new C(3,2) },
            { new C(4,6), new C(3,2) },
        });
        Matrix<C> m2 = new Matrix<C>(new[,] {
            { new C(1,3), new C(3,2) },
            { new C(4,3), new C(3,2) },
        });

        (m1 + m2).Print();

        Console.WriteLine();
        var m3 = m1 * m2;
        m3.Print();
    }
}
