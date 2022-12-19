#include <iostream>

#include "lib.h"
#include "Table.h"


void printArray(lib::Array<Item<int>>::CopyRAIterator arr);

// todo может стоит написать lib::LinkedList(T data) ??
//  и как компилятор передает данные по значению?

// todo как лучше инициализировать: source(TI(it.source)) или source(it.source)
//  по факту разницы то нет, но как принято?

/**
 * @brief чтобы добавить новое пространство ключей, нужно изменить:
 *
 * Item::keySpaces{ @b 3 } @n
 * Table::KeySpaces{ @b 3 } @n
 * Table::Table() { @b ... } @n
 * CompositeKey::CompositeKey( ...@b keys ) @n
 * CompositeKey::CompositeKey(const CompositeKey &) { @b ... } @n
 * */

int main() {
    Table<int> a;

    a.push(new CompositeKey(new Key2("as"), new Key1("sf"), new Key2("ga")), 1);
    a.push(new CompositeKey(new Key2("as"), new Key1("sf"), new Key2("ga")), 2);
    a.push(new CompositeKey(new Key2("a"), new Key1("sf"), new Key2("gb")), 33456);
    a.push(new CompositeKey(new Key2("a32eadsf"), new Key1("sf"), new Key2("ga")), 32343456);

    a.print();

    /**
     * @brief find by complete key
     * */
    std::cout << "find by complete key (as, sf, ga): ";
    typename lib::Array<Item<int>>::CopyRAIterator it = a.find(CompositeKey(new Key2("as"), new Key1("sf"), new Key2("ga")));
    printArray(it);

    std::cout << "find by complete key (ga, sf, gb): ";
    it = a.find(CompositeKey(new Key2("a"), new Key1("sf"), new Key2("gb")));
    printArray(it);


    /**
     * @brief find by incomplete key
     * */
    std::cout << "find by incomplete key (as, -, ga): ";
    it = a.find(CompositeKey(new Key2("as"), nullptr, new Key2("ga")));
    printArray(it);

    std::cout << "find by incomplete key (-, sf, ga): ";
    it = a.find(CompositeKey(nullptr, new Key1("sf"), new Key2("ga")));
    printArray(it);


    /**
     * @brief find by key + version
     */
//    std::cout << "find by key + version (as, sf, ga)_1: ";
//    lib::ActionResult<Item<int>> el = a.find(CompositeKey(new Key2("as"), new Key1("sf"), new Key2("ga")), 1);
//    if (el) std::cout << (*el).getData() << std::endl;
//    else std::cout << "NotFound" << std::endl;

    /**
     * @brief deleting elements by incomplete key
     * */
    std::cout << "del by key (a, -, gb): " << std::endl;
    a.del(CompositeKey(new Key2("a"), nullptr,  new Key2("gb")));
    a.print();

    /**
     * @brief deleting elements by complete key + version
     * */
    std::cout << "del by key + version (as, sf, ga)_1: " << std::endl;
    a.del(CompositeKey(new Key2("as"), new Key1("sf"), new Key2("ga")), 1);
    a.print();

    return 0;
}


void printArray(typename lib::Array<Item<int>>::CopyRAIterator arr) {
    while (!arr.isEnded()) {
        std::cout << (*arr).getData();
        ++arr;
        if (!arr.isEnded()) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}