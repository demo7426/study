using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace _20集_图书馆程序_MVVM_命令
{
    /// <summary>
    /// ViewMode模块
    /// </summary>
    internal class CLoginViewModel: INotifyPropertyChanged
    {
        private CLoginModel cLoginModel { get; set; }
        private MainWindow mainWindow1 { get; set; }

        public CLoginViewModel(MainWindow mainWindow)
        {
            cLoginModel = new CLoginModel();
            this.mainWindow1 = mainWindow;
        }

        public string UserName
        {
            get { return cLoginModel.UserName; }
            set { 
                cLoginModel.UserName = value;
                RaisePropertyChanged("UserName");
            }
        }

        public string Password
        {
            get { return cLoginModel.Password; }
            set { 
                cLoginModel.Password = value;
                RaisePropertyChanged("PassWord");
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


        private void LoginAction()
        {
            if (UserName.CompareTo("wpf") == 0 && Password.CompareTo("7426") == 0)
            {
                Window1 window1 = new Window1();
                window1.Show();

                this.mainWindow1.Hide();
            }
            else
            {
                UserName = "";
                Password = "";

                MessageBox.Show("输入的用户名或密码错误。");
            }
        }

        private bool CanExecute()
        {
            return true;
        }

        public ICommand LoginCommand
        {
            get
            {
                return new CReplyCommand(CanExecute, LoginAction);
            }
        }
    }
}
