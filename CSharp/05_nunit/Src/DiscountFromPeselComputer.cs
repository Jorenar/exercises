using System;
using System.Collections.Generic;

public class InvalidPeselException : Exception
{
    public InvalidPeselException(string message) :
        base(message)
    {}
}

public class DiscountFromPeselComputer : IDiscountFromPeselComputer
{
    public bool HasDiscount(string pesel)
    {
        var y = Int32.Parse(pesel.Substring(0, 2));
        var m = Int32.Parse(pesel.Substring(2, 2));
        var d = Int32.Parse(pesel.Substring(4, 2));

        if (m >= 01 && m <= 12)
        {
            y += 1900;
        }
        else if (m >= 81 && m <= 92)
        {
            m -= 80;
            y += 1800;
        }
        else if (m >= 21 && m <= 32)
        {
            m -= 20;
            y += 2000;
        }
        else if (m >= 41 && m <= 52)
        {
            m -= 40;
            y += 2100;
        }
        else if (m >= 61 && m <= 72)
        {
            m -= 60;
            y += 2200;
        }
        else
        {
            throw new InvalidPeselException("couldn't decode year");
        }

        var date = new DateTime(y, m, d);
        var yearDelta = DateTime.Now.Year - date.Year;

        if (yearDelta > 18 && yearDelta < 65)
        {
            return false;
        }

        if (yearDelta < 18 || yearDelta > 65)
        {
            return true;
        }

        // yearDelta is 18 or 65
        if (DateTime.Now.Month - date.Month <= 0 && DateTime.Now.Day - date.Day < 0)
        {
            return true;
        }

        return false;
    }
}

// vim: fdl=2
