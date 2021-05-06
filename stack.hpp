#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

mutex mut_stack;

template <typename T>
struct stack_node {
    T data;
    stack_node<T> * next;
};

template <typename T>
class Stack{
    private:
        typedef stack_node<T> stackNode;
        stackNode * top;
    public:
        Stack():top(nullptr){}

        void push(const T content){
            mut_stack.lock();
            stackNode * new_node = new stackNode;
            new_node->data = content;
            new_node->next = top;
            top = new_node;
            //cout << top->data << endl;
            mut_stack.unlock();
        }

        void pop(){
            mut_stack.lock();
            if(top){
                stackNode * temporal = top;
                top = temporal->next;
                temporal->next = nullptr;
                cout << temporal->data << endl;
                delete temporal;
            }
            mut_stack.unlock();
        }

        void repeat(int n, T element){
            for(int i = 0; i < n; i ++){
                push(element);
            }
        }

        void pop_all(){
            while (top != nullptr)
                pop();
        }

        map<T, int> count(){
            stackNode *curr = top;
            map<T, int> m;
            while (curr != nullptr){
                auto it = m.find(curr->data);
                if (it != m.end())    
                    m[curr->data] += 1;
                else m[curr->data] = 1;
                curr = curr->next;
            }
            return m;
        }

        void print(){
            stackNode *curr = top;
            while (curr != nullptr){
                cout << curr->data << " ";
                curr = curr->next;
            }
            cout << endl;
        }

        ~Stack(){}
};

template <typename T>
void push_and_pop(Stack <T>* s, T element, int n){
    for(int i = 0; i < n; i++)
        s->push(element);
}

template <typename T>
void push_elements(Stack <T> s, vector<T> vect){
    for (T element : vect)
        s.push(element);
}

template <typename T>
void pop_elements(Stack <T>* s){
    s->pop_all();
}

template <typename T>
void print_count(Stack <T>* s){
    auto m = s->count();
    for (auto element : m)
        cout << element.first << " " <<element.second << endl;
}
