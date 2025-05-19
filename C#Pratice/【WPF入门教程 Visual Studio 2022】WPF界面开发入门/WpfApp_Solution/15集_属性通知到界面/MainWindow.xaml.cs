using System;
using System.Collections.Generic;
using System.ComponentModel;
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

namespace _15集_属性通知到界面
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        public MainWindow()
        {
            InitializeComponent();

            this.DataContext = this;
        }

        private string _UserName;

        public string UserName
        {
            get { return _UserName; }
            set { 
                _UserName = value;
                RaisePropertyChanged("UserName");
            }
        }
        
        private string _Password;

        public string Password
        {
            get { return _Password; }
            set { 
                _Password = value;
                RaisePropertyChanged("Password");
            }
        }

        /// <summary>
        /// 重写INotifyPropertyChanged接口
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// 通知客户端属性值已经被修改
        /// </summary>
        /// <param name="propertyName"></param>
        private void RaisePropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
                handler(this, new PropertyChangedEventArgs(propertyName));
        }

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
                UserName = "";
                Password = "";

                MessageBox.Show("输入的用户名或密码错误。");
            }
        }
    }
}
