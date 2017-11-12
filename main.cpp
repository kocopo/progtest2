#include<cstdio>
#include<cmath>
class Node{
public:
    Node(unsigned long key){
        this->key = key;
        this->numberOfChildren = 0;
        this->height = 1;
        this->right = this->left = nullptr;
    }

    void setKey(unsigned long key) {
        Node::key = key;
    }

    unsigned long getHeight() const {
        return height;
    }

    void setHeight(unsigned long height) {
        Node::height = height;
    }
    Node *getLeft() const {
        return left;
    }

    unsigned long getKey() const {
        return key;
    }

    Node *getRight() const {
        return right;
    }

    void setRight(Node *right) {
        Node::right = right;
    }

    void setLeft(Node *left) {
        Node::left = left;
    }

    unsigned long getNumberOfChildren() const {
        return numberOfChildren;
    }

    unsigned long getLeftChildren() const {
        if(this->left != nullptr)
            return this->left->getNumberOfChildren() + 1;
        else
            return 0;
    }

    unsigned long getRightChildren() const {
        if(this->right != nullptr)
            return this->right->getNumberOfChildren() + 1;
        else
            return 0;
    }

    void setNumberOfChildren(unsigned long numberOfChildren) {
        Node::numberOfChildren = numberOfChildren;
    }

private:
    unsigned long key, height, numberOfChildren;
    Node * left, * right;
};

unsigned long max(unsigned long a, unsigned long b)
{
    return (a > b)? a : b;
}

unsigned long height(Node * N)
{
    if (N == nullptr)
        return 0;
    return N->getHeight();
}



Node * newNode(unsigned long key)
{
    Node * node = new Node(key);
    return node;
}

Node * rightRotate(Node * y)
{
    Node *x = y->getLeft();
    Node *T2 = x->getRight();

    y->setNumberOfChildren(y->getNumberOfChildren() - y->getLeftChildren());
    x->setNumberOfChildren(x->getNumberOfChildren() - x->getRightChildren());

    x->setRight(y);
    y->setLeft(T2);

    y->setNumberOfChildren(y->getNumberOfChildren() + y->getLeftChildren());
    x->setNumberOfChildren(x->getNumberOfChildren() + x->getRightChildren());

    y->setHeight(max(height(y->getLeft()), height(y->getRight()))+1);
    x->setHeight(max(height(x->getLeft()), height(x->getRight()))+1);

    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->getRight();
    Node *T2 = y->getLeft();

    x->setNumberOfChildren(x->getNumberOfChildren() - x->getRightChildren());
    y->setNumberOfChildren(y->getNumberOfChildren() - y->getLeftChildren());

    y->setLeft(x);
    x->setRight(T2);

    x->setNumberOfChildren(x->getNumberOfChildren() + x->getRightChildren());
    y->setNumberOfChildren(y->getNumberOfChildren() + y->getLeftChildren());

    x->setHeight(max(height(x->getLeft()), height(x->getRight()))+1);
    y->setHeight(max(height(y->getLeft()), height(y->getRight()))+1);

    return y;
}

int getBalance(Node *N)
{
    if (N == nullptr)
        return 0;
    return static_cast<int>(height(N->getLeft()) - height(N->getRight()));
}

Node* insert(Node* node, unsigned long key)
{
    if (node == nullptr)
        return(newNode(key));

    node->setNumberOfChildren(node->getNumberOfChildren() + 1);

    if (key < node->getKey())
        node->setLeft(insert(node->getLeft(), key));
    else if (key > node->getKey())
        node->setRight(insert(node->getRight(), key));
    else
        return node;

    node->setHeight(1 + max(height(node->getLeft()),
                            height(node->getRight())));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->getLeft()->getKey())
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->getRight()->getKey())
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->getLeft()->getKey())
    {
        node->setLeft(leftRotate(node->getLeft()));
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->getRight()->getKey())
    {
        node->setRight(rightRotate(node->getRight()));
        return leftRotate(node);
    }

    return node;
}

