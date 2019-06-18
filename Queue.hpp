#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "DoublyLinkedList.hpp"



template <typename ValueType>
class Queue : private DoublyLinkedList<ValueType>
{
public:
    // enqueue() adds the given value to the back of the queue, after
    // all of the ones that are already stored within.
    void enqueue(const ValueType& value);

    // dequeue() removes the front value from the queue, if there is
    // one.  If the queue is empty, it throws an EmptyException instead.
    void dequeue();

    // front() returns the front value in the queue, if there is one.
    // If the queue is empty, it throws an EmptyException instead.
    const ValueType& front() const;

    using DoublyLinkedList<ValueType>::isEmpty;
    using DoublyLinkedList<ValueType>::size;

    using DoublyLinkedList<ValueType>::constIterator;
    using ConstIterator = typename DoublyLinkedList<ValueType>::ConstIterator;
};



template <typename ValueType>
void Queue<ValueType>::enqueue(const ValueType& value)
{
    this->addToEnd(value);
}


template <typename ValueType>
void Queue<ValueType>::dequeue()
{
    this->removeFromStart();
}


template <typename ValueType>
const ValueType& Queue<ValueType>::front() const
{
    return this->first();
}



#endif
