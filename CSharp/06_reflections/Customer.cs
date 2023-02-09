using System;

public class Customer
{
    private string _name;
    protected int _age;
    public bool isPreferred;

    public Customer(string name)
    {
        if (string.IsNullOrEmpty(name)) {
            throw new ArgumentNullException("Customer name!");
        }
        _name = name;
    }

    public string Name
    {
        get { return _name; }
    }

    public string Address {
        get; set;
    }

    public int SomeValue {
        get; set;
    }

    public int ImportantCalculation()
    {
        return 1000;
    }

    public void ImportantVoidMethod()
    {
    }

    public enum SomeEnumeration
    {
        ValueOne = 1,
        ValueTwo = 2
    }

    public class SomeNestedClass
    {
        private string _someString;
    }
}
