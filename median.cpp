#include<cstdio>
#include<cmath>
class Node{
public:
    Node(unsigned long key){
        this->key = key;
        this->numberOfChildren = 0;
        this->height = 1;
        this->right = this->left = nullptr;
        this->medianChildren = 0;
    }

    unsigned long getMedianChildren() const {
        return medianChildren;
    }

    void setMedianChildren(unsigned long medianChildren) {
        Node::medianChildren = medianChildren;
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
    unsigned long key, height, numberOfChildren, medianChildren;
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
Node * returnChildren(Node * root, unsigned long key){
    if(root == nullptr)
        return root;
    root->setNumberOfChildren(root->getNumberOfChildren() + 1);
    if(root->getKey() < key){
        returnChildren(root->getRight(), key);
    }else{
        returnChildren(root->getLeft(), key);
    }
    return nullptr;
}
Node* deleteNode(Node* root,Node * startRoot, unsigned long key)
{

    if (root == nullptr){
        returnChildren(startRoot, key);
        return root;
    }

    if ( key < root->getKey() ){
        root->setNumberOfChildren(root->getNumberOfChildren() - 1);
        root->setLeft(deleteNode(root->getLeft(), startRoot, key));
    }
    else if( key > root->getKey() ) {
        root->setNumberOfChildren(root->getNumberOfChildren() - 1);
        root->setRight(deleteNode(root->getRight(), startRoot, key));
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
            else{
                *root = *temp;
                root->setNumberOfChildren(root->getLeftChildren() + root->getRightChildren());
            }

            delete temp;
        }
        else
        {
            Node* temp = minValueNode(root->getRight());

            root->setKey(temp->getKey());

            root->setRight(deleteNode(root->getRight(), startRoot, temp->getKey()));
            root->setNumberOfChildren(root->getLeftChildren() + root->getRightChildren());
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

Node * findNode(Node * root, Node * resultNode, Node * origoRoot, unsigned long node, bool big, unsigned long medianChildren){
    if(root == nullptr){
        if(resultNode == origoRoot)
            resultNode->setMedianChildren(1);
        else
            resultNode->setMedianChildren(medianChildren);
        return resultNode;
    }

    if(big){
        resultNode = root->getKey() < node?root:resultNode;
    }else{
        resultNode = root->getKey() > node?root:resultNode;
    }

    if(root->getKey() > node){

        if(root != origoRoot && !big){
            medianChildren += root->getRightChildren() + 1;
        }

        return findNode(root->getLeft(), resultNode,origoRoot, node, big, medianChildren);
    }else if(root->getKey() < node){

        if(root != origoRoot && big){
            medianChildren += root->getLeftChildren() + 1;
        }

        return findNode(root->getRight(), resultNode, origoRoot, node, big, medianChildren);
    }else{
        if(root != origoRoot) {
            if (big)
                medianChildren += root->getLeftChildren();
            else
                medianChildren += root->getRightChildren();
        }
        root->setMedianChildren(medianChildren + 1);
        return root;
    }
}

unsigned long findMedian(Node * root,unsigned long left, unsigned long right, bool rightWay, Node * leftNode, Node * rightNode){

    if(root == nullptr)
        return 0;

    if(left == right || left == right - 1)
        return root->getKey();

    if(left < right){
        if(rightWay && root->getKey() > rightNode->getKey())
            return findMedian(root->getLeft(), left - root->getLeftChildren() + root->getLeft()->getLeftChildren(),
                              right + root->getLeftChildren() - root->getLeft()->getLeftChildren(),
                              rightWay, leftNode, rightNode);
        else
            return findMedian(root->getRight(), left + 1 + root->getRight()->getLeftChildren(), right - 1 - root->getRight()->getLeftChildren(), rightWay, leftNode, rightNode);
    }else if(left > right){
        if(!right && root->getKey() < leftNode->getKey())
            return findMedian(root->getRight(), left + root->getRightChildren() - root->getRight()->getRightChildren(),
                              right - root->getRightChildren() + root->getRight()->getRightChildren(), rightWay, leftNode, rightNode);
        else
            return findMedian(root->getLeft(), left - 1 - root->getLeft()->getRightChildren(), right + 1 + root->getLeft()->getRightChildren(), rightWay, leftNode, rightNode);
    }

    return root->getKey();

}

unsigned long median(Node *root, unsigned long small, unsigned long big){

    if(root == nullptr)
        return 0;

    if(small > root->getKey())
        return median(root->getRight(), small, big);
    else if(big < root->getKey())
        return median(root->getLeft(), small, big);

    Node * left = findNode(root, root, root, small, false, 0);
    Node * right = findNode(root, root, root, big, true, 0);

    if((left->getKey() > right->getKey()) || (left == root && small > root->getKey()) || (right == root && big < root->getKey())){
        left->setMedianChildren(0);
        right->setMedianChildren(0);
        return 0;
    }

    if((left == root && right == root) || (left == right)){
        return left->getKey();
    }
    unsigned long leftChildren = left->getMedianChildren(), rightChildren = right->getMedianChildren();
    left->setMedianChildren(0);
    right->setMedianChildren(0);
//    printf("rc:%lu", rightChildren);
        if(left == root)
            leftChildren -= 1;
        else if(right == root){
            rightChildren -= 1;
        }
//    printf("Left:%lu LeftChildren:%lu Right:%lu RightChildren:%lu\n", left->getKey(), leftChildren, right->getKey(), rightChildren);

    return findMedian(root, leftChildren, rightChildren, leftChildren < rightChildren, left, right);


}
//1 2 1 4 1 6 1 8 1 10 1 12 1 14 1 16 1 18 1 20
//1 4 1 6 1 8 1 10 1 12 3 6 10 4

void delNodes(struct Node *root)
{
    if(root != nullptr)
    {

        delNodes(root->getLeft());
        Node * tmp = root->getRight();
        delete root;
        delNodes(tmp);
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
            root = deleteNode(root, root, number);
            scanf("%lu", &order);
            continue;
        }
        if(order == 3){

            unsigned long left = 0, right = 0, medianNumber = 0;
            scanf("%lu %lu", &left, &right);
            scanf("%lu", &order);
            medianNumber = median(root, left, right);
            if(medianNumber == 0)
                printf("notfound\n");
            else
                printf("%lu\n", medianNumber);

            continue;
        }
    }

    delNodes(root);
    return 0;
}

