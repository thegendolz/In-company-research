#include "node.h"

Node::Node() {

}

Node::Node(int level, int id) {
	this->level = level;
	this->id = id;
}

int Node::getId() {
	return this->id;
}