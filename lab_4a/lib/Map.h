#ifndef SEMINAR_16_04_TREE_H
#define SEMINAR_16_04_TREE_H

#include "ActionResult.h"
#include "Array.h"
#include "Deq.h"
#include "DynamicArray.h"
#include "fstream"

namespace lib {

    template<class Key, class Value>
    class Map {
    private:
        class Node {
        private:
            Node* left;
            Node* right;
            Node* parent;

            Node* next;
            Node* prev;
        public:
            Node* getNext() const { return next; }

            void setNext(Node* node) { this->next = node; }

            Node* getPrev() const { return prev; }

            void setPrev(Node* node) { prev = node; }

            void moveEntry(Node* node) {
                key = std::move(node->key);
                values = std::move(node->values);
            }

        private:

            Key key;
            lib::Deq<Value> values;

        public:
            void pushValue(const Value & value) {
                values.push(value);
            }


        public:
            Node(const std::pair<Key, Value> & p, Node* parent)
                    : left(nullptr), right(nullptr),
                      next(nullptr), prev(nullptr),
                      key(p.first), parent(parent) {
                values.push(p.second);
            };
        public:
            Node* getLeft() const { return this->left; }

            void setLeft(Node* left) { // for adding
                this->left = left;
                if (left != nullptr)
                    left->parent = this;

                if (prev != nullptr)
                    prev->next = left;

                left->prev = prev;
                left->next = this;
                prev = left;

            }

            void changeLeft(Node* node) {
                if (node == nullptr) {
                    if (left != nullptr) {
                        auto it = left;
                        for (; it->left != nullptr; it = it->left);

                        if (it->prev != nullptr)
                            it->prev->next = this;
                        prev = it->prev;
                    }

                    this->left = nullptr;

                    return;
                }

                if (this->left != nullptr) {
                    auto it = this->left;
                    for (; it->left != nullptr; it = it->left);
                    auto jt = node;
                    for (; jt->left != nullptr; jt = jt->left);

                    jt->prev = it->prev;
                    if (it->prev != nullptr)
                        it->prev->next = jt;
                } else {

                    auto jt = node;
                    for (; jt->left != nullptr; jt = jt->left);

                    jt->prev = prev;
                    if (prev != nullptr)
                        prev->next = jt;
                }


                auto jt = node;
                for (; jt->right != nullptr; jt = jt->right);

                jt->next = this;
                prev = jt;


                this->left = node;
                if (node != nullptr)
                    node->parent = this;
            }

            Node* getRight() const { return this->right; }

            void setRight(Node* right) {
                this->right = right;
                if (right != nullptr)
                    right->parent = this;

                if (next != nullptr)
                    next->prev = right;
                Node* tmp = next;
                next = right;

                right->prev = this;
                right->next = tmp;
            }

            void changeRight(Node* node) {
                if (node == nullptr) {
                    if (right != nullptr) {
                        auto it = this->right;
                        for (; it->right != nullptr; it = it->right);

                        if (it->next != nullptr)
                            it->next->prev = this;

                        next = it->next;
                    }


                    this->right = nullptr;

                    return;
                }


                auto it = node;
                for (; it->left != nullptr; it = it->left);
                it->prev = this;
                next = it;

                it = node;
                for (; it->right != nullptr; it = it->right);
                auto jt = this->right;
                if (this->right != nullptr) {
                    for (; jt->right != nullptr; jt = jt->right);

                    jt->next = it->next;
                    if (jt->next != nullptr)
                        jt->next->prev = it;
                }


                this->right = node;
                if (node != nullptr)
                    node->parent = this;
            }


            const Key & getKey() const { return this->key; };

            const lib::Deq<Value> & getValue() const { return this->values; };

            lib::Deq<Value> & getValue() { return this->values; };

            Node* getParent() const { return this->parent; }

            void setParent(Node* parent) { this->parent = parent; }
        };

        Node* root;

    public:
        explicit Map(Node* root) : root(root) {};

        Map() : root(nullptr) {}

        ~Map() {
            if (this->root != nullptr)
                recDelete(this->root);
        }

    private:
        bool recDelete(Node* node) {
            if (node->getLeft() != nullptr) {
                recDelete(node->getLeft());
            }
            if (node->getRight() != nullptr) {
                recDelete(node->getRight());
            }
            delete node;
            return true;
        }

    public:
        Map(Map && mp) : root(mp.root) {
            mp.root = nullptr;
        }

        Map & operator=(Map && mp) noexcept {
            if (&mp == this)
                return *this;

            if (this->root != nullptr)
                recDelete(this->root);

            root = mp.root;

            mp.root = nullptr;

            return *this;
        }

