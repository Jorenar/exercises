public interface IDialogPart
{
    string GetDialog();
}

public class HeroDialogPart : IDialogPart
{
    private string text;

    public NpcDialogPart Response {
        get; set;
    }

    public HeroDialogPart(string text, NpcDialogPart response)
    {
        this.text = text;
        this.Response = response;
    }

    public string GetDialog()
    {
        return text;
    }
}

public class NpcDialogPart : IDialogPart
{
    private string text;

    public HeroDialogPart[] Responses {
        get; set;
    }

    public NpcDialogPart(string text, HeroDialogPart[] responses)
    {
        this.text = text;
        this.Responses = responses;
    }

    public string GetDialog()
    {
        return text;
    }
}
