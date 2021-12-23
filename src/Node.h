/*
 * Node.h
 *
 *  Created on: Oct 1, 2020
 *      Author: xxdin
 */

#ifndef NODE_H_
#define NODE_H_
template<class T>
class Node{
public:
	Node(){up = nullptr;down = nullptr; left = nullptr; right = nullptr; payload = T();};

	Node(Node *u, Node *d, Node *l, Node *r, T obj){up = u;down = d; left = l; right = r; payload = obj;};

	Node* getUp(){return up;};
	void setUp(Node *u){this->up = u;};

	Node* getDown(){return down;};
	void setDown(Node *d){this->down = d;};

	Node* getLeft(){return left;};
	void setLeft(Node *l){this->left = l;};

	Node* getRight(){return right;};
	void setRight(Node *r){this->right = r;};

	T getSeatObj(){return payload;};
	void setSeatObj(T *seat){this->payload = *seat;};
protected:
	Node *up;
	Node *down;
	Node *left;
	Node *right;
	T payload;
};

#endif /* NODE_H_ */