    public:
        void write() const {
            std::ofstream fout("./tmp.dot", std::ios::out | std::ios_base::trunc);
            fout << "digraph binaryTree{node[shape=circle,color=black,fontcolor=black,fontsize=10];";
            if (!fout.is_open()) {
                std::cout << "Файл не может быть открыт или создан\n";
                return;
            }
            if (root == nullptr) {
                fout << "}";
                fout.close();
                system("dot tmp.dot | neato -n -Tpng -o tree.png");
                return;
            }


            int tmpCount = 0;
            recWrite(fout, root, tmpCount);

            for (int i = 0; i < tmpCount; ++i) {
                fout << "tmp" << i << "[style=invis];";
            }

            auto it = root;
            for (; it->getLeft() != nullptr; it = it->getLeft());
            for (; it->getNext() != nullptr; it = it->getNext()) {
                fout << "\"";
                for (int i = 0; i < it->getValue().getLength(); ++i)
                    fout << it->getKey() << " : " << it->getValue()[i] << "\\n";
                fout << "\"->\"";
                for (int i = 0; i < it->getNext()->getValue().getLength(); ++i)
                    fout << it->getNext()->getKey() << " : " << it->getNext()->getValue()[i] << "\\n";
                fout << "\"[style=dotted];";
            }

            fout << "}";
            fout.close();
            system("dot tmp.dot | neato -n -Tpng -o tree.png");
        }

        void recWrite(std::ofstream & fout, Node* node, int & tmpCount) const {
            fout << "\"";
            for (int i = 0; i < node->getValue().getLength(); ++i)
                fout << node->getKey() << " : " << node->getValue()[i] << "\\n";
            fout << "\"->";

            if (node->getLeft() != nullptr) {
                fout << "\"";
                for (int i = 0; i < node->getLeft()->getValue().getLength(); ++i)
                    fout << node->getLeft()->getKey() << " : " << node->getLeft()->getValue()[i] << "\\n";
                fout << "\";";
            } else
                fout << "tmp" << tmpCount++ << "[style=invis];";


            fout << "\"";
            for (int i = 0; i < node->getValue().getLength(); ++i)
                fout << node->getKey() << " : " << node->getValue()[i] << "\\n";
            fout << "\"->";

            if (node->getRight() != nullptr) {
                fout << "\"";
                for (int i = 0; i < node->getRight()->getValue().getLength(); ++i)
                    fout << node->getRight()->getKey() << " : " << node->getRight()->getValue()[i] << "\\n";
                fout << "\";";
            } else
                fout << "tmp" << tmpCount++ << "[style=invis];";

            if (node->getLeft() != nullptr)
                recWrite(fout, node->getLeft(), tmpCount);
            if (node->getRight() != nullptr)
                recWrite(fout, node->getRight(), tmpCount);
        }



    public:
        lib::Array<std::pair<Key, Value>> getSortedArray() const {
            lib::DynamicArray<std::pair<Key, Value>> tmp;

            auto it = root;
            while (it->getLeft() != nullptr)
                it = it->getLeft();
            while (it != nullptr) {
                tmp.push({it->getKey(), it->getValue()[0]});
                it = it->getNext();
            }

            lib::Array<std::pair<Key, Value>> res(tmp.getLength());
            for (int i = 0; i < tmp.getLength(); ++i) {
                res[i] = tmp[i];
            }
            return res;
        }

    public:
        void print() const {
            if (this->root == nullptr)
                return;
            int deep = getMaxDeep(root);
            lib::Array<std::string> arr(deep);
            deserializeTree(arr, 0, root);
            std::cout << (char) 218 << std::string(arr[0].size(), (char) 196) << (char) 191 << std::endl;
            for (int i = 0; i < arr.getLength(); ++i) {
                std::cout << (char) 179 << arr[i] << (char) 179 << std::endl;
            }
            std::cout << (char) 192 << std::string(arr[0].size(), (char) 196) << (char) 217 << std::endl;

        }

    private:
        bool deserializeTree(lib::Array<std::string> & arr, int height, Node* node) const {
            if (node->getLeft()) {
                deserializeTree(arr, height + 1, node->getLeft());
            }
            std::string tmp = "{" + std::to_string(node->getKey()) + ", " + node->getValue()[0] + "}";
            for (int i = 0; i < arr.getLength(); ++i) {
                if (i == height) {
                    arr[height] += tmp;
                } else {
                    arr[i] += std::string(tmp.size(), ' ');
                }
            }

            if (node->getRight()) {
                deserializeTree(arr, height + 1, node->getRight());
            }
        }

        int getMaxDeep(Node* node) const {
            int height = 0;
            if (node == nullptr) {
                return height;
            }
            int hl = getMaxDeep(node->getLeft());
            int hr = getMaxDeep(node->getRight());
            height = (hl > hr ? hl : hr) + 1;
            return height;
        }

