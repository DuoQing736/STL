/*******************************************
    list
        1.使用 new 运算符进行分配内存
        2.内存通过 delete 运算符进行释放
    
    版本 1.0
    作者：MuYu
*******************************************/


#ifndef _LIST_H_
#define _LIST_H_

#include<algorithm>

template<typename T>
class List
{
    private:
        struct Node
        {
            T data;
            Node *prev;
            Node *next;
            Node(const T &d = 0,Node *p = nullptr,Node *n = nullptr):data(d),prev(p),next(n){}
        };
    
    private:
        int size;
        Node *head;
        Node *tail;
        void Initialization()
        {
            size = 0;
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->prev = head;
        }

    public:
        class const_iterator
        {
            public:
                const_iterator():current(nullptr){}
                const T& operator*() const
                {
                    return retrieve();
                }
                // pre addition and post addition
                const_iterator& operator++()
                {
                    current = current->next;
                    return *this;
                }
                const_iterator& operator++(int)
                {
                    const_iterator *old = current;
                    ++(*this);
                    return *old;
                }

                bool operator==(const const_iterator& l) const
                {
                    return current == l.current;
                }
                bool operator!=(const const_iterator& l) const
                {
                    return !(*this == l);
                }
            protected:
                Node *current;
                T& retrieve() const
                {
                    return current->data;
                }
                const_iterator(Node *p):current(p){}
                friend class List<T>;
        };

        class iterator:public const_iterator
        {
            public:
                iterator(){}
                T& operator*()
                {
                    return const_iterator::retrieve();
                }
                /* const T& operator*() const
                {
                    return const_iterator::operator*();
                } */

                iterator& operator++()
                {
                    this->current = this->current->next;
                    return *this;
                }
                iterator& operator++(int)
                {
                    iterator old = *this;
                    ++(*this);
                    return old;
                }

            protected:
                iterator(Node *p):const_iterator(p){}
                friend class List<T>;
        };

    public:
        List()
        {
            Initialization();
        }
        List(const List& l)
        {
            Initialization();
            for(auto x : l)
            {
                push_back(x);
            }
        }
        List& operator=(const List& l)
        {
            List copy = l;
            std::swap(*this,copy);
            return *this;
        }
        ~List()
        {
            clear();
            delete[] head;
            delete[] tail;
        }

    public:
        iterator begin()
        {
            return head->next;
        }
        iterator end()
        {
            return tail;
        }

    public:
        int sizes()
        {
            return size;
        }
        bool empty()
        {
            return sizes() == 0;
        }
        void clear()
        {
            while(!empty())
            {
                pop_front();
            }
        }

    public:
        T& front()
        {
            return *begin();
        }
        T& back()
        {
            return *(--end());
        }
        void push_front(const T& value)
        {
            insert(begin(),value);
        }
        void push_back(const T& value)
        {
            insert(end(),value);
        }
        void pop_front()
        {
            erase(begin());
        }
        void pop_back()
        {
            erase(--end());
        }

        iterator insert(iterator it,const T& value)
        {
            Node *p = it.current;
            size++;
            return p->prev = p->prev->next = new Node(value,p->prev,p);
        }
        iterator erase(iterator it)
        {
            Node *p = it.current;
            iterator retValue(p->next);
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            size--;
            return retValue;
        }
        iterator erase(iterator from,iterator to)
        {
            for(iterator it = from;it != to;it++)
            {
                it = erase(it);
            }
            return to;
        }
};

#endif