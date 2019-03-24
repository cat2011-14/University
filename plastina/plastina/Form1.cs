using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace plastina
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        int xmax = 100;
        double Q = 0.0;
        double n_e = 0.0;
        double F(double x,double y,bool qnull)
        {
            //линеаризованние уравнение Пуассона-Больцмана
            double R0 = xmax / 100;
            double ro = 3 * Q / (4 * 3.14159 * R0 * R0 * R0);
            double fi = -1 * (n_e * y);//окончательно уравнение пуассона примет вид
            if(x<R0 && !qnull)
            {
                fi -= ro;
            }
            return fi;

        }
       
        int N = 1000;
        int j = 0;
        double deltaR = 0.5;
        double Rmax = 0;
        double RungeKutt(double Y,double Y0,double dYdX0,bool qnull)
        {
           
            double K1 = 0.0;
            double K2 = 0.0;
            double K3 = 0.0;
            double K4 = 0.0;
            double FI = Y0;
            double E = dYdX0;
            double RR = 0;
           
            do
            {
                RR += deltaR;
                K1 = deltaR * (-2.0 / RR * E + F(RR, FI, qnull));
                K2 = deltaR * (-2.0 / (RR + 0.5 * deltaR) * (E + 0.5 * K1) + F((RR + 0.5 * deltaR), (FI + E * 0.5 * deltaR), qnull));
                K3 = deltaR * (-2.0 / (RR + 0.5 * deltaR) * (E + 0.5 * K2) + F((RR + 0.5 * deltaR), (FI + E * 0.5 * deltaR + 0.25 * K1 * deltaR), qnull));
                K4 = deltaR * (-2.0 / (RR + deltaR) * (E + K3) + F((RR + deltaR), (FI + E * deltaR + 0.5 * K2 * deltaR), qnull));
                FI += (E + (K1 + K2 + K3) / 6.0) * deltaR;
                E += (K1 + K2 + K3 + K4) / 6.0;
               
            }
            while (RR <= Rmax);
            j++;
            Y = FI;
            return FI;

        }
        double potencialnachalo = 100;
        double potencialend = 0;
       
        int M = 10000;

        double RungeKutt2(double Y, double Y0, double dYdX0, bool qnull)
        {

            double K1 = 0.0;
            double K2 = 0.0;
            double K3 = 0.0;
            double K4 = 0.0;
            double FI = Y0;
            double E = dYdX0;
            double RR = 0;
            int i = 0;
            do
            {
                RR += deltaR;
                K1 = deltaR * (-2.0 / RR * E + F(RR, FI, qnull));
                K2 = deltaR * (-2.0 / (RR + 0.5 * deltaR) * (E + 0.5 * K1) + F((RR + 0.5 * deltaR), (FI + E * 0.5 * deltaR), qnull));
                K3 = deltaR * (-2.0 / (RR + 0.5 * deltaR) * (E + 0.5 * K2) + F((RR + 0.5 * deltaR), (FI + E * 0.5 * deltaR + 0.25 * K1 * deltaR), qnull));
                K4 = deltaR * (-2.0 / (RR + deltaR) * (E + K3) + F((RR + deltaR), (FI + E * deltaR + 0.5 * K2 * deltaR), qnull));
                FI += (E + (K1 + K2 + K3) / 6.0) * deltaR;
                E += (K1 + K2 + K3 + K4) / 6.0;
                double R = (double)i * Rmax / (500);
                chart1.Series[0].Points.AddXY(R, FI);
                i++;
            }
            while (RR <= Rmax);
           // j++;
            Y = FI;
            return j;

        }
        private void button1_Click(object sender, EventArgs e)
        {
            Rmax=100;
	        xmax=(int)Rmax;
            double potencial=0;
	        //метод суперпозиции
	        double Потенциал1=0.0;
	        Потенциал1=RungeKutt(potencial,potencialnachalo,0.0,false);
	        double Потенциал2=0.0;
            Потенциал2 = RungeKutt(potencial, 0.0, 1.0, true);
	        double Ню=(potencialend-Потенциал1)/Потенциал2;//ищем ню
	        RungeKutt2(potencial,potencialnachalo,Ню,false);//находим функцию

        }
    }
}
