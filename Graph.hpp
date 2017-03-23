//
//  Adjancy List.hpp
//  Void
//
//  Created by Majd Takieddine on 2/12/17.
//  Copyright © 2017 Majd Takieddine. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <list>
#include <map>

using namespace std;
enum Type
{
    Directed,
    Undirected
};

template<class T>
class Graph
{
private:
    
    struct Edge
    {
        T v;
    };
    
    struct attribs
    {
        bool visited;
        int distance,time_start,time_finish;
        T pred;
    };
    
    struct Edges_Type
    {
        list<pair<T,T>> Back;
        list<pair<T,T>> Forward;
        list<pair<T,T>> Cross;
        list<pair<T,T>> Tree;
    };
    typedef list<Edge> u;
    
    typedef map<T,u* > List;
    
    List Adj;
    
    Type mode;
    
    map<T,attribs>* ats;
    
    Edges_Type ET;
    
    int size;
    
    list<T> topologicalOrder;
    
private:
    
    void BFS(T vertix)
    {
        auto it=Adj.find(vertix);
        
        if(it==Adj.end()) { cout<<"Vertix Not Found"<<endl; exit(1); };
        
        ats=new map<T,attribs>;
        
        for(it=Adj.begin();it!=Adj.end();it++)
        {
            (*ats)[it->first].visited=false;
            (*ats)[it->first].distance=0;
            (*ats)[it->first].pred=NULL;
        }
        
        list<T> queue;
        
        queue.push_back(vertix);
        (*ats)[vertix].visited=true;
        
        while(!queue.empty())
        {
            vertix=queue.front();
            queue.pop_front();
            
            for(auto j=Adj[vertix]->begin(); j!=Adj[vertix]->end();j++)
            {
                if(!(*ats)[(*j).v].visited)
                {
                    (*ats)[(*j).v].visited=true;
                    (*ats)[(*j).v].pred=vertix;
                    (*ats)[(*j).v].distance= (*ats)[vertix].distance+1;
                    queue.push_back((*j).v);
                }
                
            }
        }
        
    }
    
    void DFS_Visit(T u,int &time)
    {
        (*ats)[u].time_start=++time;
        (*ats)[u].visited=true;
        pair<T,T> p;
        
        for(auto it=Adj[u]->begin(); it!=Adj[u]->end(); it++)
        {
            p=make_pair(u,(*it).v);
            
            if(!(*ats)[(*it).v].visited)
            {
                (*ats)[(*it).v].pred=u;
                ET.Tree.push_back(p);
                DFS_Visit((*it).v,time);
            }
            else
            {
                if((*ats)[(*it).v].time_finish && (*ats)[(*it).v].time_finish < (*ats)[u].time_start)
                    ET.Cross.push_back(p);
                else if( (*it).v==u || (*ats)[(*it).v].time_start < (*ats)[u].time_start)
                    ET.Back.push_back(p);
                else
                    ET.Forward.push_back(p);
                
            }
        }
        
        (*ats)[u].time_finish=++time;
        topologicalOrder.push_front(u);
    }
    
    void DFS()
    {
        ats=new map<T,attribs>;
        
        for(auto it=Adj.begin(); it!=Adj.end(); it++)
        {
            (*ats)[it->first].visited=false;
            (*ats)[it->first].pred=NULL;
            (*ats)[it->first].time_start=0;
            (*ats)[it->first].time_finish=0;
        }
        
        int time=0;
        
        for(auto it=Adj.begin(); it!=Adj.end(); it++)
            if(!(*ats)[it->first].visited)
                DFS_Visit(it->first,time);
        
    }
public:
    Graph(Type g) {mode=g;size=0; ats=NULL;}
    
    void Add_Vertix(T v)
    {
        Adj[v]=new u;
            
        size++;
    }
    
