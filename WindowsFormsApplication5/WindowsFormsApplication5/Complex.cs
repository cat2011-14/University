using System;
using System.Globalization;
using System.Text.RegularExpressions;

namespace Jenyay.Mathematics
{
	/// <summary>
	/// ����� ����������� �����
	/// </summary>
	[Serializable]
	public struct Complex
	{
		/// <summary>
		/// ��������� ���������� ��� ��������� �������� ������
		/// </summary>
		private double m_real;
		private double m_imag;

		#region ������������

		public Complex (double re)
		{
			m_real = re;
			m_imag = 0.0;
		}

		public Complex (double re, double im)
		{
			m_real = re;
			m_imag = im;
		}

		public Complex (Complex x)
		{
			m_real = x.Re;
			m_imag = x.Im;
		}

		/*public Complex (Polar x)
		{
			m_real = x.R * Math.Cos(x.Phi);
			m_imag = x.R * Math.Sin(x.Phi);
		}*/

		public static implicit operator Complex (double x)
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
			set {m_imag = value; }
		}

		public double Abs
		{
			get { return Math.Sqrt(m_imag * m_imag + m_real * m_real); }
		}


		/// <summary>
		/// �������� ����� � ��������� [0; 2* pi)
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
		/// ��������� 0 + j
		/// </summary>
		public static Complex J
		{
			get
			{
				return m_J;
			}
		}

