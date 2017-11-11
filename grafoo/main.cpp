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
	N mdata;
	N peso = -1;
	vector<Edge*> m_edges;
	CNode(N dato)
	{
	    mdata = dato;
	}
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
	typedef N NE;
	typedef E EE;

	vector<Node*> m_nodes;
	bool InsertNode(N x)
	{
	    Node *temp;
	    int p;
	    if(find(x,temp,&p))
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
	    int p1,p2;
        if(find(a,aux,&p1) && find(b,aux2,&p2))
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

    bool find(N dato,Node *&pos,int *t)
    {
        for(int i=0;i<m_nodes.size();i++)
        {
            if(m_nodes[i]->mdata == dato)
            {
                pos = m_nodes[i];
                *t = i;
                return 1;
            }
        }
        return 0;

    }
    bool find_edge(Node *x,Edge *t,Edge *&re)
    {
        for(int i=0;i<x->m_edges.size();i++)
        {
            if(x->m_edges[i] == t)
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


    bool remove_node(N x)
    {
        Node *aux;
        int p;
        if(!find(x,aux,&p))
        {
            return 0;
        }
        Node *temp1;
        Node *temp2;
        for(int i=0;i<aux->m_edges.size();i++)
        {
            temp1 = aux->m_edges[i]->m_nodes[0];
            temp2 = aux->m_edges[i]->m_nodes[1];
            cout<<temp1->mdata<<endl;
            cout<<temp2->mdata<<endl;
            remove_vedges(temp1,aux->m_edges[i]);
            remove_vedges(temp2,aux->m_edges[i]);
        }

    }
















    N Dijkstra(N dato)
    {
        Node *temp;
        if(!find(dato,temp))
        {
            return 0;
        }
    }





};





int main(int argc, char *argv[]) {
	CGraph<int,char> g;
	g.InsertNode(8);
	g.InsertNode(10);
	g.InsertNode(3);
	g.InsertNode(1);
	g.InsertNode(2);
	g.InsertNode(7);
	g.InsertNode(4);
	g.InsertEdge(8,10,1,'c');
	g.InsertEdge(1,2,1,'c');
	g.InsertEdge(2,3,1,'c');
    g.InsertEdge(4,7,1,'e');
    g.InsertEdge(4,8,1,'e');
    g.InsertEdge(7,1,1,'c');
    g.InsertEdge(3,1,1,'c');
    g.remove_node(4);
	g.imprimir();
	return 0;
}
