#ifndef LAB_3_TABLE_H
#define LAB_3_TABLE_H

#include "iostream"
#include "lib.h"
#include "KeySpaces/IKeySpace.h"
#include "KeySpaces/KeySpace1/KeySpace1.h"
#include "KeySpaces/KeySpace2/KeySpace2.h"
#include "Item.h"
#include "CompositeKey.h"

#include "KeySpaces/IKey.h"

class TableException : public std::exception {
private:
    std::string m_error;

public:
    explicit TableException(std::string error) : m_error(std::move(error)) {}

    const char* what() const noexcept override { return m_error.c_str(); }
};

template<class Data>
class Table {
private:
    lib::Array<IKeySpace<Data>*> keySpaces{2};

public:
    Table() {
        keySpaces[0] = new KeySpace2<Data>();
        keySpaces[1] = new KeySpace1<Data>();
    };

    ~Table() {
        std::cout << "table dest" << std::endl;
        for (int i = 0; i < keySpaces.getLength(); ++i) {
            delete keySpaces[i];
        }
    }

    bool push(const CompositeKey* key, const Data & data) {
        if (!key->isComplete())
            return false;

        lib::Array<Item<Data>*> findResArray = findPointers(*key);
        Item<Data>* findRes = nullptr;

        int version = 0;
        if (findResArray.getLength() != 0) { // if exists
            findRes = findResArray[0];
            for (; findRes->getNext() != nullptr; findRes = findRes->getNext()) {
                version = findRes->getVersion() > version ? findRes->getVersion() : version;
            }
            version += 1;
        }

        auto* item = new Item<Data>(data, key, version, findRes);
        if (findRes != nullptr) {
            findRes->setNext(item);
            item->copyKeySpaces(findRes);
        }

        if (findRes == nullptr) {
            for (int i = 0; i < keySpaces.getLength(); ++i) {
                keySpaces[i]->push((*key)[i], item);
            }
        }


        return true;
    }


    typename lib::Array<Item<Data>>::CopyRAIterator find(const CompositeKey & key) const {
        lib::Array<Item<Data>*> res = findPointers(key);

        std::vector<Item<Data>*> v;
        for (auto it = res.begin(); it != res.end(); ++it) {
            for (auto jt = *it; jt != nullptr; jt = jt->getNext()) {
                v.push_back(jt);
            }
        }

        lib::Array<Item<Data>> tmp = lib::Array<Item<Data>>(v.size());
        for (int i = 0; i < v.size(); ++i) {
            tmp[i] = *v[i];
        }
        return tmp.moveBegin();
    }

    typename lib::Array<Item<Data>>::CopyRAIterator find(const CompositeKey & key, int version) const {
        if (!key.isComplete()) {
            lib::Array<Item<Data>> tmp(0);
            return tmp.moveBegin();
        }

        lib::Array<Item<Data>*> findResArray = findPointers(key);
        Item<Data>* res = findResArray.getLength() == 0 ? nullptr : findResArray[0];

        for (auto it = res; it != nullptr; it = it->getNext()) {
            if (it->getVersion() == version) {
                lib::Array<Item<Data>> tmp(1);
                tmp[0] = *it;
                return tmp.moveBegin();
            }
        }
        lib::Array<Item<Data>> tmp(0);
        return tmp.moveBegin();
    }

private:
    lib::Array<Item<Data>*> findPointers(const CompositeKey & key) const {
        const lib::Deq<Node<Data>>* findRes;
        for (int i = 0; i < keySpaces.getLength(); ++i) {
            if (key[i] != nullptr) {
                findRes = keySpaces[i]->find(key[i]);
                break;
            }
        }
        if (findRes == nullptr) {
            return lib::Array<Item<Data>*>(0);
        }

        std::vector<Item<Data>*> dynamicArray;
        for (auto it = findRes->begin(); it != findRes->end(); ++it) {
            bool flag = true;
            for (int i = 0; i < keySpaces.getLength(); ++i) {
                if (key[i] != nullptr) {
                    if (!key[i]->isEqual((*it).getItem()->getKey()[i])) {
                        flag = false;
                        break;
                    }
                }
            }
            if (!flag)
                continue;

//            Item<Data>* tmp = (*it).getItem();
//            while (tmp->getPrev() != nullptr)
//                tmp = tmp->getPrev();

//            flag = true; // чтобы исключить одинаковые списки из item
//            for (int i = 0; i < dynamicArray.size(); ++i) { // todo как это оптимизировать
//                if (dynamicArray[i] == tmp) {
//                    flag = false;
//                    break;
//                }
//            }
//            if (flag)
//                dynamicArray.push_back(tmp);
            dynamicArray.push_back((*it).getItem());
        }
        lib::Array<Item<Data>*> res = lib::Array<Item<Data>*>(dynamicArray.size());
        for (int i = 0; i < res.getLength(); ++i) {
            res[i] = dynamicArray[i];
        }

        return res;
    }

public:
    bool del(const CompositeKey & key) {
        lib::Array<Item<Data>*> findRes = findPointers(key);

        for (int i = 0; i < findRes.getLength(); ++i) {
            Item<Data>* jt = nullptr;
            for (auto it = findRes[i]; it != nullptr; it = it->getNext()) {
                delete jt;
                jt = it;
            }

            for (int j = 0; j < jt->getNodes().getLength(); ++j) {
                jt->getNodes()[j]->remove();
            }
            jt->deleteKeySpaces();
            jt->deleteKey();
            delete jt;
        }

        return true;
    }
public:
    bool del(const CompositeKey & key, int version) {
        if (!key.isComplete())
            return false;

        lib::Array<Item<Data>*> findRes = findPointers(key);
        for (int i = 0; i < findRes.getLength(); ++i) {
            for (Item<Data>* it = findRes[i]; it != nullptr; it = it->getNext()) {
                if (it->getVersion() == version) {
//                    Item<Data>* kt = nullptr;
//                    auto jt = it;
//                    for (; jt->getNext() != nullptr; jt = jt->getNext()) {
//                        delete kt;
//                        kt = jt;
//                    }
                    auto next = it->getNext();
                    for (int j = 0; j < it->getNodes().getLength(); ++j) {
//                        std::cout << it->getNodes()[i]->getData() << std::endl;
                        if (it->getNodes()[j]->getData().getItem() == it) {
//                            it->getNext()->setPrev(nullptr);
                            it->getNodes()[j]->getData().setItem(it->getNext());
                            it->getNodes()[j]->getData().setKey(it->getNext()->getKey()[j]);
                        }
                    }
                    if (it->getNext() == nullptr && it->getPrev() == nullptr) {
                        for (int j = 0; j < it->getNodes().getLength(); ++j) {
                            it->getNodes()[j]->remove();
                        }
                        it->deleteKeySpaces();
//                        it->deleteKey();
                    }

//                    else {
//                        Item<Data>* kt = nullptr;
//                        for (auto jt = it; it->getNext() != nullptr; it = it->getNext()) {
//                            delete kt;
//                            kt = jt;
//                        }
//                    }
                    it->deleteKey();
                    delete it;
                    return true;

                }
            }
        }
        return false;
    }

