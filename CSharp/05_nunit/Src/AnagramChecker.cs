using System;
using System.Linq;
using System.Text.RegularExpressions;

class AnagramChecker : IAnagramChecker
{
    private readonly Regex RE_alfanum = new Regex("[^a-zA-Z0-9]");

    public bool IsAnagram(string word1, string word2)
    {
        word1 = RE_alfanum.Replace(word1.ToLower(), String.Empty);
        word2 = RE_alfanum.Replace(word2.ToLower(), String.Empty);

        word1 = String.Concat(word1.OrderBy(c => c));
        word2 = String.Concat(word2.OrderBy(c => c));

        return word1 == word2;
    }
}
