#pragma once
template <class T>
class RedBlackTree {
public:
	void addNode(T *value);
	void deleteNode(T *value);

	//capacity
	bool empty();
	int size();
	int max_size();

	//modifiers
	void clear();

private:
	int treeSize = 0;
	enum colors { RED, BLACK };
	struct node {
		T *value = nullptr;
		node *parent = nullptr;
		node *left = nullptr;
		node *right = nullptr;
		colors color = BLACK;
	};

	node *root = nullptr;
};

template<class T>
inline void RedBlackTree<T>::addNode(T *value)
{
	node *root = this->root;
	if (root == nullptr) {
		root = new node;
		root->value = value;
		this->root = root;
		treeSize++;
		return;
	}
	node *treeNode = root;
	while (treeNode != nullptr) {
		T nodeValue = *treeNode->value;
		T valueToInsert = *value;

		bool lessThanValue = false;
		if (nodeValue > valueToInsert)
			lessThanValue = false;
		else if (nodeValue < valueToInsert)
			lessThanValue = true;
		else // node value = value
			return;

		node *tmpNode = lessThanValue ? treeNode->right : treeNode->left;
		if (tmpNode == nullptr) {
			tmpNode = new node;
			tmpNode->value = value;

			if (lessThanValue)
				treeNode->right = tmpNode;
			else
				treeNode->left = tmpNode;
			treeSize++;
			return;
		}
		else if (tmpNode->value == value)
			return;
		else
			treeNode = tmpNode;
	}
	return;
}

template<class T>
inline bool RedBlackTree<T>::empty()
{
	return this->root == nullptr ? true : false;
}

template<class T>
inline int RedBlackTree<T>::size()
{
	return treeSize;
}

template<class T>
inline int RedBlackTree<T>::max_size()
{
	return std::numeric_limits<T>::max();
}
