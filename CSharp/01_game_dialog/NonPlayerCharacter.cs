public class NonPlayerCharacter
{
    private NpcDialogPart dialog;
    public string Name {
        get; set;
    }

    public NonPlayerCharacter(string name, NpcDialogPart dialog)
    {
        this.Name = name;
        this.dialog = dialog;
    }

    public NpcDialogPart StartTalking()
    {
        return dialog;
    }
}
