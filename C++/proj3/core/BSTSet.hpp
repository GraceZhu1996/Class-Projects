// BSTSet.hpp
//
// ICS 46 Spring 2015
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"
#include <memory>
#include <sstream>


template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct Node
    {
        T key;
        Node* left = nullptr;
        Node* right = nullptr;
    };


    Node* head;
    unsigned int _size;



public:
    void copy(Node &to, Node &from);
    void destroy(Node* n);
    int compare(const T& element1, const T& element2) const;

};


template <typename T>
BSTSet<T>::BSTSet()
{
    _size = 0;
    head = nullptr;
}


template <typename T>
BSTSet<T>::~BSTSet()
{
    destroy(this->head);
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
{
    copy(&(this->head), &(s.head));

}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
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
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
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
            if ((*temp)->right != nullptr && (*temp)->right->key == element)
                return;
            temp = &((*temp)->right);
            continue;
        }
        else if(cmpValue > 0)
        {
            if ((*temp)->left != nullptr && (*temp)->left->key == element)
                return;
           temp = &((*temp)->left);
           continue;
        }
        else
        {
            break;
        }
        
    }
    //If it is equal, then we do not need to reinsert it
}


template <typename T>
bool BSTSet<T>::contains(const T& element) const
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
unsigned int BSTSet<T>::size() const
{
    return this->_size;
}

template <typename T>
void BSTSet<T>::copy(Node &to, Node &from)
{
    while (from != nullptr)
    {
        this->add(from.key);
        if (&(from.left) != nullptr)
            copy(to.left, from.left);
        if (&(from.right) != nullptr)
            copy(to.right, from.right);
    }
}

template <typename T>
void BSTSet<T>::destroy(Node* n)
{
    if (n->left != nullptr)
        destroy( n->left);
    if (n->right != nullptr)
        destroy( n->right);
    if (n != nullptr)
        delete n;
}


template <typename T>
int BSTSet<T>::compare(const T& element1, const T& element2) const
{
    std::stringstream temp1, temp2;
    temp1 << element1;
    temp2 << element2;
    std::string s1 = temp1.str();
    std::string s2 = temp2.str();
    return std::strcmp(s1.c_str(), s2.c_str());

}



#endif // BSTSET_HPP

