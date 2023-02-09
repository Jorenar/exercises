// It is (fortunately) impossible in C# to inherit after `System.Array`,
//  thus Queue by deriving is unavailable - only through composition.

using System;

class QueueArray
{
    private Object[] array;
    private int max;
    private int length;

    public int Length {
        get { return length; }
    }

    public QueueArray()
    {
        length = 0;
        max = 32;
        array = new Object[max];
    }

    private void Enlarge()
    {
        max *= 2;
        Object[] temp = new Object[max];

        for (int i = 0; i < length; ++i)
        {
            temp[i] = array[i];
        }

        array = temp;
    }

    public void Enqueue(Object value)
    {
        array[length] = value;
        ++length;

        if (length == max) {
            Enlarge();
        }
    }

    public Object Dequeue()
    {
        if (length == 0)
        {
            throw new Exception("Queue is empty!");
        }

        Object temp = array[0];
        --length;

        // Highly inefficient, but it's not the point of exercise
        for (int i = 0; i < length; i++)
        {
            array[i] = array[i+1];
        }

        return temp;
    }
}

// vim: fdl=1
