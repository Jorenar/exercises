using NUnit.Framework;

[TestFixture]
class Anagram
{
    // taken from linked webpage
    [TestCase("",                "",                true)]
    [TestCase("Dictionary",      "Indicatory",      true)]
    [TestCase("Schoolmaster",    "The classroom",   true)]
    [TestCase("Listen",          "Silent",          true)]
    [TestCase("Evangelist",      "Evil's Agent",    true)]
    [TestCase("Astronomers",     "Moon starers",    true)]
    [TestCase("t3st t@ki s0bie", "t3st tki s0bie",  true)]
    [TestCase("Clint Eastwood",  "Old West Action", true)]
    [TestCase("Clint@Eastwood",  "Old West Action", true)]
    // thought up on the spot
    [TestCase("Clint E@stwood",  "Old West Action", false)]
    [TestCase("NYC",             "xyz",             false)]
    [TestCase("reduntant",       "redemption",      false)]
    [TestCase("home",            "ome",             false)]
    [TestCase("ome",             "home",            false)]
    // e-errors? in anagram checker?
    public void Test(string word1, string word2, bool result)
    {
        IAnagramChecker checker = new AnagramChecker();
        Assert.AreEqual(result, checker.IsAnagram(word1, word2));
    }
}
