using System;
using System.Linq;
using System.Reflection;

class Program
{
    static void Analize(Type cl, string ind0 = "  ")
    {
        string ind1 = "  " + ind0;
        string ind2 = "  " + ind1;

        var flagPublic = BindingFlags.Instance | BindingFlags.Public;
        var flagNonPublic = BindingFlags.Instance | BindingFlags.NonPublic;
        var flagDeclOnly = BindingFlags.Instance | BindingFlags.DeclaredOnly;
        var flagAll = flagPublic | flagNonPublic | flagDeclOnly;

        var A = new[] { ("", flagPublic), ("Non ", flagNonPublic) };

        // Fields {{{
        if (cl.GetFields(flagAll).Where(f => !f.Name.Contains("__BackingField")).Count() == 0)
        {
            goto skipFields;
        }
        Console.WriteLine(ind0 + "- Fields:");
        foreach (var a in A)
        {
            var fields = cl.GetFields(a.Item2).Where(f => !f.Name.Contains("__BackingField"));
            if (fields.Count() == 0) { continue; }

            Console.WriteLine(ind1 + "- {0}Public:", a.Item1);
            foreach (var field in fields)
            {
                Console.WriteLine(ind2 + "- Name: {0}", field.Name);
                Console.WriteLine(ind2 + "  Type: {0}", field.FieldType);
            }
        }
        skipFields :; // }}}

        // Properties {{{
        if (cl.GetProperties(flagAll).Length == 0)
        {
            goto skipProperties;
        }
        Console.WriteLine(ind0 + "- Properties:");
        foreach (var a in A)
        {
            var properties = cl.GetProperties(a.Item2);
            if (properties.Count() == 0) { continue; }

            Console.WriteLine(ind1 + "- {0}Public:", a.Item1);
            foreach (var prop in properties)
            {
                Console.WriteLine(ind2 + "- Name:  {0}", prop.Name);
                Console.WriteLine(ind2 + "  Type:  {0}", prop.PropertyType);
                Console.WriteLine(ind2 + "  Read:  {0}", prop.CanRead);
                Console.WriteLine(ind2 + "  Write: {0}", prop.CanWrite);
            }
        }
        skipProperties :; // }}}

        // Methods {{{
        if (cl.GetMethods(flagAll).Where(m => !m.IsSpecialName).Count() == 0)
        {
            goto skipMethods;
        }
        Console.WriteLine(ind0 + "- Methods:");
        foreach (var a in A)
        {
            var methods = cl.GetMethods(a.Item2 | flagDeclOnly).Where(m => !m.IsSpecialName);
            if (methods.Count() == 0) { continue; }

            Console.WriteLine(ind1 + "- {0}Public:", a.Item1);
            foreach (MethodInfo method in methods)
            {
                Console.WriteLine(ind2 + "- Name:    {0}", method.Name);
                Console.WriteLine(ind2 + "  Returns: {0}", method.ReturnType);
            }
        }
        skipMethods :; // }}}

        // Nested types {{{
        if (cl.GetNestedTypes(flagAll).Length == 0)
        {
            goto skipNestedTypes;
        }
        Console.WriteLine(ind0 + "- Nested types:");
        foreach (var a in A)
        {
            var nested = cl.GetNestedTypes(a.Item2);
            if (nested.Length == 0) { continue; }

            Console.WriteLine(ind1 + "- {0}Public:", a.Item1);
            foreach (Type subCl in nested)
            {
                Console.WriteLine(ind2 + "- Name: {0}", subCl.Name);

                if (subCl.IsClass)
                {
                    Console.WriteLine(ind2 + "  Class:");
                    Analize(subCl, ind2 + "  ");
                }
                else if (subCl.IsEnum)
                {
                    Console.WriteLine(ind2 + "  Enum:");
                    Console.WriteLine(ind2 + "  - Type: {0}", subCl.GetFields()[0].FieldType);
                    Console.WriteLine(ind2 + "  - Values:");
                    foreach (var val in Enum.GetValues(subCl))
                    {
                        Console.WriteLine(ind2 + "    - {0} = {1}", val, Convert.ToDecimal(val));
                    }
                }

            }
        }
        skipNestedTypes :; // }}}
    }

    static void SetProperties(Type cl, string ind0 = "")
    {
        Customer myObject = new Customer("Onamae");

        Console.WriteLine("Values of properties: ");
        Console.WriteLine("  - Name = {0}", cl.GetProperty("Name").GetValue(myObject));
        Console.WriteLine("  - Address = {0}", cl.GetProperty("Address").GetValue(myObject));
        Console.WriteLine("  - SomeValue = {0}", cl.GetProperty("SomeValue").GetValue(myObject));

        try
        {
            Console.WriteLine("\nSetting properties...");
            cl.GetProperty("Address").SetValue(myObject, "Uliczna 24; Prochowo");
            cl.GetProperty("SomeValue").SetValue(myObject, 503334103);
            cl.GetProperty("Name").SetValue(myObject, "Nkombo");
        }
        catch (ArgumentException e)
        {
            Console.WriteLine("  " + e.Message);
        }

        Console.WriteLine("\nValues of properties: ");
        Console.WriteLine("  - Name = {0}", cl.GetProperty("Name").GetValue(myObject));
        Console.WriteLine("  - Address = {0}", cl.GetProperty("Address").GetValue(myObject));
        Console.WriteLine("  - SomeValue = {0}", cl.GetProperty("SomeValue").GetValue(myObject));
    }

    static void Main(string[] args)
    {
        Console.WriteLine("# Analyzing class `Customer`\n");
        Analize(typeof (Customer), " ");

        Console.WriteLine("\n--------------------------------------------\n");

        Console.WriteLine("# Setting properties via `.GetProperty()`\n");
        SetProperties(typeof (Customer));
    }
}

// vim: fdl=1
