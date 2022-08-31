using System;
using System.Buffers;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace linq
{
    class Program
    {
        static List<Pets> Find(List<Pets> pets)
        {
            var homeless = pets.Where(x => x.Owner == "").Select(x => x);
            return homeless.ToList();
        }

        private static string HomelessCharacteristics(List<Pets> pets)
        {
            string result = "Homeless pets with their characteristics: \n";

            var find = Find(pets);
            foreach (var i in find)
            {
                if (i.Type == "")
                {
                    i.Type = "--";
                }

                if (i.Nick == "")
                {
                    i.Nick = "--";
                }

                i.Age ??= 0;

                result += i.Type + " " + i.Nick + " " + i.Age + "\n";
            }

            return result;
        }

        private static string AmountOfHomeless(List<Pets> pets)
        {
            var find = Find(pets);
            string result = "amount of all homeless :( pets: " + find.Count + "\n";
            return result;
        }

        private static string MaxHomeless(List<Pets> pets)
        {
            var res = from pet in pets
                where pet.Owner == ""
                group pet by pet.Type;

            var count = res.First().Count();
            var max = from sth in res
                where sth.Count() > count
                select count = sth.Count();
            
            string result = "max amount of homeless pets of type ... is: " + max.Max() + "\n";
            return result;
        }

        static void Main(string[] args)
        {
            string fin = @"D:\program etc\projects\linq2\linq2\in.txt";

            string fout = @"D:\program etc\projects\linq2\linq2\out.txt";

            List<Pets> pets = new List<Pets>();
            string[] arrpets;

            using (StreamReader sin = new StreamReader(fin))
            {
                while (!sin.EndOfStream)
                {
                    arrpets = sin.ReadLine()?.Split(',');

                    if (arrpets != null)
                    {
                        Pets p = new Pets(arrpets[0], arrpets[1], arrpets[2], arrpets[3]);
                        pets.Add(p);
                    }
                }
            }

            Console.WriteLine("1 - console / 2 - out.txt");
            int n = Convert.ToInt32(Console.ReadLine());
            if (n == 1)
            {
                Console.WriteLine("a - all info / b - amount of homeless / c - max amount of each type");
                string m = Console.ReadLine();
                switch (m)
                {
                    case "a":
                        Console.WriteLine(HomelessCharacteristics(pets));
                        break;
                    case "b":
                        Console.WriteLine(AmountOfHomeless(pets));
                        break;
                    case "c":
                        Console.WriteLine(MaxHomeless(pets));
                        break;
                }
            }
            else if (n == 2)
            {
                Console.WriteLine("a - all info / b - amount of homeless / c - type with the max amount");
                string m = Console.ReadLine();
                using (StreamWriter write = new StreamWriter(fout))
                {
                    switch (m)
                    {
                        case "a":
                            write.WriteLine(HomelessCharacteristics(pets));
                            break;
                        case "b":
                            write.WriteLine(AmountOfHomeless(pets));
                            break;
                        case "c":
                            write.WriteLine(MaxHomeless(pets));
                            break;
                    }
                }
            }
            else
            {
                Console.WriteLine("wat");
            }
        }
    }
}