using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace _17_Prism导航功能_A模块.ViewModels
{
    internal class ViewAViewModel : BindableBase, IConfirmNavigationRequest
    {
        public ViewAViewModel()
        {
        }

        private string _title;  

        public string Title
        {
            get { return _title; }
            set 
            { 
                _title = value;
                RaisePropertyChanged();
            }
        }

        /// <summary>
        /// 是否重用该实例对象;true--重用;false--不重用
        /// </summary>
        /// <param name="navigationContext"></param>
        /// <returns></returns>
        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
            
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            //接收调用模块传递过来的参数
            if (navigationContext.Parameters.ContainsKey("Title"))
            {
                Title = navigationContext.Parameters.GetValue<string>("Title");
            }
        }

        public void ConfirmNavigationRequest(NavigationContext navigationContext, Action<bool> continuationCallback)
        {
            bool bRes = false;          //是否允许导航切换

            if (MessageBox.Show("是否切换导航", "温馨提示", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
                bRes = true;

            continuationCallback(bRes);
        }
    }
}
