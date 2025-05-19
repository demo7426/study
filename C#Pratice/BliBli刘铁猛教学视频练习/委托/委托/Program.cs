using System;
using System.Threading;
using System.Threading.Tasks;

namespace Delgate_NameSpace
{
    public delegate double CallBack(double _X, double _Y);

    internal class Program
    {
        static void Main(string[] args)
        {
            Test01();

            Console.WriteLine();
            Test02();

            Console.WriteLine();
            Test03();
        }

        /// <summary>
        /// 一共有3中委托写法，分别是Action、Func、delegate
        /// </summary>
        static void Test01()
        {
            CCalculator cCalculator = new CCalculator();

            Console.WriteLine("Action委托：");
            Action action = new Action(cCalculator.ReportMethodNum);
            action.Invoke();

            Console.WriteLine("\nFunc委托：");
            Func<int, int, double> func01 = new Func<int, int, double>(cCalculator.Add);//最后一个是返回值类型
            Func<double, double, double> func02 = new Func<double, double, double>(cCalculator.Sub);

            Console.WriteLine("\t{0}", func01.Invoke(1, 2));
            Console.WriteLine("\t{0}", func02(1, 2));

            Console.WriteLine("\ndelegate委托：");
            CallBack callBack01 = new CallBack(cCalculator.Mul);
            CallBack callBack02 = new CallBack(cCalculator.Div);

            Console.WriteLine("\t{0}", callBack01.Invoke(1, 2));
            Console.WriteLine("\t{0}", callBack02(1, 2));
        }

        /// <summary>
        /// 委托的一般使用：
        ///     把方法当作参数传给另外一个方法
        ///         a、模板方法
        ///         a、回调方法
        /// </summary>
        static void Test02()
        {
            CProductFactory cProductFactory = new CProductFactory();
            CBoxFactory cBoxFactory = new CBoxFactory();
            CLogger cLogger = new CLogger();    


            CBox cBox01 = cBoxFactory.MakeBox(cProductFactory.MakePizza, cLogger.Log);
            CBox cBox02 = cBoxFactory.MakeBox(cProductFactory.MakeToyCar, cLogger.Log);

            Console.WriteLine("委托的一般使用：");
            Console.WriteLine("\tProduct name {0}, price is {1}", cBox01.cProduct.m_strName, cBox01.cProduct.M_dbPrice);
            Console.WriteLine("\tProduct name {0}, price is {1}", cBox02.cProduct.m_strName, cBox02.cProduct.M_dbPrice);
        }

        /// <summary>
        /// 委托的高级使用：
        ///     1、多播委托
        ///     2、隐式异步调用
        /// </summary>
        static void Test03()
        {
            CStudent cStudent01 = new CStudent(1, ConsoleColor.Magenta);
            CStudent cStudent02 = new CStudent(2, ConsoleColor.Blue);
            CStudent cStudent03 = new CStudent(3, ConsoleColor.DarkCyan);

            Action[] arrAction = new Action[] { new Action(cStudent01.DoHomework), new Action(cStudent02.DoHomework), new Action(cStudent03.DoHomework) };

            Console.WriteLine("委托的高级使用：");

            Console.WriteLine("\t委托的隐式异步调用：");
            //2、隐式异步调用
            arrAction[0].BeginInvoke(null, null);
            arrAction[1].BeginInvoke(null, null);
            arrAction[2].BeginInvoke(null, null);
            Thread.Sleep(3000);

            Console.WriteLine();
            for (int i = 1; i < arrAction.Length; i++)
            {
                arrAction[0] += arrAction[i];
            }

            Console.WriteLine("\t多播委托：");
            //1、多播委托
            arrAction[0].Invoke();
            Thread.Sleep(3000);
        }

    }

    class CStudent
    {
        public int m_nID { get; set; }
        public ConsoleColor m_consoleColor  { get; set; }

        public CStudent(int _ID, ConsoleColor _ConsoleColor)
        {
            this.m_nID = _ID;
            this.m_consoleColor = _ConsoleColor;
        }

        public void DoHomework()
        {
            for (int i = 0; i < 5; i++)
            {
                Console.BackgroundColor = this.m_consoleColor;
                Console.WriteLine("\t\tStudent {0} dohomework {1} hour(s).", m_nID, i);

                Thread.Sleep(200);
            }
        }

    }

    class CCalculator
    {
        public void ReportMethodNum()
        {
            Console.WriteLine("\tThere are four methods for CCalculator.");
        }

        public double Add(int _X, int _Y)
        { return _X + _Y; }

        public double Sub(double _X, double _Y)
            { return _X - _Y; }

        public double Mul(double _X, double _Y)
            { return _X * _Y; }

        public double Div(double _X, double _Y)
            { return _X / _Y; }

    }

    class CLogger
    {
        public void Log(CProduct cProduct)
        {
            Console.WriteLine("\tWrite to database：Product name {0}, price is {1}", cProduct.m_strName, cProduct.M_dbPrice);
        }

    }

    /// <summary>
    /// 产品类
    /// </summary>
    class CProduct
    {
        /// <summary>
        /// 产品名称
        /// </summary>
        public string m_strName { get; set; }


        /// <summary>
        /// 产品价格
        /// </summary>
        private double m_dbPrice;

        /// <summary>
        /// 产品价格属性接口
        /// </summary>
        public double M_dbPrice
        {
            get { return m_dbPrice; }
            set 
            {
                if (value >= 0)
                    m_dbPrice = value;  
                else
                    throw new Exception("Product price isn't minus.");
            }
        }
    }

    /// <summary>
    /// 盒子类
    /// </summary>
    class CBox
    {
        public CProduct cProduct { get; set; }
    }

    /// <summary>
    /// 产品工厂类
    /// </summary>
    class CProductFactory
    {
        public CProduct MakePizza()
        {
            CProduct cProduct = new CProduct();
            cProduct.m_strName = "pizza";
            cProduct.M_dbPrice = 18.8;

            return cProduct;
        }

        public CProduct MakeToyCar()
        {
            CProduct cProduct = new CProduct();
            cProduct.m_strName = "toycar";
            cProduct.M_dbPrice = 128.8;

            return cProduct;
        }
    }

    /// <summary>
    /// 盒子工厂类
    /// </summary>
    class CBoxFactory
    {
        public CBox MakeBox(Func<CProduct> _Func01, Action<CProduct> _Act)
        {
            CBox cBox = new CBox();

            CProduct cProduct = _Func01.Invoke();

            cBox.cProduct = cProduct;

            if (cProduct.M_dbPrice >= 100)
            {
                _Act(cProduct);
            }

            return cBox;
        }
    }
}
