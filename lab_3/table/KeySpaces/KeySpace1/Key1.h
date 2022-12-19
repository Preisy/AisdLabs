#ifndef LAB_3_KEY1_H
#define LAB_3_KEY1_H

#include "iostream"
#include <string>
#include "KeySpaces/IKey.h"

class Key1 : public IKey {
private:
    std::string key;
public:
    std::string toString() const override {
        return key;
    }

public:
    Key1(const Key1 & key1) : key(key1.key) {};
public:
    Key1(const IKey* key1) {
        const Key1* k = dynamic_cast<const Key1*>(key1);
        if (k == nullptr)
            throw KeyException("Error in Key1::Key1()\n"
                               "wtf: Cannot casting IKey to Key1");
        key = k->key;
    };

public:
    explicit Key1(const std::string & key)
            : key(key) {};

    bool isEqual(const IKey* key) const override {
        auto k = dynamic_cast<const Key1*>(key);
        if (k != nullptr)
            return this->key == k->key;
        else
            return false;
    }
};

#endif //LAB_3_KEY1_H
