#include "getMapFromFile.h"
#include <fstream>
#include "ActionResult.h"

lib::ActionResult<lib::Map<int, std::string>> getMapFromFile(const std::string & fileName) {
    std::ifstream fin(fileName, std::ios_base::in);
    if (!fin.is_open())
        return lib::ActionResult<lib::Map<int, std::string>>(false);

    lib::Map<int, std::string> mp;
    int n;
    std::string str;
    while (fin >> n >> str) {
        mp.add({n, str});
    }

    return lib::ActionResult<lib::Map<int, std::string>>(std::move(mp));
}