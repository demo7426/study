using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.Messaging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _10_WPF框架_CommunityToolkit.Mvvm_
{
    internal class MainWindowViewMode : ObservableObject
    {
        public RelayCommand<string> ShowMsgCommand { get; set; }

        private string _strUserName;

        public string StrUserName
        {
            get { return _strUserName; }
            set
            {
                _strUserName = value;
                OnPropertyChanged();
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
                OnPropertyChanged();
            }
        }


        public MainWindowViewMode()
        {
            ShowMsgCommand = new RelayCommand<string>(ShowMessage);
        }

        void ShowMessage(string _Arg)
        {
            StrPassword = "12345678";

            WeakReferenceMessenger.Default.Send("UserName: " + _Arg, "Messenger01");
        }
    }
}
