﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace _20集_图书馆程序_MVVM_命令
{
    internal class CReplyCommand:ICommand
    {
        /// <summary>
        /// 命令是否能够执行
        /// </summary>
        readonly Func<bool> _canExecute;

        /// <summary>
        /// 命令需要执行的方法
        /// </summary>
        readonly Action _execute;

        public CReplyCommand(Func<bool> canExecute, Action execute)
        {
            _canExecute = canExecute;
            _execute = execute;
        }

        

        public bool CanExecute(object parameter)
        {
            if (_canExecute == null)
            {
                return true;
            }
            return _canExecute();
        }

        public void Execute(object parameter)
        {
            _execute();
        }

        public event EventHandler CanExecuteChanged
        {
            add
            {
                if (_canExecute != null)
                    CommandManager.RequerySuggested += value;
            }
            remove 
            {
                if (_canExecute != null)
                    CommandManager.RequerySuggested -= value; 
            }
        }

    }
}
