using System;
using System.Linq;
using System.Collections.Generic;

public delegate void BeginVote(string topic);
public delegate void EndVote();
public delegate void Voted(bool v);

class Parliamentarian
{
    public event Voted voted;

    private int ID;
    string topic;

    public Parliamentarian(int id, Parliament parliament)
    {
        this.ID = id;
        this.topic = null;
        parliament.beginVote += StartThinking;
        parliament.endVote += StopThinking;
        voted += parliament.CountVote;
    }

    void StartThinking(string topic)
    {
        this.topic = topic;
    }

    void StopThinking()
    {
        this.topic = null;
    }

    public void Vote()
    {
        if (topic == null)
        {
            Console.Error.WriteLine($"Parliamentarian {ID} is not taking part in any voting right now");
            return;
        }

        if (topic == "")
        {
            Console.Error.WriteLine($"Parliamentarian {ID} already voted");
            return;
        }

        voted?.Invoke(new Random().Next(2) == 1);
        topic = "";
    }
}

class Parliament
{
    public event BeginVote beginVote;
    public event EndVote endVote;

    private int[] votes;
    public List<Parliamentarian> parliamentarians {
        get;
    }

    public Parliament(int n)
    {
        parliamentarians = new List<Parliamentarian>();
        for (int i = 0; i < n; ++i)
        {
            parliamentarians.Add(new Parliamentarian(i, this));
        }
    }

    public void CountVote(bool v)
    {
        ++votes[v ? 1 : 0];
    }

    public void StartVote(string topic)
    {
        votes = new int[2];
        beginVote?.Invoke(topic);
    }

    public void StopVote()
    {
        endVote?.Invoke();
    }

    public void PrintResults(string topic)
    {
        var withdrawn = parliamentarians.Count - votes[0] - votes[1];
        Console.WriteLine($"Voting topic: {topic}");
        Console.WriteLine($"  In favor:   {votes[1]}");
        Console.WriteLine($"  Against:    {votes[0]}");
        Console.WriteLine($"  Withdrawn:  {withdrawn}");
    }
}


class Program
{
    public static void Main()
    {
        Console.Write("Numer of parliamentarians: ");
        var n = Convert.ToInt32(Console.ReadLine());
        string topic = null;

        var parliament = new Parliament(n);

        while (true)
        {
            Console.Write("> ");
            var cmd = Console.ReadLine().Trim().Split();
            switch (cmd[0].ToLower())
            {
                case "begin":
                    if (topic != null)
                    {
                        Console.Error.WriteLine("You cannot start new voting in the previous one!");
                        break;
                    }

                    topic = string.Join(' ', cmd.Skip(1).ToArray());
                    parliament.StartVote(topic);
                    break;

                case "vote":
                    if (cmd[1].ToLower() == "all")
                    {
                        foreach (var p in parliament.parliamentarians)
                        {
                            p.Vote();
                        }
                    }
                    else
                    {
                        var id = Convert.ToInt32(cmd[1]);
                        parliament.parliamentarians[id].Vote();
                    }
                    break;

                case "end":
                    if (topic == null)
                    {
                        Console.Error.WriteLine("No voting takes place right now!");
                        break;
                    }

                    parliament.StopVote();
                    parliament.PrintResults(topic);
                    topic = null;
                    break;

                case "q":
                case "quit":
                    return;

                default:
                    Console.Error.WriteLine("No such operation");
                    break;
            }
        }
    }
}
