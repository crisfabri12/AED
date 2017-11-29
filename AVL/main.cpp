#include <iostream>
#include <iomanip>
#include <stack>
#include <vector>
#include <stdlib.h>

using namespace std;

template <class T>
class C_Node
{

public:
    T value;
    C_Node <T> *raices[2];
    int h_right;
    int h_left;

public:
    C_Node(T value, C_Node <T> *left, C_Node <T> *right)
    {
        this->value = value;
        raices[0] = left;
        raices[1] = right;
        h_right = 0;
        h_left = 0;
    }
};

template <class T>
class AVL_Tree
{

public:
    C_Node <T> *raiz = NULL;

public:
    void actualizar(C_Node <T> *&node)
    {
        if(node->raices[0]!=NULL)
        {
            if(node->raices[0]->h_left < node->raices[0]->h_right)
            {
                node->h_left = node->raices[0]->h_right + 1;
            }
            else
            {
                node->h_left = node->raices[0]->h_left + 1;
            }
        }
        else
        {
            node->h_left = 0;
        }
        if(node->raices[1]!=NULL)
        {
            if(node->raices[1]->h_left < node->raices[1]->h_right)
            {
                node->h_right = node->raices[1]->h_right + 1;
            }
            else
            {
                node->h_right = node->raices[1]->h_left + 1;
            }
        }
        else
        {
            node->h_right = 0;
        }
    }
    bool Buscar(T target, C_Node <T> **& ptr, vector <C_Node <T> **> &path)
    {
        ptr = &raiz;
        while(*ptr != NULL && target != (*ptr)->value)
        {
            path.push_back(ptr);
            if(target > (*ptr)->value)
            {
                ptr = &(*ptr)->raices[1];
            }
            else
                ptr = &(*ptr)->raices[0];
        }
        return *ptr && (*ptr)->value == target;
    }
    bool Rotacion_DR(C_Node <T> *&raiz)
    {
        C_Node <T> *newraiz = raiz->raices[1];
        raiz->raices[1] = newraiz->raices[0];
        newraiz->raices[0] = raiz;
        raiz = newraiz;
        return 1;
    }
    bool Rotacion_DL(C_Node <T> *&raiz)
    {
        C_Node <T> *newraiz = raiz->raices[0];
        raiz->raices[0] = newraiz->raices[1];
        newraiz->raices[1] = raiz;
        raiz = newraiz;
        return 1;
    }
    bool Rotacion_RL(C_Node <T> *&raiz)
    {
        C_Node <T> *newraiz = raiz->raices[1]->raices[0];
        raiz->raices[1]->raices[0] = newraiz->raices[1];
        newraiz->raices[1] = raiz->raices[1];
        raiz->raices[1] = newraiz->raices[0];
        newraiz->raices[0] = raiz;
        raiz = newraiz;
        return 1;
    }
    bool Rotacion_LR(C_Node <T> *&raiz)
    {
        C_Node <T> *newraiz = raiz->raices[0]->raices[1];
        raiz->raices[0]->raices[1] = newraiz->raices[0];
        newraiz->raices[0] = raiz->raices[0];
        raiz->raices[0] = newraiz->raices[1];
        newraiz->raices[1] = raiz;
        raiz = newraiz;
        return 1;
    }
    bool balancear(C_Node <T> **&raiz)
    {
        if((*raiz)->h_right - (*raiz)->h_left == -2)
        {
            if((*raiz)->raices[0]->h_left >= (*raiz)->raices[0]->h_right)
            {
                Rotacion_DL((*raiz));
                return 1;
            }
            else
                Rotacion_LR((*raiz));
                return 1;
        }
        else if((*raiz)->h_right - (*raiz)->h_left == 2)
        {
            if((*raiz)->raices[1]->h_right >= (*raiz)->raices[1]->h_left)
            {
                Rotacion_DR((*raiz));
                return 1;
            }
            else
                Rotacion_RL((*raiz));
                return 1;
        }
        return 0;
    }
    bool Insertar(T target)
    {
        C_Node <T> **ptr;
        vector <C_Node <T> **> path;
        if(Buscar(target, ptr, path)) return 0;
        C_Node <T> *newNode = new C_Node <T> (target, NULL , NULL);
        *ptr = newNode;
        for(int i = path.size() - 1; i >= 0; i--)
        {
            actualizar(*path[i]);
            if(balancear(path[i]))
            {
                actualizar((*path[i])->raices[0]);
                actualizar((*path[i])->raices[1]);
                actualizar(*path[i]);
            }
        }
        return 1;
    }
    bool Borrar(T target)
    {
        C_Node <T> **ptr;
        vector <C_Node <T> **> path;
        if(!Buscar(target, ptr, path)) return 0;
        if((*ptr)->raices[0] && (*ptr)->raices[1])
        {
            C_Node<T> **q = ptr;
            q = &((*q)->raices[1]);
            while((*q)->raices[0])
            {
                q = &((*q)->raices[0]);
            }
            (*ptr)->value = (*q)->value;
            ptr = q;
        }
        C_Node<T> *t = *ptr;
        *ptr = (*ptr)->raices[(*ptr)->raices[1] != 0];
        delete t;
        for(int i = path.size() - 1; i >= 0; i--)
        {
            actualizar(*path[i]);
            if(balancear(path[i]))
            {
                actualizar((*path[i])->raices[0]);
                actualizar((*path[i])->raices[1]);
                actualizar(*path[i]);
            }
        }
        return 1;
    }
    void Imprimir(C_Node <T> *p, int indent = 0)
    {

     if(p==NULL)
          return;
     Imprimir(p->raices[1], indent+1);

     for(int i=0; i<indent; i++){
         cout<<"   ";
     }
     cout<< p->value <<endl;

     Imprimir(p->raices[0], indent+1);
    }
};

int main()
{
    AVL_Tree <int> tree;
    tree.Insertar(1);
    tree.Insertar(8);
    tree.Insertar(3);
    tree.Insertar(7);
    tree.Insertar(2);
    tree.Insertar(9);
    tree.Insertar(4);
    tree.Insertar(5);
    tree.Insertar(6);
    tree.Imprimir(tree.raiz);
    return 0;
}