    public:
        lib::ActionResult<Value> remove(const Key & key, int version) {
            Node* node = findNode(key);
            if (node == nullptr) return lib::ActionResult<Value>(false);
            if (node->getValue().getLength() <= version) return lib::ActionResult<Value>(false);
            if (node->getValue().getLength() == 1) {
                return remove(key);
            }
            Value value = node->getValue()[version];
            node->getValue().removeAt(version);
            return lib::ActionResult<Value>(std::move(value));
        }

        lib::ActionResult<Value> remove(const Key & key) {
            Node* node = findNode(key);
            if (node == nullptr) return lib::ActionResult<Value>(false);
            Value value = node->getValue()[0];

            if (node->getRight() == nullptr) {
                replaceNode(node, node->getLeft());
                delete node;
                return lib::ActionResult<Value>(std::move(value));
            }
            Node* it = node->getRight();
            while (it->getLeft() != nullptr)
                it = it->getLeft();

            replaceNode(it, it->getRight());

            node->moveEntry(it);

            delete it;
            return lib::ActionResult<Value>(std::move(value));
        }



    private:
        Node* replaceNode(Node* oldNode, Node* newNode) {
            if (oldNode->getParent() == nullptr) {
                root = newNode;
                if (newNode != nullptr) {
                    newNode->setNext(nullptr);
                    newNode->setPrev(nullptr);
                }
            } else if (oldNode->getParent()->getLeft() != nullptr &&
                     oldNode->getParent()->getLeft()->getKey() == oldNode->getKey())
                oldNode->getParent()->changeLeft(newNode);
            else if (oldNode->getParent()->getRight() != nullptr &&
                     oldNode->getParent()->getRight()->getKey() == oldNode->getKey())
                oldNode->getParent()->changeRight(newNode);

            if (newNode != nullptr)
                newNode->setParent(oldNode->getParent());

            return newNode;
        }

    public:
        bool add(const std::pair<Key, Value> & p) {
            if (root == nullptr) {
                root = new Node(p, nullptr);
                return true;
            }
            Node* it = root;
            while (true) {
                if (p.first == it->getKey()) {
                    it->pushValue(p.second);
                    return true;
                } else if (p.first > it->getKey()) {
                    if (it->getRight() == nullptr) {
                        it->setRight(new Node(p, it));
                        break;
                    }
                    it = it->getRight();
                } else {
                    if (it->getLeft() == nullptr) {
                        it->setLeft(new Node(p, it));
                        break;
                    }
                    it = it->getLeft();
                }
            }
            return true;
        }

    public:
//        lib::Deq<Value> notfoundbuf;
        const lib::Deq<Value> & find(const Key & key) { // todo не обрабатывает notfound
            Node* res = findNode(key);
            if (res == nullptr)
                return lib::Deq<Value>();
            else
                return res->getValue();
        }

    private:
        Node* findNode(Key key) {
            if (root == nullptr)
                return nullptr;
            Node* it = root;
            while (true) {
                if (key == it->getKey()) {
                    return it;
                } else if (key > it->getKey()) {
                    if (it->getRight() == nullptr)
                        return nullptr;
                    it = it->getRight();
                } else {
                    if (it->getLeft() == nullptr)
                        return nullptr;
                    it = it->getLeft();
                }
            }
        }

    public:
        bool check() const {
            return recCheck(this->root, nullptr, nullptr);
        }

    private:
        bool recCheck(Node* node, Node* min, Node* max) const {
            if (node == nullptr)
                return true;

            if (min != nullptr && node->getKey() <= min->getKey())
                return false;
            if (max != nullptr && node->getKey() >= max->getKey())
                return false;

            return recCheck(node->getLeft(), min, node)
                   && recCheck(node->getRight(), node, max);
        }

    public:
        lib::Deq<Value>* specialFind(const Key & max) const {
            if (root == nullptr)
                return nullptr;

            Node* it = root;
            for (; it->getLeft() != nullptr; it = it->getLeft());

            for (; it->getNext() != nullptr; it = it->getNext()) {
                if (it->getNext()->getKey() > max) {
                    return &it->getValue();
                }
            }
            return nullptr;
        }

    public:
        void specialTreeTraversal(const Key & key) const {
            if (root == nullptr)
                return;

            auto it = this->root;
            for (; it->getRight() != nullptr && it->getRight()->getKey() <= key; it = it->getRight());

            it = it->getRight();
            recSpecialTreeTraversal(it);
        }
        void specialTreeTraversal() const {
            if (root == nullptr)
                return;

            recSpecialTreeTraversal(root);
        }

        void recSpecialTreeTraversal(Node* node) const {
            if (node == nullptr) return;
            recSpecialTreeTraversal(node->getLeft());
            recSpecialTreeTraversal(node->getRight());

            std::cout << "{" << node->getKey() << ": " << node->getValue()[0] << "}" << std::endl;
        }
    };

}


#endif //SEMINAR_16_04_TREE_H
