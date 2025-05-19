using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _18集_图书馆程序_MVVM_绑定ViewModle自己的属性
{
    /// <summary>
    /// 将数据模型提取到此处
    /// </summary>
    internal class CLoginModel
    {
        private string _UserName;

        public string UserName
        {
            get { return _UserName; }
            set { _UserName = value; }
        }

        private string _Password;

        public string Password
        {
            get { return _Password; }
            set { _Password = value; }
        }
    }
}
