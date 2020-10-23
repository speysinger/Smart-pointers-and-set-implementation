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
		colors color = BLACK;
	};
	node *root = nullptr;

	void deleteTree(node *treeNode);
	void destroyNode(node *treeNode);
};

template<class T>
inline void RedBlackTree<T>::addNode(T *value)
{
	T valueToInsert = *value;
	if (this->root == nullptr) {
		this->root = new node;
		this->root->value = value;
		treeSize++;
		return;
	}
	node *treeNode = this->root;
	while (treeNode != nullptr) {
		T nodeValue = *treeNode->value;
		bool currentNodeLessThanValue = false;

		if (nodeValue == valueToInsert)
			return;
		currentNodeLessThanValue = nodeValue > valueToInsert ? false : true;

		node *tmpNode = currentNodeLessThanValue ? treeNode->right : treeNode->left;
		if (tmpNode == nullptr) {
			tmpNode = new node;
			tmpNode->value = value;

			currentNodeLessThanValue ? treeNode->right = tmpNode : treeNode->left = tmpNode;
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

	while (treeNode != nullptr) {
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
			if (treeNode->left == nullptr && treeNode->right == nullptr) {
				delete treeNode;
				treeSize--;
				return;
			}
			else if (treeNode->left == nullptr || treeNode->right == nullptr) {
				node *tmpNode = treeNode->left == nullptr ? treeNode->right : treeNode->left;
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

				while (tmpNode->left != nullptr) {
					parent = tmpNode;
					tmpNode = tmpNode->left;
				}
				delete treeNode->value;
				treeNode->value = tmpNode->value;
				tmpNode->value = nullptr;
				if (tmpNode->right != nullptr)
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
inline void RedBlackTree<T>::deleteTree(node *treeNode)
{
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
