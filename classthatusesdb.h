//Файл classthatusesdb.h
#pragma once

#include "dbconnection.h"
#include <string>
#include <vector>

class ClassThatUsesDB {
   DBConnection *db_;//указатель на интерфейс
public:
   //Конструктор по умолчанию
   ClassThatUsesDB() : db_(nullptr) {}

   //Конструктор с параметрами
   explicit ClassThatUsesDB(DBConnection *db) : db_(db) {}
   
   //Деструктор
   ~ClassThatUsesDB() = default;
   
   bool openConnection(const std::string &host, const std::string &user, const std::string &password);
   void useConnection(const std::string &query, std::vector<std::string> &v);
   bool closeConnection(bool b);
};
