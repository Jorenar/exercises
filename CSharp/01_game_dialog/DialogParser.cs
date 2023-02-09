using System.Collections.Generic;

public class DialogParser
{
    Dictionary<string, string> variables;

    public DialogParser(Hero hero)
    {
        variables = new Dictionary<string, string>();
        variables.Add("#HERONAME#", hero.Name);
    }

    public string ParseDialog(IDialogPart dialog)
    {
        string result = dialog.GetDialog();

        foreach (var v in variables) {
            result = result.Replace(v.Key, v.Value);
        }

        return result;
    }
}
