//Assignment #2
//Davis Kieu

#include<sstream>
#include<fstream>
#include<string>
#include"Vertex.h"
#include"Graph.h"
#include"PQ.h"

using namespace std;

typedef Vertex<string> strVertex;

//Edge representation 
struct edge
{
	strVertex fromVertex;
	strVertex toVertex;
	int distance;

	bool operator==(const edge& other) { return this->distance == other.distance; }
	bool operator<(const edge& other) { return this->distance < other.distance; }
	bool operator<=(const edge& other) { return this->distance <= other.distance; }
	bool operator>(const edge& other) { return this->distance > other.distance; }
	bool operator>=(const edge& other) { return this->distance >= other.distance; }
};

ostream& operator<<(ostream&, const strVertex&);

void initialSelection(int&);
void departureSelection(Graph<strVertex>&,strVertex&);
void destinationSelection(Graph<strVertex>&, strVertex& , strVertex&);
void loadGraph(Graph<strVertex>&, string);
bool hasPath(Graph<strVertex>&, strVertex, strVertex, bool&, bool&);
void listPaths(Graph<strVertex>&, strVertex, strVertex);

const int MAX = 100;
const string fileName = "Load.txt";

int main()
{
	int choice;

	Graph<strVertex> flights(MAX);
	loadGraph(flights, fileName);

	do
	{
		initialSelection(choice);
		switch (choice)
		{
		case 1:
		{
			bool directFlg = false , throughFlg = false;

			strVertex start("");
			strVertex end("");

			departureSelection(flights, start);
			destinationSelection(flights, end, start);

			if (hasPath(flights, start, end, directFlg, throughFlg))
			{
				if (directFlg)
					cout << "Direct connection between [" << start << "] and [" << end << "]\n";
				else
					cout << "No direct connection between [" << start << "] and [" << end << "]\n";

				if (throughFlg)
					listPaths(flights, start, end);
				else
					cout << "No through connection between [" << start << "] and [" << end << "]\n";			
			}
			else
				cout << "No connection between [" << start << "] and [" << end << "]\n";
			
			cout << "Press any button to continue...";
			cin.get();

			break;
		}
		case 2:
		{
			cout << "Ending Program!\n";
			return 0;
		}
		default:
			cout << "Not a choice.Choose again!\n";
		}
	} while (1);
}
void listPaths(Graph<strVertex>& flights, strVertex start, strVertex end)
{
	//Uses modified shortest - path for paths

	//initalizing variables & auxiliary structures
	edge item;
	strVertex vertex;

	int minDistance;

	PQ<edge> pq(MAX);
	Queue<strVertex> vertexQ(MAX);

	//clearing previous manipulation of marks
	flights.clearMarks();

	//initalizing starting edges
	item.fromVertex = start;
	item.distance = 0;

	//skip processing the direct connection
	flights.markVertex(start);
	minDistance = item.distance;// min distance represents distance from the starting vertex
	flights.getAdjacent(item.fromVertex, vertexQ);

	while (!vertexQ.isEmpty())
	{
		vertexQ.Dequeue(vertex);
		if (!flights.isMarked(vertex) && !(end == vertex)) // if to vertex is marked then skip. To vertex is only vertex not yet visited.
		{
			//setting up edge represention 
			item.toVertex = vertex;
			item.distance = minDistance + flights.weightIs(item.fromVertex, vertex); // weight from starting vertex
			pq.Enqueue(item);
		}
	}

	//starting the traversal
	cout << "Listing connection between [" << start << "] and [" << end << "] ... \n";
	cout <<  "---- Connection list ---- \n";

	do
	{
		pq.Dequeue(item); //inspecting edge

		if (!flights.isMarked(item.toVertex)) //If the edge leads to a vertex already marked then skip processing
		{
			if (item.toVertex == end)
			{
				minDistance = item.distance;
				cout << " - Total Distance : " << minDistance << '\n';
			}
			else
			{
				flights.markVertex(item.toVertex);

				if(!(item.toVertex == item.fromVertex))
				cout << ' ' << item.toVertex << ' '; // Here it is established that we are now at the adj vertex  from from - vertex.

				//start setting up the next edge to process
				item.fromVertex = item.toVertex;
				minDistance = item.distance;// min distance represents distance from the starting vertex
				flights.getAdjacent(item.fromVertex, vertexQ);

				while (!vertexQ.isEmpty())
				{
					vertexQ.Dequeue(vertex);
					if (!flights.isMarked(vertex)) // if to vertex is marked then skip. To vertex is only vertex not yet visited.
					{
						//setting up edge represention 
						item.toVertex = vertex;
						item.distance = minDistance + flights.weightIs(item.fromVertex, vertex); // weight from starting vertex
						pq.Enqueue(item);
					}
				}
			}
		}
	} while (!pq.isEmpty());

	
}

