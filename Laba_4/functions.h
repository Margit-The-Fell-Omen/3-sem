#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "BinTree.h"
#include "Member_of_commision.h"
#include "Prepod.h"
#include "Prepod_from_commision.h"
#include <string>

// Template function to handle operations for a specific class type
template <typename T>
void handleTreeOperations(BinTree<T> &tree, const std::string &className);

#endif
