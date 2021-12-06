#include <iostream>
#include <string>


template <typename T>
struct Cell{
  T element;
  Cell * next;
};


//first in first out -> file
template <class T>
class Fifo {
private:

    Cell<T> * head;
    Cell<T> * tail;
    

public:
    Fifo() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    ~Fifo() {

        while(!this->isEmpty()) 
            this->pop();
    }


    bool isEmpty() {
        return this == nullptr || (this->head == nullptr && this->tail == nullptr);
    }

    int add(T val) {
        Cell<T> * newCell = new Cell<T>;
        newCell->element = val;
        newCell->next = nullptr;

        if(this->isEmpty()) {
            this->head = newCell;
            this->tail = newCell;

            return 0;
        }

        this->tail->next = newCell;
        this->tail = newCell;

        return 0;
    }

    T pop() {
        if(this == nullptr || this->isEmpty()) 
            throw std::out_of_range(" -- the Fifo is empty, pop is impossible -- ");
        
        T val = this->head->element;
        Cell<T> * tmp = this->head;

        this->head = this->head->next;
        if(tmp == this->tail) {
            // then the last line means : this->head = nullptr;
            this->tail = nullptr;
        }

        delete tmp;

        return val;
    }


    T get() {
        if(this == nullptr || this->isEmpty())
            throw std::out_of_range(" -- the Fifo is empty, get is impossible -- ");
        
        return this->head->element;
    }

    void print() {

        Fifo<T> * tmp = new Fifo<T>();

        while(!this->isEmpty()) {
            T t = this->pop();
            tmp->add(t);
            

            try{
                std::cout << t << " ";
            }
            catch(std::exception e) {
                throw std::invalid_argument(" your objects doesn't convert to string, try overriding the << operator ");
            }
        }

        while (!tmp->isEmpty())
            this->add(tmp->pop());
        
        std::cout << std::endl;
    }

    friend std::ostream & operator<<(std::ostream & o, Fifo<T> & f) { 

        o << "Fifo>\t";

        Fifo<T> * tmp = new Fifo<T>();

        while(!f.isEmpty()) {
            T t = f.pop();
            tmp->add(t);
            
            try{
                o << t << " ";
            }
            catch(std::exception e) {
                throw std::invalid_argument(" your objects doesn't convert to string, try overriding the << operator ");
            }
            
        }

        while (!tmp->isEmpty())
            f.add(tmp->pop());

        return o;
    }

};


//last in first out -> pile
template <class T>
class Lifo {
private:
    Cell<T> * master;


public:
    Lifo() {
        master = nullptr;
    }

    ~Lifo() {
        while(!this->isEmpty())
            this->heapDown();
    }


    bool isEmpty() {
        return master == nullptr;
    }

    int heapUp(T val) { // empiler
        Cell<T> * newCell = new Cell<T>;
        newCell->element = val;
        newCell->next = master;
        master = newCell;

        return 0;
    }

    T heapDown() { //depiler
        if(this->isEmpty()) {
            throw std::out_of_range(" -- the Lifo is empty, heapDown is impossible -- ");
        }

        T val = master->element;
        Cell<T> * tmp = master;
        master = master->next;

        delete tmp;
        return val;
    }

    T get() {
        if(this->isEmpty()){
            throw std::out_of_range(" -- the Lifo is empty, get is impossible -- ");
        }

        return master->element;
    }

    void print() {

        Lifo<T> * tmp = new Lifo<T>();

        while(!this->isEmpty()) {
            tmp->heapUp(this->heapDown());
            
            try{
                std::cout << tmp->get() << " ";
            }
            catch(std::exception e) {
                throw std::invalid_argument(" your objects doesn't convert to string, try overriding the << operator ");
            }
            
        }

        while (!tmp->isEmpty())
            this->heapUp(tmp->heapDown());
        
        std::cout << std::endl;
    }

    friend std::ostream & operator<<(std::ostream & o,  Lifo<T> & l) { 

        o << "Lifo>\t";

        Lifo<T> * tmp = new Lifo<T>();

        while(!l.isEmpty()) {
            tmp->heapUp(l.heapDown());
            
            try{
                o << tmp->get() << " ";
            }
            catch(std::exception e) {
                throw std::invalid_argument(" your objects doesn't convert to string, try overriding the << operator ");
            }
            
        }

        while (!tmp->isEmpty())
            l.heapUp(tmp->heapDown());


        return o;
    }
};

