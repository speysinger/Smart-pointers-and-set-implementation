#pragma once
template <class T>
class RedBlackTree {
public:
	void addNode(T value);
	void deleteNode(T *value);

	//capacity
	bool empty();
	int size();
	int max_size();

	//modifiers
	void clear();

private:
	enum colors { RED, BLACK };
	struct node {
		T value = nullptr;
		node *parent = nullptr;
		node *left = nullptr;
		node *right = nullptr;
		colors color = BLACK;
	};

	node *root = nullptr;
};

template<class T>
inline void RedBlackTree<T>::addNode(T value)
{
	node *root = this->root;
	this->root->
	if (root == nullptr) {//empty root
		root.value = value;
	}
	node *tempRoot = root;
	//lambda for left and right branch
	while (tempRoot != nullptr) {
		if (tempRoot->value > value) {//less than left
			node *leftNode = tempRoot->left;
			if (leftNode == nullptr) {
				leftNode = new node;
				leftNode->value = value;
			}
			else if (leftNode->value == value)
				return;
			else
				tempRoot = leftNode;
		}
		else if (tempRoot->value < value) {
			node *rightNode = tempRoot->right;
			if (rightNode == nullptr) {
				rightNode = new node;
				rightNode->value = value;
			}
			else if (rightNode->value == value)
				return;
			else
				tempRoot = rightNode;
		}
		else // node value = value
			return;
	}
}
