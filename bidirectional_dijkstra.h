using namespace std;

struct Edge
{
	int id;
	int weight;
};
struct Node
{
	int id;
	int no_neigh;
	Edge** neighbours;
};
struct Graph
{
	Node** nodes;
};
struct Queue
{
	int distance;
	int node_id;

	bool operator<(const Queue& other)const{
		return distance>other.distance;
	}
};


class Dijkstra
{
	private:
		map<string,int> mapping;
		map<int,string> mapping_rev;
		string source;
		string destination;
		int no_vertices;
		Graph* graph;
		vector <Queue> forward_queue;
		vector <Queue> backward_queue;
		int* forward_distance;
		int* backward_distance;
		int* forward_path;
		int* backward_path;
		int* forward_selected;
		int* backward_selected;
		int count;
		int meeting_point;
	public:
		Dijkstra(string, int);
		void take_input();
		void print_graph();
		void relax_edge_f(int&, int&);
		void relax_edge_b(int&, int&);
		void print_distance();
		void dijkstra();
		virtual ~Dijkstra();
};


