using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace _07_WPF命令
{
    internal class MainWindowViewMode : ViewModeBase
    {
        public ReplyCommand ShowMsgCommand { get; set; }

        private string _strUserName;

        public string StrUserName
        {
            get { return _strUserName; }
            set { _strUserName = value; 
                //OnPropertyChanged("StrUserName");
                OnPropertyChanged();
            }
        }

        private string _strPassword;

        public string StrPassword
        {
            get { return _strPassword; }
            set { _strPassword = value;
                //OnPropertyChanged("StrPassword");
                OnPropertyChanged();
            }
        }


        public MainWindowViewMode()
        {
            ShowMsgCommand = new ReplyCommand(ShowMessage);
        }

        void ShowMessage()
        {
            StrUserName = "C罗";
            StrPassword = "12345678";

            MessageBox.Show("按钮被点击");
        }
    }
}
