using System;
using System.Collections;

class Queue : ArrayList
{
    public void Enqueue(Object value)
    {
        Add(value);
    }

    public Object Dequeue()
    {
        var temp = base[0];
        RemoveAt(0);
        return temp;
    }
}

class QueueComposition
{
    private ArrayList list;

    public QueueComposition()
    {
        list = new ArrayList();
    }

    public void Enqueue(Object value)
    {
        list.Add(value);
    }

    public Object Dequeue()
    {
        if (list.Count == 0)
        {
            throw new Exception("Queue is empty!");
        }

        var temp = list[0];
        list.RemoveAt(0);
        return temp;
    }
}
