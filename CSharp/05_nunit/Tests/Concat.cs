using NUnit.Framework;

[TestFixture]
public class ConcatTests
{
    [TestCase("ab", null, ExpectedResult = null)]
    [TestCase(null, "cd", ExpectedResult = null)]
    [TestCase(null, null, ExpectedResult = null)]
    [TestCase("ab", "cd", ExpectedResult = "abcd")]
    [TestCase("",   "cd", ExpectedResult = "cd")]
    [TestCase(" ",  "cd", ExpectedResult = " cd")]
    [TestCase("ab", " ",  ExpectedResult = "ab ")]
    [TestCase("ab", " d", ExpectedResult = "ab d")]
    public string Test(string w1, string w2)
    {
        return Concatenator.Concat(w1, w2);
    }
}
