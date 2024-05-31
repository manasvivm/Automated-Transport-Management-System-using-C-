//operator overloading, insertion and extraction operators, polymorphism, structures, vectors, maps, lists, heaps, arrays, dynamic constructor, parametrized constructor, DMA, pointers, reference variables, class scope operator, iterator, access specifiers, virtual destructor, file manipulation
//  enum, inline, lambda, template, function overriding

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "bidirectional_dijkstra.h"

using namespace std;

Dijkstra::Dijkstra(string des,int vertices)
{
	mapping={{"apesuniversity", 0}, {"bannerghatta", 1},{"churchstreet", 2},{"diarycircle", 3},{"hosur", 4}, {"indiranagar", 5},{"jayadevahospital", 6}, {"kormangala", 7}, {"mgroad", 8}, {"silkboard", 9}, {"ulsoor", 10}};
	mapping_rev={{0, "apesuniversity"}, {1, "bannerghatta"},{2, "churchstreet"},{3, "diarycircle"},{4, "hosur"}, {5, "indiranagar"},{6, "jayadevahospital"}, {7, "kormangala"}, {8, "mgroad"}, {9, "silkboard"}, {10, "ulsoor"}};
	source="apesuniversity";
	destination=des;
	no_vertices=vertices;

	graph=(Graph*)calloc(1,sizeof(Graph));
	graph->nodes=(Node**)calloc(no_vertices,sizeof(Node*));

	forward_queue.push_back({0,mapping[source]});
	backward_queue.push_back({0,mapping[destination]});

	forward_distance=new int[no_vertices]{};
	backward_distance=new int[no_vertices]{};
	forward_path=new int[no_vertices]{};
	backward_path=new int[no_vertices]{};
	forward_selected=new int[no_vertices]{};
	backward_selected=new int[no_vertices]{};

	for(int i=0;i<no_vertices;i++)
	{
		forward_distance[i]=99999;
		backward_distance[i]=99999;
		forward_path[i]=-1;
		backward_path[i]=-1;
	}

	forward_distance[mapping[source]]=0;
	backward_distance[mapping[destination]]=0;
	forward_path[mapping[source]]=mapping[source];
	backward_path[mapping[destination]]=mapping[destination];

	count=0;
	meeting_point=0;
}
void Dijkstra::take_input()
{
	fstream fin;
	string line,name,no_neigh,neighbours,neighbour,distance;
    fin.open("del.csv",ios::in);
	getline(fin,line);
	//cout<<"Enter number of neighbours,id and weight of each neighbour for each node"<<endl;
	for(int i=0;i<no_vertices;i++)
	{
		graph->nodes[i]=(Node*)calloc(1,sizeof(Node));
		graph->nodes[i]->id=i;

		getline(fin,line);
    	stringstream s1(line);
		getline(s1,name,',');
		getline(s1,no_neigh,',');
		getline(s1,neighbours,',');
    	stringstream s2(neighbours);

		graph->nodes[i]->no_neigh=stoi(no_neigh);
		graph->nodes[i]->neighbours=(Edge**)calloc(graph->nodes[i]->no_neigh,sizeof(Edge*));
		for(int j=0;j<graph->nodes[i]->no_neigh;j++)
		{
			getline(s2,neighbour,';');
			stringstream s3(neighbour);
			getline(s3,name,':');
			getline(s3,distance,':');
			graph->nodes[i]->neighbours[j]=(Edge*)calloc(1,sizeof(Edge));
			graph->nodes[i]->neighbours[j]->id=mapping[name];
			graph->nodes[i]->neighbours[j]->weight=stoi(distance);
		}
	}
}	
void Dijkstra::print_graph()
{
	for(int i=0;i<no_vertices;i++)
	{
		cout<<"id "<<i<<endl;
		for(int j=0;j<graph->nodes[i]->no_neigh;j++)
		{
			cout<<"id "<<graph->nodes[i]->neighbours[j]->id<<" weight "<<graph->nodes[i]->neighbours[j]->weight<<endl;
		}
	}
}
void Dijkstra::relax_edge_f(int &u,int &v)
{
	int v_=graph->nodes[u]->neighbours[v]->id;
	count+=1;
	if(forward_distance[v_]>forward_distance[u]+graph->nodes[u]->neighbours[v]->weight)
	{
		forward_distance[v_]=forward_distance[u]+graph->nodes[u]->neighbours[v]->weight;
		forward_path[graph->nodes[u]->neighbours[v]->id]=u;
		forward_queue.push_back({forward_distance[v_],v_});
	}
}
void Dijkstra::relax_edge_b(int &u,int &v)
{
	int v_=graph->nodes[u]->neighbours[v]->id;
	count+=1;
	if(backward_distance[v_]>backward_distance[u]+graph->nodes[u]->neighbours[v]->weight)
	{
		backward_distance[v_]=backward_distance[u]+graph->nodes[u]->neighbours[v]->weight;
		backward_path[graph->nodes[u]->neighbours[v]->id]=u;
		backward_queue.push_back({backward_distance[v_],v_});
	}
}
void Dijkstra::print_distance()
{
	int node;
	int dist=forward_distance[meeting_point]+backward_distance[meeting_point];
	auto eta = [](int d,double s){return d/s;};
	cout<<"Meeting Point "<<meeting_point<<endl;
	cout<<"Distance from "<<source<<" to "<<destination<<" = "<<dist<<" Km"<<endl;
	cout<<"Estimated Time of Arrival(ETA)"<<eta(dist,30.0)<<" hrs"<<endl;
	cout<<"Path:\n";
	list <int> path;
	node=meeting_point;
	while(forward_path[node]!=node)
	{
		path.push_front(node);
		node=forward_path[node];
	}
	node=meeting_point;
	while(backward_path[node]!=node)
	{
		node=backward_path[node];
		path.push_back(node);
	}
	path.push_front(mapping[source]);
	for(auto ptr=path.begin();ptr!=path.end();ptr++)
		cout<<mapping_rev[int(*ptr)]<<" ";
	cout<<endl;
	cout<<"Count of updates: "<<count<<endl;
	for(int i=0;i<no_vertices;i++)
	{
		cout<<i<<" "<<forward_distance[i]<<" "<<forward_path[i]<<" "<<backward_distance[i]<<" "<<backward_path[i]<<endl;
	}
}

