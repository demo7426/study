using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using GalaSoft.MvvmLight.Messaging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace _09_WPF框架_MvvmLight_
{
    internal class MainWindowViewMode : ViewModelBase
    {
        public RelayCommand<string> ShowMsgCommand { get; set; }

        private string _strUserName;

        public string StrUserName
        {
            get { return _strUserName; }
            set
            {
                _strUserName = value;
                RaisePropertyChanged();
            }
        }

        private string _strPassword;

        public string StrPassword
        {
            get { return _strPassword; }
            set
            {
                _strPassword = value;
                //OnPropertyChanged("StrPassword");
                RaisePropertyChanged();
            }
        }


        public MainWindowViewMode()
        {
            ShowMsgCommand = new RelayCommand<string>(ShowMessage);
        }

        void ShowMessage(string _Arg)
        {
            StrPassword = "12345678";

            Messenger.Default.Send("UserName: " + _Arg, "Messenger01");
        }
    }
}
