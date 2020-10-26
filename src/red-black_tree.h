#pragma once
template <class T>
class RedBlackTree {
public:
	void addNode(T *value);
	void deleteNode(T *value);

	int size();
	void clear();

private:
	int treeSize = 0;
	enum colors { RED, BLACK };
	struct node {
		T *value = nullptr;
		node *parent = nullptr;
		node *left = nullptr;
		node *right = nullptr;
		colors color = RED;
	};
	node *root = nullptr;

	node *getNIL() {
		node *nilNode = new node;
		nilNode->color = BLACK;
		return nilNode;
	}
	bool isNIL(node *node);

	void deleteTree(node *treeNode);
	void destroyNode(node *treeNode);
};

template<class T>
inline void RedBlackTree<T>::addNode(T *value)
{
	T valueToInsert = *value;

	node *nodeToInsert = new node;
	nodeToInsert->value = value;
	nodeToInsert->parent = nullptr;
	nodeToInsert->left = getNIL();
	nodeToInsert->right = getNIL();
	nodeToInsert->color = RED;

	if (this->root == nullptr) {
		this->root = nodeToInsert;
		this->root->color = BLACK;
		treeSize++;
		return;
	}
	node *treeNode = this->root;
	node *parent = this->root;
	while (!isNIL(treeNode)) {
		T nodeValue = *treeNode->value;
		bool currentNodeLessThanValue = false;

		if (nodeValue == valueToInsert)
			return;
		currentNodeLessThanValue = nodeValue > valueToInsert ? false : true;

		node *tmpNode = currentNodeLessThanValue ? treeNode->right : treeNode->left;
		if (isNIL(tmpNode)) {
			nodeToInsert->parent = treeNode;
			currentNodeLessThanValue ? treeNode->right = nodeToInsert : treeNode->left = nodeToInsert;
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
inline void RedBlackTree<T>::deleteNode(T * value)
{
	node *treeNode = this->root;
	if (treeNode == nullptr)
		return;
	T valueToDelete = *value;

	while (!isNIL(treeNode)) {
		T nodeValue = *treeNode->value;

		if (nodeValue > valueToDelete) {
			treeNode = treeNode->left;
			continue;
		}
		else if (nodeValue < valueToDelete) {
			treeNode = treeNode->right;
			continue;
		}
		else { // nodevalue == value
			bool leftIsNIL = isNIL(treeNode->left);
			bool rightIsNIL = isNIL(treeNode->right);

			if (leftIsNIL && rightIsNIL) {
				delete treeNode;
				treeSize--;
				return;
			}
			else if (leftIsNIL || rightIsNIL) {
				node *tmpNode = leftIsNIL ? treeNode->right : treeNode->left;
				delete treeNode->value;
				treeNode->value = tmpNode->value;
				treeNode->left = tmpNode->left;
				treeNode->right = tmpNode->right;
				treeSize--;
				delete tmpNode;
				return;
			}
			else {//both subtree not empty
				node *tmpNode = treeNode->right;
				node *parent = tmpNode;

				while (!isNIL(tmpNode->left)) //find smallest value
					tmpNode = tmpNode->left;

				delete treeNode->value;
				treeNode->value = tmpNode->value;
				tmpNode->value = nullptr;
				if (!isNIL(tmpNode->right))//if smallest node have right child
					parent->left = tmpNode->right;
				treeSize--;
				return;
			}
		}
	}
	//value not find
	return;
}

template<class T>
inline int RedBlackTree<T>::size()
{
	return treeSize;
}

template<class T>
inline void RedBlackTree<T>::clear()
{
	deleteTree(this->root);
	this->root = nullptr;
}

template<class T>
inline bool RedBlackTree<T>::isNIL(node *node)
{
	if (node->color == BLACK && node->left == nullptr && node->right == nullptr && node->parent == nullptr)
		return true;
	return false;
}

template<class T>
inline void RedBlackTree<T>::deleteTree(node *treeNode) {
	if (treeNode->left != nullptr)
		deleteTree(treeNode->left);
	if (treeNode->right != nullptr)
		deleteTree(treeNode->right);

	destroyNode(treeNode);
	return;
}

template<class T>
inline void RedBlackTree<T>::destroyNode(node *treeNode)
{
	treeSize--;
	delete treeNode->value;
	delete treeNode;
}
