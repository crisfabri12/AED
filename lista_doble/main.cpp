#include <iostream>

using namespace std;

template <typename T>
class nodo{
public:
    T val;
    nodo<T> *next;
    nodo<T> *prev;
    nodo(T a){
        val = a;
        next = NULL;
        prev = NULL;
    };
};

template <typename T>
class lista{
private:
    nodo<T> *h;
    nodo<T> *t;
public:
    lista(){h = NULL; t = NULL;};
    bool insertar(T a){
        nodo<T> *nuevo = new nodo<T>(a);
        if(h == NULL){
            h = nuevo;
            t = nuevo;
            return 1;
        }
        nodo<T> *temp = h;
        if(a < h->val){
            nuevo->next = h;
            h->prev = nuevo;
            h = nuevo;
            t = nuevo->next;
            t->next = h;
            h->prev = t;
            return 1;
        }
        else if(t->val <= a){
            if(t->val == a)
            {
                return 0;
            }
            t->next = nuevo;
            nuevo->prev = t;
            t = nuevo;
            t->next = h;
            h->prev = t;
            return 1;
        }
        while(temp->val < a){
            temp = temp->next;
        }
        if(temp->val == a)
        {
            return 0;
        }
        nuevo->next = temp;
        nuevo->prev = temp->prev;
        temp->prev->next = nuevo;
        temp->prev = nuevo;
        return 1;
    }
    bool borrar(T a){
        if(h == NULL){
            return 0;
        }
        if(h->val == a){
            nodo<T> *elim = h;
            h = h->next;
            h->prev = t;
            t->next = h;
            delete elim;
            return 1;
        }
        if(t->val == a){
            nodo<T> *elim = t;
            t = t->prev;
            t->next = h;
            h->prev = t;
            delete elim;
            return 1;
        }
        nodo<T> *temp = h;
        while(temp->val < a && temp->next != NULL){
            temp = temp->next;
        }
        if(temp->val == a){
            nodo<T> *elim = temp;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete elim;
            return 1;
        }
        return 0;
    }
    void imprimir(){
        if(h == NULL){
            cout << "Lista Vacia" << endl;
        }
        else{
            nodo<T> *temp = h;
            nodo<T> *temp2 = t;
            while(temp!=temp2){
                cout << temp->val << " ";
                //temp = temp->prev;
                temp = temp->next;
            }
            cout << temp->val <<endl;
        }
    }

    void josephus(int numero,int vueltas)
    {
        nodo<int> *temp = h;
        int tam=numero;
        int pos = 1;
        while(tam != 1)
        {

//            cout<<"tam: "<<tam<<endl;
            imprimir();
            if(pos == 3)
            {
                int elim = temp->val;
                temp = temp->next;
                borrar(elim);
                pos = 1;
                tam--;
            }
            else{
//                cout<<"h: "<<h->val<<endl;
//                cout<<"t: "<<t->val<<endl;
//                cout<<"hh: "<<h->next->val<<endl;
//                cout<<"tt: "<<t->next->val<<endl;
                temp = temp->next;
//                cout<<"val: "<<temp->val<<endl;
                pos++;
            }
        }
    }
};

void josephus(int numero,int vueltas)
{
    lista<int> jose;
    for(int i=1;i<=numero;i++)
    {
        jose.insertar(i);
    }
    jose.imprimir();
    jose.josephus(numero,vueltas);
    cout<<"El sobreviviente es: ";
    jose.imprimir();
}
int main()
{
    josephus(10,3);
    cout << "Hello world!" << endl;
    return 0;
}
