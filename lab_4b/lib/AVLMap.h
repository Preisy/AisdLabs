#ifndef SEMINAR_16_04_TREE_H
#define SEMINAR_16_04_TREE_H

#include "ActionResult.h"
#include "Array.h"
#include "Deq.h"
#include "DynamicArray.h"
#include "fstream"

namespace lib {

    template<class Key, class Value>
    class AVLMap {
    private:
        class Node {
        private:
            Node* left = nullptr;
            Node* right = nullptr;
            Node* parent = nullptr;

        private:
            Key key;
            Value value;
            int balance = 0;


        public:
            Node(const std::pair<Key, Value> & p, Node* parent)
                    : value(p.second),
                      key(p.first), parent(parent) {};
        public:
            void moveEntry(Node* node) {
                key = std::move(node->key);
                value = std::move(node->value);
            }

            int getBalance() const { return balance; }

            void setBalance(int balance) { Node::balance = balance; }

            Node* getLeft() const { return this->left; }

            void setLeft(Node* left) { // for adding
                this->left = left;
                if (left != nullptr)
                    left->parent = this;
            }


            Node* getRight() const { return this->right; }

            void setRight(Node* right) {
                this->right = right;
                if (right != nullptr)
                    right->parent = this;
            }


            const Key & getKey() const { return this->key; };

            const Value & getValue() const { return this->value; };

            Value & getValue() { return this->value; };

            void setValue(Value value) { Node::value = value; }

            Node* getParent() const { return this->parent; }

            void setParent(Node* parent) { this->parent = parent; }
        };

        Node* root;

    public:
        AVLMap() : root(nullptr) {}

        ~AVLMap() {
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
        AVLMap(AVLMap && mp) : root(mp.root) {
            mp.root = nullptr;
        }

        AVLMap & operator=(AVLMap && mp) noexcept {
            if (&mp == this)
                return *this;

            if (this->root != nullptr)
                recDelete(this->root);

            root = mp.root;

            mp.root = nullptr;

            return *this;
        }


    public:

        lib::ActionResult<Value> remove(const Key & key) {
            Node* node = findNode(key);
            if (node == nullptr) return lib::ActionResult<Value>(false);
            Value value = node->getValue();

            if (node->getRight() == nullptr) {
                Node* parent = node->getParent();
                int side = getSide(node);
                replaceNode(node, node->getLeft());
                if (parent != nullptr) {
                    deletingCorrect(parent, side);
                }
                delete node;
                return lib::ActionResult<Value>(std::move(value));
            }
            Node* it = node->getRight();
            while (it->getLeft() != nullptr)
                it = it->getLeft();

            Node* parent = it->getParent();
            int side = getSide(it);

            replaceNode(it, it->getRight());
            node->moveEntry(it);

            if (parent != nullptr) {
                deletingCorrect(parent, side);
            }

            delete it;
            return lib::ActionResult<Value>(std::move(value));
        }

        /**
         * @param [in] side == @b 1 for deleting in @b right subtree
         * @param [in] side == @b -1 for deleting in @b left subtree
         */
        void deletingCorrect(Node* el, int side) {
            if (el == nullptr)
                return;
            if (side == -2) {
                return;
            }

            for (auto node = el; node != nullptr; node = node->getParent()) {
                if (node->getBalance() == 0) {
                    node->setBalance(node->getBalance() - side);
                    return;
                }
                node->setBalance(node->getBalance() - side);

                balanceNode(node);
                if (node->getBalance() == -1) {
                    return;
                } else if (node->getBalance() == 1) {
                    return;
                }
                if (node->getParent() != nullptr) {
                    side = getSide(node);
                }
            }
        }

        int getSide(Node* node) {
            if (node->getParent() == nullptr) {
                return -2;
            } else if (node->getParent()->getLeft() == node) {
                return -1;
            } else if (node->getParent()->getRight() == node) {
                return 1;
            } else {
                std::cout << "cannot decide which side" << node->getKey() << std::endl;
                exit(-2);
            }
        }



    private:
        Node* replaceNode(Node* oldNode, Node* newNode) {
            if (oldNode->getParent() == nullptr) {
                root = newNode;
            } else if (oldNode->getParent()->getLeft() != nullptr &&
                     oldNode->getParent()->getLeft()->getKey() == oldNode->getKey())
                oldNode->getParent()->setLeft(newNode);
            else if (oldNode->getParent()->getRight() != nullptr &&
                     oldNode->getParent()->getRight()->getKey() == oldNode->getKey())
                oldNode->getParent()->setRight(newNode);

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
                    it->setValue(p.second);
                    return true;
                } else if (p.first > it->getKey()) {
                    if (it->getRight() == nullptr) {
                        it->setRight(new Node(p, it));
                        addingCorrect(it->getRight());
                        break;
                    }
                    it = it->getRight();
                } else {
                    if (it->getLeft() == nullptr) {
                        it->setLeft(new Node(p, it));
                        addingCorrect(it->getLeft());
                        break;
                    }
                    it = it->getLeft();
                }
            }
//            if (!check()) std::cout << "Alert" << std::endl;
            return true;
        }

