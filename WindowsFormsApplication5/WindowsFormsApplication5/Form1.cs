using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication5
{
    public struct Complex
    {

        private double m_real;
        private double m_imag;

        #region Конструкторы

        public Complex(double re)
        {
            m_real = re;
            m_imag = 0.0;
        }

        public Complex(double re, double im)
        {
            m_real = re;
            m_imag = im;
        }

        public Complex(Complex x)
        {
            m_real = x.Re;
            m_imag = x.Im;
        }



        public static implicit operator Complex(double x)
        {
            return new Complex(x);
        }
        #endregion

        public double Re
        {
            get { return m_real; }
            set { m_real = value; }
        }

        public double Im
        {
            get { return m_imag; }
            set { m_imag = value; }
        }

        public double Abs
        {
            get { return Math.Sqrt(m_imag * m_imag + m_real * m_real); }
        }


        /// <summary>
        /// Аргумент числа в интервале [0; 2* pi)
        /// </summary>
        public double Arg
        {
            get
            {
                double res = Math.Atan2(m_imag, m_real);
                /*if (res < 0)
                {
                    res += Math.PI;
                }*/
                return res;
            }
        }

        private static Complex m_J = new Complex(0.0, 1.0);
        /// <summary>
        /// Константа 0 + j
        /// </summary>
        public static Complex J
        {
            get
            {
                return m_J;
            }
        }

        /// <summary>
        /// Получить комплексно-сопряженное число
        /// </summary>
        public Complex GetConjugate()
        {
            return new Complex(m_real, -m_imag);
        }

        public override string ToString()
        {
            string res = m_real.ToString();

            if (m_imag != 0.0)
            {
                if (m_imag > 0)
                {
                    res += "+";
                }

                res += m_imag.ToString() + "i";
            }

            return res;
        }


        #region Перегруженные операторы сложения
        public static Complex operator +(Complex c1, Complex c2)
        {
            return new Complex(c1.Re + c2.Re, c1.Im + c2.Im);
        }

        public static Complex operator +(Complex c1, double c2)
        {
            return new Complex(c1.Re + c2, c1.Im);
        }

        public static Complex operator +(double c1, Complex c2)
        {
            return new Complex(c1 + c2.Re, c2.Im);
        }
        #endregion


        #region Перегруженные операторы вычитания
        public static Complex operator -(Complex c1, Complex c2)
        {
            return new Complex(c1.Re - c2.Re, c1.Im - c2.Im);
        }

        public static Complex operator -(Complex c1, double c2)
        {
            return new Complex(c1.Re - c2, c1.Im);
        }

        public static Complex operator -(double c1, Complex c2)
        {
            return new Complex(c1 - c2.Re, -c2.Im);
        }
        #endregion


        #region Перегруженные операторы умножения
        public static Complex operator *(Complex c1, Complex c2)
        {
            return new Complex(c1.Re * c2.Re - c1.Im * c2.Im,
                c1.Re * c2.Im + c1.Im * c2.Re);
        }

        public static Complex operator *(Complex c1, double c2)
        {
            return new Complex(c1.Re * c2, c1.Im * c2);
        }

        public static Complex operator *(double c1, Complex c2)
        {
            return new Complex(c1 * c2.Re, c1 * c2.Im);
        }
        #endregion


        #region Перегруженные операторы деления
        public static Complex operator /(Complex c1, Complex c2)
        {
            double Denominator = c2.Re * c2.Re + c2.Im * c2.Im;
            return new Complex((c1.Re * c2.Re + c1.Im * c2.Im) / Denominator,
                (c2.Re * c1.Im - c2.Im * c1.Re) / Denominator);
        }

        public static Complex operator /(Complex c1, double c2)
        {
            return new Complex(c1.Re / c2, c1.Im / c2);
        }

        public static Complex operator /(double c1, Complex c2)
        {
            double Denominator = c2.Re * c2.Re + c2.Im * c2.Im;
            return new Complex((c1 * c2.Re) / Denominator, (-c2.Im * c1) / Denominator);
        }
        #endregion

        #region Операторы сравнения
        public static bool operator ==(Complex c1, Complex c2)
        {
            return c1.Re == c2.Re && c1.Im == c2.Im;
        }

        public static bool operator ==(Complex c, double x)
        {
            return c.Im == 0 && c.Re == x;
        }

        public static bool operator ==(double d, Complex c)
        {
            return c == d;
        }

        public static bool operator !=(Complex c1, Complex c2)
        {
            return !(c1 == c2);
        }

        public static bool operator !=(Complex c, double x)
        {
            return !(c == x);
        }

        public static bool operator !=(double x, Complex c)
        {
            return !(c == x);
        }

        public override bool Equals(object obj)
        {
            if (obj == null || obj.GetType() != this.GetType())
            {
                return false;
            }

            return this == (Complex)obj;
        }
        #endregion

        public override int GetHashCode()
        {
            return m_real.GetHashCode() + m_imag.GetHashCode();
        }

        /// <summary>
        /// Считает квадратный корень
        /// </summary>
        /// <param name="c">Число, из которого считают корень</param>
        /// <returns></returns>
        public static Complex Sqrt(Complex c)
        {
            double abs = Math.Sqrt(c.Abs);
            return new Complex(abs * Math.Cos(c.Arg / 2), abs * Math.Sin(c.Arg / 2));
        }

        public static Complex Sqrt(double x)
        {
            // По идее, если x < 0, то рез-т должен быть +- a*i, но все-таки возвращаем только с +.
            return x >= 0 ? new Complex(Math.Sqrt(x)) : new Complex(0, Math.Sqrt(-x));
        }

        /// <summary>
        /// Считает все корни степени n (n штук)
        /// </summary>
        /// <param name="c">Число, из которого извлекаем корень</param>
        /// <param name="n">Степень корня</param>
        /// <returns>Массив с результатами</returns>
        public static Complex[] Radical(Complex c, int n)
        {
            Complex[] res = new Complex[n];

            double abs = Math.Pow(c.Abs, 1.0 / n);

            // Начальный угол
            double Phi0 = c.Arg / n;

            // Шаг по углу
            double dPhi = 2 * Math.PI / n;

            for (int i = 0; i < n; ++i)
            {
                double CurrPhi = Phi0 + i * dPhi;
                res[i] = new Complex(abs * Math.Cos(CurrPhi), abs * Math.Sin(CurrPhi));
            }

            return res;
        }


        /// <summary>
        /// Создает переменную типа Complex из строки
        /// </summary>
        /// <param name="str">Строка, по которой создаем переменную</param>
        /// <remarks>
        ///	 Возможные варианты строк:
        ///	 1+5i
        ///	 1 + 5i
        ///	 +1 + 5i
        ///	 -1 - 5i
        ///	 -5
        ///	 -6i
        ///	 +6i
        ///	 i
        ///	 1+i
        ///	 -i
        /// </remarks>
    }
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        double K = 100;
        double R = 1.5;
        double time = 10;
        double Psi_0 = 20;
        double sigma = 0.1;
        double a = 0.5;
        double step_x = 0.01;
        double step_t = 0.006;
        double write_step = 6;
        double gamma = 1;
        double Potential(double x)
        {
            return (K * x * x / 2.0);
        }
        double GaussianWavePacket(double x)
        {
            return (Psi_0 * Math.Exp(-(x - a) * (x - a) / (4 * sigma * sigma)));
        }
        double[] mas;
        double xmas;
        double xmin;
        int N = 500;
        double MaxMin()
        {
            int imin = 0;
            int imax = 0;
            for (int i = 0; i < N;i++)
            {
                if (AbsPsi[i] < AbsPsi[imin]) imin = i;
                if (AbsPsi[i] > AbsPsi[imax]) imax = i;
            }
           double  yMax = AbsPsi[imax];
                return 1;
        }
        double[] x;
        double[] U;
        double[] t;
        double countofPoints_t;
        Complex[] Psi;
        double[] AbsPsi;
        double coef = 0.3;
        double Sigma(double x)
        {
            double a_gr = R - coef * R;
            if (Math.Abs(x) <= a_gr)
            {
                return 0;
            }
            if (x > a_gr)
            {
                return (x - a_gr) * (x - a_gr);
            }
            if (x < -a_gr)
            {
                return (x + a_gr) * (x + a_gr);
            }
            return 0;
        }
        Complex f(double x)
        {
           Complex buf=new Complex();
	        buf.Im=gamma*Sigma(x);
	        return (1.0/(1.0+buf));
        }
        double Sigma_diff(double x)
        {
            double a_gr = R - coef * R;
	            if (Math.Abs(x) <= a_gr)
	            {
		            return 0;
	            }
	            if (x > a_gr)
	            {
		            return 2.0*(x - a_gr);
	            }
	            if (x < -a_gr)
	            {
		            return 2*(x + a_gr);
	            }
            return 0;
        }
        Complex f_diff(double x)
        {
            Complex buf1=new Complex();
	        buf1.Im=gamma*Sigma(x);
	        Complex buf2=new Complex();
	        buf2.Im = gamma*Sigma_diff(x);
	        return ((-1)*buf2 / ((1.0 + buf1)*(1.0 + buf1)));
        }
        private void button1_Click(object sender, EventArgs e)
        {
            int countofPoints_x=(int)(2*Math.Abs(R)/step_x);
            x = new double[N];
            U = new double[N];
            Psi = new Complex[N];
            AbsPsi = new double[N];
            for(int i=0;i<N;i++)
            {
                x[i] = -Math.Abs(R) + step_x * i;
                U[i] = Potential(x[i]);
            }
            countofPoints_t = time / step_t;
            t = new double[N];
            for(int i=0;i<N;i++)
            {
                t[i] = i * step_t;
            }
            for(int i=0;i<N;i++)
            {
                Psi[i].Re = GaussianWavePacket(x[i]);
                Psi[i].Im = 0.0;
            }
            double x1=0;
            for(int k=0;k<N;k++)
            {
                AbsPsi[k] = Psi[k].Abs;
                chart1.Series[0].Points.AddXY(x1, AbsPsi[k]);
                x1 += step_x;
            }
            double tl=MaxMin();
            Timer timer = new Timer();
            timer.Interval = 10;
            int ig = 0;
           
            Complex []A;
            Complex[] B;
            Complex[] C;
            Complex[] D;
            Complex[] alpha;
            Complex[] beta;
            Complex[] Psi1;
            timer.Tick += new EventHandler((o, ev) =>
            {
                double x2 = 0;
                A=new Complex[N];
                B=new Complex[N];
                C=new Complex[N];
                D=new Complex[N];
                Psi1=new Complex[N];
                alpha=new Complex[N];
                beta=new Complex[N];
                for(int k=1;k<N-1;k++)
                {
                   Complex  buf=new Complex();
                    buf=step_t / 2.0 * ((-1)*f(x[k])*f_diff(x[k]) / (x[k + 1] - x[k - 1]) + 2.0 * f(x[k])*f(x[k]) / ((x[k + 1] - x[k - 1])*(x[k] - x[k - 1])));
                    A[k].Re=-buf.Im;
                    A[k].Im=buf.Re;

                    buf = step_t / 2.0*(f(x[k])*f_diff(x[k]) / (x[k + 1] - x[k - 1]) + 2.0* f(x[k])*f(x[k]) / ((x[k + 1] - x[k - 1])*(x[k + 1] - x[k])));
		            B[k].Re=-buf.Im;
		            B[k].Im=buf.Re;

                    buf = step_t / 2.0 * ((-1)*f(x[k])*f(x[k])*2.0 / ((x[k + 1] - x[k - 1])*(x[k + 1] - x[k])) - 2.0 * f(x[k])*f(x[k]) / ((x[k + 1] - x[k - 1])*(x[k] - x[k - 1])) - U[k]);
		            C[k].Re=-buf.Im;
		            C[k].Im=buf.Re;
		            C[k] -= 1;

                    buf = -step_t / 2.0*((f(x[k])*f_diff(x[k])*(Psi[k + 1] - Psi[k - 1]) / (x[k + 1] - x[k - 1]) + f(x[k])*f(x[k])*2.0 / (x[k + 1] - x[k - 1])*((Psi[k + 1] - Psi[k]) / (x[k + 1] - x[k]) - (Psi[k] - Psi[k - 1]) / (x[k] - x[k - 1])) - U[k] * Psi[k]));
		            D[k].Re=-buf.Im;
		            D[k].Im=buf.Re;
		            D[k] -= Psi[k];
                }
                alpha[1].Re=0;
                alpha[1].Im=0;
                beta[1].Re=0;
                beta[1].Im=0;
                for(int k=1;k<N-1;k++)
                {
                    alpha[k+1]=(-1)*B[k]/(C[k]+A[k]*alpha[k]);
                    beta[k+1]=(D[k]-A[k]*beta[k])/(C[k]+A[k]*alpha[k]);
                }
                for(int k=N-1;k>1;k--)
                {
                    Psi1[k-1]=alpha[k]*Psi[k]+beta[k];
                }
                double[] AbsPsi1;
                AbsPsi1=new double[N];
                for(int k=0;k<N-1;k++)
                {
                    AbsPsi1[k]=Psi1[k].Abs;
                }
                for (int h = 0; h < N; h++)
                {
                    chart1.Series[0].Points.AddXY(x2, AbsPsi1[h]);
                    x2 += step_x;
                }
                if (ig == 100)
                {
                    Timer tlh = o as Timer;
                    tlh.Stop();
                }
                ig++;
               
            });
            timer.Start();
        }
    }
}
