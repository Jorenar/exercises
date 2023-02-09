using System;
using NUnit.Framework;

[TestFixture]
public class ConcatExTests
{
    [TestCase]
    public void firstNull()
    {

        Assert.Throws<NullReferenceException>(() => Concatenator.Concat2(null, "abc"));
    }

    [TestCase]
    public void secNull()
    {
        Assert.Throws<NullReferenceException>(() => Concatenator.Concat2("abc", null));
    }

    [TestCase]
    public void bothNull()
    {
        Assert.Throws<NullReferenceException>(() => Concatenator.Concat2(null, null));
    }

    [TestCase]
    public void NotNull()
    {
        Assert.AreEqual("abcd", Concatenator.Concat2("ab", "cd"));
    }

    [TestCase]
    public void NotNull2()
    {
        Assert.AreEqual("ab cd", Concatenator.Concat2("ab", Concatenator.Concat2(" ", "cd")));
    }

    [TestCase]
    public void NotNullFirstEmpty()
    {
        Assert.AreEqual(" cd", Concatenator.Concat2("", " cd"));
    }
}
