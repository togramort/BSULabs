using System;
using System.Threading;

namespace mum_dad
{
    public class SayClass
    {
        public static int MaxAmount = 222;
        public static int CurAmount;
        private readonly string _word;
        private readonly int _ms, _n;

        public SayClass(string word, int ms, int n)
        {
            _word = word;
            _ms = ms;
            _n = n;
        }

        static readonly object Locker = new object();

        public void Say()
        {
            for (int i = 0; i < _n; i++)
            {
                lock (Locker)
                {
                    if (CurAmount == MaxAmount)
                    {
                        Console.WriteLine("the amount of all words: {0}", CurAmount);
                        Environment.Exit(0);
                    }
                    
                    Console.Write(_word + " ");
                    ++CurAmount;
                }
                Thread.Sleep(_ms);
            }
        }
    }

    internal static class Program
    {
        public static void Main(string[] args)
        {
            SayClass sayClass1 = new SayClass("mum ", 1000, 10);
            Thread myThread1 = new Thread(sayClass1.Say);
            myThread1.Start();
            SayClass sayClass2 = new SayClass("dad ", 500, 10);
            Thread myThread2 = new Thread(sayClass2.Say);
            myThread2.Start();
            SayClass sayClass3 = new SayClass("not u ", 1500, 5);
            Thread myThread3 = new Thread(sayClass3.Say);
            myThread3.Start();

            myThread1.Join();
            myThread2.Join();
            myThread3.Join();

            Console.WriteLine("the amount of all words: {0}", SayClass.CurAmount);
        }
    }
}