Node * minValueNode(struct Node* node)
{
    Node* current = node;

    while (current->getLeft() != nullptr)
        current = current->getLeft();

    return current;
}
void returnChildren(Node * root, unsigned long key){

}
Node* deleteNode(Node* root, unsigned long key)
{

    if (root == nullptr){
        returnChildren(root, key);
        return root;
    }

    if ( key < root->getKey() ){
        root->setNumberOfChildren(root->getNumberOfChildren() - 1);
        root->setLeft(deleteNode(root->getLeft(), key));
        }
    else if( key > root->getKey() ) {
        root->setNumberOfChildren(root->getNumberOfChildren() - 1);
        root->setRight(deleteNode(root->getRight(), key));
    }
    else
    {
        if( (root->getLeft() == nullptr) || (root->getRight() == nullptr) )
        {
            Node *temp = root->getLeft() ? root->getLeft() :
                                root->getRight();

            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
        }
        else
        {
            Node* temp = minValueNode(root->getRight());

            root->setKey(temp->getKey());

            root->setRight(deleteNode(root->getRight(), temp->getKey()));
        }
    }

    if (root == nullptr)
        return root;

    root->setHeight(1 + max(height(root->getLeft()),
                            height(root->getRight())));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->getLeft()) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->getLeft()) < 0)
    {
        root->setLeft(leftRotate(root->getLeft()));
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->getRight()) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->getRight()) > 0)
    {
        root->setRight(rightRotate(root->getRight()));
        return leftRotate(root);
    }

    return root;
}

void preOrder(struct Node *root)
{
    if(root != nullptr)
    {

        preOrder(root->getLeft());
        printf("k:%lu noc:%lu L:%lu R:%lu\n", root->getKey(), root->getNumberOfChildren(),
               root->getLeft()!= nullptr?root->getLeft()->getKey():0,
               root->getRight()!= nullptr?root->getRight()->getKey():0);
        preOrder(root->getRight());
    }
}
Node * findnewLeft(Node * root, unsigned long small){

    if(root->getLeft()->getRight()->getKey() > small && small > root->getLeft()->getKey()){
        return findnewLeft(root->getLeft()->getRight(), small);
    }
    if(root->getKey() > small && root->getLeft()->getKey() < small){
        return root;
    }else if(small > root->getKey()){
        return findnewLeft(root->getRight(), small);
    }else{
        return findnewLeft(root->getLeft(), small);
    }
}
Node * findLeft(Node * currentRoot, Node * previousRoot, Node * root, unsigned long small){

    if(small > currentRoot->getKey() && currentRoot->getRight() == nullptr && small < previousRoot->getKey()){
        return previousRoot;
    }else if(small > currentRoot->getKey() && currentRoot->getRight() == nullptr){
        return findnewLeft(root, small);
    }else if((small < currentRoot->getKey() && currentRoot->getLeft() == nullptr) || (small == currentRoot->getKey())){
        return currentRoot;
    }else if(small > currentRoot->getKey()){
        return findLeft(currentRoot->getRight(), currentRoot, root, small);
    }else if(small < currentRoot->getKey()){
        return findLeft(currentRoot->getLeft(), currentRoot, root, small);
    }
}

Node * findnewRight(Node * root, unsigned long big){

    if(root->getRight()->getLeft()->getKey() < big && big < root->getRight()->getKey()){
        return findnewRight(root->getRight()->getLeft(), big);
    }
    if(root->getKey() < big && root->getRight()->getKey() > big){
        return root;
    }else if(big > root->getKey()){
        return findnewRight(root->getRight(), big);
    }else{
        return findnewRight(root->getLeft(), big);
    }

}
Node * findRight(Node * currentRoot, Node * previousRoot, Node * root, unsigned long big){

    if(big < currentRoot->getKey() && currentRoot->getLeft() == nullptr && big > previousRoot->getKey()){
        return previousRoot;
    }else if(big < currentRoot->getKey() && currentRoot->getLeft() == nullptr){
        return findnewRight(root, big);
    }else if((big > currentRoot->getKey() && currentRoot->getRight() == nullptr) || (big == currentRoot->getKey())){
        return currentRoot;
    }else if(big > currentRoot->getKey()){
        return findRight(currentRoot->getRight(), currentRoot, root, big);
    }else if(big < currentRoot->getKey()){
        return findRight(currentRoot->getLeft(), currentRoot, root, big);
    }
}

