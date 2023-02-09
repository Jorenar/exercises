public class zleceniePiwo : Common.IZlecenie
{
    string[] recipe = {
        "Zacieranie w okolo 66 C",
        "Chmielenie:",
        "  Citra 15 g, Amarillo 15 g, Simcoe 15 g na 20 min",
        "  Citra 15 g, Amarillo 15 g, Simcoe 15 g na 5 min",
        "  Citra 15 g, Amarillo 15 g, Simcoe 15 g po wylaczeniu palnika",
        "  Citra 15 g, Amarillo 15 g, Simcoe 15 g hop stand w 85 C",
        "  Drozdze US-05",
        "Fermentacja:",
        "  3 tygodnie w temperaturze 19-20 C",
        "Na ostanie 4 dni chmielenie na zimno",
        "  Citra 30 g, Amarillo 30, Simcoe 30 g",
    };

    public string Title {
        get; set;
    }

    public void Process()
    {
        System.Console.WriteLine("# " + Title);
        foreach (string line in recipe)
        {
            System.Console.WriteLine("    " + line);
            System.Threading.Thread.Sleep(2000);
        }
    }
}
