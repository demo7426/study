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
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace _13_动画基础_线性动画
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
            DoubleAnimation cDoubleAnimation = new DoubleAnimation();       //创建一个双精度动画
            cDoubleAnimation.From = btn01.Width;                            //设置动画的起始值
            cDoubleAnimation.To = btn01.Width - 30;                         //设置动画的结束值
            cDoubleAnimation.Duration = TimeSpan.FromSeconds(2);            //设置动画单次的持续时间

            cDoubleAnimation.AutoReverse = true;
            //cDoubleAnimation.RepeatBehavior = RepeatBehavior.Forever;     //设置无限执行
            cDoubleAnimation.RepeatBehavior = new RepeatBehavior(3);

            cDoubleAnimation.Completed += (object s02, EventArgs e02) =>
            {
                btn01.Content = "动画已完成";
            };

            btn01.BeginAnimation(Button.WidthProperty, cDoubleAnimation);
        }
    }
}
