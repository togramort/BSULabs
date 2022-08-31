using System;

namespace linq
{
    public class Pets
    {
        public string Owner { get; set; }
        public string Type { get; set; }
        public string Nick { get; set; }
        public int? Age { get; set; }

        public Pets(string owner, string type, string nick, string age)
        {
            if (string.IsNullOrEmpty(type))
            {
                throw new ArgumentException(nameof(type));
            }
            Owner = owner;
            Type = type;
            Nick = nick;
            if (String.IsNullOrEmpty(age))
            {
                Age = null;
            }
            else
            {
                Age = Convert.ToInt32(age);
            }
        }
    }
}