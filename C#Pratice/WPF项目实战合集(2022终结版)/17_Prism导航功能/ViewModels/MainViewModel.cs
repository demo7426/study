using _17_Prism导航功能.Views;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _17_Prism导航功能.ViewModels
{
    internal class MainViewModel : BindableBase
    {
        public MainViewModel(IRegionManager regionManager) {
            OpenCommand = new DelegateCommand<string>(Open);
            BackCommand = new DelegateCommand(Back);
            RegionManager = regionManager;
        }


        public DelegateCommand<string> OpenCommand { get; private set; }
        public DelegateCommand BackCommand { get; private set; }

        private IRegionNavigationJournal RegionNavigationJournal { get; set; }          //存储导航日志
        private readonly IRegionManager RegionManager;

        private void Open(string _Arg)
        {
            //为"ContentRegion"区域请求导航
            //向接收导航日志,模块A传递参数
            NavigationParameters keyValuePairs = new NavigationParameters();
            keyValuePairs.Add("Title", "Hello world");

            RegionManager.Regions["ContentRegion"].RequestNavigate(_Arg, _Res =>
            {
                RegionNavigationJournal = _Res.Context.NavigationService.Journal;
            }, keyValuePairs);

        }

        private void Back()
        {
            if (RegionNavigationJournal != null && RegionNavigationJournal.CanGoBack) 
            {
                RegionNavigationJournal.GoBack();
            }
        }
    }
}
