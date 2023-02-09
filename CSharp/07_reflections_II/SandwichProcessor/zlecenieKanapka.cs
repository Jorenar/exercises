public class zlecenieKanapka : Common.IZlecenie
{
    string[] recipe = {
        "Krojenie chleba",
        "Smarowanie maslem",
        "Polozenie szynki",
        "Zlozenie kanapki",
        "Zawiniecie w papier",
        "Wpakowanie do plecaka",
        "Wyjscie na trening",
        "Trening",
        "Powrot do domu",
        "Polozenie plecaka przy kaloryferze",
        "Reakcje biologiczne",
        "Reakcje chemiczne",
        "Reakcje radioaktywne",
        "Wydzielanie ciepla",
        "Utylizacja",
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
            System.Threading.Thread.Sleep(1000);
        }
    }
}
