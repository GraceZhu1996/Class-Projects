// AVLSet.hpp
//
// ICS 46 Spring 2015
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"
#include <memory>
#include <sstream>


template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct Node
    {
        T key;
        Node* left = nullptr;
        Node* right = nullptr;
        unsigned int depth = 1;
    };


    Node* head;
    unsigned int _size;



public:
    void copy(Node &to, Node &from);
    void destroy(Node* n);
    int compare(const T& element1, const T& element2) const;
    void incrementDepths(Node* &node);
    void rearrangeTree();
    int max(const Node* left, const Node* right);
    int diff(const Node* left, const Node* right);
    void rotateLeft(Node* &n);
    void rotateRight(Node* &n);
    void rotateRightLeft(Node* &n);
    void rotateLeftRight(Node* &n);
    Node* findImbalance(Node* &n);
    void print(Node* &n);

};


template <typename T>
AVLSet<T>::AVLSet()
{
    _size = 0;
    head = nullptr;
}


template <typename T>
AVLSet<T>::~AVLSet()
{
    destroy(this->head);
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
    copy(&(this->head), &(s.head));
    _size = s.size();

}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
    if (this != &s)
    {
        destroy(this->head);
        head = nullptr;
        copy(&(this->head), &(s.head));
        _size = s.size();
    }

    return *this;

}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{

    int cmpValue;
    Node **temp = &head;

    while(true)
    {
        if (*temp == nullptr)
        {
            *temp = new Node{element};
            this->_size++;
            break;
        }
        cmpValue = compare((*temp)->key, element);

        if (cmpValue < 0)
        { 
            if ((*temp)->right == nullptr)
            {
                (*temp)->right = new Node{element};
                this->_size++;

                break;
                
            }
            else
            {
                temp = &((*temp)->right);
                continue;

            }
        }
        else if(cmpValue > 0)
         {
           if ((*temp)->left == nullptr)
            {
                (*temp)->left = new Node{element};
                this->_size++;
                break;
            }
            else
            {
                temp = &((*temp)->left);
                continue;

            }
        }
        else
        {
            break;
        }

    }
      
    rearrangeTree();
    //If it is equal, then we do not need to reinsert it
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    int cmpValue;
    Node *temp = head;
    while(true)
    {
        if (temp == nullptr)
        {
            break;
        }else{
            if (element == temp->key)
                return true;
            else  
            {
                cmpValue = compare(temp->key, element);
                if (cmpValue < 0)
                {
                    temp = temp->right;
                    continue;
                }
                else if(cmpValue > 0)
                {
                   temp = temp->left;
                   continue;
                }
                else
                {
                    break;
                }
            }
        }
        
    }
    return false;
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return this->_size;
}

template <typename T>
void AVLSet<T>::copy(Node &to, Node &from)
{
    while (from != nullptr)
    {
        to = new Node();
        to.key = from.key;
        to.depth = from.depth;
        to.parent = from.parent;
        if (&(from.left) != nullptr)
            copy(to.left, from.left);
        if (&(from.right) != nullptr)
            copy(to.right, from.right);
    }
}

template <typename T>
void AVLSet<T>::destroy(Node* n)
{
    if (n->left != nullptr)
        destroy( n->left);
    if (n->right != nullptr)
        destroy( n->right);
    if (n != nullptr)
        delete n;
}


template <typename T>
int AVLSet<T>::compare(const T& element1, const T& element2) const
{
    std::stringstream temp1, temp2;
    temp1 << element1;
    temp2 << element2;
    std::string s1 = temp1.str();
    std::string s2 = temp2.str();
    return std::strcmp(s1.c_str(), s2.c_str());

}


//Starting at a the very bottom, it increments the depth all the way to the top
template <typename T>
void AVLSet<T>::incrementDepths(Node* &node)
{
    if (node == nullptr)
    { 
        return;
    }
    else
    {
        incrementDepths(node->left);
        incrementDepths(node->right);
        node->depth = max(node->left, node->right) + 1;
    }
}

 //For testing purposes
template <typename T>
void AVLSet<T>::print(Node* &n)
{
    if (n!= nullptr)
    {
        std::stringstream temp1;
        temp1 << n->key;
        std::string s1 = temp1.str();

        if(n->left != nullptr)
        {
            print(n->left);
        }
        if(n->right != nullptr)
        {
            print(n->right);
        }
    }
}


