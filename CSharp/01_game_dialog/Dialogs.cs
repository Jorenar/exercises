using NpcD = NpcDialogPart;
using HD = HeroDialogPart;

class Dialogs
{
    public static NpcD Dialog1 = new NpcD(
        "Hi, could you help me get to the next town?", new[] {
            new HD("Yeah, with pleasure",
                new NpcD("Thank you! As a reward I'll give you 100 gold", new[] {
                        new HD("I'll notify you when I'm ready", null),
                        new HD("100 gold is not enough!",
                            new NpcD("I am very poor, I do not have more money", new[] {
                                    new HD("OK, my loss, 100 gold will do",
                                        new NpcD("Thank you", null)
                                    ),
                                    new HD("Then deal with it yourself", null)
                                }
                            )
                        )
                    }
                )
            ),
            new HD("No, I'll not, bye", null)
        }
    );

    public static NpcD Dialog2 = new NpcD(
        "Oi! Aren't you the faumous dragon slayer #HERONAME#?!", new[] {
            new HD("Yes, I am #HERONAME#",
                new NpcD("WOW! It's an honour to meet you!", null)
            ),
            new HD("No.", null)
        }
    );
}
