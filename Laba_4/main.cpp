#include "BinTree.h"
#include "Member_of_commision.h"
#include "Prepod.h"
#include "Prepod_from_commision.h"
#include <iostream>
#include <limits>
#include <string>

// Template function to handle operations for a specific class type
template <typename T>
void handleTreeOperations(BinTree<T> &tree, const std::string &className)
{
  int choice;
  T value;
  T oldValue, newValue;

  while (true)
  {
    std::cout << "\n=== " << className << " Tree Operations ===\n";
    std::cout << "1. Insert a " << className << "\n";
    std::cout << "2. Remove a " << className << "\n";
    std::cout << "3. Update a " << className << "\n";
    std::cout << "4. Display InOrder\n";
    std::cout << "5. Display PreOrder\n";
    std::cout << "6. Display PostOrder\n";
    std::cout << "7. Display LevelOrder\n";
    std::cout << "8. Clear the tree\n";
    std::cout << "9. Back to main menu\n";
    std::cout << "Enter your choice: ";

    if (!(std::cin >> choice))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter a number.\n";
      continue;
    }

    switch (choice)
    {
    case 1: // Insert
    {
      std::cout << "Enter " << className << " data:\n";
      std::cin.ignore(); // Clear newline from buffer
      if (std::cin >> value)
      {
        tree.insert(value);
        std::cout << "Inserted successfully!\n";
      }
      else
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.\n";
      }
      break;
    }
    case 2: // Remove
    {
      std::cout << "Enter " << className << " data to remove:\n";
      std::cin.ignore();
      if (std::cin >> value)
      {
        tree.remove(value);
        std::cout << "Removed successfully!\n";
      }
      else
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.\n";
      }
      break;
    }
    case 3: // Update
    {
      std::cout << "Enter old " << className << " data:\n";
      std::cin.ignore();
      if (std::cin >> oldValue)
      {
        std::cout << "Enter new " << className << " data:\n";
        if (std::cin >> newValue)
        {
          if (tree.update(oldValue, newValue))
          {
            std::cout << "Updated successfully!\n";
          }
          else
          {
            std::cout << "Update failed. Old value not found.\n";
          }
        }
        else
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Invalid new value.\n";
        }
      }
      else
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid old value.\n";
      }
      break;
    }
    case 4: // InOrder
    {
      std::cout << "InOrder:\n";
      T dummy;
      dummy.printHeader(std::cout);
      std::cout << std::endl;

      auto inIt = tree.template begin<Order::InOrder>();
      auto inEnd = tree.template end<Order::InOrder>();
      if (!(inIt != inEnd))
      {
        std::cout << "(Tree is empty)" << std::endl;
      }
      else
      {
        while (inIt != inEnd)
        {
          std::cout << *inIt << std::endl;
          ++inIt;
        }
      }
      break;
    }
    case 5: // PreOrder
    {
      std::cout << "PreOrder:\n";
      T dummy;
      dummy.printHeader(std::cout);
      std::cout << std::endl;

      auto preIt = tree.template begin<Order::PreOrder>();
      auto preEnd = tree.template end<Order::PreOrder>();
      if (!(preIt != preEnd))
      {
        std::cout << "(Tree is empty)" << std::endl;
      }
      else
      {
        while (preIt != preEnd)
        {
          std::cout << *preIt << std::endl;
          ++preIt;
        }
      }
      break;
    }
    case 6: // PostOrder
    {
      std::cout << "PostOrder:\n";
      T dummy;
      dummy.printHeader(std::cout);
      std::cout << std::endl;

      auto postIt = tree.template begin<Order::PostOrder>();
      auto postEnd = tree.template end<Order::PostOrder>();
      if (!(postIt != postEnd))
      {
        std::cout << "(Tree is empty)" << std::endl;
      }
      else
      {
        while (postIt != postEnd)
        {
          std::cout << *postIt << std::endl;
          ++postIt;
        }
      }
      break;
    }
    case 7: // LevelOrder
    {
      std::cout << "LevelOrder:\n";
      T dummy;
      dummy.printHeader(std::cout);
      std::cout << std::endl;

      auto levelIt = tree.template begin<Order::LevelOrder>();
      auto levelEnd = tree.template end<Order::LevelOrder>();
      if (!(levelIt != levelEnd))
      {
        std::cout << "(Tree is empty)" << std::endl;
      }
      else
      {
        while (levelIt != levelEnd)
        {
          std::cout << *levelIt << std::endl;
          ++levelIt;
        }
      }
      break;
    }
    case 8: // Clear
      tree = BinTree<T>();
      std::cout << "Tree cleared.\n";
      break;
    case 9: // Back to main menu
      return;
    default:
      std::cout << "Invalid choice. Please enter 1-9.\n";
    }
  }
}

int main()
{
  BinTree<Member_of_commision> memberTree;
  BinTree<Prepod> prepodTree;
  BinTree<Prepod_from_commision> prepodMemberTree;

  int mainChoice;

  std::cout << "=== Binary Tree Management System ===\n";

  while (true)
  {
    std::cout << "\nMain Menu:\n";
    std::cout << "1. Work with Member_of_commision tree\n";
    std::cout << "2. Work with Prepod tree\n";
    std::cout << "3. Work with Prepod_from_commision tree\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";

    if (!(std::cin >> mainChoice))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter a number.\n";
      continue;
    }

    switch (mainChoice)
    {
    case 1:
      handleTreeOperations(memberTree, "Member_of_commision");
      break;
    case 2:
      handleTreeOperations(prepodTree, "Prepod");
      break;
    case 3:
      handleTreeOperations(prepodMemberTree, "Prepod_from_commision");
      break;
    case 4:
      std::cout << "Exiting program.\n";
      return 0;
    default:
      std::cout << "Invalid choice. Please enter 1-4.\n";
    }
  }
}
