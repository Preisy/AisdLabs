#ifndef LAB_3_KEYSPACE1_H
#define LAB_3_KEYSPACE1_H

#include "vector"
#include "algorithm"
#include "KeySpaces/IKeySpace.h"
#include "KeySpaces/Node.h"
#include "Key1.h"
#include "lib.h"

template<class Data>
class KeySpace1 : public IKeySpace<Data> {
    using typename IKeySpace<Data>::KeySpaceException;
private:
    lib::Deq<lib::Deq<Node<Data>>> list = lib::Deq<lib::Deq<Node<Data>>>();

public:
    KeySpace1() = default;

    ~KeySpace1() {
        for (auto it = list.begin(); it != list.end(); ++it) {
            while (true) {
                if ((*it).empty())
                    break;
                auto jt = (*it).begin();
                Item<Data>* item = (*jt).getItem();
                for (int i = 0; i < item->getNodes().getLength(); ++i) {
                    item->getNodes()[i]->remove();
                }
                item->deleteKeySpaces();
                delete item;
            }
        }
    }


public:
    const lib::Deq<Node<Data>>* find(const IKey* key) const override {
        return nonConstFind(key);
    }

private:
    lib::Deq<Node<Data>>* nonConstFind(const IKey* key) const {
        const Key1* k = dynamic_cast<const Key1*>(key);
        if (k == nullptr)
            throw KeySpaceException("Error in KeySpace1::nonConstFind()\n"
                                    "wtf: Cannot casting IKey to Key1");

//        typename lib::LinkedList<lib::LinkedList<INode<Data>>>::ForwardIterator it = list.begin();
        auto it = list.begin();
        for (; it != list.end(); ++it) {
            if (!(*it).empty()) {
                if ((*it)[0].getKey()->isEqual(key)) {
                    return &(*it);
                }
            }
        }
        return nullptr;
    }

public:
    bool push(const IKey* key, Item<Data>* data) override {
        const Key1* k = dynamic_cast<const Key1*>(key);
        if (k == nullptr)
            throw KeySpaceException("Error in KeySpace1::push()\n"
                                    "wtf: Cannot casting IKey to Key1");

        lib::Deq<Node<Data>>* findRes = nonConstFind(k);
        if (findRes == nullptr) {
            lib::Deq<Node<Data>> ll;
            ll.push(Node<Data>(k, 0, data));
            list.push(std::move(ll));
            auto it = list.end();
            --it;
            auto jt = (*it).pEnd();
            --*jt;
            data->pushNode(jt);
        } else {
            int version;
            for (auto it = findRes->begin(); it != findRes->end(); ++it)
                version = (*it).getVersion();
            version = version + 1;
            findRes->push(Node<Data>(k, version, data));
            auto it = findRes->pEnd();
            --*it;
            data->pushNode(it);
        }
        return true;
    };

    lib::Array<Node<Data>*> getAll() override {
        std::vector<Node<Data>*> v;
        for (auto it = list.begin(); it != list.end(); ++it) {
            for (auto jt = (*it).begin(); jt != (*it).end(); jt = ++jt) {
                v.push_back(&*jt);
            }
        }
        lib::Array<Node<Data>*> res(v.size());
        for (int i = 0; i < v.size(); ++i) {
            res[i] = v[i];
        }
        return res;
    }
};

#endif //LAB_3_KEYSPACE1_H
