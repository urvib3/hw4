#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <algorithm>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    Node<Key, Value> *getLargestNode() const; // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value> *getSmallestNodeOfTree(Node<Key,Value>* root); 
    static Node<Key, Value> *getLargestNodeOfTree(Node<Key,Value>* root); 
    static Node<Key, Value>* insertHelper(Node<Key, Value>* current, const std::pair<const Key, Value>& keyValuePair);
    virtual void removeHelper(Node<Key, Value>* current, const Key& key);
    static int isBalancedHelper(Node<Key, Value>* current); 
    void clearHelper(Node<Key, Value>* current); 


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr; 
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    current_ = nullptr;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    return this->current_ == rhs.current_; 
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    return this->current_ != rhs.current_; 

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    current_ = successor(current_); 
    return *this; 

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    root_ = nullptr; 
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clearHelper(root_); 

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{ 

    Node<Key, Value>* current = root_; 
    Node<Key, Value>* parent = nullptr; 

    while(current && (current->getKey() != keyValuePair.first)) {
      if(keyValuePair.first < current->getKey()) {
        parent = current; 
        current = current->getLeft(); 
      } else if(keyValuePair.first > current->getKey()) {
        parent = current; 
        current = current->getRight(); 
      }
    }

    // check if current is null, which means new node
    if(!current) {
      current = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent); 
      // check if parent is null, if it is then update root
      if(!parent) root_ = current; 
      // check if its a right or left link with parent
      else if(current->getKey() < parent->getKey())
        parent->setLeft(current); 
      else  
        parent->setRight(current); 
    }

    // otherwise current should have same key as keyValuePair
    else if(current->getKey() == keyValuePair.first)
      current->setValue(keyValuePair.second); 



}


