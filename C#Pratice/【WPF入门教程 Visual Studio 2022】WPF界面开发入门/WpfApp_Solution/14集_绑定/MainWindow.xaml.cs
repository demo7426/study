using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace _14集_绑定
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            this.DataContext = this;
        }

        public string UserName { get; set; }
        public string Password { get; set; }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (UserName.CompareTo("wpf") == 0 && Password.CompareTo("7426") == 0)
            {
                Window1 window1 = new Window1();
                window1.Show();

                this.Hide();
            }
            else
            {
                MessageBox.Show("输入的用户名或密码错误。");
            }
        }
    }
}
