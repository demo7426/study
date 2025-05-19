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

namespace _17集_图书馆程序_MVVM_ViewMode演示
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private CLoginViewModel cLoginViewModel { get; set; }
        public MainWindow()
        {
            InitializeComponent();

            cLoginViewModel = new CLoginViewModel();
            this.DataContext = cLoginViewModel;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (cLoginViewModel.cLoginModel.UserName.CompareTo("wpf") == 0 && cLoginViewModel.cLoginModel.Password.CompareTo("7426") == 0)
            {
                Window1 window1 = new Window1();
                window1.Show();

                this.Hide();
            }
            else
            {
                cLoginViewModel.cLoginModel.UserName = "";
                cLoginViewModel.cLoginModel.Password = "";
                cLoginViewModel.NotifyPropertyChanged();

                MessageBox.Show("输入的用户名或密码错误。");
            }
        }
    }
}