    void Add_Edge(T src,T dest)
    {
        
        auto it=Adj.find(src);
        
        if(it==Adj.end()) { cout<<"Vertix Not Found"<<endl; return; };
      
        Edge temp; temp.v=dest;
        
        Adj[src]->push_back(temp);
        
        if(mode==Undirected)
        {
            temp.v=src;
            Adj[dest]->push_back(temp);
        }
    }
    
    void Remove_Edge(T src,T dest)
    {
        auto it=Adj.find(src);
        
        if(it==Adj.end()) { cout<<"Vertix Not Found"<<endl; return; };
        
        typename u::iterator j;
        
        for(j=Adj[src]->begin(); j!=Adj[src]->end();j++)
            if(*j.v==dest)
                Adj[src]->erase(j);
        
        if(j==Adj[src]->end())
            cout<<"Edge Not Found"<<endl;
    }
    void Print()
    {
        
        for(auto i=Adj.begin();i!=Adj.end();i++)
        {
            cout<<i->first<<":";
            
            for(auto j=Adj[i->first]->begin(); j!=Adj[i->first]->end();j++)
                cout<<" -> "<<(*j).v;
            cout<<endl;
        }
    }
    
    void _Print_Path_h(T s, T v,map<T,attribs>& Attbs)
    {
        if(v==s)
            cout<<s;
        else
            if(!Attbs[v].pred)
                cout<<"No path exsits"<<endl;
        else
        {
            _Print_Path_h(s, Attbs[v].pred, Attbs);
            cout<<"->"<<v;
        }
    }
    
    void Print_Path(T s,T v)
    {
        BFS(s);
        
        cout<<"Shortest Path Length: "<<(*ats)[v].distance<<endl;
        
        _Print_Path_h(s, v,*ats);
        
    }
    
    void Times()
    {
        if(!ats)
            DFS();
        
        for(auto it=Adj.begin();it!=Adj.end();it++)
            cout<<it->first<<": ("<<(*ats)[it->first].time_start<<","<<(*ats)[it->first].time_finish<<")\n";
    }
    
    void Edges_Type()
    {
        if(!ats)
            DFS();
        
        cout<<"Tree Edges: ";
        for(auto it=ET.Tree.begin(); it!= ET.Tree.end(); it++)
            cout<<"("<<(*it).first<<","<<(*it).second<<")"<<" ";
        cout<<"\nForward Edges: ";
        for(auto it=ET.Forward.begin(); it!= ET.Forward.end(); it++)
            cout<<"("<<(*it).first<<","<<(*it).second<<")"<<" ";
        cout<<"\nCross Edges: ";
        for(auto it=ET.Cross.begin(); it!= ET.Cross.end(); it++)
            cout<<"("<<(*it).first<<","<<(*it).second<<")"<<" ";
        cout<<"\nBack Edges: ";
        for(auto it=ET.Back.begin(); it!= ET.Back.end(); it++)
            cout<<"("<<(*it).first<<","<<(*it).second<<")"<<" ";
    }
    
    Graph Transpose()
    {
        Graph trans(Directed);
        
        for(auto i=Adj.begin(); i!=Adj.end();i++)
            trans.Adj[i->first]=new u;
        
        for(auto i=Adj.begin(); i!=Adj.end();i++)
            for(auto j=Adj[i->first]->begin(); j!=Adj[i->first]->end();j++)
            { Edge e; e.v=i->first; trans.Adj[(*j).v]->push_back(e); }
        
        return trans;
    }
    
    list<T> getTopologicalOrder()
    {
        if(topologicalOrder.empty())
            DFS();
        
        return topologicalOrder;
    }
    
    void StronglyConnected()
    {
        if(!ats)
            DFS();
        
        cout<<"Strongly Connected Components"<<endl;
        
        for(auto it=ET.Back.begin(); it!= ET.Back.end(); it++)
        { _Print_Path_h((*it).second, (*it).first,*ats); cout<<endl;}
    }
    
    ~Graph()
    {
        for(auto it=Adj.begin() ;it!=Adj.end() ;it++)
            delete it->second;
        
    }
};

#endif /* Graph_hpp */
