using System;
using System.Linq;
using System.Collections.Generic;

using static System.String; // just to fit the one line with under 80 chars...

class Program
{
    static void Main(string[] args)
    {
        string input;
        var cities = new List<string>();

        while ((input = Console.ReadLine()) != "X")
        {
            cities.Add(input);
        }

        var c2 = cities
                 .OrderBy(x => x)
                 .GroupBy(x => x[0])
                 .ToDictionary(x => x.Key, x => x);

        while (!string.IsNullOrEmpty(input = Console.ReadLine()))
        {
            char k = input[0];
            Console.WriteLine(c2.ContainsKey(k) ? Join(", ", c2[k]) : "PUSTE");
        }
    }
}
