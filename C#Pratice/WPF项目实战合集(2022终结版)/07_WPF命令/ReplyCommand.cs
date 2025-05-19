using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace _07_WPF命令
{
    internal class ReplyCommand : ICommand
    {
        private Action ActCallBack {  get; set; }

        public ReplyCommand(Action _Action) 
        {
            ActCallBack = _Action;
        }

        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            try
            {
                MessageBox.Show(parameter.ToString());
                ActCallBack();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