template<class Key, class Value>
Node<Key, Value>* 
BinarySearchTree<Key, Value>::insertHelper(Node<Key, Value>* current, const std::pair<const Key, Value>& keyValuePair) {
  
  // CASE 1: current node is null, so return new node
  if(!current) return new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr); 

  // std::cout << "Current start " << current->getKey() << " "<< current->getValue() << std::endl;

  // CASE 2: new key is less than current node, recurse to the left
  if(keyValuePair.first < current->getKey()) {
    current->setLeft(insertHelper(current->getLeft(), keyValuePair)); 
    if(current->getLeft())
      current->getLeft()->setParent(current); 
  }

  // CASE 3: new key is greater than current node, recurse to the right
  else if(keyValuePair.first > current->getKey()) {

    Key currentKey = current->getKey(); 
    Node<Key, Value>* currentParent = current->getParent(); 
    Node<Key, Value>* currentLeft = current->getLeft(); 
    Node<Key, Value>* currentRight = current->getRight(); 
    current->setRight(insertHelper(current->getRight(), keyValuePair));
    if(current->getRight())
      current->getRight()->setParent(current); 
  }

  // CASE 4: current node has the same key and node just has to be updated
  else {
    // std::cout << "FIRSTS ARE EQUAL " << current->getKey() << " " << keyValuePair.first << std::endl;
    current->setValue(keyValuePair.second); 
  }

  // std::cout << "Current end " << current->getKey() << " " << current->getValue() << std::endl;

  return current; 

}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO

    Node<Key,Value>* current = root_; 
    while(current && current->getKey() != key) {
      if(key < current->getKey())
        current = current->getLeft(); 
      else if(key > current->getKey())
        current = current->getRight();   
    }

    // CASE 1: There is no node with the desired key to be removed
    if(!current) return;

      // removes current node
    // CASE 1: 2 Children (Swaps current with predecessor)
    if(current->getLeft() && current->getRight()) {
      // std::cout << "value of root " << root_->getValue() << std::endl; 
      // std::cout << "predecessor of " << current->getValue() << " is " << predecessor(current)->getValue() << std::endl; 
      nodeSwap(current, predecessor(current)); 
      // std::cout << "tree after swapping with predecessor" << std::endl; 
      // std::cout << "value of root " << root_->getValue() << std::endl; 
      // this->print(); 
    }

    // Node now can have 0-1 parents, 0-1 children

    // CASE 2: Node is ROOT
    if(current == root_) {
      // CASE 2A: only left child
      if(current->getLeft()) {
        current->getLeft()->setParent(nullptr); 
        root_ = current->getLeft(); 
      }
      // CASE 2B: only right child
      else if(current->getRight()) {
        current->getRight()->setParent(nullptr);
        root_ = current->getRight(); 
      }
      // CASE 2C: no child
      else {
        root_ = nullptr; 
      }
    }

    // CASE 3: Node HAS A PARENT

    else if(current->getParent()) {

      // CASE3-1: Node is Left Child
      if(current->getParent()->getLeft() == current) {
        // CASE 3A: Only has Left child
        if(current->getLeft()) {
          current->getParent()->setLeft(current->getLeft()); 
          current->getLeft()->setParent(current->getParent()); 
        }
        // CASE 3B: Only has Right child
        else if(current->getRight()) {
          current->getParent()->setLeft(current->getRight()); 
          current->getRight()->setParent(current->getParent()); 
        }
        // CASE 3C: Has No children
        else {
          current->getParent()->setLeft(nullptr); 
        }
      }
      // CASE3-2: Node is Right Child
      else {
          // CASE 3A: Only has Left child
        if(current->getLeft()) {
          current->getParent()->setRight(current->getLeft()); 
          current->getLeft()->setParent(current->getParent()); 
        }
        // CASE 3B: Only has Right child
        else if(current->getRight()) {
          current->getParent()->setRight(current->getRight()); 
          current->getRight()->setParent(current->getParent()); 
        }
        // CASE 3C: Has No children
        else {
          current->getParent()->setRight(nullptr); 
        }
      }

      
    }
    // free memory of current node
    delete current; 
    
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeHelper(Node<Key, Value>* current, const Key& key) {
  
  if(!current) return;

  // checks if key is less than current node and recurses left
  if(key < current->getKey())
    return removeHelper(current->getLeft(), key); 

  // checks if key is greater than current node and recurses right
  if(key > current->getKey())
    return removeHelper(current->getRight(), key); 


  // removes current node
  // CASE 1: 2 Children (Swaps current with predecessor)
  if(current->getLeft() && current->getRight()) {
    // std::cout << "value of root " << root_->getValue() << std::endl; 
    // std::cout << "predecessor of " << current->getValue() << " is " << predecessor(current)->getValue() << std::endl; 
    nodeSwap(current, predecessor(current)); 
    // std::cout << "tree after swapping with predecessor" << std::endl; 
    // std::cout << "value of root " << root_->getValue() << std::endl; 
    // this->print(); 
  }

  // Node now can have 0-1 parents, 0-1 children

  // CASE 2: Node is ROOT
  if(current == root_) {
    // CASE 2A: only left child
    if(current->getLeft()) {
      current->getLeft()->setParent(nullptr); 
      root_ = current->getLeft(); 
    }
    // CASE 2B: only right child
    else if(current->getRight()) {
      current->getRight()->setParent(nullptr);
      root_ = current->getRight(); 
    }
    // CASE 2C: no child
    else {
      root_ = nullptr; 
    }
  }

   // CASE 3: Node HAS A PARENT

  else if(current->getParent()) {

    // CASE3-1: Node is Left Child
    if(current->getParent()->getLeft() == current) {
      // CASE 3A: Only has Left child
      if(current->getLeft()) {
        current->getParent()->setLeft(current->getLeft()); 
        current->getLeft()->setParent(current->getParent()); 
      }
      // CASE 3B: Only has Right child
      else if(current->getRight()) {
        current->getParent()->setLeft(current->getRight()); 
        current->getRight()->setParent(current->getParent()); 
      }
      // CASE 3C: Has No children
      else {
        current->getParent()->setLeft(nullptr); 
      }
    }
    // CASE3-2: Node is Right Child
    else {
        // CASE 3A: Only has Left child
      if(current->getLeft()) {
        current->getParent()->setRight(current->getLeft()); 
        current->getLeft()->setParent(current->getParent()); 
      }
      // CASE 3B: Only has Right child
      else if(current->getRight()) {
        current->getParent()->setRight(current->getRight()); 
        current->getRight()->setParent(current->getParent()); 
      }
      // CASE 3C: Has No children
      else {
        current->getParent()->setRight(nullptr); 
      }
    }

    
  }
  // free memory of current node
  delete current; 


  /*
  // CASE 2: NO children
  if(!current->getLeft() && !current->getRight()) {

    // if key does not have a parent, set root to null
    if(!current->getParent()) root_ = nullptr; 

    // checks if node is left or right child and updates parent respectively
    else if(current->getParent()->getLeft() == current)
      current->getParent()->setLeft(nullptr); 
    else if(current->getParent()->getRight() == current) 
      current->getParent()->setRight(nullptr); 

  }

  // CASE 3: ONLY LEFT child (no right child)
  else if(!current->getRight()) {
    nodeSwap(current, current->getLeft()); 
    current->getParent()->setLeft(current->getLeft()); 
  }
  
  // CASE 4: ONLY RIGHT child (no left child)
  else if(!current->getLeft()) {
    nodeSwap(current, current->getRight()); 
    current->getParent()->setRight(nullptr); 
  }
  */

  

}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current) 
{
    // if node has a left subtree, predecessor is max node of right subtree
    // otherwise, predecessor is the first parent that comes up from a right link

    if(!current) return nullptr; 

    // std::cout << "finding predecessor of " << current->getKey() << std::endl; 

    if(current->getLeft()) {
      // std::cout << "in predecessor func pred of current " << current->getValue() << " is " << getLargestNodeOfTree(current->getLeft())->getValue()<< std::endl; 
      // std::cout << "largest node of tree " << current->getLeft()->getValue() << " is " << getLargestNodeOfTree(current->getLeft())->getValue() << std::endl; 
      return getLargestNodeOfTree(current->getLeft()); 
    }

    // recurse upwards and look for parent predecessors
    Node<Key, Value>* parent = current->getParent(); 
    while(parent && parent->getLeft() == current) {
      parent = parent->getParent(); 
      current = current->getParent(); 
    }
    return parent; 

}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // if node has a right subtree, predecessor is min node of left subtree
    // otherwise, successor is the first parent that comes up from a left link
    
    if(!current) return nullptr; 

    // std::cout << "finding successor of " << current->getKey() << std::endl;

    if(current->getRight()) return getSmallestNodeOfTree(current->getRight()); 

    // recurse upwards and look for parent predecessors
    Node<Key, Value>* parent = current->getParent(); 
    while(parent && parent->getRight() == current) {
      parent = parent->getParent(); 
      current = current->getParent(); 
    }
    return parent; 
}


