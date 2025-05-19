using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _17集_图书馆程序_MVVM_ViewMode演示
{
    /// <summary>
    /// ViewMode模块
    /// </summary>
    internal class CLoginViewModel: INotifyPropertyChanged
    {
        public CLoginModel cLoginModel { get; set; }

        public CLoginViewModel()
        {
            cLoginModel = new CLoginModel();
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

        public void NotifyPropertyChanged()
        {
            RaisePropertyChanged("cLoginModel");
        }
    }
}
