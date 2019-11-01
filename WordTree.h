//Ben Wabschall
//COSC 2300
//Program 2
//Section 11

#ifndef WordTree_h
#define WordTree_h

template<class T>
struct Node
{
public:
	T data;
	Node<T>* left;
	Node<T>* right;

	//Node default constructor
	Node(T d) : data(d), left(nullptr), right(nullptr) {};
};

template <class T>
class WordTree
{
public:
	WordTree(); //Tree default constructor	
	~WordTree(); //destructor, uses burnTree 
	void burnTree(Node<T>* Nroot);
	bool remove(T d, Node<T>* n);

	Node<T>* findMin(Node<T>* n);
	Node<T>* findMax(Node<T>* n);

	bool callFind(T d, int& compares);//public overlay for find
	void callInsert(T d);//public overlay for insert 

	int height(Node<T>* treeH);
	int difference(Node<T>* treeD);

	Node<T>* rr_rotate(Node<T>* parent);
	Node<T>* ll_rotate(Node<T>* parent);
	Node<T>* lr_rotate(Node<T>* parent);
	Node<T>* rl_rotate(Node<T>* parent);

	Node<T>* balance(Node<T>* treeN);

protected:
	Node<T>* root[26];

	Node<T>* find(T d, Node<T>* n, int& compares);
	void insert(T d, Node<T>*& tree);
};
#endif 
