#include <iostream>
#include <map>
#include <cmath>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<int,int> bt;
    
    srand(1); 
    // insert 100 random elements from -100 to 100
    for(int i = 0; i < 10000; i++) {
        int num = (int)((double)rand() / RAND_MAX * 10000); 
        bt.insert(std::make_pair(num, num)); 
    }

  cout << "Binary Search Tree contents:" << endl;
  for(BinarySearchTree<int,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
      cout << it->first << " " << it->second << endl;
  }

    for(int i = 0; i < 10000; i++)
      bt.remove(i); 

    bt.clear(); 

    bt.print(); 
    

    /*
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<int,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }*/
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');

    return 0;
}