void Dijkstra::dijkstra()
{
	int q_count=1;
	int u;
	Queue pop;
	while(q_count<no_vertices)
	{
		while(1)
		{
			make_heap(forward_queue.begin(),forward_queue.end());
			pop=forward_queue.front();
			pop_heap(forward_queue.begin(),forward_queue.end());
			forward_queue.pop_back();
			u=pop.node_id;
			if(forward_selected[u]==1)
				continue;
			else
				break;
		}
		//cout<<"min node f "<<u<<endl;
		forward_selected[u]=1;
		if(backward_selected[u]==1)
		{
			meeting_point=u;
			break;
		}
		else
		{
			for(int j=0;j<graph->nodes[u]->no_neigh;j++)
			{
				if(forward_selected[graph->nodes[u]->neighbours[j]->id]==0)
				{
					relax_edge_f(u,j);
				}
			}
		}
		while(1)
		{
			make_heap(backward_queue.begin(),backward_queue.end());
			pop=backward_queue.front();
			pop_heap(backward_queue.begin(),backward_queue.end());
			backward_queue.pop_back();
			u=pop.node_id;
			if(backward_selected[u]==1)
				continue;
			else
				break;
		}
		//cout<<"min node b "<<u<<endl;
		backward_selected[u]=1;
		if(forward_selected[u]==1)
		{
			meeting_point=u;
			break;
		}
		else
		{
			for(int j=0;j<graph->nodes[u]->no_neigh;j++)
			{
				if(backward_selected[graph->nodes[u]->neighbours[j]->id]==0)
				{
					relax_edge_b(u,j);
				}
			}
		}
	}
}
Dijkstra::~Dijkstra()
{
	delete[] forward_distance;
	delete[] backward_distance;
	delete[] forward_path;
	delete[] backward_path;
	delete[] forward_selected;
	delete[] backward_selected;
}		

int main()
{
	string destination;
	int no_vertices;
	cout<<"Enter the destination and number of vertices"<<endl;
	cin>>destination>>no_vertices;
	Dijkstra obj(destination,no_vertices);
	obj.take_input();
	obj.print_graph();
	obj.dijkstra();
	obj.print_distance();
	return 0;
}
