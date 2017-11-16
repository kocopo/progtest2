//#include<cstdio>
//#include<cmath>
//class Node{
//public:
//    Node(unsigned long key){
//        this->key = key;
//        this->numberOfChildren = 0;
//        this->height = 1;
//        this->right = this->left = nullptr;
//    }
//
//    void setKey(unsigned long key) {
//        Node::key = key;
//    }
//
//    unsigned long getHeight() const {
//        return height;
//    }
//
//    void setHeight(unsigned long height) {
//        Node::height = height;
//    }
//    Node *getLeft() const {
//        return left;
//    }
//
//    unsigned long getKey() const {
//        return key;
//    }
//
//    Node *getRight() const {
//        return right;
//    }
//
//    void setRight(Node *right) {
//        Node::right = right;
//    }
//
//    void setLeft(Node *left) {
//        Node::left = left;
//    }
//
//    unsigned long getNumberOfChildren() const {
//        return numberOfChildren;
//    }
//
//    unsigned long getLeftChildren() const {
//        if(this->left != nullptr)
//            return this->left->getNumberOfChildren() + 1;
//        else
//            return 0;
//    }
//
//    unsigned long getRightChildren() const {
//        if(this->right != nullptr)
//            return this->right->getNumberOfChildren() + 1;
//        else
//            return 0;
//    }
//
//    void setNumberOfChildren(unsigned long numberOfChildren) {
//        Node::numberOfChildren = numberOfChildren;
//    }
//
//private:
//    unsigned long key, height, numberOfChildren;
//    Node * left, * right;
//};
//
//unsigned long max(unsigned long a, unsigned long b)
//{
//    return (a > b)? a : b;
//}
//
//unsigned long height(Node * N)
//{
//    if (N == nullptr)
//        return 0;
//    return N->getHeight();
//}
//
//
//
//Node * newNode(unsigned long key)
//{
//    Node * node = new Node(key);
//    return node;
//}
//
//Node * rightRotate(Node * y)
//{
//    Node *x = y->getLeft();
//    Node *T2 = x->getRight();
//
//    y->setNumberOfChildren(y->getNumberOfChildren() - y->getLeftChildren());
//    x->setNumberOfChildren(x->getNumberOfChildren() - x->getRightChildren());
//
//    x->setRight(y);
//    y->setLeft(T2);
//
//    y->setNumberOfChildren(y->getNumberOfChildren() + y->getLeftChildren());
//    x->setNumberOfChildren(x->getNumberOfChildren() + x->getRightChildren());
//
//    y->setHeight(max(height(y->getLeft()), height(y->getRight()))+1);
//    x->setHeight(max(height(x->getLeft()), height(x->getRight()))+1);
//
//    return x;
//}
//
//Node *leftRotate(Node *x)
//{
//    Node *y = x->getRight();
//    Node *T2 = y->getLeft();
//
//    x->setNumberOfChildren(x->getNumberOfChildren() - x->getRightChildren());
//    y->setNumberOfChildren(y->getNumberOfChildren() - y->getLeftChildren());
//
//    y->setLeft(x);
//    x->setRight(T2);
//
//    x->setNumberOfChildren(x->getNumberOfChildren() + x->getRightChildren());
//    y->setNumberOfChildren(y->getNumberOfChildren() + y->getLeftChildren());
//
//    x->setHeight(max(height(x->getLeft()), height(x->getRight()))+1);
//    y->setHeight(max(height(y->getLeft()), height(y->getRight()))+1);
//
//    return y;
//}
//
//int getBalance(Node *N)
//{
//    if (N == nullptr)
//        return 0;
//    return static_cast<int>(height(N->getLeft()) - height(N->getRight()));
//}
//
//Node* insert(Node* node, unsigned long key)
//{
//    if (node == nullptr)
//        return(newNode(key));
//
//    node->setNumberOfChildren(node->getNumberOfChildren() + 1);
//
//    if (key < node->getKey())
//        node->setLeft(insert(node->getLeft(), key));
//    else if (key > node->getKey())
//        node->setRight(insert(node->getRight(), key));
//    else
//        return node;
//
//    node->setHeight(1 + max(height(node->getLeft()),
//                            height(node->getRight())));
//
//    int balance = getBalance(node);
//
//    // Left Left Case
//    if (balance > 1 && key < node->getLeft()->getKey())
//        return rightRotate(node);
//
//    // Right Right Case
//    if (balance < -1 && key > node->getRight()->getKey())
//        return leftRotate(node);
//
//    // Left Right Case
//    if (balance > 1 && key > node->getLeft()->getKey())
//    {
//        node->setLeft(leftRotate(node->getLeft()));
//        return rightRotate(node);
//    }
//
//    // Right Left Case
//    if (balance < -1 && key < node->getRight()->getKey())
//    {
//        node->setRight(rightRotate(node->getRight()));
//        return leftRotate(node);
//    }
//
//    return node;
//}
//
//Node * minValueNode(struct Node* node)
//{
//    Node* current = node;
//
//    while (current->getLeft() != nullptr)
//        current = current->getLeft();
//
//    return current;
//}
//Node * returnChildren(Node * root, unsigned long key){
//    if(root == nullptr)
//      return root;
//    root->setNumberOfChildren(root->getNumberOfChildren() + 1);
//    if(root->getKey() < key){
//        returnChildren(root->getRight(), key);
//    }else{
//        returnChildren(root->getLeft(), key);
//    }
//    return nullptr;
//}
//Node* deleteNode(Node* root,Node * startRoot, unsigned long key)
//{
//
//    if (root == nullptr){
//        returnChildren(startRoot, key);
//        return root;
//    }
//
//    if ( key < root->getKey() ){
//        root->setNumberOfChildren(root->getNumberOfChildren() - 1);
//        root->setLeft(deleteNode(root->getLeft(), startRoot, key));
//        }
//    else if( key > root->getKey() ) {
//        root->setNumberOfChildren(root->getNumberOfChildren() - 1);
//        root->setRight(deleteNode(root->getRight(), startRoot, key));
//    }
//    else
//    {
//        if( (root->getLeft() == nullptr) || (root->getRight() == nullptr) )
//        {
//            Node *temp = root->getLeft() ? root->getLeft() :
//                                root->getRight();
//
//            if (temp == nullptr)
//            {
//                temp = root;
//                root = nullptr;
//            }
//            else{
//                *root = *temp;
//                root->setNumberOfChildren(root->getLeftChildren() + root->getRightChildren());
//            }
//
//            delete temp;
//        }
//        else
//        {
//            Node* temp = minValueNode(root->getRight());
//
//            root->setKey(temp->getKey());
//
//            root->setRight(deleteNode(root->getRight(), startRoot, temp->getKey()));
//            root->setNumberOfChildren(root->getLeftChildren() + root->getRightChildren());
//        }
//    }
//
//    if (root == nullptr)
//        return root;
//
//    root->setHeight(1 + max(height(root->getLeft()),
//                            height(root->getRight())));
//
//    int balance = getBalance(root);
//
//    // Left Left Case
//    if (balance > 1 && getBalance(root->getLeft()) >= 0)
//        return rightRotate(root);
//
//    // Left Right Case
//    if (balance > 1 && getBalance(root->getLeft()) < 0)
//    {
//        root->setLeft(leftRotate(root->getLeft()));
//        return rightRotate(root);
//    }
//
//    // Right Right Case
//    if (balance < -1 && getBalance(root->getRight()) <= 0)
//        return leftRotate(root);
//
//    // Right Left Case
//    if (balance < -1 && getBalance(root->getRight()) > 0)
//    {
//        root->setRight(rightRotate(root->getRight()));
//        return leftRotate(root);
//    }
//
//    return root;
//}
//
//void preOrder(struct Node *root)
//{
//    if(root != nullptr)
//    {
//
//        preOrder(root->getLeft());
//        printf("k:%lu noc:%lu L:%lu R:%lu\n", root->getKey(), root->getNumberOfChildren(),
//               root->getLeft()!= nullptr?root->getLeft()->getKey():0,
//               root->getRight()!= nullptr?root->getRight()->getKey():0);
//        preOrder(root->getRight());
//    }
//}
//Node * findnewLeft(Node * root, unsigned long small){
//
//    if(root->getLeft()->getRight()->getKey() > small && small > root->getLeft()->getKey()){
//        return findnewLeft(root->getLeft()->getRight(), small);
//    }
//    if(root->getKey() > small && root->getLeft()->getKey() < small){
//        return root;
//    }else if(small > root->getKey()){
//        return findnewLeft(root->getRight(), small);
//    }else{
//        return findnewLeft(root->getLeft(), small);
//    }
//}
//Node * findLeft(Node * currentRoot, Node * previousRoot, Node * root, unsigned long small){
//
//    if(small > currentRoot->getKey() && currentRoot->getRight() == nullptr && small < previousRoot->getKey()){
//        return previousRoot;
//    }else if(small > currentRoot->getKey() && currentRoot->getRight() == nullptr){
//        return findnewLeft(root, small);
//    }else if((small < currentRoot->getKey() && currentRoot->getLeft() == nullptr) || (small == currentRoot->getKey())){
//        return currentRoot;
//    }else if(small > currentRoot->getKey()){
//        return findLeft(currentRoot->getRight(), currentRoot, root, small);
//    }else if(small < currentRoot->getKey()){
//        return findLeft(currentRoot->getLeft(), currentRoot, root, small);
//    }
//
//    return nullptr;
//}
//
//Node * findnewRight(Node * root, unsigned long big){
//
//    if(root->getRight()->getLeft()->getKey() < big && big < root->getRight()->getKey()){
//        return findnewRight(root->getRight()->getLeft(), big);
//    }
//    if(root->getKey() < big && root->getRight()->getKey() > big){
//        return root;
//    }else if(big > root->getKey()){
//        return findnewRight(root->getRight(), big);
//    }else{
//        return findnewRight(root->getLeft(), big);
//    }
//
//}
//Node * findRight(Node * currentRoot, Node * previousRoot, Node * root, unsigned long big){
//    if(big < currentRoot->getKey() && currentRoot->getLeft() == nullptr && big > previousRoot->getKey()){
//        return previousRoot;
//    }else if(big < currentRoot->getKey() && currentRoot->getLeft() == nullptr){
//        return findnewRight(root, big);
//    }else if((big > currentRoot->getKey() && currentRoot->getRight() == nullptr) || (big == currentRoot->getKey())){
//        return currentRoot;
//    }else if(big > currentRoot->getKey()){
//        return findRight(currentRoot->getRight(), currentRoot, root, big);
//    }else if(big < currentRoot->getKey()){
//        return findRight(currentRoot->getLeft(), currentRoot, root, big);
//    }
//
//    return nullptr;
//}
//
//Node * sNewRootLeft(Node *root, unsigned long small){
//    if(root == nullptr)
//        return nullptr;
//    if(root->getKey() >= small)
//        return root;
//    return sNewRootLeft(root->getRight(), small);
//}
//
//Node * sNewRootRight(Node *root, unsigned long big){
//    if(root == nullptr)
//        return nullptr;
//    if(root->getKey() <= big)
//        return root;
//    return sNewRootRight(root->getLeft(), big);
//}
//
//unsigned long scountLeftChildren(Node *root, unsigned long left){
//    if(root == nullptr){
//        return 0;
//    }
//    if(root->getKey() == left)
//        return 0;
//    if(left > root->getKey()){
//        return scountLeftChildren(root->getRight(), left);
//    }else{
//        return 1 + root->getRightChildren() + scountLeftChildren(root->getLeft(), left);
//    }
//}
//unsigned long scountRightChildren(Node *root, unsigned long right){
//    if(root == nullptr){
//        return 0;
//    }
//    if(root->getKey() == right)
//        return 0;
//    if(right < root->getKey()){
//        return scountRightChildren(root->getLeft(), right);
//    }else{
//        return 1 + root->getLeftChildren() + scountRightChildren(root->getRight(), right);
//    }
//}
//
//unsigned long sfindMedianOnLeft(Node *root, unsigned long median, Node *left){
//    if(median == 0)
//        return root->getKey();
//
//    if(left != nullptr){
//        if(left->getKey() > root->getKey())
//            return sfindMedianOnLeft(root->getRight(), median, left);
//
//        unsigned long leftChildren = scountLeftChildren(root->getLeft(), left->getKey()) + left->getRightChildren() + 1;
////        printf("median left chiuldren:%lu\n", leftChildren);
//        if(leftChildren < median){
//            median -= leftChildren;
//            if(median - 1 == 0){
//                return root->getKey();
//            }
//            return sfindMedianOnLeft(root->getRight(), median - 1, nullptr);
//        }else if(leftChildren == median){
//
//            if(root->getLeft() == nullptr){
//                return root->getKey();
//            }else{
//                if(root == left && root->getLeft()->getKey() > left->getKey())
//                    return sfindMedianOnLeft(root->getLeft(), median - 1, nullptr);
//                else
//                    if(root->getLeft()->getKey() < left->getKey())
//                        return sfindMedianOnLeft(root->getRight(), median - 1, nullptr);
//                    else
//                        return root->getLeft()->getKey();
//            }
//        }else{
//            return sfindMedianOnLeft(root->getLeft(), median, left);
//        }
//    }else{
//        unsigned long leftChildren = root->getLeftChildren();
//        if(leftChildren < median){
//            median -= leftChildren;
//            if(median - 1 == 0)
//                return root->getKey();
//            return sfindMedianOnLeft(root->getRight(), median - 1, nullptr);
//        }else if(leftChildren == median){
//            if(root->getLeft() == nullptr){
//                return root->getKey();
//            }else{
//                    return root->getLeft()->getKey();
//            }
//        }else{
//            return sfindMedianOnLeft(root->getLeft(), median, nullptr);
//        }
//    }
//
//}
//
//unsigned long sfindMedianOnRight(Node *root, unsigned long median, Node *right){
//    if(median == 0)
//        return root->getKey();
//
//    if(right != nullptr){
//        if(right->getKey() < root->getKey())
//            return sfindMedianOnRight(root->getLeft(), median, right);
//
//        unsigned long rightChildren =
//                scountRightChildren(root->getRight(), right->getKey()) + right->getLeftChildren() + 1;
//        if(rightChildren < median){
//            median -= rightChildren;
//
//            if(median - 1 == 0){
//                return root->getKey();
//            }
//            return sfindMedianOnRight(root->getLeft(), median - 1, nullptr);
//        }else if(rightChildren == median){
//            if(root->getRight() == nullptr){
//                return root->getKey();
//            }else{
//                if(root == right && root->getRight()->getKey() < right->getKey()) {
//                    return sfindMedianOnRight(root->getLeft(), median - 1, nullptr);
//                }else{
//                    if(root->getRight()->getKey() > right->getKey())
//                        return sfindMedianOnRight(root->getLeft(), median - 1, nullptr);
//                    else
//                        return root->getRight()->getKey();
//                }
//
//            }
//        }else{
//
//            return sfindMedianOnRight(root->getRight(), median, right);
//        }
//    }else{
//
//        unsigned long rightChildren = root->getRightChildren();
//        if(rightChildren < median){
//            median -= rightChildren;
//            if(median - 1 == 0)
//                return root->getKey();
//            return sfindMedianOnRight(root->getLeft(), median - 1, nullptr);
//        }else if(rightChildren == median){
//            if(root->getRight() == nullptr){
//                return root->getKey();
//            }else{
//                    return root->getRight()->getKey();
//            }
//        }else{
//            return sfindMedianOnRight(root->getRight(), median, nullptr);
//        }
//    }
//
//}
//
//unsigned long smedian(Node *root, unsigned long small, unsigned long big){
//    if(root == nullptr)
//        return 0;
//    if(root->getKey() == small && root->getKey() == big){
//        return root->getKey();
//    }
//
//    Node * left, * right, * newLeftRoot = nullptr, * newRightRoot = nullptr;
//    unsigned long leftChildren, rightChildren;
//    if(small > root->getKey()){
//        newLeftRoot = sNewRootLeft(root->getRight(), small);
//        if(newLeftRoot == nullptr){
//            return 0;
//        }
//        if((newLeftRoot->getKey() == small) || (newLeftRoot->getLeft() == nullptr)){
//            left = newLeftRoot;
//        }else{
//            left = findLeft(newLeftRoot->getLeft(), newLeftRoot, newLeftRoot, small);
//        }
//    }else{
//        if(small == root->getKey() || root->getLeft() == nullptr){
//            left = root;
//        }else{
//            left = findLeft(root->getLeft(),root, root, small);
//        }
//    }
//
//    if(left->getKey() > big){
//        return 0;
//    }
//
//    if(big < root->getKey()){
//        newRightRoot = sNewRootRight(root->getLeft(), big);
//        if(newRightRoot == nullptr)
//            return 0;
//        if((newRightRoot->getKey() == big) || (newRightRoot->getRight() == nullptr))
//            right = newRightRoot;
//        else
//        right = findRight(newRightRoot->getRight(), newRightRoot, newRightRoot, big);
//    }else{
//        if(big == root->getKey() || root->getRight() == nullptr){
//            right = root;
//        }else{
//            right = findRight(root->getRight(),root, root, big);
//        }
//    }
//
//
//
//    if(left->getKey() == right->getKey()){
//        return left->getKey();
//    }
//
//
//    if(newRightRoot != nullptr){
//        leftChildren = scountLeftChildren(newRightRoot->getLeft(), left->getKey()) + left->getRightChildren() + 1;
//        rightChildren = scountRightChildren(newRightRoot->getRight(), right->getKey()) + right->getLeftChildren() + 1;
//    }else if(newLeftRoot != nullptr){
//        leftChildren = scountLeftChildren(newLeftRoot->getLeft(), left->getKey()) + left->getRightChildren() + 1;
//        rightChildren = scountRightChildren(newLeftRoot->getRight(), right->getKey()) + right->getLeftChildren() + 1;
//    }else{
//        leftChildren = scountLeftChildren(root->getLeft(), left->getKey()) + left->getRightChildren() + 1;
//        rightChildren = scountRightChildren(root->getRight(), right->getKey()) + right->getLeftChildren() + 1;
//    }
//
//
//    if(right == newRightRoot){
//        rightChildren -= right->getLeftChildren();
//    }
//    if(left == newLeftRoot){
//        leftChildren -= left->getRightChildren();
//    }
//    if(right == root || right == newRightRoot){
//        rightChildren = 0;
//    }
//    if(left == root || left == newLeftRoot){
//        leftChildren = 0;
//    }
//
//    unsigned long median = static_cast<unsigned long>(ceil((static_cast<double>(leftChildren + rightChildren + 1) / 2)));
//    unsigned long correction = (leftChildren + rightChildren + 1) % 2 == 0?1:0;
////    printf("%lu\n", median);
////    printf("number of left children:%lu number of right children:%lu\n", leftChildren, rightChildren);
////    printf("leftkey:%lu rightkey:%lu\n", left->getKey(), right->getKey());
//
//    if(newRightRoot != nullptr){
//
//        if(leftChildren == rightChildren){
//            return newRightRoot->getKey();
//        }else if(leftChildren > rightChildren){
//            if(median > leftChildren)
//                return newRightRoot->getKey();
//            else
//                return sfindMedianOnLeft(newRightRoot->getLeft(), median, left);
//        }else{
//            if(median + correction > rightChildren)
//                return newRightRoot->getKey();
//            else
//                return sfindMedianOnRight(newRightRoot->getRight(), median + correction, right);
//        }
//    }else if(newLeftRoot != nullptr){
//
//        if(leftChildren == rightChildren){
//            return newLeftRoot->getKey();
//        }else if(leftChildren > rightChildren){
//            if(median > leftChildren)
//                return newLeftRoot->getKey();
//            else
//                return sfindMedianOnLeft(newLeftRoot->getLeft(), median, left);
//        }else{
//            if(median + correction > rightChildren)
//                return newLeftRoot->getKey();
//            else
//                return sfindMedianOnRight(newLeftRoot->getRight(), median + correction, right);
//        }
//    }else{
//        if(leftChildren == rightChildren){
//            return root->getKey();
//        }else if(leftChildren > rightChildren){
//            if(median > leftChildren)
//                return root->getKey();
//            else
//                return sfindMedianOnLeft(root->getLeft(), median, left);
//        }else{
//            if(median + correction > rightChildren)
//                return root->getKey();
//            else
//                return sfindMedianOnRight(root->getRight(), median + correction, right);
//        }
//    }
//
//}
