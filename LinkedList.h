//
// Created by elif zorlu on 4.11.2025.
//

// the LinkedList implementation on the lecture slides
// were used.

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <cstddef>

class BadIterator {
public:
    BadIterator() {}
};

template <class Object>
class List;

template <class Object>
class ListItr;

template <class Object>
class ListNode {
    ListNode(const Object& theElement = Object(), ListNode* n = NULL)
        : element(theElement), next(n) {}

    Object element;
    ListNode* next;

    friend class List<Object>;
    friend class ListItr<Object>;
};

template <class Object>
class ListItr {
public:
    ListItr() : current(NULL) {}
    bool isPastEnd() const { return current == NULL; }
    void advance() { if (!isPastEnd()) current = current->next; }
    const Object& retrieve() const {
        if (isPastEnd()) throw BadIterator();
        return current->element;
    }

private:
    ListNode<Object>* current;
    ListItr(ListNode<Object>* theNode) : current(theNode) {}
    friend class List<Object>;
};

template <class Object>
class List {
public:
    List() { header = new ListNode<Object>; }
    ~List() { makeEmpty(); delete header; }

    bool isEmpty() const { return header->next == NULL; }
    ListItr<Object> zeroth() const { return ListItr<Object>(header); }
    ListItr<Object> first() const { return ListItr<Object>(header->next); }

    void insert(const Object& x, const ListItr<Object>& p) {
        if (p.current != NULL)
            p.current->next = new ListNode<Object>(x, p.current->next);
    }

    void makeEmpty() {
        ListNode<Object>* current = header->next;
        while (current != NULL) {
            ListNode<Object>* next = current->next;
            delete current;
            current = next;
        }
        header->next = NULL;
    }

    int size() const {
        int count = 0;
        ListNode<Object>* current = header->next;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        return count;
    }

private:
    ListNode<Object>* header;
};

#endif
