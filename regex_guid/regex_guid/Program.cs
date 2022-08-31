using System;
using System.IO;
using System.Text.RegularExpressions;

namespace regex_guid
{
    static class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("enter the file's directory: ");
            string file = Console.ReadLine();
            if (File.Exists(file))
            {
                string[] lines = File.ReadAllLines(file!);

                Console.WriteLine("enter the out file's directory: ");
                string fout = Console.ReadLine();
                string res = "";
                foreach (string line in lines)
                {
                    if (!Regex.IsMatch(line, @"([\da-fA-F]{8}-)([\da-fA-F]{4}-){3}[\da-fA-F]{12}"))
                    {
                        res += line + "\n";
                    }
                }
                File.WriteAllTextAsync(fout!, res);
            }
            else
            {
                Console.WriteLine("no input file");
            }
        }
    }
}