    private:
        void addingCorrect(Node* el) {
            auto node = el;
            for (auto parent = el->getParent(); parent != nullptr; parent = parent->getParent()) {
                if (parent->getLeft() == node) {
                    parent->setBalance(parent->getBalance() - 1);
                } else if (parent->getRight() == node) {
                    parent->setBalance(parent->getBalance() + 1);
                } else {
                    std::cout << "asasd" << std::endl;
                }

                balanceNode(parent);

                if (parent->getBalance() == 0)
                    return;

                node = parent;
            }
        }

        bool balanceNode(Node*& parent) {
            if (parent->getBalance() == 2) {
                if (parent->getRight() == nullptr) {
                    std::cout << "Aaaa" << std::endl;
                }
                if (parent->getRight() != nullptr && parent->getRight()->getBalance() == 1) {
                    Node* a = parent;
                    Node* b = parent->getRight();
                    leftTurn(a);
                    a->setBalance(0);
                    b->setBalance(0);
                    parent = b;
                } else {
                    Node* a = parent;
                    Node* b = parent->getRight();
                    Node* c = parent->getRight()->getLeft();
                    rightTurn(parent->getRight());
                    leftTurn(parent);

                    if (b->getBalance() == 0) {
                        a->setBalance(0);
                        b->setBalance(1);
                        c->setBalance(1);
                    } else if (c->getBalance() == 0) {
                        a->setBalance(0);
                        int bBalance = b->getBalance();
                        if (bBalance == -1) {
                            b->setBalance(0);
                            c->setBalance(0);
                        } else if (bBalance == 0) {
                            b->setBalance(1);
                            c->setBalance(1);
                        } else {
                            std::cout << "bBalance != -1/0" << std::endl;
                            exit(3);
                        }
                    } else if (c->getBalance() == -1) {
                        a->setBalance(0);
                        b->setBalance(1);
                        c->setBalance(0);
                    } else if (c->getBalance() == 1) {
                        a->setBalance(-1);
                        b->setBalance(0);
                        c->setBalance(0);
                    }

                    parent = c;
                }
                return true;
            } else if (parent->getBalance() == -2) {
                if (parent->getLeft() != nullptr && parent->getLeft()->getBalance() == -1) {
                    Node* a = parent;
                    Node* b = parent->getLeft();
                    rightTurn(a);
                    a->setBalance(0);
                    b->setBalance(0);
                    parent = b;
                } else {
                    Node* a = parent;
                    Node* b = parent->getLeft();
                    Node* c = parent->getLeft()->getRight();
                    leftTurn(parent->getLeft());
                    rightTurn(parent);

                    if (b->getBalance() == 0) {
                        a->setBalance(0);
                        b->setBalance(-1);
                        c->setBalance(-1);
                    } else if (c->getBalance() == 0) {
                        a->setBalance(0);
                        int bBalance = b->getBalance();
                        if (bBalance == 1) {
                            b->setBalance(0);
                            c->setBalance(0);
                        } else if (bBalance == 0) {
                            b->setBalance(-1);
                            c->setBalance(-1);
                        } else {
                            std::cout << "bBalance != 1/0" << std::endl;
                            exit(3);
                        }
                    } else if (c->getBalance() == -1) {
                        a->setBalance(1);
                        b->setBalance(0);
                        c->setBalance(0);
                    } else if (c->getBalance() == 1) {
                        a->setBalance(0);
                        b->setBalance(-1);
                        c->setBalance(0);
                    }
                    parent = c;
                }
                return true;
            }
            return false;
        }

