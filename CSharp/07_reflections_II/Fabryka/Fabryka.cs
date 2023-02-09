using System;
using System.IO;
using System.Linq;
using System.Reflection;

class Program
{
    static void Main(string[] args)
    {
        Console.OutputEncoding = System.Text.Encoding.Default;

        Assembly.LoadFrom(
            Path.Combine(Path.GetDirectoryName(
                             Assembly.GetEntryAssembly().Location),
                         "../Common/Common.dll"));

        foreach (var arg in args)
        {
            var temp = arg.Split(';');
            var dll = temp[0];
            var title = temp[1];

            var assem = Assembly.LoadFrom(Path.GetFullPath(dll));
            var proc = assem.GetTypes()
                       .Where(t => (t.GetInterface("Common.IZlecenie") != null))
                       .First();

            var o = Activator.CreateInstance(proc);
            proc.GetProperty("Title").SetValue(o, title, null);

            proc.GetMethod("Process").Invoke(o, null);
            Console.WriteLine("");
        }

    }
}
