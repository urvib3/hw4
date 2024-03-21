#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &keyValuePair); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    virtual void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n); 
    virtual void removeFix(AVLNode<Key,Value>* n, int diff); 
    virtual void rotateRight (AVLNode<Key,Value>* n); 
    virtual void rotateLeft (AVLNode<Key,Value>* n); 
    virtual int height(AVLNode<Key,Value>* n);
    virtual bool verifyBalances(AVLNode<Key,Value>* n);  
    // Add helper functions here


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &keyValuePair)
{ 

    AVLNode<Key, Value>* current = dynamic_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::root_); 
    AVLNode<Key, Value>* parent = nullptr; 

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
      current = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, parent); 
      // check if parent is null, if it is then update root
      if(!parent) BinarySearchTree<Key,Value>::root_ = current; 
      // check if its a right or left link with parent
      else if(current->getKey() < parent->getKey())
        parent->setLeft(current); 
      else  
        parent->setRight(current); 

      // AVL updates
      // if node has a parent, update balances
      if(parent) {
        // if parent's balance is -1 or 1, update parent's balance to 0
        if(parent->getBalance()) {
          parent->setBalance(0);
        } 
        // if parent's balance is 0, update balance and call insert-fix to rebalance
        // if current is left child, parent balance is -1; right child, parent balance is +1
        else if(parent->getBalance() == 0) {
          parent->setBalance((parent->getLeft() == current) ? -1 : 1); 
          insertFix(parent, current); 
        }
      }
    }

    // otherwise current should have same key as keyValuePair
    else if(current->getKey() == keyValuePair.first)
      current->setValue(keyValuePair.second); 
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n) {
 
  if(!p || !p->getParent()) return; 

  AVLNode<Key, Value>* g = p->getParent();  

  // CASE 1: P is LEFT child of g
  if(g->getLeft() == p) {
    g->updateBalance(-1); 
    // CASE 1A: G Balance is 0
    if(g->getBalance() == 0) return; 
    // CASE 1B: G Balance is -1 and recurse
    else if(g->getBalance() == -1) insertFix(g,p); 
    // CASE 1C: G Balance is -2 and tree needs to be rebalanced
    else if(g->getBalance() == -2) {
      // CASE 1C-1: ZIG-ZIG (P Balance is 0 or -1)
      if(p->getBalance() <= 0) {
        rotateRight(g); g->setBalance(0); p->setBalance(0);
      }
      // CASE 1C-2: ZIG-ZAG
      else if(p->getBalance() == 1) {
        rotateLeft(p); rotateRight(g); 
        // CASE 1C-2A: N Balance is -1
        if(n->getBalance() == -1) {
          p->setBalance(0); g->setBalance(1); 
        }
        // CASE 1C-2B: N Balance is 0
        else if(n->getBalance() == 0) {
          p->setBalance(0); g->setBalance(0);
        }
        // CASE 1C-2C: N Balance is +1
        else if(n->getBalance() == 1) {
          p->setBalance(-1); g->setBalance(0);
        }
        n->setBalance(0);
      }
    }
  }

  // CASE 2: P is RIGHT child of g
  else if(g->getRight() == p) {
    g->updateBalance(1); 
    // CASE 2A: G Balance is 0
    if(g->getBalance() == 0) return; 
    // CASE 2B: G Balance is 1 and recurse
    else if(g->getBalance() == 1) insertFix(g,p); 
    // CASE 2C: G Balance is 2 and tree needs to be rebalanced
    else if(g->getBalance() == 2) {
      // CASE 2C-1: ZIG-ZIG (P Balance is 0 or 1)
      if(p->getBalance() >= 0) {
        rotateLeft(g); g->setBalance(0); p->setBalance(0);
      }
      // CASE 2C-2: ZIG-ZAG
      else if(p->getBalance() == -1) {
        rotateRight(p); rotateLeft(g); 
        // CASE 2C-2A: N Balance is 1
        if(n->getBalance() == 1) {
          p->setBalance(0); g->setBalance(-1); 
        }
        // CASE 2C-2B: N Balance is 0
        else if(n->getBalance() == 0) {
          p->setBalance(0); g->setBalance(0);
        }
        // CASE 2C-2C: N Balance is -1
        else if(n->getBalance() == -1) {
          p->setBalance(1); g->setBalance(0);
        }
        n->setBalance(0); 
      }
    }
  }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{ 


    AVLNode<Key,Value>* current = dynamic_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::root_); 
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
      nodeSwap(current, dynamic_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::predecessor(current))); 
      // std::cout << "tree after swapping with predecessor" << std::endl; 
      // std::cout << "value of root " << root_->getValue() << std::endl; 
      // this->print(); 
    }

    // Node now can have 0-1 parents, 0-1 children

    int ndiff = 0; 

    // CASE 2: Node is ROOT
    if(current == BinarySearchTree<Key,Value>::root_) {
      // CASE 2A: only left child
      if(current->getLeft()) {
        current->getLeft()->setParent(nullptr); 
        BinarySearchTree<Key,Value>::root_ = current->getLeft(); 
      }
      // CASE 2B: only right child
      else if(current->getRight()) {
        current->getRight()->setParent(nullptr);
        BinarySearchTree<Key,Value>::root_ = current->getRight(); 
      }
      // CASE 2C: no child
      else {
        BinarySearchTree<Key,Value>::root_ = nullptr; 
      }
    }

    // CASE 3: Node HAS A PARENT

    else if(current->getParent()) {

      // CASE3-1: Node is Left Child
      if(current->getParent()->getLeft() == current) {
        
        // removing a left child will increase parent balance by +1
        ndiff = 1; 

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

        // if removed node is a right child, parent's balance will increase by -1
        ndiff = -1; 

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

    // access parent of removed node to start rebalancing tree
    AVLNode<Key,Value>* parent = current->getParent(); 

    // free memory of current node
    delete current;  

    // call removeFix to rebalance tree
    if(parent)
      removeFix(parent, ndiff); 


}

// patch tree after removal
template<class Key, class Value>
void AVLTree<Key,Value>::removeFix(AVLNode<Key,Value>* n, int diff) {

  // CASE 1: Current node is null
  if(!n) return; 

  AVLNode<Key,Value>* p = n->getParent(); 

  // std::cout << "current key " << n->getKey() << " current balance " << (int) n->getBalance() << " diff " << diff << std::endl;

  // Compute diff for next recursive call before altering tree
  int ndiff = 0; 
  if(n->getParent()) ndiff = (n->getParent()->getLeft() == n) ? 1 : -1; 

  // CASE 2: new node balance is 0
  if(n->getBalance() + diff == 0) {
    n->setBalance(0); 
    removeFix(p, ndiff); 
    return; 
  }

  // CASE 3: new node balance is -1 or 1
  if(abs(n->getBalance() + diff) == 1) {
    n->setBalance(n->getBalance() + diff); 
    return; 
  }

  // CASE 4: Removed node was on the right subtree of node and new node balance is -2
  if(n->getBalance() + diff == -2) {
    AVLNode<Key,Value>* c = n->getLeft(); 
    // CASE 4A: C Balance is -1, Zig-Zig
    if(c->getBalance() == -1) {
      rotateRight(n);
      n->setBalance(0); c->setBalance(0); 
      removeFix(p, ndiff); 
      return;
    }
    // CASE 4B: C Balance is 0, Zig-Zig
    else if(c->getBalance() == 0) {
      rotateRight(n); 
      n->setBalance(-1); c->setBalance(1); 
      return;
    }
    // CASE 4C: C Balance is +1, Zig-Zag
    else if(c->getBalance() == 1) {
      AVLNode<Key,Value>* g = c->getRight(); 
      rotateLeft(c); 
      rotateRight(n); 
      // CASE 4C-1: G Balance is -1
      if(g->getBalance() == -1) {
        n->setBalance(1); 
        c->setBalance(0); 
      }
      // CASE 4C-2: G Balance is 0
      else if(g->getBalance() == 0) {
        n->setBalance(0); 
        c->setBalance(0); 
      }
      // CASE 4C-3: G Balance is 1
      else if(g->getBalance() == 1) {
        n->setBalance(0); 
        c->setBalance(-1); 
      }
      g->setBalance(0); 
      removeFix(p, ndiff);
      return; 
    }

  }

  // CASE 5: Removed node was on the left subtree of node and new node balance is +2
  if(n->getBalance() + diff == 2) {
    AVLNode<Key,Value>* c = n->getRight(); 
    // CASE 4A: C Balance is 1, Zig-Zig
    if(c->getBalance() == 1) {
      rotateLeft(n);
      n->setBalance(0); c->setBalance(0); 
      removeFix(p, ndiff); 
      return;
    }
    // CASE 4B: C Balance is 0, Zig-Zig
    if(c->getBalance() == 0) {
      rotateLeft(n); 
      n->setBalance(1); c->setBalance(-1); 
      return;
    }
    // CASE 4C: C Balance is -1, Zig-Zag
    if(c->getBalance() == -1) {
      AVLNode<Key,Value>* g = c->getLeft(); 
      rotateRight(c); 
      rotateLeft(n); 
      // CASE 4C-1: G Balance is 1
      if(g->getBalance() == 1) {
        n->setBalance(-1); 
        c->setBalance(0); 
      }
      // CASE 4C-2: G Balance is 0
      else if(g->getBalance() == 0) {
        n->setBalance(0); 
        c->setBalance(0); 
      }
      // CASE 4C-3: G Balance is -1
      else if(g->getBalance() == -1) {
        n->setBalance(0); 
        c->setBalance(1); 
      }
      g->setBalance(0); 
      removeFix(p, ndiff);
      return; 
    }
  }
}

// precondition: n has a right child
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* n) {
  
  // std::cout << "rotating right " << n->getKey() << std::endl; 
  
  AVLNode<Key,Value>* g = n->getParent();   // grandparent
  AVLNode<Key,Value>* a = n->getLeft();    // replacing n's node
  AVLNode<Key,Value>* m = a->getRight();     // moving node

  a->setParent(g); 
  // If there is no parent, root must be updated
  if(!g) 
    BinarySearchTree<Key,Value>::root_ = a; 
  else if(g->getLeft() == n)
    g->setLeft(a); 
  else if(g->getRight() == n)
    g->setRight(a); 

  n->setParent(a); 
  a->setRight(n); 

  n->setLeft(m); 
  if(m) m->setParent(n); 
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n) {
  
  // std::cout << "rotating left " << n->getKey() << std::endl; 

  AVLNode<Key,Value>* g = n->getParent();   // grandparent
  AVLNode<Key,Value>* a = n->getRight();    // replacing n's node
  AVLNode<Key,Value>* m = a->getLeft();     // moving node

  a->setParent(g); 
  // if node has no parent, root must be updated
  if(!g)
    BinarySearchTree<Key,Value>::root_ = a; 
  else if(g->getLeft() == n)
    g->setLeft(a); 
  else if(g->getRight() == n)
    g->setRight(a); 

  n->setParent(a); 
  a->setLeft(n); 

  n->setRight(m); 
  if(m) m->setParent(n); 
}



template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
int AVLTree<Key, Value>::height(AVLNode<Key,Value>* n) {
  if(!n) return 0; 
  return 1 + std::max(height(n->getLeft()), height(n->getRight())); 
}

template<class Key, class Value>
bool AVLTree<Key, Value>::verifyBalances(AVLNode<Key,Value>* n) {
  if(!n) return true; 
  if((height(n->getRight()) - height(n->getLeft())) != n->getBalance()) return false; 
  return verifyBalances(n->getLeft()) && verifyBalances(n->getRight()); 
}


#endif