        void rightTurn(Node* node) {
            Node* left = node->getLeft();
            Node* lr = node->getLeft()->getRight();
            if (node->getParent() == nullptr) {
                root = node->getLeft();
                node->getLeft()->setParent(nullptr);
            } else if (node->getParent()->getRight() == node) {
                node->getParent()->setRight(left);
            } else if (node->getParent()->getLeft() == node) {
                node->getParent()->setLeft(left);
            }
            node->setLeft(lr);
            left->setRight(node);
        }

        void leftTurn(Node* node) {
            Node* right = node->getRight();
            Node* rl = node->getRight()->getLeft();
            if (node->getParent() == nullptr) {
                root = node->getRight();
                node->getRight()->setParent(nullptr);
            } else if (node->getParent()->getRight() == node) {
                node->getParent()->setRight(right);
            } else if (node->getParent()->getLeft() == node) {
                node->getParent()->setLeft(right);
            }
            node->setRight(rl);
            right->setLeft(node);
        }

    public:
        lib::ActionResult<Value> find(const Key & key) {
            auto res = findNode(key);
            if (res == nullptr) return lib::ActionResult<Value>(false);
            else return lib::ActionResult<Value>(std::move(res->getValue()));
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
        Key* specialFind(const Key & key) const {
            if (root == nullptr)
                return nullptr;

            Key* res = nullptr;
            recSpecialFind(root, key, res);

            return res;
        }

    private:
         void recSpecialFind(Node* node, const Key & base, Key* & current) const {
            if (node == nullptr) return;
            if (node->getKey() >= base) {
                recSpecialFind(node->getLeft(), base, current);
            }
            if (current == nullptr) {
                current = const_cast<Key*>(&node->getKey());
            }
            if (current != nullptr && node->getKey() != base
                && abs(*current - base) > abs(node->getKey() - base)) {
                current = const_cast<Key*>(&node->getKey());
            }

            if (node->getKey() <= base) {
                recSpecialFind(node->getRight(), base, current);
            }
        }

        Key abs(const Key & key) const {
            return (key > 0 ? key : -key);
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

            std::cout << "{" << node->getKey() << ": " << node->getValue() << "}" << std::endl;
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

            fout << "}";
            fout.close();
            system("dot tmp.dot | neato -n -Tpng -o tree.png");
            system("rm -rf tmp.dot");
        }

        void recWrite(std::ofstream & fout, Node* node, int & tmpCount) const {
            fout << "\"" << node->getKey() << " : " << node->getValue() << " (" << node->getBalance() << ")" << "\"->";

            if (node->getLeft() != nullptr) {
                fout << "\"" << node->getLeft()->getKey() << " : " << node->getLeft()->getValue() << " (" << node->getLeft()->getBalance() << ")" << "\";";
            } else
                fout << "tmp" << tmpCount++ << "[style=invis];";


            fout << "\"" << node->getKey() << " : " << node->getValue() << " (" << node->getBalance() << ")" << "\"->";

            if (node->getRight() != nullptr) {
                fout << "\"" << node->getRight()->getKey() << " : " << node->getRight()->getValue() << " (" << node->getRight()->getBalance() << ")" << "\";";
            } else
                fout << "tmp" << tmpCount++ << "[style=invis];";

            if (node->getLeft() != nullptr)
                recWrite(fout, node->getLeft(), tmpCount);
            if (node->getRight() != nullptr)
                recWrite(fout, node->getRight(), tmpCount);
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
            std::string tmp = "{" + std::to_string(node->getKey()) + ", " + node->getValue() + "}";
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


    };

}


#endif //SEMINAR_16_04_TREE_H
