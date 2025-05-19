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

namespace _04_WPF数据模板
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            Init02();
        }

        /// <summary>
        /// 简单初始化驱动ui显示操作
        /// </summary>
        /// <returns></returns>
        int Init01()
        {
            try
            {
                List<int> list = new List<int>();
                for (int i = 0; i < 10; i++)
                {
                    list.Add(i);
                }

                listBox.ItemsSource = list;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                
            }

            return 0;
        }

        private class CListBoxInfo
        {
            /// <summary>
            /// 名称
            /// </summary>
            public string Name { get; set; }

            /// <summary>
            /// 颜色
            /// </summary>
            public string ColorDescription { get; set; }
        }

        int Init02()
        {
            try
            {
                List<CListBoxInfo> list = new List<CListBoxInfo>();
                list.Add(new CListBoxInfo() { Name = "Gold", ColorDescription = "#FFD700" });
                list.Add(new CListBoxInfo() { Name = "Firebrick4", ColorDescription = "#8B1A1A" });
                list.Add(new CListBoxInfo() { Name = "SteelBlue3", ColorDescription = "#4F94CD" });

                listBox.ItemsSource = list;
                dataGrid.ItemsSource = list;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);

            }
            return 0;
        }
    }
}