		/// <summary>
		/// �������� ����������-����������� �����
		/// </summary>
		public Complex GetConjugate()
		{
			return new Complex (m_real, -m_imag);
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


		#region ������������� ��������� ��������
		public static Complex operator + (Complex c1, Complex c2)
		{
			return new Complex (c1.Re + c2.Re, c1.Im + c2.Im);
		}

		public static Complex operator + (Complex c1, double c2)
		{
			return new Complex (c1.Re + c2, c1.Im);
		}

		public static Complex operator + (double  c1, Complex c2)
		{
			return new Complex (c1 + c2.Re, c2.Im);
		}
		#endregion


		#region ������������� ��������� ���������
		public static Complex operator - (Complex c1, Complex c2)
		{
			return new Complex (c1.Re - c2.Re, c1.Im - c2.Im);
		}

		public static Complex operator - (Complex c1, double c2)
		{
			return new Complex (c1.Re - c2, c1.Im);
		}

		public static Complex operator - (double  c1, Complex c2)
		{
			return new Complex (c1 - c2.Re, -c2.Im);
		}
		#endregion


		#region ������������� ��������� ���������
		public static Complex operator * (Complex c1, Complex c2)
		{
			return new Complex (c1.Re * c2.Re - c1.Im * c2.Im,
				c1.Re * c2.Im + c1.Im * c2.Re);
		}

		public static Complex operator * (Complex c1, double c2)
		{
			return new Complex (c1.Re * c2, c1.Im * c2);
		}

		public static Complex operator * (double c1, Complex c2)
		{
			return new Complex (c1 * c2.Re, c1 * c2.Im);
		}
		#endregion


		#region ������������� ��������� �������
		public static Complex operator / (Complex c1, Complex c2)
		{
			double Denominator = c2.Re * c2.Re + c2.Im * c2.Im;
			return new Complex ((c1.Re * c2.Re + c1.Im * c2.Im) / Denominator,
				(c2.Re * c1.Im - c2.Im * c1.Re) / Denominator);
		}

		public static Complex operator / (Complex c1, double c2)
		{
			return new Complex (c1.Re / c2, c1.Im / c2);
		}

		public static Complex operator / (double c1, Complex c2)
		{
			double Denominator = c2.Re * c2.Re + c2.Im * c2.Im;
			return new Complex ((c1 * c2.Re) / Denominator, (-c2.Im * c1) / Denominator);
		}
		#endregion

		#region ��������� ���������
		public static bool operator == (Complex c1, Complex c2)
		{
			return c1.Re == c2.Re && c1.Im == c2.Im;
		}

		public static bool operator == (Complex c, double x)
		{
			return c.Im == 0 && c.Re == x;
		}

		public static bool operator == (double d, Complex c)
		{
			return c == d;
		}

		public static bool operator != (Complex c1, Complex c2)
		{
			return !(c1 == c2);
		}

		public static bool operator != (Complex c, double x)
		{
			return !(c == x);
		}

		public static bool operator != (double x, Complex c)
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

		/*public Polar Polar
		{
			get
			{
				return new Polar(this);
			}
			set
			{
				m_real = value.R * Math.Cos(value.Phi);
				m_imag = value.R * Math.Sin(value.Phi);
			}
		}*/

		/// <summary>
		/// ������� ���������� ������
		/// </summary>
		/// <param name="c">�����, �� �������� ������� ������</param>
		/// <returns></returns>
		public static Complex Sqrt (Complex c)
		{
			double abs = Math.Sqrt(c.Abs);
			return new Complex (abs * Math.Cos(c.Arg / 2), abs * Math.Sin(c.Arg / 2));
		}

		public static Complex Sqrt(double x)
		{
			// �� ����, ���� x < 0, �� ���-� ������ ���� +- a*i, �� ���-���� ���������� ������ � +.
			return x >= 0 ? new Complex(Math.Sqrt(x)) : new Complex (0, Math.Sqrt(-x));
		}

		/// <summary>
		/// ������� ��� ����� ������� n (n ����)
		/// </summary>
		/// <param name="c">�����, �� �������� ��������� ������</param>
		/// <param name="n">������� �����</param>
		/// <returns>������ � ������������</returns>
		public static Complex[] Radical (Complex c, int n)
		{
			Complex[] res = new Complex[n];

			double abs = Math.Pow(c.Abs, 1.0 / n);

			// ��������� ����
			double Phi0 = c.Arg / n;

			// ��� �� ����
			double dPhi = 2 * Math.PI / n;

			for (int i = 0; i < n; ++i)
			{
				double CurrPhi = Phi0 + i * dPhi;
				res[i] = new Complex(abs * Math.Cos(CurrPhi), abs * Math.Sin(CurrPhi));
			}

			return res;
		}


		/// <summary>
		/// ������� ���������� ���� Complex �� ������
		/// </summary>
		/// <param name="str">������, �� ������� ������� ����������</param>
		/// <remarks>
		///	 ��������� �������� �����:
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
		/// <returns>���������� ���������� ��� ������� ���������� � ������ �������</returns>
		public static Complex Parse(string str)
		{
			/*Regex r = new Regex(@"^\s*(?<re>[\+-]?\d+([,.]\d+)?([eE][\+-]?\d+)?)?\s*((?<im>([\+-]\d+([,.]\d+)?([eE]?[\+-]?\d*)?)?)[ij])?\s*$");
			Match match = r.Match(str);


			string re = match.Groups["re"].Value;
			string im = match.Groups["im"].Value;

			if (re.Length == 0)
			{
				re = "0";
			}

			if (im.Length == 0)
			{
				im = "0";
			}*/

			Complex res = 0;

			// ������ ������ ����� ������ � ������ ��������
			Regex regim = new Regex(@"(?<im>[\+-]?\d*(?:[,.]\d+)?(?:[eE][\+-]?\d+)?[ij])");
			Match match = regim.Match(str);

			string im = match.Groups["im"].Value;
			if (im.Length == 0)
			{
				im = "0";
			}
			else if (im[im.Length - 1] == 'i' || im[im.Length - 1] == 'j')
			{
				// ������ ������ �������
				im = im.Substring(0, im.Length - 1);

				if (im == "+" || im.Length == 0)
				{
					im = "1";
				}
				else if (im == "-")
				{
					im = "-1";
				}
			}
			else
			{
				throw new FormatException(str);
			}

			string re = regim.Replace(str, "");
			if (re.Length == 0)
			{
				re = "0";
			}

			res = new Complex(Double.Parse(re), Double.Parse(im));

			return res;
		}
		/*public static Complex Parse(string str)
		{
			// � �������� i ����� ���� �������� j � ����� ���� ����� ����� ��������

			// 1. ������� ��� �������
			string TempStr = str.Replace(" ", "");

			// 2. �������� j �� i
			TempStr = TempStr.Replace("j", "i");

			// 3. ������� ������ �����
			double imag = 0;

			// ���� ��������� ������ - i, ������ ������ ����� ����
			int pos = TempStr.Length - 1;
			if (TempStr[TempStr.Length - 1] == 'i')
			{
				string ImagStr = "";

				for (pos--; pos >= 0; --pos)
				{
					char CurrChar = TempStr[pos];

					// ���� ���� �����, �� ������ ��������� ������ � ������
					if (CurrChar >= '0' && CurrChar <= '9' || 
						CurrChar.ToString() == CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator)
					{
						ImagStr = CurrChar + ImagStr;
					}
					else if (CurrChar == '+' || CurrChar == '-')
					{
						// ���� ����, �� ��������� ��� � �������� ����
						ImagStr = CurrChar + ImagStr;

						// ���� ������ ������ ������� �� ������ �����, �� ������� 1
						if (ImagStr.Length == 1)
						{
							ImagStr += "1";
						}
						break;
					}
					else
					{
						// ���� ���-�� ������, ������ ������
						throw new FormatException (str);
					}
				}

				if (ImagStr.Length == 0)
				{
					imag = 1.0;
				}
				else
				{
					imag = Convert.ToDouble(ImagStr);
				}
				pos--;
			}

			// 4. �������� �������� �����
			double real = 0;
			// ���� ��� ����� ���� �������� �����
			if (pos >= 0)
			{

				// ���� ������ ���� �����
				if (TempStr[pos] >= '0' && TempStr[pos] <= '9')
				{
					string RealStr = TempStr[pos].ToString();

					for (pos--; pos >= 0; --pos)
					{
						char CurrChar = TempStr[pos];

						// ���� ���� �����, �� ������ ��������� ������ � ������
						if (CurrChar >= '0' && CurrChar <= '9' || 
							CurrChar.ToString() == CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator)
						{
							RealStr = CurrChar + RealStr;
						}
						else if (CurrChar == '+' || CurrChar == '-')
						{
							// ���� ����, �� ��������� ��� � �������� ����
							RealStr = CurrChar + RealStr;
							break;
						}
						else
						{
							// ���� ���-�� ������, ������ ������
							throw new FormatException (str);
						}
					}

					real = Convert.ToDouble(RealStr);
				}
				else
				{
					throw new FormatException (str);
				}
			}

			return new Complex(real, imag);
		}*/

		/// <summary>
		/// ���������� ���������� ������������ �����
		/// </summary>
		/// <param name="c">����� �� �������� ���� ����������</param>
		public static Complex Exp (Complex c)
		{
			//return new Complex (new Polar(Math.Exp(c.Re), c.Im) );

			double abs = Math.Exp(c.Re);
			return new Complex (abs * Math.Cos (c.Im), abs * Math.Sin (c.Im));
		}


		/// <summary>
		/// ���������� ������������ ����� � �������
		/// </summary>
		/// <param name="n">������� � ������� �������� �����</param>
		


		/// <summary>
		/// �����
		/// </summary>
		/// <param name="x"></param>
		/// <returns></returns>
		public static Complex Sin (Complex x)
		{
			return (Complex.Exp(Complex.J * x) -
				Complex.Exp (-1 * Complex.J * x) ) / ( 2 * Complex.J );
		}

		/// <summary>
		/// �������
		/// </summary>
		/// <param name="x"></param>
		/// <returns></returns>
		public static Complex Cos (Complex x)
		{
			return ( Complex.Exp (Complex.J * x) +
				Complex.Exp (-1 * Complex.J * x) ) / 2;
		}

		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="x"></param>
		/// <returns></returns>
		public static Complex Asin (Complex x)
		{
			return -1 * Complex.J * Complex.Log (Complex.J * x + 
				Complex.Sqrt (1 - x * x));
		}

		/// <summary>
		/// ����������
		/// </summary>
		/// <param name="x"></param>
		/// <returns></returns>
		public static Complex Acos (Complex x)
		{
			return -1 * Complex.J * Complex.Log (x + Complex.J * 
				Complex.Sqrt (1 - x * x));
		}

		/// <summary>
		/// ����������� ��������
		/// </summary>
		/// <param name="x"></param>
		/// <returns></returns>
		public static Complex Log (Complex x)
		{
			return Math.Log(x.Abs) + Complex.J * x.Arg;
		}
	}
}