bool hasPath(Graph<strVertex>& flights, strVertex start , strVertex end, bool& direct, bool& through)
{
	//Uses BFS to determine if there is a path between two Vertex. Uses flag parameters to signal direct and through connections and returns true if a connection exists.
	bool found = false;

	strVertex currVertex("");
	strVertex item("");

	const int NULL_EDGE = 0;

	Queue<strVertex> vertexQ(MAX);
	Queue<strVertex> adjQ(MAX);


	flights.clearMarks();

	if (flights.weightIs(start, end) != NULL_EDGE) //A direct connection exists if row representing start index has a non-null value to end index
	{
		direct = true;

		flights.markVertex(start);
		flights.getAdjacent(start, adjQ);

		while (!adjQ.isEmpty())
		{
			adjQ.Dequeue(item);
			//skipping the adj direct connection vertex
			if (!(item == end))
				vertexQ.Enqueue(item);
		}
	}
	else
	{
		direct = false;
		vertexQ.Enqueue(start);
	}

	do
	{
		vertexQ.Dequeue(currVertex);

		if (currVertex == end)
			found = through = true;
		else
		{
			if (!flights.isMarked(currVertex))
			{
				flights.markVertex(currVertex);
				flights.getAdjacent(currVertex, adjQ);

				while (!adjQ.isEmpty()) 
				{
					adjQ.Dequeue(item);
					if (!flights.isMarked(item))
						vertexQ.Enqueue(item);
				}
			}
		}
	} while (!vertexQ.isEmpty() && !found);

	if (!found)
		through = false;

	return (direct || through);
	
}
ostream& operator<<(ostream& out, const strVertex& vertex)
{
	out << vertex.value;
	return out;
}
void initialSelection(int& choice)
{
	string line;

	cout << "1.Choose Departure City\n"
		<< "2.Exit\n";

	getline(cin, line);
	stringstream(line) >> choice;
}
void departureSelection(Graph<strVertex>& flights, strVertex& start)
{
	string line;
	int selection;

	for (int i = 0; i < flights.numVertex; i++)
		cout << i << '.' << flights.vertices[i] << '\n';

	cout << "Select city: ";
	getline(cin, line);

	stringstream(line) >> selection;
	start = flights.vertices[selection];

}
void destinationSelection(Graph<strVertex>& flights, strVertex& end , strVertex& start)
{
	string line;
	int selection;

	for (int i = 0; i < flights.numVertex;i++)
	{
			if(!(flights.vertices[i] == start))
			cout << i << '.' << flights.vertices[i] << '\n';	
	}

	cout << "Select city: ";
	getline(cin, line);

	stringstream(line) >> selection;

	end = flights.vertices[selection];
}
void loadGraph(Graph<strVertex>& flights, string fileName)
{
	//Assumes file is formated according to procedure process.
	string line, buff;
	string auxilary[2];

	ifstream input(fileName);

	if (input.is_open())
	{
		getline(input, line);

		stringstream ss(line);

		while (!ss.eof())
		{
			ss >> buff;
			flights.addVertex((*new strVertex(buff)));
		}

		while (!input.eof())
		{
			strVertex * fromVertex, *toVertex;
			int weight;

			getline(input, line);

			//clear error bits and empty any old previous string 
			ss.clear();
			ss.str("");

			ss << line;			
			ss >> auxilary[0] >> auxilary[1] >> weight;

			fromVertex = new strVertex(auxilary[0]);
			toVertex = new strVertex(auxilary[1]);

			flights.addEdge(*fromVertex, *toVertex, weight);

			delete fromVertex;
			delete toVertex;

		}

		input.close();
	}
}
