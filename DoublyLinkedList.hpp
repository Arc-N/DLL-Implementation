// DoublyLinkedList.hpp
#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include "EmptyException.hpp"
#include "IteratorException.hpp"



template <typename ValueType>
class DoublyLinkedList
{
	// The forward declarations of these classes allows us to establish
	// that they exist, but delay displaying all of the details until
	// later in the file.
public:
	class Iterator;
	class ConstIterator;

private:
	struct Node;


public:
	// Initializes this list to be empty.
	DoublyLinkedList() noexcept;

	// Initializes this list as a copy of an existing one.
	DoublyLinkedList(const DoublyLinkedList& list);

	// Initializes this list from an expiring one.
	DoublyLinkedList(DoublyLinkedList&& list) noexcept;


	// Destroys the contents of this list.
	virtual ~DoublyLinkedList() noexcept;


	// Replaces the contents of this list with a copy of the contents
	// of an existing one.
	DoublyLinkedList& operator=(const DoublyLinkedList& list);

	// Replaces the contents of this list with the contents of an
	// expiring one.
	DoublyLinkedList& operator=(DoublyLinkedList&& list) noexcept;


	// addToStart() adds a value to the start of the list, meaning that
	// it will now be the first value, with all subsequent elements still
	// being in the list (after the new value) in the same order.
	void addToStart(const ValueType& value);

	// addToEnd() adds a value to the end of the list, meaning that
	// it will now be the last value, with all subsequent elements still
	// being in the list (before the new value) in the same order.
	void addToEnd(const ValueType& value);


	// removeFromStart() removes a value from the start of the list, meaning
	// that the list will now contain all of the values *in the same order*
	// that it did before, *except* that the first one will be gone.
	// In the event that the list is empty, an EmptyException will be thrown.
	void removeFromStart();

	// removeFromEnd() removes a value from the end of the list, meaning
	// that the list will now contain all of the values *in the same order*
	// that it did before, *except* that the last one will be gone.
	// In the event that the list is empty, an EmptyException will be thrown.
	void removeFromEnd();


	// first() returns the value at the start of the list.  In the event that
	// the list is empty, an EmptyException will be thrown.  There are two
	// variants of this member function: one for a const DoublyLinkedList and
	// another for a non-const one.
	const ValueType& first() const;
	ValueType& first();


	// last() returns the value at the end of the list.  In the event that
	// the list is empty, an EmptyException will be thrown.  There are two
	// variants of this member function: one for a const DoublyLinkedList and
	// another for a non-const one.
	const ValueType& last() const;
	ValueType& last();


	// isEmpty() returns true if the list has no values in it, false
	// otherwise.
	bool isEmpty() const noexcept;


	// size() returns the number of values in the list.
	unsigned int size() const noexcept;

	// iterator() creates a new Iterator over this list.  It will
	// initially be referring to the first value in the list, unless the
	// list is empty, in which case it will be considered both "past start"
	// and "past end".
	Iterator iterator();


	// constIterator() creates a new ConstIterator over this list.  It will
	// initially be referring to the first value in the list, unless the
	// list is empty, in which case it will be considered both "past start"
	// and "past end".
	ConstIterator constIterator() const;


public:
	// The IteratorBase class is the base class for our two kinds of
	// iterators.  Because there are so many similarities between them,
	// we write those similarities in a base class, then inherit from
	// that base class to specify only the differences.
	class IteratorBase
	{
	public:
		// Initializes a newly-constructed IteratorBase to operate on
		// the given list.  It will initially be referring to the first
		// value in the list, unless the list is empty, in which case
		// it will be considered to be both "past start" and "past end".
		IteratorBase(const DoublyLinkedList& list) noexcept;


		// moveToNext() moves this iterator forward to the next value in
		// the list.  If the iterator is refrering to the last value, it
		// moves to the "past end" position.  If it is already at the
		// "past end" position, an IteratorException will be thrown.
		void moveToNext();


