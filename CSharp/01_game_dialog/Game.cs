using System;
using System.Linq;
using System.Collections.Generic;
using System.Text.RegularExpressions;

class Game
{
    List<Location> locations;
    Location currentLoc;
    Hero hero;

    void GenLocations()
    {
        locations = new List<Location>();

        var locs = new[] {
            ("Calimport", new[] {
                ("Akara", Dialogs.Dialog1),
                ("Charsi", Dialogs.Dialog2)
            }),
            ("Neverwinter", new[] {
                ("Deckard", Dialogs.Dialog1),
                ("Cain", Dialogs.Dialog2)
            }),
            ("Silverymoon", new[] {
                ("Gheed", Dialogs.Dialog1),
                ("Kashya", Dialogs.Dialog2)
            }),
            ("Baldur's Gate", new[] {
                ("Warriv", Dialogs.Dialog1),
                ("Drognan", Dialogs.Dialog2)
            }),
        };

        foreach (var loc in locs)
        {
            locations.Add(new Location(loc.Item1, loc.Item2));
        }
    }

    private int ShowLocation(Location loc)
    {
        Console.Write($"You are at {loc.Name}. What do you want to do?\n");

        int i = 1;
        foreach (var npc in loc.NPCs)
        {
            Console.Write($"  [{i++}] Talk with {npc.Name}\n");
        }

        return i;
    }

    private static string AskForHeroName()
    {
        do
        {
            Console.Write("# name (letters, capitalize first): ");
            string name = Console.ReadLine().Trim();
            if (Regex.IsMatch(name, @"^([A-Z][a-z]+ ?)+$")) {
                return name;
            }
            Console.Error.WriteLine("Incorrect name");
        }
        while (true);
    }

    private static EHeroClass AskForHeroClass(string name)
    {
        var foo = Enum.GetValues(typeof (EHeroClass)).Cast<EHeroClass>();

        Console.Write($"# Hello {name}, choose your hero class:\n");

        for (var i = foo.Min(); i <= foo.Max(); ++i)
        {
            Console.Write($"  [{(int)i}] {i.ToString()}\n");
        }

        do
        {
            Console.Write("Choice: ");
            var cl = (EHeroClass)Convert.ToInt32(Console.ReadLine());
            if (cl >= foo.Min() && cl <= foo.Max())
            {
                return cl;
            }

            Console.Error.WriteLine("Incorrect number");
        }
        while (true);
    }

    private static Hero NewHero()
    {
        var name = AskForHeroName();
        var type = AskForHeroClass(name);
        return new Hero(name, type);
    }

    void NewGame()
    {
        Console.Clear();

        hero = NewHero();
        Console.Clear();
        Console.WriteLine("{0} {1} sets off on an adventure",
                          Regex.Replace(hero.Type.ToString(),
                                        "^[a-z]", m => m.Value.ToUpper()),
                          hero.Name);
        GenLocations();
        currentLoc = locations[0];

        Play();
    }

    void TalkTo(NonPlayerCharacter npc, DialogParser parser)
    {
        var dialog = npc.StartTalking();

        while (dialog != null)
        {
            Console.WriteLine(parser.ParseDialog(dialog));

            if (dialog.Responses == null)
            {
                break;
            }

            Console.WriteLine("What's your response?");
            int i = 1;
            foreach (var resp in dialog.Responses)
            {
                string temp = parser.ParseDialog(resp);
                Console.Write($"  [{i++}] {temp}\n");
            }

            do
            {
                Console.Write("Choice: ");
                int opt = Convert.ToInt32(Console.ReadLine());
                if (opt > 0 && opt < i) {
                    dialog = dialog.Responses[opt-1].Response;
                    break;
                }

                Console.Error.WriteLine("Incorrect number");
            }
            while (true);
        }
    }

    void Play()
    {
        var i = ShowLocation(currentLoc);
        int opt = 0;
        do
        {
            Console.Write("Choice: ");
            opt = Convert.ToInt32(Console.ReadLine());
            if (opt > 0 && opt < i) {
                break;
            }

            Console.Error.WriteLine("Incorrect number");
        }
        while (true);

        TalkTo(currentLoc.NPCs[opt-1], new DialogParser(hero));
    }

    public void Run()
    {
        Console.Clear();
        Console.Write(""
                      + "Welcome in game\n"
                      + "  [1] Start a new game\n"
                      + "  [X] End game\n");
        while (true)
        {
            Console.Write("Choice: ");
            var opt = Console.ReadLine().Trim();
            switch (opt)
            {
                case "1":
                    NewGame();
                    return;
                case "X":
                    return;
                default:
                    Console.Error.WriteLine("Wrong command number, please try again!");
                    break;
            }
        }
    }
}

// vim: fdl=1
