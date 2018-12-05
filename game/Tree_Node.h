#include "flip.cpp"
#include <unordered_map>
#include <string>
#include <queue> 

#ifndef Tree_Node_H
#define Tree_Node_H

struct Tree;

struct Tree_Node //structure that contains the pancake stack as the node, and all posibilities as the children 
{
	vector<int> node; //the current node we are on when traversing
	vector<Tree_Node> children; // all of the possible flips of the node, the size should be equal to node.size()
	int index;
	Tree_Node* parent;
	string parent_key;
	int node_sortedness = 1000; //the sortedness value of the current node based on the sortedness value, starts off withi impossible value
	int total_sortedness = 1000; //total known sortedeness of the shortest path to our goal, should be updated every move
	int depth = 0;
	string key = " ";
	void set_children(Tree* t); //creates the children of the current node using the sortednessfunction
	Tree_Node(){}
	Tree_Node(vector<int> n)
	{
		node = n;
		for (int i = 0; i < n.size(); ++i)
		{
			key += to_string(n[i]);
		}
	}
	void print_layer(); //will print the parent node followed by the children nodes, for debugging purposes only
	void set_sortedness(); //sets the node sortedness of all of the children
};
	
struct Tree
{
	vector<int>* path;
	std::unordered_map<std::string, Tree_Node> created_map = {}; //a map of all of the nodes we have already traversed, if we come across something already in the list we know not to use it 
	priority_queue<Tree_Node> mpq; //minimum priority queue of all of the available nodes 
	Tree_Node next_start_node;
	Tree_Node solution; 
	int count = 0; 
};

bool operator<(const Tree_Node& a, const Tree_Node& b) {
  return a.node_sortedness > b.node_sortedness;
}

#endif