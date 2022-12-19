#ifndef LAB_3_NODE_H
#define LAB_3_NODE_H

#include <iostream>
#include "lib.h"
//#include <Item.h>
#include "Item.h"
#include "IKey.h"

//template<class Data> class Node;

template<class Data>
bool operator==(const Node<Data> & el1, const Node<Data> & el2) {
    return (el1.key->isEqual(el2.key) &&
            el1.version == el2.version &&
            el1.item == el2.item);
}

template<class Data>
class Node {
    friend bool operator==<Data>(const Node & el1, const Node & el2);

private:
    const IKey* key;
public:
    void setKey(const IKey* key) { this->key = key; }

private:
    int version;
    Item<Data>* item;


public:
    Node() = default;

    ~Node() = default;

    Node(const IKey* key, int version, Item<Data>* item)
            : key(key),
              version(version), item(item) {}

    const IKey* getKey() const { return key; }

    int getVersion() const { return version; }

    Item<Data>* getItem() const { return item; }

    void setItem(Item<Data>* item) { this->item = item; }

public:
    Node(Node && node)
            : key(node.key),
              version(node.version),
              item(node.item) {
        node.key = nullptr;
        node.item = nullptr;
    }

    Node & operator=(Node && node) noexcept {
        if (&node == this)
            return *this;

        delete this->key;
        delete this->item;

        this->key = node.key;
        this->item = node.item;

        node.key = nullptr;
        node.item = nullptr;

        return *this;
    };

private:
    Node(const Node & node) = default;

    Node & operator=(const Node & node) = default;
};


#endif //LAB_3_NODE_H
