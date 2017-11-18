#include <iostream>
#include <list>
#include <vector>
using namespace std;
template<class N,class E>
class CGraph;
template<class G>
class CEdge ;

template<class G>
class CNode
{
    public:
	typedef typename G::Edge Edge;
	typedef typename G::NE N;
	typedef typename G::EE E;
	typedef typename G::Camino Camino;
	N mdata;
	E peso = 0;
	int marca = false;
	Camino recorrido;
	vector<Edge*> m_edges;
	CNode(N dato)
	{
	    mdata = dato;
	}
};

template<class G>
class camino
{
    public:
    typedef typename G::Node Node;
    vector<Node*> camino_r;

};

template<class G>
class CEdge
{
    public:
	typedef typename G::Node Node;
	typedef typename G::EE E;
	Node* m_nodes[2];
	E m_data;
	CEdge(Node *a, Node *b, E dato)
	{
	    m_nodes[0] = a;
	    m_nodes[1] = b;
	    m_data = dato;
	}
};




template<class N,class E>
class CGraph
{
public:
	typedef CGraph<N,E> self;
	typedef CNode<self> Node;
	typedef CEdge<self> Edge;
	typedef camino<self> Camino;
	typedef N NE;
	typedef E EE;

	vector<Node*> m_nodes;
	bool InsertNode(N x)
	{
	    Node *temp;
	    if(find(x,temp))
        {
            return 0;
        }
        Node *nuevo = new Node(x);
        m_nodes.push_back(nuevo);
	}
	bool InsertEdge(N a,N b,bool dir,E dato)
	{
	    Node *aux;
	    Node *aux2;
        if(find(a,aux) && find(b,aux2))
        {
                Edge *nuevo = new Edge(aux,aux2,dato);
                if(dir == 1)
                {
                    Edge *nuevo2 = new Edge(aux2,aux,dato);
                    aux->m_edges.push_back(nuevo);
                    aux->m_edges.push_back(nuevo2);
                    aux2->m_edges.push_back(nuevo2);
                    aux2->m_edges.push_back(nuevo);

                }else{
                    aux->m_edges.push_back(nuevo);
                    aux2->m_edges.push_back(nuevo);

                }
                return 1;

        }
        return 0;
	}

	void imprimir()
	{
	    for(int i=0;i<m_nodes.size();i++)
        {
            cout<<m_nodes[i]->mdata<<endl;
            cout<<"-----------------------"<<endl;
            vector<Edge*> aux = m_nodes[i]->m_edges;
            for(int j=0;j<aux.size();j++)
            {
                cout<<aux[j]->m_nodes[1]->mdata<<"->"<<aux[j]->m_data<<"->"<<aux[j]->m_nodes[0]->mdata<<endl;
            }
            cout<<endl;
        }

	}

    bool find(N dato,Node *&pos)
    {
        for(int i=0;i<m_nodes.size();i++)
        {
            if(m_nodes[i]->mdata == dato)
            {
                pos = m_nodes[i];
                return 1;
            }
        }
        return 0;

    }
    bool find_edge(Node *x,E t,Edge *&re)
    {
        for(int i=0;i<x->m_edges.size();i++)
        {
            if(x->m_edges[i]->m_data == t)
            {
                re = x->m_edges[i];
                return 1;
            }
        }
    }

    bool remove_vedges(Node *t,Edge *borrado)
    {
        for(int i=0;i<t->m_edges.size();i++)
        {
            if(t->m_edges[i]== borrado)
            {
                t->m_edges.erase(t->m_edges.begin()+i);
            }
        }

    }
    bool  remove_edge(N a,N b,E x)
    {
        Edge *temp;
        Node *n1;
        Node *n2;
        find(a,n1);
        find(b,n2);
        find_edge(n1,x,temp);
        remove_vedges(n1,temp);
        remove_vedges(n2,temp);


    }

