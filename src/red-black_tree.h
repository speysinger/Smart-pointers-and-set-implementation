#pragma once
template <class T>
class RedBlackTree {
public:
	RedBlackTree() {
		node *root = nullptr;
	}
	void addNode(T &value);
	void deleteNode(T *value);
	T *find(T &value);

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

	void insertionFix(node *insertedNode);

	void rotateLeft(node *treeNode);
	void rotateRight(node *treeNode);

	void deleteTree(node *treeNode);
	void destroyNode(node *treeNode);
};

template<class T>
inline void RedBlackTree<T>::addNode(T &value)
{
	node *nodeToInsert = new node;
	nodeToInsert->value = &value;
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

	while (!isNIL(treeNode)) {
		T nodeValue = *treeNode->value;
		bool currentNodeLessThanValue = false;

		if (nodeValue == value)
			return;
		currentNodeLessThanValue = nodeValue > value ? false : true;

		node *tmpNode = currentNodeLessThanValue ? treeNode->right : treeNode->left;
		if (isNIL(tmpNode)) {
			nodeToInsert->parent = treeNode;
			currentNodeLessThanValue ? treeNode->right = nodeToInsert : treeNode->left = nodeToInsert;
			treeSize++;
			currentNodeLessThanValue ? insertionFix(treeNode->right) : insertionFix(treeNode->left);
			return;
		}
		else if (*tmpNode->value == value)
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

				while (!isNIL(tmpNode->left)) //find smallest value
					tmpNode = tmpNode->left;

				delete treeNode->value;
				treeNode->value = tmpNode->value;
				tmpNode->value = nullptr;
				if (!isNIL(tmpNode->right))//if smallest node have right child
					tmpNode->parent->left = tmpNode->right;
				treeSize--;
				return;
			}
		}
	}
	//value not find
	return;
}

template<class T>
inline T * RedBlackTree<T>::find(T &value)
{
	node *treeNode = this->root;
	while (!isNIL(treeNode)) {
		T nodeValue = *treeNode->value;
		if (nodeValue == value)
			return treeNode->value;
		else if (nodeValue > value) {
			treeNode = treeNode->left;
			continue;
		}
		else {
			treeNode = treeNode->right;
			continue;
		}
	}
	return nullptr;
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
inline void RedBlackTree<T>::insertionFix(node *insertedNode)
{
	node *parent = insertedNode->parent;

	if (parent == nullptr) {
		insertedNode->color = BLACK;
		return;
	}

	if (parent->color == RED) {
		while (!isNIL(insertedNode) && parent->color == RED) {
			parent = insertedNode->parent;
			node *grandParent = parent->parent;
			node *uncle = grandParent->left == parent ? grandParent->right : grandParent->left;
			if (parent->color == RED && (uncle && uncle->color == RED)) {//case 1: red parent and red uncle
				parent->color = BLACK;
				uncle->color = BLACK;
				grandParent->color = RED;

				if (this->root == grandParent) {
					grandParent->color = BLACK;
					return;
				}
				insertedNode = grandParent;
				continue;
			}
			else if (parent->color == RED && uncle->color == BLACK) {//case 2: red parent and black uncle
				bool nodeIsRightChild = parent->right == insertedNode;
				bool parentIsRightChild = grandParent->right == parent;
				if (nodeIsRightChild && !parentIsRightChild) {
					rotateLeft(parent);
					insertedNode = insertedNode->left;
				}
				else if (!nodeIsRightChild && parentIsRightChild) {
					rotateRight(parent);
					insertedNode = insertedNode->right;
				}

				parent->color = BLACK;
				grandParent->color = RED;
				if (!nodeIsRightChild && !parentIsRightChild)
					rotateRight(grandParent);
				else
					rotateLeft(grandParent);
			}
			else
				return;
		}
	}
}

template<class T>
inline void RedBlackTree<T>::rotateLeft(node * treeNode)
{
	node *pivot = treeNode->right;

	pivot->parent = treeNode->parent;
	if (treeNode->parent != nullptr) {
		if (treeNode->parent->left == treeNode)
			treeNode->parent->left = pivot;
		else
			treeNode->parent->right = pivot;
	}

	treeNode->right = pivot->left;
	if (pivot->left != nullptr)
		pivot->left->parent = treeNode;

	treeNode->parent = pivot;
	pivot->left = treeNode;
	if (treeNode == this->root)
		this->root = pivot;
}

template<class T>
inline void RedBlackTree<T>::rotateRight(node *treeNode)
{
	node *pivot = treeNode->left;

	pivot->parent = treeNode->parent;
	if (pivot->parent == nullptr) {
		this->root = pivot;
	}
	if (treeNode->parent != nullptr) {
		if (treeNode->parent->left == treeNode)
			treeNode->parent->left = pivot;
		else
			treeNode->parent->right = pivot;
	}

	treeNode->left = pivot->right;
	if (pivot->right != nullptr)
		pivot->right->parent = treeNode;

	treeNode->parent = pivot;
	pivot->right = treeNode;
	if (treeNode == this->root)
		this->root = pivot;
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
	if (!isNIL(treeNode))
		treeSize--;
	delete treeNode->value;
	delete treeNode;
}
