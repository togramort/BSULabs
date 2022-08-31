using System;
using System.Xml;
using System.Xml.Schema;

namespace xml
{
    class Program
    {
        static void Main(string[] args)
        {
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.DtdProcessing = DtdProcessing.Parse;
            settings.ValidationType = ValidationType.DTD;
            using (XmlReader reader = XmlReader.Create("family.xml", settings))
            {
                try
                {
                    int count = 1;
                    while (reader.Read())
                    {
                        switch (reader.NodeType)
                        {
                            case XmlNodeType.Element:
                                if (reader.Name == "family")
                                {
                                    Console.WriteLine("=====================");
                                    Console.WriteLine("member(s) of family:");
                                    Console.WriteLine("=====================");
                                }
                                else if (reader.Name == "member")
                                {
                                    Console.ForegroundColor = ConsoleColor.DarkRed;
                                    Console.WriteLine("member " + count);
                                    Console.ForegroundColor = ConsoleColor.White;
                                }
                                else if (reader.Name == "minfo")
                                {
                                    Console.WriteLine("name: " + reader.GetAttribute("name"));
                                    Console.WriteLine("date of birth: " + reader.GetAttribute("birth"));
                                    ++count;
                                }
                                else if (reader.Name == "sinfo")
                                {
                                    Console.ForegroundColor = ConsoleColor.DarkCyan;
                                    Console.WriteLine("other info...");
                                    Console.WriteLine("");
                                    Console.ForegroundColor = ConsoleColor.White;
                                }
                                else if (reader.Name == "spouse")
                                {
                                    Console.WriteLine("spouse name: " + reader.GetAttribute("spouse_name"));
                                    Console.WriteLine("date of marriage: " + reader.GetAttribute("marriage"));
                                    Console.WriteLine("child's name: " + reader.GetAttribute("child_name"));
                                    Console.WriteLine("date of divorce: " + reader.GetAttribute("divorce"));
                                    Console.WriteLine("");
                                }
                                reader.MoveToElement();
                                break;
                            case XmlNodeType.Text:
                                Console.WriteLine(reader.Value);
                                break;
                        }
                    }
                }
                catch (XmlSchemaException ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
        }
    }
}