		// moveToPrevious() moves this iterator backward to the previous
		// value in the list.  If the iterator is refrering to the first
		// value, it moves to the "past start" position.  If it is already
		// at the "past start" position, an IteratorException will be thrown.
		void moveToPrevious();


		// isPastStart() returns true if this iterator is in the "past
		// start" position, false otherwise.
		bool isPastStart() const noexcept;


		// isPastEnd() returns true if this iterator is in the "past end"
		// position, false otherwise.
		bool isPastEnd() const noexcept;

	protected:
		Node * current;
		Node* pastStart;
		Node* pastEnd;
	};


	class ConstIterator : public IteratorBase
	{
	public:
		// Initializes a newly-constructed ConstIterator to operate on
		// the given list.  It will initially be referring to the first
		// value in the list, unless the list is empty, in which case
		// it will be considered to be both "past start" and "past end".
		ConstIterator(const DoublyLinkedList& list) noexcept;


		// value() returns the value that the iterator is currently
		// referring to.  If the iterator is in the "past start" or
		// "past end" positions, an IteratorException will be thrown.
		const ValueType& value() const;
	};


	class Iterator : public IteratorBase
	{
	private:
		int* s;
	public:
		// Initializes a newly-constructed Iterator to operate on the
		// given list.  It will initially be referring to the first
		// value in the list, unless the list is empty, in which case
		// it will be considered to be both "past start" and "past end".
		Iterator(DoublyLinkedList& list) noexcept;


		// value() returns the value that the iterator is currently
		// referring to.  If the iterator is in the "past start" or
		// "past end" positions, an IteratorException will be thrown.
		ValueType& value() const;


		// insertBefore() inserts a new value into the list before
		// the one to which the iterator currently refers.  If the
		// iterator is in the "past start" position, an IteratorException
		// is thrown.
		void insertBefore(const ValueType& value);


		// insertAfter() inserts a new value into the list after
		// the one to which the iterator currently refers.  If the
		// iterator is in the "past end" position, an IteratorException
		// is thrown.
		void insertAfter(const ValueType& value);


		// remove() removes the value to which this iterator refers,
		// moving the iterator to refer to either the value after it
		// (if moveToNextAfterward is true) or before it (if
		// moveToNextAfterward is false).  If the iterator is in the
		// "past start" or "past end" position, an IteratorException
		// is thrown.
		void remove(bool moveToNextAfterward = true);
	};


private:
	// A structure that contains the vital parts of a Node in a
	// doubly-linked list, the value and two pointers: one pointing
	// to the previous node (or nullptr if there isn't one) and
	// one pointing to the next node (or nullptr if there isn't
	// one).
	struct Node
	{
		ValueType value;
		Node* prev;
		Node* next;
	};
	Node* head;
	Node* tail;
	int s;
};