    int posicion(Node *aux)
    {
        for(int i=0;i<m_nodes.size();i++)
        {
            if(m_nodes[i] == aux)
            {
                return i;
            }
        }
    }

    bool remove_node(N x)
    {
        Node *aux;
        if(!find(x,aux))
        {
            return 0;
        }
        N temp1;
        N temp2;
        int tam = aux->m_edges.size();
        for(int i=0;i< tam;i++)
        {
            E Edge_borrado = aux->m_edges[0]->m_data;
            temp1 = aux->m_edges[0]->m_nodes[0]->mdata;
            temp2 = aux->m_edges[0]->m_nodes[1]->mdata;
            remove_edge(temp1,temp2,Edge_borrado);
        }
        int pos = posicion(aux);
        m_nodes.erase(m_nodes.begin()+pos);
    }

    void Dijkstra(N nodo)
    {
        Node *temp;
        find(nodo,temp);
        bool marca;
        if(temp->marca == true)
        {
            return ;
        }
        cout<<temp->mdata<<endl;
        int cont =0;
        for(int i=0;i<temp->m_edges.size();i++)
        {
            Node *entrada = temp->m_edges[i]->m_nodes[1];
            if(entrada == temp)
            {
                entrada = temp->m_edges[i]->m_nodes[0];
            }
            cout<<entrada->mdata;
            E peso = temp->m_edges[i]->m_data + temp->peso;
            if(entrada->peso == 0 && entrada->marca == false)
            {
                entrada->recorrido.camino_r.push_back(temp);
                entrada->peso = peso ;
            }
            else if(entrada->peso > peso && entrada->marca == false)
            {
                entrada->recorrido.camino_r.push_back(temp);
                entrada->peso = peso;
            }
            if(entrada->marca == true)
            {
                marca = true;
            }
        }
        temp->marca = true;

        cout<<endl;

        if(marca)
        {
            return;
        }
        for(int i=0;i<temp->m_edges.size();i++)
        {
            Edge* menor = temp->m_edges[0];
            for(int j=0;j<temp->m_edges.size();j++)
            {
                Edge * x = temp->m_edges[j];
                if(x->m_data < menor->m_data && x->m_nodes[1]->marca == false)
                {
                    menor = x;

                }
            }
            N dato = menor->m_nodes[1]->mdata;
            Dijkstra(dato);
        }

        for(int i=0;i<m_nodes.size();i++)
        {
            if(m_nodes[i]->marca == false)
            {
                Dijkstra(m_nodes[i]->mdata);
            }
        }
        for(int i=0;i<m_nodes.size();i++)
        {
            cout<<m_nodes[i]->mdata<<"------"<<m_nodes[i]->peso<<endl;
            for(int j =0;j<m_nodes[i]->recorrido.camino_r.size();j++)
            {
                cout<<m_nodes[i]->recorrido.camino_r[j]->mdata;
            }
            cout<<endl;
        }

    }




};





int main(int argc, char *argv[]) {
	CGraph<char,int> g;
	g.InsertNode('1');
	g.InsertNode('2');
	g.InsertNode('3');
	g.InsertNode('4');
	g.InsertNode('6');
	g.InsertNode('5');

	g.InsertNode('7');
	g.InsertNode('8');


	g.InsertEdge('1','2',0,2);
	g.InsertEdge('1','3',0,5);
	g.InsertEdge('2','3',0,3);
	g.InsertEdge('2','4',0,8);
	g.InsertEdge('2','5',0,15);
	g.InsertEdge('3','4',0,4);
	g.InsertEdge('3','6',0,3);
	g.InsertEdge('4','6',0,1);
	g.InsertEdge('4','5',0,4);
	g.InsertEdge('4','7',0,2);
	g.InsertEdge('5','7',0,1);
	g.InsertEdge('7','6',0,1);
	g.InsertEdge('6','8',0,5);
	g.InsertEdge('5','8',0,2);
	g.InsertEdge('7','8',0,7);
	g.imprimir();
    g.Dijkstra('1');
	return 0;
}
