using System;
using System.Collections;
using System.Diagnostics.Tracing;
using System.IO;
using System.Threading.Tasks;
using System.Linq;
using System.Net.Sockets;

namespace linq_pets
{
    static class Collection
    {
        private static string owner;
        private static string species;
        private static string name;
        private static int age;
        public static ArrayList NewColl(int wordsLength, ArrayList words)
        {
            ArrayList arr = new ArrayList();
            for (int i = 0; i < wordsLength - 3; i += 4)
            {
                owner = (string) words[i];
                species = (string) words[i + 1];
                name = (string) words[i + 2];
                age = (int) words[i + 3];
                arr.AddRange(new ArrayList(){owner, species, name, age});
            }
            return arr;
        }
    }

    static class Program
    {
        static async Task Main(string[] args)
        {
            string path = @"D:\program etc\projects\linq_pets\linq_pets\input.txt";
            using StreamReader sr = new StreamReader(path, System.Text.Encoding.Default);
            string line;
            int wordsLength = 0;
            ArrayList words = new ArrayList();
            while ((line = await sr.ReadLineAsync()) != null)
            {
                words.Add(line.Split(new[] {','}));
                wordsLength = words.Capacity;
            }
            ArrayList coll = Collection.NewColl(wordsLength, words);

            for (int i = 0; i < coll.Capacity; i++)
            {
                Console.WriteLine(coll[i]);
            }
        }
    }
}