template <typename T>
void AVLSet<T>::rotateLeft(Node* &n)
{
    Node* temp = new Node{n->key};
    Node* newright = &*(n->right);
    Node* newr_r = &*(n->right->right);
    n->key = newright->key;
    n->right = &*(newr_r);
    delete newright;
    n->left = &*temp;
}

template <typename T>
void AVLSet<T>::rotateRight(Node* &n)
{
    Node* temp = new Node{n->key};
    Node* newleft = &*(n->left);
    Node* newl_l = &*(n->left->left);
    n->key = newleft->key;
    n->left = &*(newl_l);
    delete newleft;
    n->right = &*temp;
}
template <typename T>
void AVLSet<T>::rotateRightLeft(Node* &n)
{
    Node* temp = new Node{n->key};
    Node* newleft = new Node{n->left->key};
    Node* newnode = &*(n->left->right);
    n->key = newnode->key;
    n->left = &*newleft;
    n->right = &*temp;
    delete newnode;
}

template <typename T>
void AVLSet<T>::rotateLeftRight(Node* &n)
{
    Node* temp = new Node{n->key};
    Node* newright = new Node{n->right->key};
    Node* newnode = &*(n->right->left);
    n->key = newnode->key;
    n->right = &*newright;
    n->left = &*temp;
    delete newnode;
}


template<typename T>
typename AVLSet<T>::Node* AVLSet<T>::findImbalance(Node* &n)
{
    if(n == nullptr)
    { 
        return nullptr;
    }
    else
    {

        Node* l = findImbalance(n->left);
        Node* r = findImbalance(n->right);

        if (l != nullptr)
            return l;
        if (r !=  nullptr)
            return r;

        int d = diff(n->left, n->right);
        
        if (d > 1 || d < -1)
        {
            return n;
        }
    }

    return nullptr;
}


template <typename T>
void AVLSet<T>::rearrangeTree()
{   
    incrementDepths(head);  
    Node* node = findImbalance(head);

    if (node == nullptr)
    { 
        return;
    }
    else
    {
        if (node != nullptr)
        {
            Node* left = nullptr;
            Node* right = nullptr;

            if (node->left != nullptr)
                left = &*(node->left);
            if (node->right != nullptr)
                right = &*(node->right);

            if (left == nullptr && right != nullptr)
            {
                Node* right_left = nullptr;
                 Node* right_right = nullptr;
                 if (right->left != nullptr)
                    right_left = &*(right->left);
                 if (right->right != nullptr)
                     right_right = &*(right->right);

                if (right_left == nullptr && right_right != nullptr)
                {
                    rotateLeft(node);
                }
                else if (right_right == nullptr && right_left != nullptr)
                {
                    rotateLeftRight(node);
                }
            }
            else if(right == nullptr && left != nullptr)
            {
                Node* left_left = nullptr;
                Node* left_right = nullptr;
                if(left->left != nullptr)
                    left_left = &*(left->left);
                if(left->right != nullptr)
                    left_right = &*(left->right);

                if (left_left == nullptr && left_right != nullptr)
                {
                    rotateRightLeft(node);
                }
                else if (left_right == nullptr && left_left != nullptr)
                {  
                    rotateRight(node);
                }
            }


        }

    }
}


//Reeturns the max depth of two nodes
template <typename T>
int AVLSet<T>::max(const Node* left, const Node* right)
{
    if (left == nullptr && right != nullptr)
        return right->depth;
    else if (right == nullptr && left != nullptr)
        return left->depth;
    else if (right == nullptr && left == nullptr)
        return 0;
    else
        return ((right->depth > left->depth) ? right->depth : left->depth);

}  

//Reeturns the difference between two child nodes' depth.
template <typename T>
int AVLSet<T>::diff(const Node* left, const Node* right)
{
    if (right == nullptr && left == nullptr)
        return 0; //0
    else if (left == nullptr && right != nullptr)
        return 0 - right->depth;
    else if (right == nullptr && left != nullptr)
        return left->depth  - 0;
    else
        return (left->depth - right->depth);

}  


#endif // AVLSET_HPP

