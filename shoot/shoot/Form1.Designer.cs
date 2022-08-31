namespace shoot
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.R1 = new System.Windows.Forms.Label();
            this.R2 = new System.Windows.Forms.Label();
            this.bullets = new System.Windows.Forms.Label();
            this.Start = new System.Windows.Forms.Button();
            this.textBoxR1 = new System.Windows.Forms.TextBox();
            this.textBoxR2 = new System.Windows.Forms.TextBox();
            this.textBoxB3 = new System.Windows.Forms.TextBox();
            this.coord = new System.Windows.Forms.Label();
            this.X = new System.Windows.Forms.Label();
            this.Y = new System.Windows.Forms.Label();
            this.textBoxX = new System.Windows.Forms.TextBox();
            this.textBoxY = new System.Windows.Forms.TextBox();
            this.Shoot = new System.Windows.Forms.Button();
            this.labelStatistics = new System.Windows.Forms.Label();
            this.labelDone = new System.Windows.Forms.Label();
            this.labelRemained = new System.Windows.Forms.Label();
            this.labelHits = new System.Windows.Forms.Label();
            this.labelMisses = new System.Windows.Forms.Label();
            this.labelDone1 = new System.Windows.Forms.Label();
            this.labelRemained1 = new System.Windows.Forms.Label();
            this.labelHits1 = new System.Windows.Forms.Label();
            this.labelMisses1 = new System.Windows.Forms.Label();
            this.End = new System.Windows.Forms.Button();
            this.errorProvider1 = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize) (this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize) (this.errorProvider1)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(551, 529);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseClick);
            // 
            // R1
            // 
            this.R1.AutoSize = true;
            this.R1.Location = new System.Drawing.Point(585, 13);
            this.R1.Name = "R1";
            this.R1.Size = new System.Drawing.Size(104, 17);
            this.R1.TabIndex = 1;
            this.R1.Text = "Enter R1 (<R2)";
            // 
            // R2
            // 
            this.R2.AutoSize = true;
            this.R2.Location = new System.Drawing.Point(585, 43);
            this.R2.Name = "R2";
            this.R2.Size = new System.Drawing.Size(104, 17);
            this.R2.TabIndex = 2;
            this.R2.Text = "Enter R2 (>R1)";
            // 
            // bullets
            // 
            this.bullets.AutoSize = true;
            this.bullets.Location = new System.Drawing.Point(585, 71);
            this.bullets.Name = "bullets";
            this.bullets.Size = new System.Drawing.Size(117, 17);
            this.bullets.TabIndex = 3;
            this.bullets.Text = "Amount of bullets";
            // 
            // Start
            // 
            this.Start.Location = new System.Drawing.Point(614, 107);
            this.Start.Name = "Start";
            this.Start.Size = new System.Drawing.Size(181, 23);
            this.Start.TabIndex = 4;
            this.Start.Text = "Start";
            this.Start.UseVisualStyleBackColor = true;
            this.Start.Click += new System.EventHandler(this.Start_Click);
            // 
            // textBoxR1
            // 
            this.textBoxR1.Location = new System.Drawing.Point(716, 13);
            this.textBoxR1.Name = "textBoxR1";
            this.textBoxR1.Size = new System.Drawing.Size(79, 22);
            this.textBoxR1.TabIndex = 5;
            this.textBoxR1.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxR1_Validating);
            // 
            // textBoxR2
            // 
            this.textBoxR2.Location = new System.Drawing.Point(716, 43);
            this.textBoxR2.Name = "textBoxR2";
            this.textBoxR2.Size = new System.Drawing.Size(79, 22);
            this.textBoxR2.TabIndex = 6;
            this.textBoxR2.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxR2_Validating);
            // 
            // textBoxB3
            // 
            this.textBoxB3.Location = new System.Drawing.Point(716, 71);
            this.textBoxB3.Name = "textBoxB3";
            this.textBoxB3.Size = new System.Drawing.Size(79, 22);
            this.textBoxB3.TabIndex = 7;
            this.textBoxB3.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxB3_Validating);
            // 
            // coord
            // 
            this.coord.AutoSize = true;
            this.coord.Location = new System.Drawing.Point(647, 147);
            this.coord.Name = "coord";
            this.coord.Size = new System.Drawing.Size(120, 17);
            this.coord.TabIndex = 8;
            this.coord.Text = "Enter coordinates";
            // 
            // X
            // 
            this.X.AutoSize = true;
            this.X.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte) (204)));
            this.X.Location = new System.Drawing.Point(565, 170);
            this.X.Name = "X";
            this.X.Size = new System.Drawing.Size(29, 24);
            this.X.TabIndex = 9;
            this.X.Text = "X:";
            // 
            // Y
            // 
            this.Y.AutoSize = true;
            this.Y.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte) (204)));
            this.Y.Location = new System.Drawing.Point(565, 208);
            this.Y.Name = "Y";
            this.Y.Size = new System.Drawing.Size(27, 24);
            this.Y.TabIndex = 10;
            this.Y.Text = "Y:";
            // 
            // textBoxX
            // 
            this.textBoxX.Location = new System.Drawing.Point(650, 171);
            this.textBoxX.Name = "textBoxX";
            this.textBoxX.Size = new System.Drawing.Size(100, 22);
            this.textBoxX.TabIndex = 11;
            this.textBoxX.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxX_Validating);
            // 
            // textBoxY
            // 
            this.textBoxY.Location = new System.Drawing.Point(650, 210);
            this.textBoxY.Name = "textBoxY";
            this.textBoxY.Size = new System.Drawing.Size(100, 22);
            this.textBoxY.TabIndex = 12;
            this.textBoxY.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxY_Validating);
            // 
            // Shoot
            // 
            this.Shoot.Location = new System.Drawing.Point(614, 249);
            this.Shoot.Name = "Shoot";
            this.Shoot.Size = new System.Drawing.Size(180, 53);
            this.Shoot.TabIndex = 13;
            this.Shoot.Text = "SHOOT";
            this.Shoot.UseVisualStyleBackColor = true;
            this.Shoot.Click += new System.EventHandler(this.Shoot_Click);
            // 
            // labelStatistics
            // 
            this.labelStatistics.AutoSize = true;
            this.labelStatistics.Location = new System.Drawing.Point(675, 321);
            this.labelStatistics.Name = "labelStatistics";
            this.labelStatistics.Size = new System.Drawing.Size(64, 17);
            this.labelStatistics.TabIndex = 14;
            this.labelStatistics.Text = "Statistics";
            // 
            // labelDone
            // 
            this.labelDone.AutoSize = true;
            this.labelDone.Location = new System.Drawing.Point(596, 362);
            this.labelDone.Name = "labelDone";
            this.labelDone.Size = new System.Drawing.Size(42, 17);
            this.labelDone.TabIndex = 15;
            this.labelDone.Text = "Done";
            // 
            // labelRemained
            // 
            this.labelRemained.AutoSize = true;
            this.labelRemained.Location = new System.Drawing.Point(755, 362);
            this.labelRemained.Name = "labelRemained";
            this.labelRemained.Size = new System.Drawing.Size(72, 17);
            this.labelRemained.TabIndex = 16;
            this.labelRemained.Text = "Remained";
            // 
            // labelHits
            // 
            this.labelHits.AutoSize = true;
            this.labelHits.Location = new System.Drawing.Point(596, 441);
            this.labelHits.Name = "labelHits";
            this.labelHits.Size = new System.Drawing.Size(32, 17);
            this.labelHits.TabIndex = 17;
            this.labelHits.Text = "Hits";
            // 
            // labelMisses
            // 
            this.labelMisses.AutoSize = true;
            this.labelMisses.Location = new System.Drawing.Point(765, 441);
            this.labelMisses.Name = "labelMisses";
            this.labelMisses.Size = new System.Drawing.Size(51, 17);
            this.labelMisses.TabIndex = 18;
            this.labelMisses.Text = "Misses";
            // 
            // labelDone1
            // 
            this.labelDone1.AutoSize = true;
            this.labelDone1.Location = new System.Drawing.Point(610, 379);
            this.labelDone1.Name = "labelDone1";
            this.labelDone1.Size = new System.Drawing.Size(13, 17);
            this.labelDone1.TabIndex = 19;
            this.labelDone1.Text = "-";
            // 
            // labelRemained1
            // 
            this.labelRemained1.AutoSize = true;
            this.labelRemained1.Location = new System.Drawing.Point(787, 379);
            this.labelRemained1.Name = "labelRemained1";
            this.labelRemained1.Size = new System.Drawing.Size(13, 17);
            this.labelRemained1.TabIndex = 20;
            this.labelRemained1.Text = "-";
            // 
            // labelHits1
            // 
            this.labelHits1.AutoSize = true;
            this.labelHits1.Location = new System.Drawing.Point(610, 458);
            this.labelHits1.Name = "labelHits1";
            this.labelHits1.Size = new System.Drawing.Size(13, 17);
            this.labelHits1.TabIndex = 21;
            this.labelHits1.Text = "-";
            // 
            // labelMisses1
            // 
            this.labelMisses1.AutoSize = true;
            this.labelMisses1.Location = new System.Drawing.Point(787, 458);
            this.labelMisses1.Name = "labelMisses1";
            this.labelMisses1.Size = new System.Drawing.Size(13, 17);
            this.labelMisses1.TabIndex = 22;
            this.labelMisses1.Text = "-";
            // 
            // End
            // 
            this.End.Location = new System.Drawing.Point(650, 482);
            this.End.Name = "End";
            this.End.Size = new System.Drawing.Size(116, 35);
            this.End.TabIndex = 23;
            this.End.Text = "End";
            this.End.UseVisualStyleBackColor = true;
            this.End.Click += new System.EventHandler(this.End_Click);
            // 
            // errorProvider1
            // 
            this.errorProvider1.ContainerControl = this;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(770, 529);
            this.Controls.Add(this.End);
            this.Controls.Add(this.labelMisses1);
            this.Controls.Add(this.labelHits1);
            this.Controls.Add(this.labelRemained1);
            this.Controls.Add(this.labelDone1);
            this.Controls.Add(this.labelMisses);
            this.Controls.Add(this.labelHits);
            this.Controls.Add(this.labelRemained);
            this.Controls.Add(this.labelDone);
            this.Controls.Add(this.labelStatistics);
            this.Controls.Add(this.Shoot);
            this.Controls.Add(this.textBoxY);
            this.Controls.Add(this.textBoxX);
            this.Controls.Add(this.Y);
            this.Controls.Add(this.X);
            this.Controls.Add(this.coord);
            this.Controls.Add(this.textBoxB3);
            this.Controls.Add(this.textBoxR2);
            this.Controls.Add(this.textBoxR1);
            this.Controls.Add(this.Start);
            this.Controls.Add(this.bullets);
            this.Controls.Add(this.R2);
            this.Controls.Add(this.R1);
            this.Controls.Add(this.pictureBox1);
            this.Name = "Form1";
            this.Text = "Shoot!";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Resize += new System.EventHandler(this.Form1_Resize);
            ((System.ComponentModel.ISupportInitialize) (this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize) (this.errorProvider1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label R1;
        private System.Windows.Forms.Label R2;
        private System.Windows.Forms.Label bullets;
        private System.Windows.Forms.Button Start;
        private System.Windows.Forms.TextBox textBoxR1;
        private System.Windows.Forms.TextBox textBoxR2;
        private System.Windows.Forms.TextBox textBoxB3;
        private System.Windows.Forms.Label coord;
        private System.Windows.Forms.Label X;
        private System.Windows.Forms.Label Y;
        private System.Windows.Forms.TextBox textBoxX;
        private System.Windows.Forms.TextBox textBoxY;
        private System.Windows.Forms.Button Shoot;
        private System.Windows.Forms.Label labelStatistics;
        private System.Windows.Forms.Label labelDone;
        private System.Windows.Forms.Label labelRemained;
        private System.Windows.Forms.Label labelHits;
        private System.Windows.Forms.Label labelMisses;
        private System.Windows.Forms.Label labelDone1;
        private System.Windows.Forms.Label labelRemained1;
        private System.Windows.Forms.Label labelHits1;
        private System.Windows.Forms.Label labelMisses1;
        private System.Windows.Forms.Button End;
        private System.Windows.Forms.ErrorProvider errorProvider1;
    }
}

