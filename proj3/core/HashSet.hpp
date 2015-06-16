// HashSet.hpp
//
// ICS 46 Spring 2015
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;

    int getHashValue(const T& element) const;

private:
    struct LinkedList
    {
        T key;
        LinkedList* next = nullptr;
    };

private:
    HashFunction hashFunction;
    LinkedList** hashArray;
    unsigned int capacity;
    unsigned int _size;
};



template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    capacity = DEFAULT_CAPACITY;
    hashArray = new LinkedList*[capacity];
    _size = 0;
}


template <typename T>
HashSet<T>::~HashSet()
{
    for (int i = 0; i < capacity; ++i)
        delete hashArray[i];
    delete hashArray;
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{s.hashFunction}
{
    hashArray = s.hashArray;
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        hashFunction = s.hashFunction;
        hashArray = s.hashArray;
    }

    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{

    if (_size == capacity*.8)
    {
        //Resize table
        int new_capacity = capacity*2;
        LinkedList** newtable = new LinkedList*[new_capacity];
        for (int j = 0; j < capacity; j++)
        {
            if (hashArray[j] != nullptr)
                newtable[j] = &*hashArray[j];
        }
        capacity = new_capacity;
        delete hashArray;
        hashArray = nullptr;
        hashArray = &*newtable;
    }

    int loc = getHashValue(element);
    //std::cout << "Inserting in: " << loc << std::endl;
    LinkedList** temp = &(hashArray[loc]);

    while(true)
    {
        if (*temp == nullptr)
        {
            *temp = new LinkedList{element};
            _size++;
            break;
        }
        else
        {
            if ((*temp)->key == element)
                break;
            temp = &((*temp)->next);
            continue;
        }
    }
}



template <typename T>
bool HashSet<T>::contains(const T& element) const
{
    LinkedList* temp;
    for (int i = 0; i < capacity; ++i)
    {
        if (hashArray[i] != nullptr)
        {
            temp = &*(hashArray[i]);
             while(true)
             {
                if (temp->key == element)
                    return true;
                else
                {
                     temp = &*(temp->next);
                     if (temp == nullptr)
                        break;
                }
                  
                 continue;     
             }
        }
    }
     return false;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return _size ;
}


template <typename T>
int HashSet<T>::getHashValue(const T& element) const
{
    int result =  static_cast<unsigned int>(hashFunction(element)) % capacity;
    if (capacity == DEFAULT_CAPACITY)
        return result;
    else
    {
        if (hashArray[result] == nullptr)
            return result;
        else
        {
            int tempresult = (static_cast<unsigned int>(hashFunction(element)) % (capacity - 1) + 1);
            int newresult = result;
            for (int i = 0; i < tempresult; ++i)
            {
                //STEP
                newresult++;
                if (newresult == capacity)
                    newresult = 1;
            }
            return newresult;

        }
    }
}

#endif // HASHSET_HPP

