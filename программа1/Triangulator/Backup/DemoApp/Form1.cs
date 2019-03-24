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
		private System.Windows.Forms.Label lbPntCount;
		private System.Windows.Forms.Label lbTriCount;
		private System.Windows.Forms.Label lbMousePos;
		private Button btnRestart;

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
			this.lbPntCount = new System.Windows.Forms.Label();
			this.lbTriCount = new System.Windows.Forms.Label();
			this.lbMousePos = new System.Windows.Forms.Label();
			this.btnRestart = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
			this.SuspendLayout();
			// 
			// pictureBox2
			// 
			this.pictureBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.pictureBox1.BackColor = System.Drawing.Color.White;
			this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pictureBox1.Location = new System.Drawing.Point(8, 32);
			this.pictureBox1.Name = "pictureBox2";
			this.pictureBox1.Size = new System.Drawing.Size(446, 342);
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox2_MouseDown);
			this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox2_MouseMove);
			// 
			// label4
			// 
			this.lbPntCount.Location = new System.Drawing.Point(8, 8);
			this.lbPntCount.Name = "label4";
			this.lbPntCount.Size = new System.Drawing.Size(120, 16);
			this.lbPntCount.TabIndex = 1;
			this.lbPntCount.Text = "# points";
			this.lbPntCount.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label5
			// 
			this.lbTriCount.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.lbTriCount.Location = new System.Drawing.Point(326, 8);
			this.lbTriCount.Name = "label5";
			this.lbTriCount.Size = new System.Drawing.Size(128, 16);
			this.lbTriCount.TabIndex = 2;
			this.lbTriCount.Text = "# triangles";
			this.lbTriCount.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// label6
			// 
			this.lbMousePos.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.lbMousePos.Location = new System.Drawing.Point(16, 382);
			this.lbMousePos.Name = "label6";
			this.lbMousePos.Size = new System.Drawing.Size(438, 16);
			this.lbMousePos.TabIndex = 3;
			this.lbMousePos.Text = "X,Y";
			this.lbMousePos.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// btnRestart
			// 
			this.btnRestart.Location = new System.Drawing.Point(135, 8);
			this.btnRestart.Name = "btnRestart";
			this.btnRestart.Size = new System.Drawing.Size(75, 23);
			this.btnRestart.TabIndex = 4;
			this.btnRestart.Text = "Restart";
			this.btnRestart.UseVisualStyleBackColor = true;
			this.btnRestart.Click += new System.EventHandler(this.btnRestart_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(462, 403);
			this.Controls.Add(this.btnRestart);
			this.Controls.Add(this.lbMousePos);
			this.Controls.Add(this.lbTriCount);
			this.Controls.Add(this.lbPntCount);
			this.Controls.Add(this.pictureBox1);
			this.Name = "Form1";
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
			this.ResumeLayout(false);

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

		private void pictureBox2_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			lbMousePos.Text = e.X.ToString() + "," + e.Y.ToString();
		}		

		private void pictureBox2_MouseDown(System.Object eventSender, System.Windows.Forms.MouseEventArgs eventArgs)
		{			
			Image b = (Image)new Bitmap(pictureBox1.Width, pictureBox1.Height);
			Graphics g = Graphics.FromImage(b);
			g.CompositingMode = CompositingMode.SourceOver;
			g.SmoothingMode = SmoothingMode.None;
			Pen myPen = new Pen(Color.Blue, 1);

			//Set Vertex coordinates where you clicked the pic box
			Triangulator.Geometry.Point pNew = new Triangulator.Geometry.Point(eventArgs.X, eventArgs.Y);
			//To create a 3D point, use the Point<double> type instead:
			//Triangulator.Geometry.Point<double> pNew = new Triangulator.Geometry.Point<double>(eventArgs.X, eventArgs.Y, 3.457);

			//Only add point if another point hasn't already been added at the x,y position
			if(!Vertices.Exists(delegate(Triangulator.Geometry.Point p) { return pNew.Equals2D(p); }))
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
				lbTriCount.Text = "Triangles: " + tris.Count;
			}
			//Draw vertices
			for(int i=0;i<Vertices.Count;i++)
				g.DrawEllipse(Pens.Red, (float)Vertices[i].X-2, (float)Vertices[i].Y-2, 4, 4);

			// Display the total points and total triangles
			lbPntCount.Text = "Points: " + Vertices.Count.ToString();
		
			g.Dispose();
			pictureBox1.Image = b;
		}

		private void btnRestart_Click(object sender, EventArgs e)
		{
			Vertices.Clear();
			pictureBox1.Image = null;
			lbTriCount.Text = "Triangles: 0";
			lbPntCount.Text = "Points: 0";
		}
	}
}
