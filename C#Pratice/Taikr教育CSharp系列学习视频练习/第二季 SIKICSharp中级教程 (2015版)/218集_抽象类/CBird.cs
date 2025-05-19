using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _218集_抽象类
{
    internal abstract class CBird//如果类里面有抽象方法，则类必须是抽象类
    {
        //当子类里面的方法各不相同时，就可以使用抽象方法，让下面子类各自实现抽象方法
        public abstract void Fly();
    }
}
