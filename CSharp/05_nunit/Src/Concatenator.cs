static class Concatenator
{
    public static string Concat(string w1, string w2)
    {
        if (w1 == null || w2 == null)
        {
            return null;
        }

        return w1 + w2;
    }

    public static string Concat2(string w1, string w2)
    {
        if (w1 == null || w2 == null)
        {
            throw new System.NullReferenceException("");
        }

        return w1 + w2;
    }
}