Node * NewRootLeft(Node * root, unsigned long small){
    if(root == nullptr)
        return nullptr;
    if(root->getKey() >= small)
        return root;
    return NewRootLeft(root->getRight(), small);
}

Node * NewRootRight(Node * root, unsigned long big){
    if(root == nullptr)
        return nullptr;
    if(root->getKey() <= big)
        return root;
    return NewRootRight(root->getLeft(), big);
}

unsigned long countLeftChildren(Node * root, unsigned long left){
    if(root == nullptr){
        return 0;
    }
    if(root->getKey() == left)
        return 0;
    if(left > root->getKey()){
        return countLeftChildren(root->getRight(), left);
    }else{
        return 1 + root->getRightChildren() + countLeftChildren(root->getLeft(), left);
    }
}
unsigned long countRightChildren(Node * root, unsigned long right){
    if(root == nullptr){
        return 0;
    }
    if(root->getKey() == right)
        return 0;
    if(right < root->getKey()){
        return countRightChildren(root->getLeft(), right);
    }else{
        return 1 + root->getLeftChildren() + countRightChildren(root->getRight(), right);
    }
}

unsigned long findMedianOnLeft(Node * root, unsigned long median, Node * left){
    if(median == 0)
        return root->getKey();

    if(left != nullptr){
        if(left->getKey() > root->getKey())
            return findMedianOnLeft(root->getRight(), median, left);

        unsigned long leftChildren = countLeftChildren(root->getLeft(), left->getKey()) + left->getRightChildren() + 1;
        if(leftChildren < median){
            median -= leftChildren;
            if(median - 1 == 0){
                return root->getKey();
            }
            return findMedianOnLeft(root->getRight(), median - 1, nullptr);
        }else if(leftChildren == median){
            if(root->getLeft() == nullptr){
                return root->getKey();
            }else{
                return root->getLeft()->getKey();
            }
        }else{
            return findMedianOnLeft(root->getLeft(), median, left);
        }
    }else{
        unsigned long leftChildren = root->getLeftChildren();
        if(leftChildren < median){
            median -= leftChildren;
            if(median - 1 == 0)
                return root->getKey();
            return findMedianOnLeft(root->getRight(), median - 1, nullptr);
        }else if(leftChildren == median){
            if(root->getLeft() == nullptr){
                return root->getKey();
            }else{
                return root->getLeft()->getKey();
            }
        }else{
            return findMedianOnLeft(root->getLeft(), median, nullptr);
        }
    }

}

unsigned long findMedianOnRight(Node * root, unsigned long median, Node * right){
    if(median == 0)
        return root->getKey();

    if(right != nullptr){
        if(right->getKey() < root->getKey())
            return findMedianOnRight(root->getLeft(), median, right);

        unsigned long rightChildren = countRightChildren(root->getRight(), right->getKey()) + right->getLeftChildren() + 1;
        if(rightChildren < median){
            median -= rightChildren;
            if(median - 1 == 0){
                return root->getKey();
            }
            return findMedianOnRight(root->getLeft(), median - 1, nullptr);
        }else if(rightChildren == median){
            if(root->getRight() == nullptr){
                return root->getKey();
            }else{
                return root->getRight()->getKey();
            }
        }else{
            return findMedianOnRight(root->getRight(), median, right);
        }
    }else{
        unsigned long rightChildren = root->getRight()->getNumberOfChildren() + 1;
        if(rightChildren < median){
            median -= rightChildren;
            if(median - 1 == 0)
                return root->getKey();
            return findMedianOnRight(root->getLeft(), median - 1, nullptr);
        }else if(rightChildren == median){
            if(root->getRight() == nullptr){
                return root->getKey();
            }else{
                return root->getRight()->getKey();
            }
        }else{
            return findMedianOnRight(root->getRight(), median, nullptr);
        }
    }

}

