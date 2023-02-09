using System;
using System.Linq;

class Program
{
    static void Main(string[] args)
    {
        Console.Write("N = ");
        var N = Convert.ToInt32(Console.ReadLine());

        /*
         *  var c = from x in Enumerable.Range(1,N)
         *          where x != 5 && x != 9 && (x % 2 == 1 || x % 7 == 0)
         *          select x*x;
         */

        var c = Enumerable.Range(1, N)
                .Where(x => (x != 5 && x != 9 && (x % 2 == 1 || x % 7 == 0)))
                .Select(x => x*x);

        Console.Write(  $"sum = {c.Sum()}\n"
                      + $"count = {c.Count()}\n"
                      + $"1st = {c.First()}\n"
                      + $"last = {c.Last()}\n"
                      + $"3rd = ");
        Console.WriteLine(c.Count() > 2 ? c.ElementAt(2).ToString() : "null");
    }
}
