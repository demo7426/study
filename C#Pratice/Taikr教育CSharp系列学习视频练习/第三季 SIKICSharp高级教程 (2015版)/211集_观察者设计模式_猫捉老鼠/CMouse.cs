using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _211集_观察者设计模式_猫捉老鼠
{
    internal class CMouse
    {
        private string name;
        private string color;
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
        public CMouse(string _Name, string _Color, CCat _Cat)
        {
            this.Name = _Name;
            this.Color = _Color;
            _Cat.action += this.RunAway;
        }

        public void RunAway()
        {
            Console.WriteLine(this.Color + "颜色的老鼠，" + this.Name + "跑出了房间。");
        }
    }
}
