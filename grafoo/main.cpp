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
	bool m_dir;
	CEdge(Node *a, Node *b ,bool dir , E dato)
	{
	    m_nodes[0] = a;
	    m_nodes[1] = b;
	    m_dir = dir;
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
//	    for(int i=0;i<m_nodes.size();i++)
//        {
//            if(m_nodes[i]->mdata == a)
//            {
//                aux = m_nodes[i];
//            }
//            if(m_nodes[i]->mdata == b)
//            {
//                aux2 = m_nodes[i];
//            }
//
//        }
        if(find(a,aux) && find(b,aux2))
        {
                Edge *nuevo = new Edge(aux,aux2,dir,dato);
                aux->m_edges.push_back(nuevo);
                bool dir2 = (dir+1)%2;
                Edge *nuevo2 = new Edge(aux,aux2,dir2,dato);
                aux2->m_edges.push_back(nuevo2);
        }

	}

	void imprimir()
	{
	    for(int i=0;i<m_nodes.size();i++)
        {
            cout<<m_nodes[i]->mdata;
            vector<Edge*> aux = m_nodes[i]->m_edges;
            for(int j=0;j<aux.size();j++)
            {
                cout<<aux[j]->m_data<<endl;
                if(aux[j]->m_dir == 1)
                    cout<<"->"<<aux[j]->m_nodes[1]->mdata<<endl;
                else{
                    cout<<"<-"<<aux[j]->m_nodes[0]->mdata<<endl;
                }

            }
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

    N Dijkstra(N dato)
    {
        Node *temp;
        if(!find(dato,temp))
        {
            return 0;
        }
        for()




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
	g.InsertEdge(10,8,1,'c');
	g.InsertEdge(1,2,1,'c');
	g.InsertEdge(2,3,1,'c');
    g.InsertEdge(4,7,1,'c');
    g.InsertEdge(7,1,1,'c');
    g.InsertEdge(3,1,1,'c');
	g.imprimir();
	return 0;
}
