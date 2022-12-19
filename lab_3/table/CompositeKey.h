#ifndef LAB_3_COMPOSITEKEY_H
#define LAB_3_COMPOSITEKEY_H

#include "lib.h"
#include "KeySpaces/IKey.h"
#include "KeySpaces/KeySpace1/Key1.h"
#include "KeySpaces/KeySpace2/Key2.h"

class CompositeKey {
private:
    int len = 2;
    lib::Array<IKey*> keys{len};

public:
    CompositeKey() = default;

    CompositeKey(Key2* key1, Key1* key2) {
        keys[0] = key1;
        keys[1] = key2;
    }

    ~CompositeKey() {
        for (int i = 0; i < keys.getLength(); ++i) {
            delete keys[i];
        }
    }

    CompositeKey(const CompositeKey & key) {
//        for (int i = 0; i < keys.getLength(); ++i) {
        keys[0] = new Key2(key.keys[0]);
        keys[1] = new Key1(key.keys[1]);
//        }
    };

    CompositeKey & operator=(const CompositeKey & key) {
        if (&key == this)
            return *this;

        for (int i = 0; i < keys.getLength(); ++i) {
            delete keys[i];
        }

        for (int i = 0; i < keys.getLength(); ++i) {
            *(keys[i]) = *(key.keys[i]);
        }

        return *this;
    }

public:
    std::string toString() const {
        std::string res = "(";
        for (int i = 0; i < len; ++i) {
            res += keys[i]->toString();
            if (i != len - 1)
                res += ", ";
            else
                res += ")";
        }
        return res;
    }
public:
    const IKey* operator[](int index) const {
        return this->keys[index];
    }

    bool isComplete() const {
        for (int i = 0; i < keys.getLength(); ++i) {
            if (keys[i] == nullptr) {
                return false;
            }
        }
        return true;
    }

    friend bool operator==(const CompositeKey & el1, const CompositeKey & el2);


};

bool operator==(const CompositeKey & el1, const CompositeKey & el2) {
    if (el1.keys.getLength() != el2.keys.getLength())
        return false;
    for (int i = 0; i < el1.keys.getLength(); ++i) {
        if (!el1.keys[i]->isEqual(el2.keys[i]))
            return false;
    }
    return true;
}


#endif //LAB_3_COMPOSITEKEY_H
