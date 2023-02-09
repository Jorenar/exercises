using System;
using System.Linq;

class Program
{
    static void Main(string[] args)
    {
        Console.Write("N = ");
        var N = Convert.ToInt32(Console.ReadLine());
        Console.Write("M = ");
        var M = Convert.ToInt32(Console.ReadLine());
        Console.Write('\n');

        Random rnd = new Random();

        var c = Enumerable.Range(1, N)
                .Select(x => Enumerable.Range(1, M)
                             .Select(a => rnd.Next(-100, 100))
                .ToList());

        Console.WriteLine($"matrix [{N} x {M}]:");

        Console.WriteLine("  _  " + "_".PadLeft(M * 4));
        var sum = 0;
        c.SelectMany(x => {
            Console.Write(" |  ");
            x.Select(a => {
                Console.Write(a.ToString().PadLeft(3) + " ");
                sum += a;
                return a;
            }).ToList();
            Console.Write(" |\n");
            return x;
        }).ToList();
        Console.WriteLine("  ‾  " + "‾".PadLeft(M * 4));

        Console.WriteLine($"\nsum = {sum}");
    }
}
