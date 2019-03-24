using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace maytnik
{
    public partial class Form1 : Form
    {
        Graphics gr;
        Pen p;
        SolidBrush fon;
        SolidBrush fig;
        public Form1()
        {
            InitializeComponent();
            textBox1.Text = Convert.ToString(0.5);
            textBox2.Text = Convert.ToString(0.4);
            textBox3.Text = Convert.ToString(0.8);
            textBox4.Text = Convert.ToString(0.4);
            textBox5.Text = Convert.ToString(1);
            textBox6.Text = Convert.ToString(0.1);
        }
        //Реализация метода Рунге-Кутты для обыкновенного дифференциального уравнения
        public abstract class RungeKutta
        {
            //текущее время
            public double t;
            //Искомое решение Y[0]-само решение , Y[i]-i-я производная решения
            public double[] Y;
            //внутренние переменные
            double[] YY, Y1, Y2, Y3, Y4;
            protected double[] FY;
            //конструктор 
            //N-размерность системы
            public RungeKutta(uint N)
            {
                Init(N);
            }
            //конструктор
            public RungeKutta() { }
            //Выделение памяти под рабочие массивы
            //N - размерность массивов
            protected void Init(uint N)
            {
                Y = new double[N];
                YY = new double[N];
                Y1 = new double[N];
                Y2 = new double[N];
                Y3 = new double[N];
                Y4 = new double[N];
                FY = new double[N];
            }
            //установка начальных условий
            //t0-начальное время
            //Y0-начальное условие
            public void SetInit(double t0, double[] Y0)
            {
                t = t0;
                if (Y == null)
                    Init((uint)Y0.Length);
                for (int i = 0; i < Y.Length; i++)
                    Y[i] = Y0[i];
            }
            //расчет правых частей системы 
            //t- текущее время
            //Y-вектор решения
            //returns правая часть
            abstract public double[] F(double t, double[] Y, double k, double m, double l0, double x0, double xt0, double nu);

            //следующий шаг метода Рунге-Кутта
            //dt-текущий шаг по времени(м.б. переменным)
            public void NextStep(double dt, double k, double m, double l0, double x0, double xt0, double nu)
            {

                int i;

                if (dt < 0) return;

                // рассчитать Y1
                Y1 = F(t, Y, k, m, l0, x0, xt0, nu);

                for (i = 0; i < Y.Length; i++)
                    YY[i] = Y[i] + Y1[i] * (dt / 2.0);

                // рассчитать Y2
                Y2 = F(t + dt / 2.0, YY, k, m, l0, x0, xt0, nu);

                for (i = 0; i < Y.Length; i++)
                    YY[i] = Y[i] + Y2[i] * (dt / 2.0);

                // рассчитать Y3
                Y3 = F(t + dt / 2.0, YY, k, m, l0, x0, xt0, nu);

                for (i = 0; i < Y.Length; i++)
                    YY[i] = Y[i] + Y3[i] * dt;

                // рассчитать Y4
                Y4 = F(t + dt, YY, k, m, l0, x0, xt0, nu);

                // рассчитать решение на новом шаге
                for (i = 0; i < Y.Length; i++)
                    Y[i] = Y[i] + dt / 6.0 * (Y1[i] + 2.0 * Y2[i] + 2.0 * Y3[i] + Y4[i]);

                // рассчитать текущее время
                t = t + dt;
            }
        }
        class TMyRK : RungeKutta
        {
            public TMyRK(uint N) : base(N) { }

            /// <summary>
            /// пример математический маятник 
            /// y''(t)+y(t)=0
            /// </summary>
            /// <param name="t">Время</param>
            /// <param name="Y">Решение</param>
            /// <returns>Правая часть</returns>
            public override double[] F(double t, double[] Y, double k, double m, double l0, double x0, double xt0, double nu)
            {
                double /*k = 0.5, m = 0.4, l0 = 0.8,*/ dl,/*,nu=0.1,*/g = 10;
                // double k = Convert.ToDouble(textbox1.Text);
                //FY[0] = Y[1];
                // FY[1] = -Y[0];
                FY[0] = Y[1];//1
                //dl = l0-Math.Sqrt(l0 * l0 + Y[1] * Y[1]);
                dl = Math.Sqrt(l0 * l0 + Y[1] * Y[1])-l0;
               /* if (Y[1] > 0)
                {
                    FY[0] = ((k * dl / m * (Y[1]) / Math.Sqrt(l0 * l0 + Y[1] * Y[1])) - nu*g);
                }
                else
                    FY[0] = ((k * dl / m * (Y[1]) / Math.Sqrt(l0 * l0 + Y[1] * Y[1])) + nu*g );
                */
                FY[1] = (k * dl * (FY[0])) / (m * Math.Sqrt(l0 * l0 + FY[0] * FY[0]));
                return FY;
            }
            /// <summary>
         
            /// </summary>

        }
        const int Nk = 500;
        double Xmin = 0;
        double Xmax;
        double step;
        int i = 0;
        double[] xmass;
        double[] xtmass;
        double[] tmass;
        double k, m, l0, x0, xt0, nu;
        double[] T;
        double[] A;
        private void CalcFunction()
        {
            Update();
            int count = i;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            chart1.Series[0].Points.Clear();
            chart1.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            xmass = new double[Nk];
            tmass = new double[Nk];
            xtmass = new double[Nk];
            double xmas, tmas, xtmas;
            k = Convert.ToDouble(textBox1.Text);
            m = Convert.ToDouble(textBox2.Text);
            l0 = Convert.ToDouble(textBox3.Text);
            x0 = Convert.ToDouble(textBox4.Text);
            xt0 = Convert.ToDouble(textBox5.Text);
            nu = Convert.ToDouble(textBox6.Text);
            // Шаг по времени
            double dt = 0.1;//0.001
            step = dt;
            // Объект метода
            TMyRK task = new TMyRK(2);
            // Определим начальные условия y(0)=0, y'(0)=1 задачи
            // double[] Y0 = { 0, 1 };
            double[] Y0 = { x0, xt0 };
            // Установим начальные условия задачи
            task.SetInit(0, Y0);
            i = 0;
            chart2.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            // решаем до 30 секунд
            while (task.t <= 50)
            {
                //Console.WriteLine("Time = {0:F5}; Func = {1:F8};  d Func / d x = {2:F8}", task.t, task.Y[0], task.Y[1]); // вывести t, y, y'
                xmass[i] = Math.Round(task.Y[0], 3);
                tmass[i] = Math.Round(task.t, 3);
                xtmass[i] = Math.Round(task.Y[1], 3);
                xmas= Math.Round(task.Y[0], 3);
                tmas = Math.Round(task.t, 3);
                xtmas = Math.Round(task.Y[1], 3);
                chart1.Series[0].Points.AddXY(xmas,xtmas);
                chart2.Series[0].Points.AddXY(tmas, xmas);
                // рассчитать на следующем шаге, шаг интегрирования 
                task.NextStep(dt, k, m, l0, x0, xt0, nu);
                i++;
            }
            double[] xrez;
            double[] trez;
            CalcFunction();
            //chart2.Series[0].Points.DataBindXY(tmass, xmass);
           // chart1.Series[0].Points.DataBindXY(xmass, xtmass);
            int x_ravn = 0, ik = 0, x1_err = 0;
            double x1 = 0, x3 = 0;
            T = new double[100];
            A = new double[100];
            xrez=new double[100];
            trez = new double[100];
            double Amax = 0;
            int yt = 0;
            int ku = 0;
            int p=0;
            int time = 0,index=0;
            double tx=0;
            int error1 = 0;
            for (int jk = 0; jk < i - 1; jk++)
            {
                if (((xmass[jk] <= 0) && (xmass[jk + 1] >= 0)) || ((xmass[jk] >= 0) && (xmass[jk + 1] <= 0)))
                {
                    if (time == 0)
                    {
                        time++;
                        error1 = 1;
                    }
                    if((time==1)&&(error1==0))
                    {
                        time++;
                    }
                    if (time==2)
                    {
                        time = 0;
                        x3 = tmass[jk];
                        double Ampl = 0;
                        for (int tk = index; tk < jk; tk++)
                        {
                            if (Math.Abs(xmass[tk]) >= Ampl) Ampl = xmass[tk];
                        }
                            chart3.Series[0].Points.AddXY(Math.Round(x3 - x1,2), Ampl);
                            x1 = x3;
                            index = jk;
                    }
                    error1 = 0;
                }
            }
           CalcFunction();
           chart3.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
         }

        private void button2_Click(object sender, EventArgs e)
        {
            Timer timer = new Timer();
            timer.Interval = 50;
            int count = 0;
            int max = Nk - 1;
            int i = 0;
            Graphics g = pictureBox1.CreateGraphics();
            g.Clear(Color.White);
            int x = 10;
            int y = 200;
            g.DrawEllipse(Pens.Black, 200 + (int)(xmass[i] * 50), y, 20, 20);
            timer.Tick += new EventHandler((o, ev) =>
            {
                i++;
                x = (int)(xmass[i] * 50);
                SolidBrush ellipse = new SolidBrush(Color.Aqua);
                SolidBrush rect = new SolidBrush(Color.DarkBlue);
                g.Clear(Color.Black);
                g.DrawRectangle(Pens.White, 170, 10, 80, 1);
                g.DrawLine(Pens.White, 210, 10, 210 + x, y);
                g.DrawRectangle(Pens.Black, 10, y + 10, 400, 5);
                g.FillRectangle(rect, 10, y + 10, 400, 5);
                g.DrawEllipse(Pens.Black, 200 + x, y, 30, 30);
                g.FillEllipse(ellipse, 200 + x, y, 30, 30);
                count++;
                if (count == max)
                {
                    Timer t = o as Timer;
                    t.Stop();
                }
            });
            timer.Start();
        }
    }
}
