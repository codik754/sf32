//Файл dbconnection.h
#pragma once

#include <string>
#include <vector>

//Интерфейс
class DBConnection{
public:
   //Деструктор
   virtual ~DBConnection() = default;

   //Виртуальные методы
   virtual bool open(const std::string &host, const std::string &user, const std::string &password) = 0;
   virtual bool close(bool b) = 0;
   virtual void execQuery(const std::string &query, std::vector<std::string> &v) = 0;
};
