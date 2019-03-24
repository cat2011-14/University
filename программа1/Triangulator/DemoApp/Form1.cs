//Credit to Paul Bourke (pbourke@swin.edu.au) for the original Fortran 77 Program :))
//Converted from the VB-Conversion by EluZioN (EluZioN@casesladder.com)
//Check out: http://astronomy.swin.edu.au/~pbourke/terrain/triangulate/
//You can use this code however you like providing the above credits remain in tact
//Create

using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Collections.Generic;

namespace Triangulator_Demo
{


	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;


        private System.Windows.Forms.PictureBox pictureBox1;
        private Button button1;
        private TextBox textBox1;
        private Button button2;

		//List for storing our vertices
		private List<Triangulator.Geometry.Point> Vertices;

		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
			Vertices = new List<Triangulator.Geometry.Point>();
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				if (components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox1.BackColor = System.Drawing.Color.White;
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Location = new System.Drawing.Point(8, 8);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(570, 482);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(584, 38);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(88, 27);
            this.button1.TabIndex = 5;
            this.button1.Text = "рандом";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(584, 12);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(88, 20);
            this.textBox1.TabIndex = 6;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(584, 71);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(88, 27);
            this.button2.TabIndex = 7;
            this.button2.Text = "рекурсия";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // Form1
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(679, 502);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.pictureBox1);
            this.Name = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
        [STAThread]
        static void Main()
        {
            Application.Run(new Form1());
        }
	
