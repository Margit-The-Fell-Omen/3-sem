#pragma once
#include "BinTree.h"
#include "FileException.h"
#include "Human.h"
#include "Member_of_commision.h"
#include "Prepod.h"
#include "Prepod_from_commision.h"
#include <fstream>
#include <string>

#define WRITE_FILE_ERROR_CODE 300

template <typename T> class FileHandler
{
private:
  std::string filename;

  // Helper method to read object from file without interactive prompts
  void readObjectFromFile(std::ifstream &file, T &obj) const
  {
    // For file reading, we need a non-interactive way to read objects
    // We'll read the data directly without using operator>>
    if constexpr (std::is_same_v<T, Human>)
    {
      std::string name, surname, birthday;
      file >> surname >> name >> birthday;
      obj.set("surname", surname);
      obj.set("name", name);
      obj.set("birthday", birthday);
    }
    else if constexpr (std::is_same_v<T, Prepod>)
    {
      std::string name, surname, birthday, degree, position, works;
      file >> surname >> name >> birthday >> degree >> position >> works;
      obj.set("surname", surname);
      obj.set("name", name);
      obj.set("birthday", birthday);
      obj.set("degree", degree);
      obj.set("position", position);
      obj.set("works", works);
    }
    else if constexpr (std::is_same_v<T, Member_of_commision>)
    {
      std::string name, surname, birthday, commision_name, biography;
      file >> surname >> name >> birthday >> commision_name >> biography;
      obj.set("surname", surname);
      obj.set("name", name);
      obj.set("birthday", birthday);
      obj.set("commision_name", commision_name);
      obj.set("biography", biography);
    }
    else if constexpr (std::is_same_v<T, Prepod_from_commision>)
    {
      std::string name, surname, birthday, degree, position, works,
          commision_name, biography, commision_works;
      file >> surname >> name >> birthday >> degree >> position >> works >>
          commision_name >> biography >> commision_works;
      obj.set("surname", surname);
      obj.set("name", name);
      obj.set("birthday", birthday);
      obj.set("degree", degree);
      obj.set("position", position);
      obj.set("works", works);
      obj.set("commision_name", commision_name);
      obj.set("biography", biography);
      obj.set("commision_works", commision_works);
    }
  }

  // Helper method to write object to file
  void writeObjectToFile(std::ofstream &file, const T &obj) const
  {
    if constexpr (std::is_same_v<T, Human>)
    {
      file << obj.get("surname") << " " << obj.get("name") << " "
           << obj.get("birthday");
    }
    else if constexpr (std::is_same_v<T, Prepod>)
    {
      file << obj.get("surname") << " " << obj.get("name") << " "
           << obj.get("birthday") << " " << obj.get("degree") << " "
           << obj.get("position") << " " << obj.get("works");
    }
    else if constexpr (std::is_same_v<T, Member_of_commision>)
    {
      file << obj.get("surname") << " " << obj.get("name") << " "
           << obj.get("birthday") << " " << obj.get("commision_name") << " "
           << obj.get("biography");
    }
    else if constexpr (std::is_same_v<T, Prepod_from_commision>)
    {
      file << obj.get("surname") << " " << obj.get("name") << " "
           << obj.get("birthday") << " " << obj.get("degree") << " "
           << obj.get("position") << " " << obj.get("works") << " "
           << obj.get("commision_name") << " " << obj.get("biography") << " "
           << obj.get("commision_works");
    }
    file << "\n";
  }

public:
  FileHandler(const std::string &fname) : filename(fname) {}

  // Write tree to file
  void writeToFile(const BinTree<T> &tree) const
  {
    std::ofstream file(filename);
    if (!file.is_open())
    {
      throw FileException("Ошибка записи файла '" + filename +
                          "': файл не удалось открыть.");
    }

    auto it = tree.template begin<Order::InOrder>();
    auto end = tree.template end<Order::InOrder>();

    while (it != end)
    {
      writeObjectToFile(file, *it);
      ++it;
    }

    if (file.fail())
    {
      throw FileException("Ошибка записи в файл '" + filename +
                          "': недостаточно места или доступ запрещен.");
    }

    file.close();
  }

  void readFromFile(BinTree<T> &tree) const
  {
    std::ifstream file(filename);
    if (!file.is_open())
    {
      throw FileException("Ошибка чтения файла '" + filename +
                          "': файл не удалось открыть.");
    }

    tree = BinTree<T>();
    T obj;

    while (file.peek() != EOF)
    {
      readObjectFromFile(file, obj);
      if (!file.fail())
      {
        tree.insert(obj);
      }
      else if (!file.eof())
      {
        throw FileException("Ошибка чтения файла '" + filename +
                            "': некорректные данные или поврежденный файл.");
      }
    }

    file.close();
  }
  // Get current filename
  std::string getFilename() const { return filename; }

  // Set new filename
  void setFilename(const std::string &newFilename) { filename = newFilename; }
};
