using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication6
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            textBox1.Text = Convert.ToString(7);
        }
        
        int[,] number = new int[2000, 2000];
       int[,] xmass = new int[2000, 2000];
        int[,] ymass = new int[2000, 2000];
       
        private void button1_Click(object sender, EventArgs e)
        {
            Pen myPen = new Pen(Color.Black, 1);
            Graphics g = Graphics.FromHwnd(pictureBox1.Handle);
            this.pictureBox1.Location = new System.Drawing.Point(10, 10);
            this.pictureBox1.Height = 600;
            this.pictureBox1.Width = 600;
            int width = pictureBox1.Width;
            int height = pictureBox1.Height;
            int n;
            int kolich = Convert.ToInt32(textBox1.Text);
            
            n = kolich * 2 + 1;
            double size = (width)/(n+1);
            double x1=0, y1=0;
            double a = 0;
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                     x1 = j * size;
                     y1 = a;
                    int m = j % 2;
                    int k = i % 2;
                    if ((m == 1) || (k == 1))
                    {
                        number[i, j] = 1;
                    }
                    else
                    {
                        number[i, j] = 0;
                    }
                    xmass[i, j] =(int) x1;
                    ymass[i, j] = (int)y1;
                }
                a += size;
            }
            SolidBrush StenaBrush = new SolidBrush(Color.Blue);
            SolidBrush OknoBrush = new SolidBrush(Color.White);
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    double x = xmass[i, j];
                    double y = ymass[i, j];
                    if (number[i, j] == 1)
                    {
                        
                        Rectangle rect = new Rectangle((int)x, (int)y, (int)size, (int)size);
                        g.FillRectangle(StenaBrush, rect);
                    }
                    else
                    {
                        Rectangle rect = new Rectangle((int)x, (int)y, (int)size, (int)size);
                        g.FillRectangle(OknoBrush, rect);
                    }
                }
            }
        }
        int x_end, y_end, ik_end, jk_end;
        private void button2_Click(object sender, EventArgs e)
        {
            Stack<int> x = new Stack<int>();
            Stack<int> y = new Stack<int>();
            Stack<int> ikl = new Stack<int>();
            Stack<int> jkl = new Stack<int>();
            Pen myPen = new Pen(Color.Black, 1);
            Graphics g = Graphics.FromHwnd(pictureBox1.Handle);
            this.pictureBox1.Location = new System.Drawing.Point(10, 10);
            this.pictureBox1.Height = 600;
            this.pictureBox1.Width = 600;
            int width = pictureBox1.Width;
            int height = pictureBox1.Height;
            int n;
            int kolich = Convert.ToInt32(textBox1.Text);
            n = kolich * 2 + 1;
            double size = (width) / (n + 1);
            double x1 = size, y1 = size;
            double a = 0;
            int ik=2;
            int jk=2;
            
            number[ik, jk] = 2;
            SolidBrush Put1Brush = new SolidBrush(Color.Yellow);
            Rectangle rect1 = new Rectangle((int)(2*x1), (int)(y1), (int)size, (int)size);
            g.FillRectangle(Put1Brush, rect1);
            Random rand = new Random(Guid.NewGuid().GetHashCode());
            int temp,err=0;
            int sum=0;
            int ch = 0;
            int errorx=0, errory=0,errorx1=0,errory1=0;
            while(err!=1)
            {
                 errorx = 0;
                errory = 0;
                Random rand1 = new Random(unchecked((int)DateTime.Now.Ticks));
                temp = rand.Next(-1, 1);
                if (temp == -1)
                {
                    //jk += 2;
                    if ((number[ik, jk+2] == 0) && (jk+2 <= n))
                    {
                        jk += 2;
                        number[ik, jk] = 2;
                        number[ik, jk - 1] = 3;
                    }
                    else
                    {
                       // jk -= 2;
                        if ((number[ik, jk-2] == 0) && (jk-2 >= 1))
                        {
                            jk -= 2;
                            number[ik, jk] = 2;
                            number[ik, jk+1] = 3;
                        }
                        else errorx=1;
                    }
                }
                else
                {
                   // ik += 2;
                    if ((number[ik+2, jk] == 0) && (ik+2 <= n))
                    {
                        ik += 2;
                        number[ik, jk] = 2;
                        number[ik-1,jk]=3;
                    }
                    else
                    {
                        //ik -= 2;
                        if ((number[ik-2, jk] == 0) && (ik-2 >= 1))
                        {
                            ik -= 2;
                            number[ik, jk] = 2;
                            number[ik + 1, jk] = 3;
                        }
                        else errory=1;
                    }
                }
                if ((errorx == 1) || (errory == 1))
                {
                    if (errorx == 1)
                    {
                        //ik += 2;
                        if ((number[ik+2, jk] == 0) && (ik+2 <= n))
                        {
                            ik += 2;
                            number[ik, jk] = 2;
                            number[ik - 1, jk] = 3;
                        }
                        else
                        {
                           // ik -= 2;
                            if ((number[ik-2, jk] == 0) && (ik-2 >= 1))
                            {
                                ik -= 2;
                                number[ik, jk] = 2;
                                number[ik + 1, jk] = 3;
                            }
                            else errory1 = 1;
                        }
                    }

                    else
                    {
                        if (errory == 1)
                        {

                          //
                            if ((number[ik, jk+2] == 0) && (jk+2 <= n))
                            {
                                jk += 2;
                                number[ik, jk] = 2;
                                number[ik, jk - 1] = 3;
                                errory = 0;
                            }
                            else
                            {
                                //jk -= 4;
                                if ((number[ik, jk-2] == 0) && (jk-2 >= 1))
                                {
                                    jk -= 2;
                                    number[ik, jk] = 2;
                                    number[ik, jk + 1] = 3;
                                    errory = 0;
                                }
                                else errorx1 = 1;
                            }
                        }

                    }
                }
                if ((errorx1 == 1) || (errory1 == 1))
                {
                    if (x.Count() == 0)
                    {
                        err = 1;
                    }
                    else
                    {
                        x1 = x.Pop();
                        y1 = y.Pop();
                        ik = ikl.Pop();
                        jk = jkl.Pop();
                        errorx1 = 0;
                        errory1 = 0;
                        ch++;
                    }
                    if (ch == 1)
                    {
                        x_end = (int)x1;
                        y_end =(int) y1;
                        ik_end = ik;
                        jk_end = jk;
                    }
                    
                }
                else
                {
                    x1 = xmass[ik, jk];
                    y1 = ymass[ik, jk];
                    x.Push((int)x1);
                    y.Push((int)y1);
                    ikl.Push(ik);
                    jkl.Push(jk);
                    SolidBrush StenaBrush = new SolidBrush(Color.Blue);
                    SolidBrush OknoBrush = new SolidBrush(Color.White);
                    SolidBrush PutBrush = new SolidBrush(Color.Orange);
                    Rectangle rect = new Rectangle((int)x1, (int)y1, (int)size, (int)size);
                    if (number[ik, jk] == 1)
                        g.FillRectangle(StenaBrush, rect);
                    if (number[ik, jk] == 0)
                        g.FillRectangle(OknoBrush, rect);
                    if (number[ik, jk] == 2)
                        g.FillRectangle(PutBrush, rect);
                    ch = 0;
                }
        
                
            }

            SolidBrush put1Brush = new SolidBrush(Color.Orange);
            for (int i = 1; i <= n ; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    double x3 = xmass[i, j];
                    double y3 = ymass[i, j];
                    if (number[i, j] == 3)
                    {

                        Rectangle rect = new Rectangle((int)x3, (int)y3, (int)size, (int)size);
                        g.FillRectangle(put1Brush, rect);
                    }
                    
                }
            } 
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Stack<int> x_mas = new Stack<int>();
            Stack<int> y_mas = new Stack<int>();
            Stack<int> iklq = new Stack<int>();
            Stack<int> jklq = new Stack<int>();
            Pen myPen = new Pen(Color.Black, 1);
            Graphics g = Graphics.FromHwnd(pictureBox1.Handle);
            this.pictureBox1.Location = new System.Drawing.Point(10, 10);
            this.pictureBox1.Height = 600;
            this.pictureBox1.Width = 600;
            int width = pictureBox1.Width;
            int height = pictureBox1.Height;
            int n;
            int kolich = Convert.ToInt32(textBox1.Text);
            n = kolich * 2 + 1;
            double size = (width) / (n + 1);
            double x1 = size, y1 = size;
            double a = 0;
            int ik = 2;
            int jk = 2;
            number[ik, jk] = 2;
            int[] masx = new int[2000];
            int[] masy = new int[2000];
            SolidBrush Put1Brush = new SolidBrush(Color.Yellow);
            SolidBrush Put2Brush = new SolidBrush(Color.Red);
            Rectangle rect1 = new Rectangle((int)(2 * x1), (int)(y1), (int)size, (int)size);
            g.FillRectangle(Put2Brush, rect1);
            Random rand = new Random(Guid.NewGuid().GetHashCode());
            int temp,x,y, err = 0;
            int sum = 0;
            int hj = 0;
            int errorx = 0, errory = 0, errorx1 = 0, errory1 = 0;
            //while((ik!=ik_end)||(jk!=jk_end))     
            while(err!=1)
            {
                if ((number[ik, jk+1] == 2)||(number[ik,jk+1]==3))
                {
                    //if(number[ik,jk+1]==4)
                    number[ik, jk + 1] = 4;
                    //else
                    //number[ik, jk+1] = 4;
                    jk++;
                }
                else
                {
                    if ((number[ik, jk - 1] == 2) || (number[ik, jk - 1] == 3))
                     {
                       number[ik, jk - 1] = 4;
                        jk--;
                    }
                    else
                    {
                        if ((number[ik + 1, jk] == 2) || (number[ik + 1, jk] == 3))
                        {
                            number[ik + 1, jk] = 4;
                            ik++;
                        }
                        else
                        {
                            if ((number[ik - 1, jk] == 2) || (number[ik - 1, jk] == 3))
                            {
                               number[ik - 1, jk] = 4;
                                ik--;
                            }
                                else
                                {
                                    if (x_mas.Count() == 0)
                                    {
                                        err = 1;
                                    }
                                    else
                                    {
                                        number[ik, jk] = 5;
                                       // number[ik, jk] = 4;
                                        x = x_mas.Pop();
                                        y = y_mas.Pop();
                                        ik = iklq.Pop();
                                        jk = jklq.Pop();
                                        number[ik, jk] = 5;
                                        //number[ik, jk] = 4;
                                        if (number[ik, jk + 1] == 4) number[ik, jk + 1] = 3;
                                        else
                                        {
                                            if (number[ik, jk - 1] == 4) number[ik, jk - 1] = 3;
                                            else
                                            {
                                                if (number[ik + 1, jk] == 4) number[ik + 1, jk] = 3;
                                                else
                                                {
                                                    if (number[ik - 1, jk] == 4) number[ik - 1, jk] = 3;
                                                    else number[ik, jk] = 5;
                                                }
                                            }
                                        }
                                        errorx = 1;
                                    }
                                /////
                                    if ((ik == ik_end) && (jk == jk_end))
                                    {
                                        err = 1;
                                        int i = 0;
                                        x = x_mas.Pop();
                                        y = y_mas.Pop();
                                        SolidBrush put11Brush = new SolidBrush(Color.Black);
                                        Rectangle rect = new Rectangle((int)x, (int)y, (int)size, (int)size);
                                        g.FillRectangle(put11Brush, rect);
                                        
                                    }
                                }
                            }
                        }
                    }
                ///
                if (errorx == 0)
                {
                    x = xmass[ik, jk];
                    y = ymass[ik, jk];
                    x_mas.Push(x);
                    y_mas.Push(y);
                    iklq.Push(ik);
                    jklq.Push(jk);
                }
                errorx = 0;
               }

           
            SolidBrush put1Brush = new SolidBrush(Color.Black);
            SolidBrush put2Brush = new SolidBrush(Color.Yellow);
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    double x3 = xmass[i, j];
                    double y3 = ymass[i, j];
                    if (number[i, j] == 4)
                    {

                        Rectangle rect = new Rectangle((int)x3, (int)y3, (int)size, (int)size);
                        g.FillRectangle(put1Brush, rect);
                    }
                    else
                    {
                        if (number[i, j] == 5)
                        {
                            Rectangle rect = new Rectangle((int)x3, (int)y3, (int)size, (int)size);
                            g.FillRectangle(put2Brush, rect);
                        }
                    }

                }
            }
            Rectangle rect45 = new Rectangle((int)xmass[ik_end,jk_end], (int)ymass[ik_end,jk_end], (int)size, (int)size);
            g.FillRectangle(Put2Brush, rect45);
       }

       
    }
}
