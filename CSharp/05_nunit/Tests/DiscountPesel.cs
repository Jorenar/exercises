using System;
using NUnit.Framework;

[TestFixture]
public class DiscountPesel
{
    [TestCase("12102525765")]
    [TestCase("40092384613")]
    [TestCase("32100538686")]
    [TestCase("26100285877")]
    [TestCase("36121695854")]
    [TestCase("42010618851")]
    [TestCase("26060312743")]
    [TestCase("22051218476")]
    [TestCase("02072828467")]
    [TestCase("38091342327")]
    public void SurelyOver65(string pesel)
    {
        IDiscountFromPeselComputer d = new DiscountFromPeselComputer();
        Assert.AreEqual(true, d.HasDiscount(pesel));
    }

    [TestCase("12902525765")]
    [TestCase("40892384613")]
    [TestCase("32900538686")]
    [TestCase("26900285877")]
    [TestCase("36921695854")]
    [TestCase("42810618851")]
    [TestCase("26860312743")]
    [TestCase("22851218476")]
    [TestCase("02872828467")]
    [TestCase("38891342327")]
    public void Over100(string pesel)
    {
        IDiscountFromPeselComputer d = new DiscountFromPeselComputer();
        Assert.AreEqual(true, d.HasDiscount(pesel));
    }

    [TestCase("12702525765")]
    [TestCase("40692384613")]
    [TestCase("32700538686")]
    [TestCase("26700285877")]
    [TestCase("36721695854")]
    [TestCase("42610618851")]
    [TestCase("26660312743")]
    [TestCase("22651218476")]
    [TestCase("02672828467")]
    [TestCase("38691342327")]
    public void BornAfter2200(string pesel)
    {
        IDiscountFromPeselComputer d = new DiscountFromPeselComputer();
        Assert.AreEqual(true, d.HasDiscount(pesel));
    }

    [TestCase(5, true)]
    [TestCase(17, true)]
    [TestCase(18, false)]
    [TestCase(19, false)]
    [TestCase(20, false)]
    [TestCase(40, false)]
    [TestCase(64, false)]
    [TestCase(65, false)]
    [TestCase(66, true)]
    public void TestAges(int age, bool result)
    {
        var year = DateTime.Now.Year - age;
        var month = DateTime.Now.Month + (year >= 2000 ? 20 : 0);
        var day = DateTime.Now.Day;

        var pesel = year.ToString().Substring(2,2)
                    + month.ToString("00")
                    + day.ToString("00")
                    + "00000";

        IDiscountFromPeselComputer d = new DiscountFromPeselComputer();
        Assert.AreEqual(result, d.HasDiscount(pesel));
    }
}

// vim: fdl=1
