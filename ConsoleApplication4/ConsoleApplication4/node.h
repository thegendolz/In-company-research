#ifndef NODE_H
#define NODE_H

class Node {
	public:
		//Constructors
		Node();
		Node(int level, int id);
		int getId();
	
	private:
		//Variables
		int level;
		int id;
};

#endif 
