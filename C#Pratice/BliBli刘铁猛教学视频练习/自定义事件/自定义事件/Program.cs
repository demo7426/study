using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace 自定义事件
{
    internal class Program
    {
        static void Main(string[] args)
        {
            CCustomer cCustomer = new CCustomer();
            CWaiter cWaiter = new CWaiter();

            cCustomer.Order += cWaiter.Action;

            cCustomer.Action();
            cCustomer.PayBill();
        }
    }

    public class OrderEventArgs:EventArgs
    {
        /// <summary>
        /// 菜名
        /// </summary>
        public string m_strDishName { get; set; }

        /// <summary>
        /// 菜的分量
        /// </summary>
        public string m_strSize { get; set; }

    }

    public delegate void OrderEventHandler(CCustomer _Customer, OrderEventArgs _OrderEventArgs);

    public class CCustomer
    {
        //事件的完整声明
        /*private OrderEventHandler orderEventHandler { get; set; }

        public event OrderEventHandler Order
        {
            add
            {
                this.orderEventHandler += value;
            }
            remove
            {
                this.orderEventHandler -= value;
            }
        }*/

        public event OrderEventHandler Order;
        /// <summary>
        /// 账单
        /// </summary>
        public double m_Bill { get; set; }

        /// <summary>
        /// 结账
        /// </summary>
        public void PayBill()
        {
            Console.WriteLine("I will pay ${0}.", m_Bill);
        }

        private void WalkIn()
        {
            Console.WriteLine("Wall into the restaurant.");
        }

        private void SitDown()
        {
            Console.WriteLine("Sit down.");
        }

        private void Think()
        {
            for (int i = 0; i < 5; i++)
            {
                Console.WriteLine("Let me think...{0}", i);
                Thread.Sleep(1000);
            }

            this.Onder("Kongpao Chicken", "large");

        }

        protected void Onder(string _DishName, string _Size)
        {
            //完整写法
            //if (this.orderEventHandler != null)
            //{
            //    this.orderEventHandler(this, new OrderEventArgs() { m_strDishName = "Kongpao Chicken", m_strSize = "small"});
            //}

            //简略写法
            if (this.Order != null)
            {
                this.Order(this, new OrderEventArgs() { m_strDishName = _DishName, m_strSize = _Size });
            }
        }

        public void Action()
        {
            Console.ReadLine();

            this.WalkIn();
            this.SitDown();
            this.Think();
        }
    }

    class CWaiter
    {
        internal void Action(CCustomer _Customer, OrderEventArgs _OrderEventArgs)
        {
            double dbPrice = 10;

            Console.WriteLine("I will serve you the dish - {0}, {1}.", _OrderEventArgs.m_strSize, _OrderEventArgs.m_strDishName);
            switch (_OrderEventArgs.m_strSize)
            {
                case "small":
                    dbPrice *= 0.5;
                    break;
                case "middle":
                    break;
                case "large":
                    dbPrice *= 1.5;
                    break;
                default:
                    throw new Exception("There is no such size!");
            }

            _Customer.m_Bill += dbPrice;
        }
    }

}
