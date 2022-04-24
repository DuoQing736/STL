/*******************************************
    vector
        1.使用 new 运算符进行分配内存
        2.内存通过 delete 运算符进行释放
    
    版本 1.0
    作者：MuYu
*******************************************/

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include<algorithm>

namespace mystl
{

template<typename T>
class Vector
{ 
    public:
        explicit Vector(int si = 0):size(si),capacity(size + space_capacity)
        {   
            point = new T[capacity];
            for(int i=0;i<size;++i)
            {
                point[i] = 0;
            }
        }
        Vector(const Vector& v):size(v.size),capacity(v.capacity),point(nullptr)
        {
            point = new T[capacity];
            for(int i=0;i<size;++i)
            {
                point[i] = v.point[i]; 
            }
        }
        ~Vector()
        {
            delete[] point;
        }

        Vector& operator=(const Vector& v)
        {
            Vector copy = v;
            std::swap(*this,copy);
            return *this;
        }

    public:
        int sizes()
        {
            return size;
        }
        int capacitys()
        {
            return capacity;
        }
        bool empty()
        {
            return sizes() == 0; 
        }

        void reserve(int newcapacity)
        {
            if(newcapacity < size)
            {
                return;
            }
            T* newArray = new T[newcapacity];
            for(int i=0;i<size;++i)
            {
                newArray[i] = std::move(point[i]);
            }
            capacity = newcapacity;
            std::swap(point,newArray);
            delete[] newArray;
        }
        void resize(int newsize)
        {
            if(newsize > capacity)
            {
                reserve(newsize * 2);
            }
            size = newsize;
        }

        void push_back(const T& value)
        {
            if(size == capacity)
            {
                reserve(capacity * 2 + 1);
            }
            point[size++] = value;
        }
        void push_back(const T&& value)
        {
            if(size == capacity)
            {
                reserve(capacity * 2 + 1);
            }
            point[size++] = value;
        }
        void pop_back()
        {
            // Replace the position of the deleted element with zero
            point[--size] = 0;
        }

    public:
        T& operator[](const int index)
        {
            return point[index];
        }
        bool operator==(const Vector& v)
        {
            if(this->size != v.size)
            {
                return false;
            }
            for(int i=0;i<this.size;++i)
            {
                if(this->point[i] != v.point[i])
                {
                    return false;
                }
                this.point++;
                v.point++;
            }
            return true;
        }
        bool operator!=(const Vector& v)
        {
            if(this->size != v.size)
            {
                return true;
            }
            for(int i=0;i<this.size;++i)
            {
                if(this->point[i] == v.pointi)
                {
                    this.point++;
                    v.point++;
                }
                else
                {
                    return false;
                }
            }
            return true;
        }

    public:    
        typedef T* iterator;
        typedef const T* const_iterator;

        iterator begin()
        {
            return &point[0];
        }
        const_iterator cbegin()
        {
            return &point[0];
        }
        iterator end()
        {
            return &point[this.sizes()];
        }
        const_iterator cend()
        {
            return &point[this->sizes()];
        }
    
    public:
        static const int space_capacity = 10;

    private:
        int size;
        int capacity;
        T* point;
};

};

#endif