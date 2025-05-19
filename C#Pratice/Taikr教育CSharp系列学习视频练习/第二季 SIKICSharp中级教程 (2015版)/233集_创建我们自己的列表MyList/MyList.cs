using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _233集_创建我们自己的列表MyList
{
    internal class MyList<T> where T:IComparable
    {
        private T[] array;
        /// <summary>
        /// 容量
        /// </summary>
        private int capacity = 0;
        /// <summary>
        /// 数量
        /// </summary>
        private int count = 0;
        /// <summary>
        /// 容量
        /// </summary>
        public int Capacity
        {
            get { return this.capacity; }
        }
        /// <summary>
        /// 数量
        /// </summary>
        public int Count
        {
            get { return this.count; }
        }

        public MyList(int _Size)
        {
            if (_Size >= 0)
            {
                this.capacity = _Size;
                array = new T[this.capacity];
            }
            else
            {
                throw new Exception("Error of set value.");
            }
        }

        public MyList()
        {
            this.capacity = 0;
            array = new T[0];
        }
        /// <summary>
        /// 添加数据
        /// </summary>
        /// <param name="item">值</param>
        public void Add(T item)
        {
            if (this.Count == this.Capacity)
            {
                if (this.Count == 0)
                {
                    this.capacity = 4;
                    this.array = new T[this.capacity];
                }
                else
                {
                    this.capacity *= 2;
                    T[] newArray = new T[this.capacity];
                    Array.Copy(this.array, newArray, this.count);

                    this.array = newArray;
                }
            }

            this.array[this.Count] = item;
            this.count++;
        }

        /// <summary>
        /// 索引器
        /// </summary>
        /// <param name="_Index">索引</param>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        public T this[int _Index]
        {
            get
            {
                if (_Index >= 0 && _Index < this.Count)
                    return array[_Index];

                else
                    throw new Exception("IndexOutOfRangeException");
            }
            set
            {
                if (_Index >= 0 && _Index < this.Count)
                    array[_Index] = value;
                else
                    throw new Exception("IndexOutOfRangeException");
            }
        }

        /// <summary>
        /// 在指定位置插入元素
        /// </summary>
        /// <param name="_Index">位置</param>
        /// <param name="_Item">值</param>
        public void Insert(int _Index, T _Item)
        {
            if (_Index < 0 || _Index > this.Count)
                throw new Exception("IndexOutOfRangeException");

            if (this.Count == this.Capacity)
            {
                if (this.Count == 0)
                {
                    this.capacity = 4;
                    this.array = new T[this.capacity];
                }
                else
                {
                    this.capacity *= 2;
                    T[] newArray = new T[this.capacity];
                    Array.Copy(this.array, newArray, this.count);

                    this.array = newArray;
                }
            }

            for (int i = this.Count; i >= _Index; i--)
            {
                this.array[i + 1] = this.array[i];
            }

            this.array[_Index] = _Item;
            this.count++;
        }
        /// <summary>
        /// 移除某个位置的元素
        /// </summary>
        /// <param name="_Index"></param>
        /// <exception cref="Exception"></exception>
        public void RemoveAt(int _Index)
        {
            if (_Index < 0 || _Index >= this.Count)
                throw new Exception("IndexOutOfRangeException");

            for (int i = _Index; i < this.Count - 1; i++)
            {
                this.array[i] = this.array[i + 1];
            }
            this.count--;
        }
        public int IndexOf(T item)
        {
            int nRtn = -1;
            for (int i = 0; i < this.Count; i++)
            {
                if (item.Equals(this.array[i]))
                {
                    nRtn = i;
                    break;
                }
            }

            return nRtn;
        }
        public int LastIndexOf(T item)
        {
            int nRtn = -1;
            for (int i = this.Count - 1; i >= 0; i--)
            {
                if (item.Equals(this.array[i]))
                {
                    nRtn = i;
                    break;
                }
            }

            return nRtn;
        }

        public void Sort()
        {
            T tempValue;
            for (int i = 0; i < this.Count - 1; i++)
            {
                for (int j = 0; j < this.Count - 1 - i; j++)
                {
                    if (this.array[j].CompareTo(this.array[j+1]) > 0)
                    {
                        tempValue = this.array[j + 1];
                        this.array[j + 1] = this.array[j];
                        this.array[j] = tempValue;
                    }
                }
            }

        }
    }
}
