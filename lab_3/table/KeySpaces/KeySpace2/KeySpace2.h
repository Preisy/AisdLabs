#ifndef LAB_3_KEYSPACE2_H
#define LAB_3_KEYSPACE2_H

#include "iostream"
#include "vector"
#include "algorithm"
#include "KeySpaces/IKeySpace.h"
#include "KeySpaces/Node.h"
#include "Key2.h"
#include "lib.h"

template<class Data>
class KeySpace2 : public IKeySpace<Data> {
    using typename IKeySpace<Data>::KeySpaceException;
private:
    int capacity = 100;
    lib::Array<lib::Deq<lib::Deq<Node<Data>>>> array = lib::Array<lib::Deq<lib::Deq<Node<Data>>>>(capacity);

public:
    KeySpace2() = default;

    ~KeySpace2() {
        std::cout << "ks2 dest" << std::endl;
        for (auto it = array.begin(); it != array.end(); ++it) {
            for (auto jt = (*it).begin(); jt != (*it).end(); ++jt) {
                while (true) {
                    if ((*jt).empty())
                        break;

                    auto kt = (*jt).begin();

                    Item<Data>* itemjt = nullptr;
                    Item<Data>* item = (*kt).getItem();
                    for (item = (*kt).getItem(); item->getNext() != nullptr; item = item->getNext()) {
                        delete itemjt;
                        itemjt = item;
                    }
                    delete itemjt;
                    for (int i = 0; i < item->getNodes().getLength(); ++i) {
                        item->getNodes()[i]->remove();
                    }
                    item->deleteKeySpaces();
                    item->deleteKey();
                    delete item;
                }
            }
        }
    }


public:
    const lib::Deq<Node<Data>>* find(const IKey* key) const override {
        return nonConstFind(key);
    }

private:
    lib::Deq<Node<Data>>* nonConstFind(const IKey* key) const {
        const Key2* k = dynamic_cast<const Key2*>(key);
        if (k == nullptr)
            throw KeySpaceException("Error in KeySpace2::nonConstFind()\n"
                                    "wtf: Cannot casting IKey to Key2");

        int hash = getHash(key->toString());
        for (auto it = array[hash].begin(); it != array[hash].end() ; ++it) {
            if (!(*it).empty() && (*it)[0].getKey()->isEqual(key)) {
                return &*it;
            }
        }
        return nullptr;
    }

public:
    bool push(const IKey* key, Item<Data>* data) override {
        const Key2* k = dynamic_cast<const Key2*>(key);
        if (k == nullptr)
            throw KeySpaceException("Error in KeySpace2::push()\n"
                                    "wtf: Cannot casting IKey to Key2");

        lib::Deq<Node<Data>>* findRes = nonConstFind(k);
        if (findRes == nullptr) {
            int hash = getHash(key->toString());
            lib::Deq<Node<Data>> deq;
            deq.push(Node<Data>(k, 0, data));
            array[hash].push(std::move(deq));

            auto it = (*(array[hash].end() - 1)).pEnd();
            --*it;
            data->pushNode(it);
        } else {
            findRes->push(Node<Data>(k, (*(findRes->end() - 1)).getVersion() + 1, data));

            auto it = findRes->pEnd();
            --*it;
            data->pushNode(it);
        }
        return true;
    };

    lib::Array<Node<Data>*> getAll() override {
        std::vector<Node<Data>*> v;
        for (auto it = array.begin(); it != array.end(); ++it) {
            for (auto jt = (*it).begin(); jt != (*it).end(); ++jt) {
                for (auto kt = (*jt).begin(); kt != (*jt).end(); ++kt) {
                    v.push_back(&*kt);
                }
            }
        }
        lib::Array<Node<Data>*> res(v.size());
        for (int i = 0; i < v.size(); ++i) {
            res[i] = v[i];
        }
        return res;
    }

public:
    void printArray() {
        for (int i = 0; i < array.getLength(); ++i) {
            if (!array[i].empty())
                std::cout << i << ": [" << std::endl;
            for (auto jt = array[i].begin(); jt != array[i].end(); ++jt) {
                std::cout << "  { " << std::endl;
                for (auto kt = (*jt).begin(); kt != (*jt).end(); ++kt) {
                    if ((*kt).getItem() != nullptr)
                        std::cout << "    ( ";
                    for (auto lt = (*kt).getItem(); lt != nullptr; lt = lt->getNext()) {
                        std::cout <<  lt->getKey().toString() << " │ " << lt->getData() << "; ";
                    }
                    if ((*kt).getItem() != nullptr)
                        std::cout << " )" << std::endl;
                }
                std::cout << "  }" << std::endl;
            }
            if (!array[i].empty())
                std::cout << "]" << std::endl;
        }
    }



private:
    mutable std::string cacheStr = "";
    mutable int cacheHash = 0;
    unsigned int getHash(const std::string & str) const {
        if (cacheStr == str) {
            return cacheHash;
        } else {
            cacheStr = str;
            cacheHash = (int) (HashRot13(str.c_str()) % (unsigned int) capacity);
            return cacheHash;
        }
    }

private:
    unsigned int HashFAQ6(const char* str) const {
        unsigned int hash = 0;
        for (; *str; str++) {
            hash += (unsigned char) (*str);
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);

        return hash;
    }

    unsigned int HashRot13(const char* str) const {
        unsigned int hash = 0;
        for (; *str; str++) {
            hash += (unsigned char) (*str);
            hash -= (hash << 13) | (hash >> 19);
        }
        return hash;
    }

    unsigned int HashLy(const char* str) const {
        unsigned int hash = 0;
        for (; *str; str++)
            hash = (hash * 1664525) + (unsigned char) (*str) + 1013904223;

        return hash;
    }

    unsigned int HashRs(const char* str) const {
        static const unsigned int b = 378551;
        unsigned int a = 63689;
        unsigned int hash = 0;

        for (; *str; str++) {
            hash = hash * a + (unsigned char) (*str);
            a *= b;
        }

        return hash;
    }
};

#endif //LAB_3_KEYSPACE2_H
