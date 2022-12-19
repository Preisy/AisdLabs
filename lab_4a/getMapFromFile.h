#ifndef LAB_4_GETFROMFILE_H
#define LAB_4_GETFROMFILE_H

#include "iostream"
#include "ActionResult.h"
#include "Map.h"

lib::ActionResult<lib::Map<int, std::string>> getMapFromFile(const std::string & fileName);


#endif //LAB_4_GETFROMFILE_H