    void printKeySpace2Array() const {
        KeySpace2<Data>* ks2 = dynamic_cast<KeySpace2<Data>*>(keySpaces[0]);
        ks2->printArray();
    }

    void print() const {
        lib::Array<std::string> ksRes(keySpaces.getLength());

        // данные, преобразованные в строки
        lib::Array<lib::Array<lib::Array<std::string, 4>>> keySpacesData;
        keySpacesData = getStringArray();

        // узнаю "длины вывода" пространств ключей
        lib::Array<int> keySpacesSizes(keySpaces.getLength());
        if (keySpacesData[0].getLength() == 0) {
            for (int i = 0; i < keySpaces.getLength(); ++i) {
                keySpacesSizes[i] = 20;
            }
        } else {
            for (int i = 0; i < keySpaces.getLength(); ++i) {
                int size = 1;
                for (int k = 0; k < 4; ++k)
                    size += (int) keySpacesData[i][0][k].size() + 2;
                keySpacesSizes[i] = size;
            }
        }


        // открывающая горизонтальная линия
        std::cout << ((char) 218);
//        std::cout << "┌";
        for (int i = 0; i < keySpaces.getLength(); ++i) {
            std::cout <<" KeySpace" << i + 1 << " ";
            for (int j = 9; j < keySpacesSizes[i] - 1; ++j) {
                if (j != keySpacesSizes.getLength() - 1)
                    std::cout << ((char) 196);
//                    std::cout << "─";
            }
            if (i == keySpaces.getLength() - 1)
                std::cout << ((char) 191);
//                std::cout << "┐";
            else
                std::cout << ((char) 194);
//                std::cout << "┬";
        }
        std::cout << std::endl;


        // KeySpaces info
        if (keySpacesData[0].getLength() != 0) {
            for (int i = 0; i < keySpaces.getLength(); ++i) {
                std::cout << ((char) 179) << " Key" << i + 1;
//                std::cout << "│" << " Key" << i + 1;
                for (int j = 4; j < (int) keySpacesData[i][0][0].size(); ++j)
                    std::cout << " ";
                std::cout << "  nv";
                std:: cout << " " << ((char) 179) << " ";
//                std:: cout << " " << "│" << " ";
                std::cout << "iv ";
                std::cout << "data";
                for (int j = 4; j < (int) keySpacesData[i][0][3].size(); ++j)
                    std::cout << " ";
                std::cout << "   ";
            }
            std::cout << ((char) 179);
//            std::cout << "│";
            std::cout << std::endl;
        }

        // горизонтальная линия
        std::cout << ((char) 195);
//        std::cout << "├";
        for (int i = 0; i < keySpaces.getLength(); ++i) {
            for (int j = 0; j < keySpacesSizes[i] + 2; ++j) {
                if (j != keySpacesSizes.getLength() - 1)
                    std::cout << ((char) 196);
//                    std::cout << "─";
            }
            if (i == keySpaces.getLength() - 1)
                std::cout << ((char) 180);
//                std::cout << "┤";
            else
                std::cout << ((char) 197);
//                std::cout << "┼";
        }
        std::cout << std::endl;


        // keySpaces data
        if (keySpacesData[0].getLength() != 0) {
            for (int i = 0; i < keySpacesData[0].getLength(); ++i) {
                std::cout << ((char) 179) << " ";
//                std::cout << "│" << " ";
                for (int j = 0; j < keySpacesData.getLength(); ++j) {
                    std::cout << keySpacesData[j][i][0] << "  ";
                    std::cout << keySpacesData[j][i][1] << " " << ((char) 179) << " ";
//                    std::cout << keySpacesData[j][i][1] << " " << "│" << " ";
                    std::cout << keySpacesData[j][i][2] << " ";
                    std::cout << keySpacesData[j][i][3];
                    std::cout << "   " << ((char) 179) << " ";
//                    std::cout << "   " << "│" << " ";
                }
                std::cout << std::endl;
            }
        }

        // закрывающая горизонтальная линия
        std::cout << ((char) 192);
//        std::cout << "└";
        for (int i = 0; i < keySpaces.getLength(); ++i) {
            for (int j = 0; j < keySpacesSizes[i] + 2; ++j) {
                if (j != keySpacesSizes.getLength() - 1)
                    std::cout << ((char) 196);
//                    std::cout << "─";
            }
            if (i == keySpaces.getLength() - 1)
                std::cout << ((char) 217);
//                std::cout << "┘";
            else
                std::cout << ((char) 193);
//                std::cout << "┴";
        }
        std::cout << std::endl;


    }

private:
    lib::Array<lib::Array<lib::Array<std::string, 4>>> getStringArray() const {
        lib::Array<lib::Array<lib::Array<std::string, 4>>> keySpacesData(keySpaces.getLength());

        for (int i = 0; i < keySpaces.getLength(); ++i) {
            lib::Array<Node<Data>*> ks = keySpaces[i]->getAll();
//            keySpacesData[i] = lib::Array<lib::Array<std::string, 4>>(ks.getLength());

            std::vector<lib::Array<std::string, 4>> tmp;

            int keyLength = 4;
            int dataLength = 4;
            for (int j = 0; j < ks.getLength(); ++j) {
                for (auto kt = ks[j]->getItem(); kt != nullptr; kt = kt->getNext()) {
                    if ((int) ks[j]->getKey()->toString().size() > keyLength)
                        keyLength = ks[j]->getKey()->toString().size();
                    if ((int) std::to_string(kt->getData()).size() > dataLength)
                        dataLength = std::to_string(kt->getData()).size();
                }
//                if ((int) ks[j]->getKey()->toString().size() > keyLength)
//                    keyLength = ks[j]->getKey()->toString().size();
//                if ((int) std::to_string(ks[j]->getItem()->getData()).size() > dataLength)
//                    dataLength = std::to_string(ks[j]->getItem()->getData()).size();
            }

            for (int j = 0; j < ks.getLength(); ++j) {
                for (auto kt = ks[j]->getItem(); kt != nullptr; kt = kt->getNext()) {
                    lib::Array<std::string, 4> buf;

                    buf[0] += ks[j]->getKey()->toString();
                    for (int k = ks[j]->getKey()->toString().size(); k < keyLength; ++k)
                        buf[0] += " ";
                    buf[1] += std::to_string(ks[j]->getVersion()) + " ";
                    buf[2] += std::to_string(kt->getVersion()) + " ";
                    buf[3] += std::to_string(kt->getData());
                    for (int k = std::to_string(kt->getData()).size(); k < dataLength; ++k)
                        buf[3] += " ";

                    tmp.push_back(buf);
                }

//                keySpacesData[i][j][0] += ks[j]->getKey()->toString();
//                for (int k = ks[j]->getKey()->toString().size(); k < keyLength; ++k)
//                    keySpacesData[i][j][0] += " ";
//                keySpacesData[i][j][1] += std::to_string(ks[j]->getVersion()) + " ";
//                keySpacesData[i][j][2] += std::to_string(ks[j]->getItem()->getVersion()) + " ";
//                keySpacesData[i][j][3] += std::to_string(ks[j]->getItem()->getData());
//                for (int k = std::to_string(ks[j]->getItem()->getData()).size(); k < dataLength; ++k)
//                    keySpacesData[i][j][3] += " ";
            }

            keySpacesData[i] = lib::Array<lib::Array<std::string, 4>>(tmp.size());
            for (int j = 0; j < tmp.size(); ++j) {
                keySpacesData[i][j] = std::move(tmp[j]);
            }

        }

        return keySpacesData;
    }
};


#endif //LAB_3_TABLE_H