unsigned long median(Node * root,unsigned long small, unsigned long big){

    if(root->getKey() == small && root->getKey() == big){
        return root->getKey();
    }

    Node * left, * right, * newLeftRoot = nullptr, * newRightRoot = nullptr;
    unsigned long leftChildren, rightChildren;
    if(small > root->getKey()){

        newLeftRoot = NewRootLeft(root->getRight(), small);

        if(newLeftRoot == nullptr){
            return 0;

        }
        if(newLeftRoot->getKey() == small){
            left = newLeftRoot;
        }else{
            left = findLeft(newLeftRoot->getLeft(), newLeftRoot, newLeftRoot, small);
        }
    }else{
        left = findLeft(root->getLeft(),root, root, small);
    }

    if(left->getKey() > big){
        return 0;
    }

    if(big < root->getKey()){
        newRightRoot = NewRootRight(root->getLeft(), big);
        if(newRightRoot == nullptr)
            return 0;
        if(newRightRoot->getKey() == big)
            right = newRightRoot;
        else
        right = findRight(newRightRoot->getRight(), newRightRoot, newRightRoot, big);
    }else{
        right = findRight(root->getRight(),root, root, big);
    }
    if(left->getKey() == right->getKey()){
        return left->getKey();
    }
    if(newRightRoot != nullptr){
        leftChildren = countLeftChildren(newRightRoot->getLeft(), left->getKey()) + left->getRightChildren() + 1;
        rightChildren = countRightChildren(newRightRoot->getRight(), right->getKey()) + right->getLeftChildren() + 1;
    }else if(newLeftRoot != nullptr){
        leftChildren = countLeftChildren(newLeftRoot->getLeft(), left->getKey()) + left->getRightChildren() + 1;
        rightChildren = countRightChildren(newLeftRoot->getRight(), right->getKey()) + right->getLeftChildren() + 1;
    }else{
        leftChildren = countLeftChildren(root->getLeft(), left->getKey()) + left->getRightChildren() + 1;
        rightChildren = countRightChildren(root->getRight(), right->getKey()) + right->getLeftChildren() + 1;
    }



    unsigned long median = static_cast<unsigned long>(ceil((static_cast<double>(leftChildren + rightChildren + 1) / 2)));

//    printf("%lu\n", median);
//    printf("number of left children:%lu number of right children:%lu\n", leftChildren, rightChildren);
//    printf("leftkey:%lu rightkey:%lu\n", left->getKey(), right->getKey());

    if(newRightRoot != nullptr){
        if(leftChildren == rightChildren){
            return newRightRoot->getKey();
        }else if(leftChildren > rightChildren){
            return findMedianOnLeft(newRightRoot->getLeft(), median, left);
        }else{
            return findMedianOnRight(newRightRoot->getRight(), median, right);
        }
    }else if(newLeftRoot != nullptr){
        if(leftChildren == rightChildren){
            return newLeftRoot->getKey();
        }else if(leftChildren > rightChildren){
            return findMedianOnLeft(newLeftRoot->getLeft(), median, left);
        }else{
            return findMedianOnRight(newLeftRoot->getRight(), median, right);
        }
    }else{
        if(leftChildren == rightChildren){
            return root->getKey();
        }else if(leftChildren > rightChildren){
            return findMedianOnLeft(root->getLeft(), median, left);
        }else{
            return findMedianOnRight(root->getRight(), median, right);
        }
    }

}

int main()
{
    struct Node *root = nullptr;

    unsigned long order = 0;
    scanf("%lu", &order);
    while(order != 4){
        if(order == 1){
            unsigned long number = 0;
            scanf("%lu", &number);
            root = insert(root, number);
            scanf("%lu", &order);
            continue;
        }
        if(order == 2){
            unsigned long number = 0;
            scanf("%lu", &number);
            root = deleteNode(root, number);
            scanf("%lu", &order);
            continue;
        }
        if(order == 3){

            unsigned long left = 0, right = 0, medianNumber = 0;
            scanf("%lu %lu", &left, &right);
            scanf("%lu", &order);
            if(order == 4){
                medianNumber = median(root, left,right);
                if(medianNumber == 0)
                    printf("notfound");
                else
                    printf("%lu", median(root, left,right));

            }else{
                medianNumber = median(root, left,right);
                if(medianNumber == 0)
                    printf("notfound\n");
                else
                    printf("%lu\n", median(root, left,right));
            }
            continue;
        }
    }
    preOrder(root);
//
//    1 2
//    1 3
//    1 1
//    3 3 3
//    4
//    3 4 4
//    4
    return 0;
}