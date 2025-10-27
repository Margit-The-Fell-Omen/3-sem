#include "BinTree.h"
#include <iostream>
#include <limits>

int main()
{
  BinTree<int> tree;
  int choice;
  int value;
  int oldValue, newValue;

  std::cout << "Binary Tree Operations Menu\n";
  std::cout << "---------------------------\n";

  while (true)
  {
    std::cout << "\n1. Insert a value\n";
    std::cout << "2. Remove a value\n";
    std::cout << "3. Update a value\n";
    std::cout << "4. Display InOrder\n";
    std::cout << "5. Display PreOrder\n";
    std::cout << "6. Display PostOrder\n";
    std::cout << "7. Display LevelOrder\n";
    std::cout << "8. Clear the tree\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";

    // Input validation
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
      std::cout << "Enter value to insert: ";
      if (std::cin >> value)
      {
        tree.insert(value);
        std::cout << "Inserted: " << value << std::endl;
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
      std::cout << "Enter value to remove: ";
      if (std::cin >> value)
      {
        tree.remove(value);
        std::cout << "Removed: " << value << std::endl;
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
      std::cout << "Enter old value: ";
      if (std::cin >> oldValue)
      {
        std::cout << "Enter new value: ";
        if (std::cin >> newValue)
        {
          if (tree.update(oldValue, newValue))
          {
            std::cout << "Updated " << oldValue << " to " << newValue
                      << std::endl;
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
      std::cout << "InOrder: ";
      std::cout << tree; // Uses overloaded << for InOrder
      std::cout << std::endl;
      break;

    case 5: // PreOrder
    {
      std::cout << "PreOrder: ";
      auto preIt = tree.begin<Order::PreOrder>();
      auto preEnd = tree.end<Order::PreOrder>();
      while (preIt != preEnd)
      {
        std::cout << *preIt << " ";
        ++preIt;
      }
      std::cout << std::endl;
      break;
    }
    case 6: // PostOrder
    {
      std::cout << "PostOrder: ";
      auto postIt = tree.begin<Order::PostOrder>();
      auto postEnd = tree.end<Order::PostOrder>();
      while (postIt != postEnd)
      {
        std::cout << *postIt << " ";
        ++postIt;
      }
      std::cout << std::endl;
      break;
    }
    case 7: // LevelOrder
    {
      std::cout << "LevelOrder: ";
      auto levelIt = tree.begin<Order::LevelOrder>();
      auto levelEnd = tree.end<Order::LevelOrder>();
      while (levelIt != levelEnd)
      {
        std::cout << *levelIt << " ";
        ++levelIt;
      }
      std::cout << std::endl;
      break;
    }
    case 8: // Clear
    {
      tree.~BinTree();            // Explicitly call destructor
      new (&tree) BinTree<int>(); // Reinitialize
      std::cout << "Tree cleared.\n";
      break;
    }
    case 9: // Exit
      std::cout << "Exiting program.\n";
      return 0;

    default:
      std::cout << "Invalid choice. Please enter 1-9.\n";
    }
  }
}
