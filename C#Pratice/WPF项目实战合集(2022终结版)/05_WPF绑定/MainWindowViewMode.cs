using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _05_WPF绑定
{
    internal class MainWindowViewMode
    { 
        public MainWindowViewMode() {}
        public MainWindowViewMode(string _Name) 
        {
            StrName = _Name;
        }

        public string StrName { get; set; }

    }
}
