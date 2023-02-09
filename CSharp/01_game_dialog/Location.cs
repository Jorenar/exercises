using System.Collections.Generic;

class Location
{
    public string Name {
        get; set;
    }
    public List<NonPlayerCharacter> NPCs {
        get; set;
    }

    public Location(string name, (string, NpcDialogPart)[] NPCs)
    {
        this.Name = name;
        this.NPCs = new List<NonPlayerCharacter>();
        foreach (var npc in NPCs)
        {
            this.NPCs.Add(new NonPlayerCharacter(npc.Item1, npc.Item2));
        }
    }
}
