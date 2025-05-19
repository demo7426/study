using GalaSoft.MvvmLight.Messaging;
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

namespace _09_WPF框架_MvvmLight_
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            //安装NuGet程序包,它在其中继承了ICommand、INotifyPropertyChanged接口，不需要自己实现
            DataContext = new MainWindowViewMode();

            //注册一个Messenger01接收员标记符
            Messenger.Default.Register<string>(this, "Messenger01", Show);
        }

        void Show(string _Msg)
        {
            MessageBox.Show(_Msg);
        }
    }
}
