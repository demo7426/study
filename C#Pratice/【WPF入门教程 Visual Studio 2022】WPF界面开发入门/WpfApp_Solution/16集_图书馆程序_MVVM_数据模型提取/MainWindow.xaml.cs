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

namespace _16集_图书馆程序_MVVM_数据模型提取
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private CLoginModel cLoginModel { get; set; }

        public MainWindow()
        {
            InitializeComponent();

            cLoginModel = new CLoginModel();
            this.DataContext = cLoginModel;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (cLoginModel.UserName.CompareTo("wpf") == 0 && cLoginModel.Password.CompareTo("7426") == 0)
            {
                Window1 window1 = new Window1();
                window1.Show();

                this.Hide();
            }
            else
            {
                cLoginModel.UserName = "";
                cLoginModel.Password = "";

                MessageBox.Show("输入的用户名或密码错误。");
            }
        }
    }
}
