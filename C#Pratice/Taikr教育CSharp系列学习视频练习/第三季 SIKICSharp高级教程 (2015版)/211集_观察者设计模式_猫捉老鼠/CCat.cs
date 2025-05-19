using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _211集_观察者设计模式_猫捉老鼠
{
    internal class CCat
    {
        private string name;
        private string color;
        public event Action action;//事件不能在类的外部直接被调用

        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        public string Color
        {
            get { return color; }
            set { color = value; }
        }
        public CCat(string _Name, string _Color)
        {
            this.Name = _Name;
            this.Color = _Color;
        }

        public void Comming()
        {
            Console.WriteLine(this.Color + "颜色的猫咪，" + this.Name + "走进了房间。");

            if (this.action != null)
                this.action();
        }
    }
}
