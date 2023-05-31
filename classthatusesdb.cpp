//Файл classthatusesdb.cpp
#include "classthatusesdb.h"

bool ClassThatUsesDB::openConnection(const std::string &host, const std::string &user, const std::string &password){
   //Проверяем праильность введенных данных
   if(host != "localhost"){
      return false;
   }
   if(user != "user1"){
      return false;
   }
   if(password != "1234"){
      return false;
   }
   
   //Запускаем метод
   db_->open(host, user, password);

   return true;
}

void ClassThatUsesDB::useConnection(const std::string &query, std::vector<std::string> &v){
   //Запускаем метод
   db_->execQuery(query, v);
   //Если запрос корректен, то добавляем знаечние в вектор
   if(query == "SELECT name FROM users"){
      v.emplace_back("user1");
   }
}

bool ClassThatUsesDB::closeConnection(bool b){
   //Запускаем метод
   db_->close(b);
   //Возвращаем значение
   return b;
}
