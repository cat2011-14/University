using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace zadanie1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        int[] xm = new int[1000];
        int[] ym = new int[1000];
        int[] mm = new int[1000];

        private void button1_Click(object sender, EventArgs e)
        {
            Graphics g = pictureBox1.CreateGraphics();
            int x = 600;
            int y = 400;
            g.DrawRectangle(new Pen(Color.Black, 2), 0, 0, x, y);
            int x1 = x - 80;
            int y1 = y - 80;
            int x2 = 40;
            int y2 = 40;
            g.DrawRectangle(new Pen(Color.Blue, 2), x2, y2, x1, y1);
            g.DrawEllipse(new Pen(Color.Blue, 2), x / 2, 0, 4, 4);
            g.DrawEllipse(new Pen(Color.Blue, 2), 0, y / 2, 4, 4);
            g.DrawEllipse(new Pen(Color.Blue, 2), x / 2, y, 4, 4);
            g.DrawEllipse(new Pen(Color.Blue, 2), x, y / 2, 4, 4);
            int N = 10;
            int step_x = (x1) / N;
            int step_y = (y1) / N;
            xm[0] = x / 2;
            ym[0] = 0;
            xm[1]=0;
            ym[1] = y / 2;
            xm[2] = x / 2;
            ym[2] = y;
            xm[3] = x;
            ym[3] = y / 2;
            int h = 4;
            for (int i = 0; i <=1;i++)
            {
                for(int j=0;j<=N;j++)
                {
                    g.DrawEllipse(new Pen(Color.Blue, 2), x2 + (step_x * i), y1*i+y2, 3, 3);
                    xm[h] = x2 + (step_x * i);
                    ym[h] = y1 * i + y2;
                    h++;
                    g.DrawEllipse(new Pen(Color.Blue, 2), x1*i+x2, y2 + (step_y * i), 3, 3);
                    xm[h] = x1 * i + x2;
                    ym[h] = y2 + (step_y * i);
                    h++;
                }
            }
            for (int i = 0; i < N - 2; i++)
            {
                for (int j = i + 1; j < N - 1; j++)
                {
                    for (int k = j + 1; k < N; k++)
                    {
                        int error = 0;
                        double del = ((xm[j] - xm[i]) * (ym[k] - ym[i]) - ((xm[k] - xm[i]) * (ym[j] - ym[i])));
                        if (del != 0)
                        {
                            double xc = (((xm[j] * xm[j]) - (xm[i] * xm[i]) + (ym[j] * ym[j]) - (ym[i] * ym[i])) * (ym[k] - ym[i]) - (((xm[k] * xm[k]) - (xm[i] * xm[i]) + (ym[k] * ym[k]) - (ym[i] * ym[i])) * (ym[j] - ym[i]))) / del;
                            xc = xc / 2;
                            double yc = (((xm[k] * xm[k] - xm[i] * xm[i] + ym[k] * ym[k] - ym[i] * ym[i]) * (xm[j] - xm[i])) - ((xm[j] * xm[j] - xm[i] * xm[i] + ym[j] * ym[j] - ym[i] * ym[i]) * (xm[k] - xm[i]))) / ((xm[j] - xm[i]) * (ym[k] - ym[i]) - ((xm[k] - xm[i]) * (ym[j] - ym[i])));
                            yc = yc / 2;
                            double rc = ((xc - xm[i]) * (xc - xm[i]) + ((yc - ym[i]) * (yc - ym[i])));
                            for (int l = 0; l < N; l++)
                            {

                                if ((Math.Abs((xm[l] - xc) * (xm[l] - xc) + ((ym[l] - yc) * (ym[l] - yc)))) < (Math.Abs(rc)))
                                {
                                    error++;
                                }
                            }
                            if (error == 0)
                            {
                                g.DrawLine(new Pen(Color.Black, 2), xm[i], ym[i], xm[j], ym[j]);
                                g.DrawLine(new Pen(Color.Black, 2), xm[k], ym[k], xm[j], ym[j]);
                                g.DrawLine(new Pen(Color.Black, 2), xm[i], ym[i], xm[k], ym[k]);
                            }
                        }
                    }
                }
            }

        }
    }
}
