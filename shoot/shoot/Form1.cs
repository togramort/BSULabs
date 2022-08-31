using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace shoot
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        int r1 = 100, r2 = 120;
        int num = 0, done, miss, hit;
        int x = 0, y = 0;
        bool Hit = false;
        int lastx, lasty;

        private void Form1_Load(object sender, EventArgs e)
        {
            Shoot.Enabled = false;
            End.Enabled = false;
            textBoxX.Enabled = false;
            textBoxY.Enabled = false;
            textBoxR1.Text = r1.ToString();
            textBoxR2.Text = r2.ToString();
            textBoxB3.Text = num.ToString();
            textBoxX.Text = x.ToString();
            textBoxY.Text = y.ToString();
        }

        private void CheckNumber(object sender, CancelEventArgs e, ref int a, bool isSigned)
        {
            try
            {
                if (isSigned)
                    a = int.Parse(((TextBox) sender).Text);
                else
                    a = (int) uint.Parse(((TextBox) sender).Text);
                errorProvider1.Clear();
            }
            catch (Exception ex)
            {
                errorProvider1.SetError(sender as TextBox, ex.Message);
                e.Cancel = true;
                ((TextBox) sender).Text = "";
            }
        }

        private void Start_Click(object sender, EventArgs e)
        {
            if (num == 0)
            {
                MessageBox.Show("you dont have bullets, you cant shoot!");
            }
            else
            {
                textBoxR1.Enabled = false;
                textBoxR2.Enabled = false;
                textBoxB3.Enabled = false;
                Start.Enabled = false;
                textBoxX.Enabled = true;
                textBoxY.Enabled = true;
                Shoot.Enabled = true;
                End.Enabled = true;
                labelDone1.Text = done.ToString();
                labelHits1.Text = hit.ToString();
                labelMisses1.Text = miss.ToString();
            }
        }

        private void Shoot_Click(object sender, EventArgs e)
        {
            if (num == 0)
            {
                MessageBox.Show("you dont have bullets, you cant shoot!");
            }
            else
            {
                num--;
                done++;
                labelDone1.Text = done.ToString();
                labelRemained1.Text = num.ToString();
                if (Math.Pow(x, 2) + Math.Pow(y, 2) <= Math.Pow(r1, 2) && x <= 0 && y >= 0
                    || Math.Pow(x, 2) + Math.Pow(y, 2) <= Math.Pow(r2, 2)
                    && Math.Pow(x, 2) + Math.Pow(y, 2) >= Math.Pow(r1, 2) && x >= 0 && y <= 0)
                {
                    hit++;
                    labelHits1.Text = hit.ToString();
                }
                else
                {
                    miss++;
                    labelMisses1.Text = miss.ToString();
                }

                if (Math.Abs(x) > pictureBox1.Width / 2 || Math.Abs(y) > pictureBox1.Height / 2)
                {
                    MessageBox.Show("are you blind or what");
                }

                lastx = x;
                lasty = y;
                Hit = true;
                Invalidate();
            }
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            int mouseX = e.X - pictureBox1.Width / 2;
            int mouseY = pictureBox1.Height / 2 - e.Y;
            if (num == 0)
            {
                MessageBox.Show("you dont have bullets, you cant shoot!");
            }
            else
            {
                num--;
                done++;
                labelDone1.Text = done.ToString();
                labelRemained1.Text = num.ToString();
                if (Math.Pow(mouseX, 2) + Math.Pow(mouseY, 2) <= Math.Pow(r1, 2) && mouseX <= 0 && mouseY >= 0
                    || Math.Pow(mouseX, 2) + Math.Pow(mouseY, 2) <= Math.Pow(r2, 2)
                    && Math.Pow(mouseX, 2) + Math.Pow(mouseY, 2) >= Math.Pow(r1, 2) && mouseX >= 0 && mouseY <= 0)
                {
                    hit += 3;
                    labelHits1.Text = hit.ToString();
                }
                else
                {
                    miss++;
                    labelMisses1.Text = miss.ToString();
                }

                if (Math.Abs(x) > pictureBox1.Width / 2 || Math.Abs(y) > pictureBox1.Height / 2)
                {
                    MessageBox.Show("are you blind or what");
                }

                lastx = mouseX;
                lasty = mouseY;
                Hit = true;
                Invalidate();
            }
        }

        private void End_Click(object sender, EventArgs e)
        {
            Shoot.Enabled = false;
            End.Enabled = false;
            textBoxX.Enabled = false;
            textBoxY.Enabled = false;
            textBoxB3.Enabled = true;
            textBoxR1.Enabled = true;
            textBoxR2.Enabled = true;
            Start.Enabled = true;
            done = miss = hit = num = 0;
            Hit = false;
            textBoxB3.Focus();
        }

        private void textBoxR1_Validating(object sender, CancelEventArgs e)
        {
            CheckNumber(sender, e, ref r1, false);
            if (r1 > pictureBox1.Width / 2)
            {
                MessageBox.Show("target is too big. you can change the r1 or continue");
            }

            if (r1 == 0)
            {
                MessageBox.Show("what are you doing..");
            }
        }

        private void textBoxR2_Validating(object sender, CancelEventArgs e)
        {
            CheckNumber(sender, e, ref r2, false);
            if (r2 > pictureBox1.Width / 2)
            {
                MessageBox.Show("target is too big. you can change the r2 or continue");
            }

            if (r2 == 0)
            {
                MessageBox.Show("what are you doing..");
            }
        }

        private void textBoxB3_Validating(object sender, CancelEventArgs e)
        {
            CheckNumber(sender, e, ref num, true);
        }

        private void textBoxX_Validating(object sender, CancelEventArgs e)
        {
            CheckNumber(sender, e, ref x, true);
        }

        private void textBoxY_Validating(object sender, CancelEventArgs e)
        {
            CheckNumber(sender, e, ref y, true);
        }

        Bitmap MyBitmap;
        Graphics gr;

        protected override void OnPaint(PaintEventArgs e)
        {
            MyBitmap = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            gr = Graphics.FromImage(MyBitmap);
            base.OnPaint(e);
            DrawTarget(gr);
            if (Hit)
            {
                DrawHit(gr);
            }

            pictureBox1.Image = MyBitmap;
        }

        private void DrawHit(Graphics g)
        {
            int h = pictureBox1.Height;
            int w = pictureBox1.Width;
            SolidBrush brush = new SolidBrush(Color.PaleVioletRed);
            Pen pen = new Pen(brush);
            g.DrawEllipse(pen, lastx - 3 + w / 2, h / 2 - lasty - 3, 6, 6);
            g.FillEllipse(brush, lastx - 3 + w / 2, h / 2 - lasty - 3, 6, 6);
            g.DrawEllipse(pen, lastx - 6 + w / 2, h / 2 - lasty - 6, 12, 12);
        }

        private void DrawTarget(Graphics g)
        {
            g.Clear(Color.White);
            int h = pictureBox1.Height;
            int w = pictureBox1.Width;
            Point o = new Point(w / 2, h / 2);
            SolidBrush brush = new SolidBrush(Color.Black);
            Rectangle rectangle = new Rectangle(o.X - r1, o.Y - r1, 2 * r1, 2 * r1);
            g.FillPie(brush, rectangle, 180, 90);

            brush.Color = Color.Black;
            g.FillPie(brush, new Rectangle(o.X - r2, o.Y - r2, 2 * r2, 2 * r2), 360, 90);

            brush.Color = Color.White;
            g.FillPie(brush, new Rectangle(o.X - r1, o.Y - r1, 2 * r1, 2 * r1), 360, 90);

            brush.Dispose();
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            Invalidate();
        }
    }
}