template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList() noexcept
{
	head = tail = nullptr;
	s = 0;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(const DoublyLinkedList& list)
{
	head = tail = nullptr;
	s = 0;
	*this = list;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(DoublyLinkedList&& list) noexcept
{
	this->head = list.head;
	list.head = nullptr;
	this->tail = list.tail;
	list.tail = nullptr;
	this->s = list.s;
	list.s = 0;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::~DoublyLinkedList() noexcept
{
	Node* iter = head;
	Node* iterNext;
	while (iter != nullptr)
	{
		iterNext = iter->next;
		delete iter;
		iter = iterNext;
	}
}

template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(const DoublyLinkedList& list)
{
	//save old data
	Node* saveH = head;
	Node* saveT = tail;
	int saveS = s;
	//in case of exception rollback saved memory address
	Node* iter;
	Node* iterNext;
	if (list.head == nullptr)
	{
		head = nullptr;
	}
	else
	{
		iter = list.head;
		s = list.s;
		try
		{
			head = new Node;
			head->value = iter->value;
			head->next = nullptr;
			head->prev = nullptr;
			tail = head;
			iter = iter->next;
		}
		catch (...)
		{
			head = saveH;
			saveH = nullptr;
			tail = saveT;
			saveT = nullptr;
			s = saveS;
			saveS = 0;
		}
		while (iter != nullptr)
		{
			try
			{
				Node* newN = new Node;
				newN->value = iter->value;
				newN->next = nullptr;
				newN->prev = tail;
				tail->next = newN;
				tail = newN;
				iter = iter->next;
			}
			catch (...)
			{
				head = saveH;
				saveH = nullptr;
				tail = saveT;
				saveT = nullptr;
				s = saveS;
				saveS = 0;
			}
		}
	}
	iter = saveH;
	while (iter != nullptr)
	{
		iterNext = iter->next;
		delete iter;
		iter = iterNext;
	}
	return *this;
}


template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(DoublyLinkedList&& list) noexcept
{
	Node* temp = this->head;
	this->head = list.head;
	list.head = temp;

	temp = this->tail;
	this->tail = list.tail;
	list.tail = temp;

	int tem = this->s;
	this->s = list.s;
	list.s = tem;
	return *this;
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToStart(const ValueType& value)
{
	Node* saveH = head;
	Node* saveT = tail;
	int saveS = s;
	try
	{
		if (head == nullptr)
		{
			head = new Node;
			head->value = value;
			head->prev = nullptr;
			head->next = nullptr;
			tail = head;
			s++;
		}
		else if (s == 1)
		{
			Node* newN = new Node;
			newN->value = value;
			newN->prev = nullptr;
			newN->next = head;
			head = newN;
			tail->prev = head;
			s++;
		}
		else
		{
			Node* newN = new Node;
			newN->value = value;
			newN->prev = nullptr;
			newN->next = head;
			head->prev = newN;
			head = newN;
			s++;
		}
	}
	catch (...)
	{
		head = saveH;
		saveH = nullptr;
		tail = saveT;
		saveT = nullptr;
		s = saveS;
		saveS = 0;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToEnd(const ValueType& value)
{
	Node* saveT = tail;
	Node* saveH = head;
	int saveS = s;
	try
	{
		if (head == nullptr)
		{
			head = new Node;
			head->value = value;
			head->prev = nullptr;
			head->next = nullptr;
			tail = head;
			s++;
		}
		else if (s == 1)
		{
			Node* newN = new Node;
			newN->value = value;
			newN->prev = tail;
			newN->next = nullptr;
			tail = newN;
			head->next = tail;
			s++;
		}
		else
		{
			Node* newN = new Node;
			newN->value = value;
			newN->prev = tail;
			newN->next = nullptr;
			tail->next = newN;
			tail = newN;
			s++;
		}
	}
	catch (...)
	{
		tail = saveT;
		saveT = nullptr;
		head = saveH;
		saveH = nullptr;
		s = saveS;
		saveS = 0;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromStart()
{
	if (head == nullptr)
	{
		throw EmptyException{};
	}
	else
	{
		Node* temp = head;
		head = head->next;
		if (head == nullptr)
		{
			tail = head;
		}
		else if (head == tail)
		{
			tail->prev = nullptr;
		}
		delete temp;
		if(head != nullptr) head->prev = nullptr;
		s--;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromEnd()
{
	if (head == nullptr)
	{
		throw EmptyException{};
	}
	else
	{
		Node* temp = tail;
		tail = tail->prev;
		if (tail == nullptr)
		{
			head = tail;
		}
		else if (tail == head)
		{
			head->next = nullptr;
		}
		delete temp;
		if(tail != nullptr)tail->next = nullptr;
		s--;
	}
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::first() const
{
	if (head == nullptr)
	{
		throw EmptyException{};
	}
	else
	{
		return head->value;
	}
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::first()
{
	if (head == nullptr)
	{
		throw EmptyException{};
	}
	else
	{
		return (ValueType&)(head->value);
	}
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::last() const
{
	if (head == nullptr)
	{
		throw EmptyException{};
	}
	else
	{
		return tail->value;
	}
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::last()
{
	if (head == nullptr)
	{
		throw EmptyException{};
	}
	else
	{
		return (ValueType&)(tail->value);
	}
}


template <typename ValueType>
unsigned int DoublyLinkedList<ValueType>::size() const noexcept
{
	return s;
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::isEmpty() const noexcept
{
	if (s == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::Iterator DoublyLinkedList<ValueType>::iterator()
{
	return Iterator{ *this };
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::ConstIterator DoublyLinkedList<ValueType>::constIterator() const
{
	return ConstIterator{ *this };
}


template <typename ValueType>
DoublyLinkedList<ValueType>::IteratorBase::IteratorBase(const DoublyLinkedList& list) noexcept
{
	if (list.head == nullptr)
	{
		current = pastStart = pastEnd = list.head;
	}
	else
	{
		current = list.head;
		pastStart = list.head->prev;
		pastEnd = list.tail->next;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToNext()
{
	if (current == pastEnd)
	{
		throw IteratorException{};
	}
	else if (current->next == pastEnd)
	{
		current = pastEnd;
	}
	else
	{
		current = current->next;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToPrevious()
{
	if (current == pastStart)
	{
		throw IteratorException{};
	}
	else if (current->prev == pastStart)
	{
		current = pastStart;
	}
	else
	{
		current = current->prev;
	}
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastStart() const noexcept
{
	if (current == pastStart)
	{
		return true;
	}
	return false;
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastEnd() const noexcept
{
	if (current == pastEnd)
	{
		return true;
	}
	return false;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::ConstIterator::ConstIterator(const DoublyLinkedList& list) noexcept
	: IteratorBase{ list }
{
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::ConstIterator::value() const
{
	if (IteratorBase::current == IteratorBase::pastEnd || IteratorBase::current == IteratorBase::pastStart)
	{
		throw IteratorException{};
	}
	else
	{
		return IteratorBase::current->value;
	}
}


template <typename ValueType>
DoublyLinkedList<ValueType>::Iterator::Iterator(DoublyLinkedList& list) noexcept
	: IteratorBase{ list }
{
	s = &(list.s);
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::Iterator::value() const
{
	if (IteratorBase::current == IteratorBase::pastEnd || IteratorBase::current == IteratorBase::pastStart)
	{
		throw IteratorException{};
	}
	else
	{
		return (ValueType&)(IteratorBase::current->value);
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertBefore(const ValueType& value)
{
	if (IteratorBase::current == IteratorBase::pastStart)
	{
		throw IteratorException{};
	}
	else
	{
		Node* saveC = IteratorBase::current;
		int saveS = *s;
		try
		{
			Node* newN = new Node;
			Node* previous = IteratorBase::current->prev;
			newN->value = value;
			newN->next = IteratorBase::current;
			newN->prev = previous;
			previous->next = newN;
			IteratorBase::current->prev = newN;
			(*s)++;
		}
		catch (...)
		{
			IteratorBase::current = saveC;
			saveC = nullptr;
			*s = saveS;
			saveS = 0;
		}
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertAfter(const ValueType& value)
{
	if (IteratorBase::current == IteratorBase::pastEnd)
	{
		throw IteratorException{};
	}
	else
	{
		Node* saveC = IteratorBase::current;
		int saveS = *s;
		try
		{
			Node* newN = new Node;
			Node* nextNode = IteratorBase::current->next;
			newN->value = value;
			newN->prev = IteratorBase::current;
			newN->next = nextNode;
			nextNode->prev = newN;
			IteratorBase::current->next = newN;
			(*s)++;
		}
		catch (...)
		{
			IteratorBase::current = saveC;
			saveC = nullptr;
			*s = saveS;
			saveS = 0;
		}
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::remove(bool moveToNextAfterward)
{
	if (IteratorBase::current == IteratorBase::pastEnd || IteratorBase::current == IteratorBase::pastStart)
	{
		throw IteratorException{};
	}
	else
	{
		Node* previous = IteratorBase::current->prev;
		Node* nextNode = IteratorBase::current->next;
		previous->next = nextNode;
		nextNode->prev = previous;
		delete IteratorBase::current;
		if (moveToNextAfterward)
		{
			IteratorBase::current = nextNode;
		}
		else
		{
			IteratorBase::current = previous;
		}
	}
}
#endif
