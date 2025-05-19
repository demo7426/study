using _15_Prism区域介绍.Views;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _15_Prism区域介绍.ViewModels
{
    internal class MainViewModel : BindableBase
    {
        public MainViewModel(IRegionManager regionManager) {
            OpenCommand = new DelegateCommand<string>(Open);
            RegionManager = regionManager;
        }

        public DelegateCommand<string> OpenCommand { get; private set; }
        private readonly IRegionManager RegionManager;

        private void Open(string _Arg)
        {
            //为"ContentRegion"区域请求导航
            RegionManager.Regions["ContentRegion"].RequestNavigate(_Arg);
        }

    }
}
