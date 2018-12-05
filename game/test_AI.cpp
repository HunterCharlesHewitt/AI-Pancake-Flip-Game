#include "flip.cpp"

struct Tree_node
{
	vector<int> node;
	vector<Tree_node> children;
	int node_sortedness;
	void set_children();
	Tree_node(vector<int> n)
	{
		node = n;
	}
	void print_layer();
	int find_best_child(); //returns the position of the best child in the child vector
};

vector<Tree_node> path;

void Tree_node::set_children()
{
	for(int i = 1; i < node.size(); ++i)
	{
		Tree_node dummy(flip(node,i+1));
		children.push_back(dummy);
	}
}

void Tree_node::print_layer()
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
		cout << endl;
	}
}

int Tree_node::find_best_child()
{
	bool is_less = false; //true indicates that the current value is less than the next
	bool switch_sign = false; //true indicates that the previous is_less evaluated the same as the current
	vector<bool> is_less_vect; //vector containing all of the is less bools in order
	is_less_vect.push_back(true); //the first value will always be less than the next because we begin our comparisons with zero
	int sortedness = 0;
	int min_sortedness = 1000;
	int min_sortedness_index;
	for(int i = 0; i < children.size(); ++i)
	{
		for(int j = 0; j < children[i].node.size()-1; ++j)
		{
			if(children[i].node.at(j) < children[i].node.at(j+1))
			{
				is_less_vect.push_back(true);
			}
			else
			{
				is_less_vect.push_back(false);
			}
		}
		for(int k = 0; k < is_less_vect.size() -1; ++k)
		{
			if(is_less_vect[k] != is_less_vect[k+1])
			{
				++sortedness;
			}
		}
		children[i].node_sortedness = sortedness;
		cout << "Sortedness at " << i << ": " << children[i].node_sortedness << endl;
		if(sortedness < min_sortedness)
		{
			min_sortedness = sortedness;
			min_sortedness_index = i;
		}
		is_less_vect.clear();
		is_less_vect.push_back(true);
		sortedness = 0;
	}
	cout << "Min sortedness: " << min_sortedness << endl;
	return min_sortedness_index;
}

Tree_node traverse_depth(int diff, Tree_node t)
{
	for(int i = 0; i < diff; ++i)
	{
		t.set_children();
		t.print_layer();
		t = t.children.at(t.find_best_child());
		path.push_back(t);
		if(t.node_sortedness == 0)
		{
			return t;
		}
	}
	return t;
}

int main(){
    vector<int> stack = {6,4,5,2,3,1};
    int flip_location = 1;;
    //print stack
    cout << "Original stack: " << endl;
    for(int i=0; i<stack.size(); ++i){
        cout << stack.at(i) << " ";
    }
   Tree_node tn(stack);
   Tree_node sol = traverse_depth(10, tn);
   if(sol.node[0] == 1, sol.node[1] == 2, sol.node[2] == 3, sol.node[3] == 4, sol.node[4] == 5, sol.node[5] == 6)
   {
   		cout << "Tests Passed " << endl;
   }
}