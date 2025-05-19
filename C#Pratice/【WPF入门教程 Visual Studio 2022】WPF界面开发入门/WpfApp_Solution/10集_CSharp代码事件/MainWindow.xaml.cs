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

namespace _10集_CSharp代码事件
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            int[] nArrayNum = new int[2] { 100, 200 };
            int nSum = 0;
            foreach (var item in nArrayNum)
            {
                nSum += item;
            }

            xamlTextBlock.Text = nSum.ToString();
            xamlTextBlock.Visibility = Visibility.Visible;//可视化
        }

        private void Button_MouseEnter(object sender, MouseEventArgs e)
        {
            xamlTextBlock.Text = "鼠标进入按钮";
            xamlTextBlock.Visibility = Visibility.Visible;//可视化
        }

        private void Button_MouseLeave(object sender, MouseEventArgs e)
        {
            xamlTextBlock.Text = "鼠标离开按钮";
            xamlTextBlock.Visibility = Visibility.Visible;//可视化
        }
    }
}
