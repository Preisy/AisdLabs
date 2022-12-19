#ifndef LAB_3_ITEM_H
#define LAB_3_ITEM_H

#include "iostream"
#include "lib.h"
#include "CompositeKey.h"
#include "KeySpaces/Node.h" // todo что делать с рекурсией?

template<class Data>
class Node;

template<class Data>
class Item {
private:
    Data data;

    const CompositeKey* key = nullptr;

    Item* next = nullptr;

    Item* prev = nullptr;

    int version;

    int nodeCount = 0;
    lib::Array<lib::RemoveIterator<Node<Data>>*> keySpaces{2};

public:
    void copyKeySpaces(Item* item) {
        nodeCount = item->nodeCount;
        keySpaces = item->keySpaces;
    }

public:
    Item(const Item & item)
            : key(new CompositeKey(*item.key)),
              next(nullptr), prev(nullptr), data(Data(item.data)), keySpaces(item.keySpaces) {};

    Item & operator=(const Item & item) {
        if (&item == this)
            return *this;

        delete key;
//        for (int i = 0; i < keySpaces.getLength(); ++i) {
//            delete keySpaces[i];
//        }

        data = item.data;
        key = new CompositeKey(*item.key);
        version = item.version;
        keySpaces = item.keySpaces;

        return *this;
    };

public:
//    Item(Item && item)
//            : key(item.key), next(item.next), prev(item.prev) {
//        std::cout << "Item move constructor" << std::endl;
//        item.key = nullptr;
//        item.next = nullptr;
//        item.prev = nullptr;
////        item.keySpaces = lib::Array<lib::RemoveIterator<Node<Data>>*>(0);
//    };
//
//    Item & operator=(Item && item) noexcept {
//        std::cout << "Item move =" << std::endl;
//        if (&item == this)
//            return *this;
//
//        delete key;
////        for (int i = 0; i < keySpaces.getLength(); ++i) {
////            delete keySpaces[i];
////        }
//
//        key = item.key;
////        keySpaces = std::move(item.keySpaces);
//
//        item.key = nullptr;
//        item.prev = nullptr;
//        item.next = nullptr;
////        item.keySpaces = lib::Array<lib::RemoveIterator<Node<Data>>*>(0);
//
//        return *this;
//    };

public:
    Item() = default;

    ~Item() {
        if (next != nullptr) {
            next->prev = prev;
        }
        if (prev != nullptr) {
            prev->next = next;
        }

//        delete key;
    }

    void deleteKey() {
        delete key;
    }

    void deleteKeySpaces() {
        for (int i = 0; i < keySpaces.getLength(); ++i) {
            delete keySpaces[i];
        }
    }

    Item(const Data & data, const CompositeKey* key, int version, Item* prev)
            : data(data), key(key), next(nullptr), prev(prev), version(version) {};

//    Item(const Data & data) : data(data) {};

    lib::Array<lib::RemoveIterator<Node<Data>>*> & getNodes() {
        return keySpaces;
    }

    bool pushNode(lib::RemoveIterator<Node<Data>>* node) {
        if (nodeCount >= keySpaces.getLength())
            return false;
        keySpaces[nodeCount++] = node;
        return true;
    }

    const Data & getData() const {
        return data;
    }

    Item* getNext() const {
        return next;
    }

    Item* getPrev() const {
        return prev;
    }

    void setPrev(Item* el) {
        prev = el;
    }

    void setNext(Item* el) {
        next = el;
    }

    const CompositeKey & getKey() const {
        return *key;
    }

    int getVersion() const {
        return version;
    }
};


#endif //LAB_3_ITEM_H