// returns pointer to smallest node in a subtree
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNodeOfTree(Node<Key, Value>* current)
{

  if(!current || !current->getLeft()) return current; 
  else return getSmallestNodeOfTree(current->getLeft()); 
}

// returns pointer to largest node in a subtree
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getLargestNodeOfTree(Node<Key, Value>* current)
{
  if((!current) || (!current->getRight())) return current; 
  else return getLargestNodeOfTree(current->getRight()); 
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{ 
    clearHelper(root_); 
    root_ = nullptr; 
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* current)
{
    if(!current) return; 
    clearHelper(current->getLeft()); 
    clearHelper(current->getRight()); 
    delete current; 
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // std::cout << "getting smallest node" << std::endl; 
    return getSmallestNodeOfTree(root_); 
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    // std::cout << "finding key " << key << std::endl; 
    Node<Key, Value>* current = root_; 
    while(current && current->getKey() != key) {
      if(key < current->getKey())
        current = current->getLeft(); 
      else
        current = current->getRight(); 
    }
    return current; 
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    // std::cout << "findng balance " << std::endl;
    return isBalancedHelper(root_) >= 0; 
}

// returns height of the tree if the subtree is balanced
// returns -1 if the tree is not balanced
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* current) 
{
  if(!current) return 0; 

  int leftBalance = isBalancedHelper(current->getLeft());
  int rightBalance = isBalancedHelper(current->getRight()); 

  // if left or right subtree is unbalanced, return false
  // if left and right subtree height differs by more than 1, return false
  if(leftBalance < 0 || rightBalance < 0 || abs(leftBalance - rightBalance) > 1)
    return -1; 

  // else return height of subtree
  return 1 + std::max(leftBalance, rightBalance); 
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{

    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }

    // std::cout << "swapping nodes " << n1->getKey() << " and " << n2->getKey() << std::endl; 

    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
