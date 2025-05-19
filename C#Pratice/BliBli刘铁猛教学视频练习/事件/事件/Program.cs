using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Forms;

namespace 事件
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //Test01();
            //Test02();
            Test03();
        }

        /// <summary>
        /// 事件的拥有者和事件的响应者不是同一个人
        /// </summary>
        static void Test01()
        {
            System.Timers.Timer timer = new System.Timers.Timer();
            CBoy cBoy = new CBoy();
            CGirl cGirl = new CGirl();

            timer.Interval = 1000;
            timer.Elapsed += cBoy.Action;
            timer.Elapsed += cGirl.Action;

            timer.Start();
            Console.ReadLine();
        }

        /// <summary>
        /// 事件的拥有者同时也是事件的响应者
        /// </summary>
        static void Test02()
        {
            Form form = new Form();
            CMyForm cMyForm = new CMyForm(form);

            form.ShowDialog();
        }

        /// <summary>
        /// 事件的拥有者、事件的响应者不是同一人，但同属于一个集合,
        /// </summary>
        static void Test03()
        {
            CMyForm02 cMyForm02 = new CMyForm02();
            cMyForm02.ShowDialog();
        }
    }

    class CBoy
    {
        internal void Action(object sender, ElapsedEventArgs e)
        {
            Console.WriteLine("Boy jump!");
        }
    }

    class CGirl
    {
        internal void Action(object sender, ElapsedEventArgs e)
        {
            Console.WriteLine("Girl jump!");
        }
    }

    class CMyForm
    {
        private Form m_form { get; set; }

        public CMyForm(Form _Form)
        {
            if (_Form != null)
            {
                this.m_form = _Form;
                this.m_form.Click += this.ClickEvent;
            }
        }

        private void ClickEvent(object sender, EventArgs e)
        {
            this.m_form.Text = DateTime.Now.ToString();
        }
    }

    class CMyForm02 : Form
    {
        private TextBox m_textBox { get; set; }
        private Button m_button { get; set; }

        /// <summary>
        /// 事件响应者的四种订阅方法
        /// </summary>
        public CMyForm02()
        {
            this.m_textBox = new TextBox();
            this.m_button = new Button();
            this.Controls.Add(this.m_textBox);
            this.Controls.Add(this.m_button);

            this.m_button.Text = "Say Hello world.";
            this.m_button.Top = 20;
            this.m_button.AutoSize = true;

            //this.m_button.Click += this.ButtonClicked;

            ////委托(两个委托实质上是一致的，EventHandler底层也是delegate)
            //this.m_button.Click += new System.EventHandler(this.ButtonClicked);

            //lamda表达式
            this.m_button.Click += (s, e) =>
            {
                this.m_textBox.Text = "Hello world.";
            };

            ////委托(两个委托实质上是一致的)
            //this.m_button.Click += delegate (object sender, EventArgs e)
            //{
            //    this.m_textBox.Text = "Hello world.";
            //};
        }

        private void ButtonClicked(object sender, EventArgs e)
        {
            this.m_textBox.Text = "Hello world.";
        }
    }
}