        private void button1_Click(object sender, EventArgs e)
        {

            Vertices.Clear();
            pictureBox1.Image = null;
            Random rnd = new Random();
            for (int ik = 0; ik <= Convert.ToInt32(textBox1.Text); ik++)
            {
            Image b = (Image)new Bitmap(pictureBox1.Width, pictureBox1.Height);
            Graphics g = Graphics.FromImage(b);
            g.CompositingMode = CompositingMode.SourceOver;
            g.SmoothingMode = SmoothingMode.None;
            Pen myPen = new Pen(Color.Blue, 1);
            int X,Y;
            X=rnd.Next(10,300);
            Y=rnd.Next(10,300);
            //Set Vertex coordinates where you clicked the pic box
            Triangulator.Geometry.Point pNew = new Triangulator.Geometry.Point(X,Y);
            //To create a 3D point, use the Point<double> type instead:
            //Triangulator.Geometry.Point<double> pNew = new Triangulator.Geometry.Point<double>(eventArgs.X, eventArgs.Y, 3.457);

            //Only add point if another point hasn't already been added at the x,y position
            if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew.Equals2D(p); }))
                Vertices.Add(pNew);

            // Perform Triangulation if there are more than 2 points in the collection
            if (Vertices.Count > 2)
            {
                //Do triangulation
                List<Triangulator.Geometry.Triangle> tris = Triangulator.Delauney.Triangulate(Vertices);
                // Draw the created triangles
                foreach (Triangulator.Geometry.Triangle t in tris)
                {
                    g.DrawLine(myPen, (float)Vertices[t.p1].X, (float)Vertices[t.p1].Y, (float)Vertices[t.p2].X, (float)Vertices[t.p2].Y);
                    g.DrawLine(myPen, (float)Vertices[t.p2].X, (float)Vertices[t.p2].Y, (float)Vertices[t.p3].X, (float)Vertices[t.p3].Y);
                    g.DrawLine(myPen, (float)Vertices[t.p1].X, (float)Vertices[t.p1].Y, (float)Vertices[t.p3].X, (float)Vertices[t.p3].Y);
                }
                //lbTriCount.Text = "Triangles: " + tris.Count;
            }
            //Draw vertices
            for (int i = 0; i < Vertices.Count; i++)
                g.DrawEllipse(Pens.Red, (float)Vertices[i].X - 2, (float)Vertices[i].Y - 2, 4, 4);

            // Display the total points and total triangles
          //  lbPntCount.Text = "Points: " + Vertices.Count.ToString();

            g.Dispose();
            pictureBox1.Image = b;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Vertices.Clear();
            pictureBox1.Image = null;
            Random rnd = new Random();
            for (int ik = 1; ik <10; ik++)
            {
                for(int ij=1;ij<10;ij++)
                {
                Image b = (Image)new Bitmap(pictureBox1.Width, pictureBox1.Height);
                Graphics g = Graphics.FromImage(b);
                g.CompositingMode = CompositingMode.SourceOver;
                g.SmoothingMode = SmoothingMode.None;
                Pen myPen = new Pen(Color.Blue, 1);
                int X, Y;
                int width = (pictureBox1.Width) - 20;
                int height = (pictureBox1.Height) - 20;

                // X = rnd.Next(10, 300);
                //Y = rnd.Next(10, 300);
                //Set Vertex coordinates where you clicked the pic box
                Triangulator.Geometry.Point pNew0 = new Triangulator.Geometry.Point(width / 2, height);
                //To create a 3D point, use the Point<double> type instead:
                //Triangulator.Geometry.Point<double> pNew = new Triangulator.Geometry.Point<double>(eventArgs.X, eventArgs.Y, 3.457);

                //Only add point if another point hasn't already been added at the x,y position
                if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew0.Equals2D(p); }))
                    Vertices.Add(pNew0);

                Triangulator.Geometry.Point pNew1 = new Triangulator.Geometry.Point(width / 2, 0);
                if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew1.Equals2D(p); }))
                    Vertices.Add(pNew1);

                Triangulator.Geometry.Point pNew2 = new Triangulator.Geometry.Point(0, height / 2);
                if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew2.Equals2D(p); }))
                    Vertices.Add(pNew2);

                Triangulator.Geometry.Point pNew3 = new Triangulator.Geometry.Point(width, height / 2);
                if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew3.Equals2D(p); }))
                    Vertices.Add(pNew3);
                // Perform Triangulation if there are more than 2 points in the collection
                int step = (width-20)/ 10;
                int stepx = (height - 20) / 10;
                Triangulator.Geometry.Point pNew = new Triangulator.Geometry.Point(step*ik, 20);
                if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew.Equals2D(p); }))
                    Vertices.Add(pNew);
                
                Triangulator.Geometry.Point pNew4 = new Triangulator.Geometry.Point(20, stepx*ik);
                if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew4.Equals2D(p); }))
                    Vertices.Add(pNew4);

                Triangulator.Geometry.Point pNew5 = new Triangulator.Geometry.Point(step*ik,height-20);
                if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew5.Equals2D(p); }))
                    Vertices.Add(pNew5);

                Triangulator.Geometry.Point pNew6 = new Triangulator.Geometry.Point(width-20, stepx * ik);
                if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew6.Equals2D(p); }))
                    Vertices.Add(pNew6);


                Triangulator.Geometry.Point pNew7 = new Triangulator.Geometry.Point(step*ik, stepx * ij);
                if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew7.Equals2D(p); }))
                    Vertices.Add(pNew7);

                
                /*    int x1 = width / 4;
                    int d = 100;
                    int D = 200;
                    int y1 = height / 3;
                    Triangulator.Geometry.Point pNew8 = new Triangulator.Geometry.Point(x1,y1);
                    if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew8.Equals2D(p); }))
                        Vertices.Add(pNew8);
                   
                    Triangulator.Geometry.Point pNew9 = new Triangulator.Geometry.Point(x1+d, y1+D);
                    if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew9.Equals2D(p); }))
                        Vertices.Add(pNew8);

                    Triangulator.Geometry.Point pNew10 = new Triangulator.Geometry.Point(x1 + d, y1);
                    if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew10.Equals2D(p); }))
                        Vertices.Add(pNew10 );

                    Triangulator.Geometry.Point pNew11 = new Triangulator.Geometry.Point(x1 , y1 + D);
                    if (!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew11.Equals2D(p); }))
                        Vertices.Add(pNew11);
*/
                

            if (Vertices.Count > 2)
                {
                    //Do triangulation
                    List<Triangulator.Geometry.Triangle> tris = Triangulator.Delauney.Triangulate(Vertices);
                    // Draw the created triangles
                    foreach (Triangulator.Geometry.Triangle t in tris)
                    {
                        g.DrawLine(myPen, (float)Vertices[t.p1].X, (float)Vertices[t.p1].Y, (float)Vertices[t.p2].X, (float)Vertices[t.p2].Y);
                        g.DrawLine(myPen, (float)Vertices[t.p2].X, (float)Vertices[t.p2].Y, (float)Vertices[t.p3].X, (float)Vertices[t.p3].Y);
                        g.DrawLine(myPen, (float)Vertices[t.p1].X, (float)Vertices[t.p1].Y, (float)Vertices[t.p3].X, (float)Vertices[t.p3].Y);
                    }
                    //lbTriCount.Text = "Triangles: " + tris.Count;
                }
                //Draw vertices
                for (int i = 0; i < Vertices.Count; i++)
                    g.DrawEllipse(Pens.Red, (float)Vertices[i].X - 2, (float)Vertices[i].Y - 2, 4, 4);

                // Display the total points and total triangles
                //  lbPntCount.Text = "Points: " + Vertices.Count.ToString();

                g.Dispose();
                pictureBox1.Image = b;
                }
            }
        }
	}
}
