#include <vector>
#include <iostream>

using namespace std;

typedef struct tree_elem {
int value;
struct tree_elem* left;
struct tree_elem* right;
} tree_elem;
class Container
{
public:

    // Виртуальные методы, будут реализованы далее
    virtual void insert(int value) = 0;
    virtual bool exists(int value) = 0;
    virtual void remove(int value) = 0;
    // Это потом заменим на перегруженный оператор <<
    virtual void print() = 0;
    // Виртуальный деструктор
    virtual ~Container();
};


Container::~Container() { }

class SimpleTree: public Container
{
protected:
   tree_elem* root;
   tree_elem* cr(int a)
   {
    tree_elem* tree1= (tree_elem*)malloc(sizeof( tree_elem));
    tree1->value = a;
    tree1->right = NULL;
    tree1->left = NULL;
    return(tree1);
};
void insert1(int b, tree_elem *root1)
    {
        if (root1 == NULL) root1 = cr(b);
        if (b < root1->value)
        if (root1->left == NULL)
            root1->left = cr(b);
        else insert1(b, root1->left);
    else if (root1->right == NULL)
             root1->right = cr(b);
       else insert1(b, root1->right);
    };
bool exist(int c, tree_elem *tree)
{
    if (tree == NULL) return false; else
    if (tree->value == c) return true;
    else if (tree->value < c) exist(c, tree->right);
    else exist(c, tree->left);
};
void deletee (tree_elem* root1)
{
  if (root1->left != NULL) deletee(root1->left);
	if (root1->right != NULL) deletee(root1->right);
	delete root1;
};
void printt(tree_elem *tree){
    cout << tree->value << endl;
    if (tree->left != NULL) printt(tree->left);
    if (tree->right != NULL) printt(tree->right);
}
void removee(int c,  tree_elem *tree)
{
    if (tree == NULL) cout << "error" << endl; else
    if (tree->value == c) if (tree->right != NULL) {
            tree->value = tree->right->value;
            tree->right = tree->right->right;
        }
    else {
            tree->value = tree->left->value;
            tree->left = tree->left->left;
        }
    else if (tree->value < c) removee(c, tree->right);
    else removee(c, tree->left);
}
public:
    SimpleTree()
    {
        this->root = NULL;
    };
    ~SimpleTree()
    {
        if (this->root != NULL) deletee(this->root);
    };

    void print()
    {
       if (this->root != NULL)  printt(this->root);
    };

    void remove(int value)
    {
        removee(value, this->root);
    };


    void insert(int b)
    {
        insert1(b, this->root);
    };

    bool exists(int value)
    {
       return exist(value, this->root);
    };
};

int main()
{
    Container* c = new SimpleTree();

    for(int i = 1; i < 10; i++)
        c->insert(i*i);

    cout <<"List after creation:\n";
    c->print();

    if(c->exists(25))
        cout << "Search for value 25: found" << endl;

    if(!c->exists(111))
        cout << "Search for value 111: not found" << endl;

//    c->remove(25);
    cout << "List after deletion of the element:" << endl;
    c->print();

    delete c;
    return 0;
};
