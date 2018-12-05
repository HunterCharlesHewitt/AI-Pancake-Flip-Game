#include "Tree_Node.h"

void Tree_Node::print_layer()
{
	cout << endl << "Parent of this layer: " << endl;
	for(int i = 0; i < node.size(); ++i)
	{
		cout << node[i] << ", ";
	}
	cout << endl << endl;
	cout << "Children of this layer: " << endl;
	for(int i = 0; i < children.size(); ++i)
	{
		for(int j = 0; j < children[i].node.size(); ++j)
		{
			cout << children[i].node.at(j) << ", ";
		}
		cout << ": " << children[i].node_sortedness;
		cout << endl;
	}
}

void Tree_Node::set_children(Tree* t)
{
	for(int i = 1; i < node.size(); ++i)
	{
		Tree_Node dummy((flip(node,i+1)));
		dummy.index = i+1;
		std::unordered_map<std::string,Tree_Node>::const_iterator got = t->created_map.find(dummy.key);
		if(got == t->created_map.end())
		{
			dummy.parent = this;
			dummy.parent_key = this->key;
			dummy.depth = this->depth;
			dummy.depth += 1;
			dummy.set_sortedness();
			children.push_back(dummy);
			t->mpq.push(dummy);
			std::pair<std::string,Tree_Node> dummy_pair (dummy.key,dummy);
			t->created_map.insert(dummy_pair);
			if(dummy.node_sortedness == 0)
			{
			 	return;
			}
		}
	}
}

void Tree_Node::set_sortedness()
{
	bool is_less = false; //true indicates that the current value is less than the next
	vector<bool> is_less_vect; //vector containing all of the is less bools in order
	is_less_vect.push_back(true); //the first value will always be less than the next because we begin our comparisons with zero
	node_sortedness = 0;
	for(int i = 0; i < node.size()-1; ++i)
	{
		if(node.at(i) < node.at(i+1))
			is_less_vect.push_back(true);
		else
			is_less_vect.push_back(false);
	}
	for(int i = 0; i < is_less_vect.size() -1; ++i)
	{
		if(is_less_vect[i] != is_less_vect[i+1])
			++node_sortedness;
	}
}

Tree_Node make_move(Tree_Node tn, Tree* t, int diff, int move_level)
{
	tn = t->next_start_node;
	if(tn.node_sortedness != 0)
		while(tn.depth < diff+move_level)
		{
			tn.set_children(t);
			tn = (t->mpq.top());
			t->mpq.pop();
			if(tn.node_sortedness == 0)
			{
				break;

			}	
		}
	t->next_start_node = tn;
	while(tn.depth > move_level+1)
	{
		tn = t->created_map.at(tn.parent_key);
	}
	cout << tn.index << endl;
	return tn;
}