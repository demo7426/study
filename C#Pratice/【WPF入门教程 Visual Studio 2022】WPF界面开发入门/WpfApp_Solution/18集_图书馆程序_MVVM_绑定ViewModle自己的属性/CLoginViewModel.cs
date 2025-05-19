using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _18集_图书馆程序_MVVM_绑定ViewModle自己的属性
{
    /// <summary>
    /// ViewMode模块
    /// </summary>
    internal class CLoginViewModel: INotifyPropertyChanged
    {
        private CLoginModel cLoginModel { get; set; }

        public CLoginViewModel()
        {
            cLoginModel = new CLoginModel();
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
    }
}
