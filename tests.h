//Файл tests.h
#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <iostream>
#include "mockdbconnection.h"
#include "classthatusesdb.h"

//Класс для тестирования
class Tests : public ::testing::Test{
protected:
   ClassThatUsesDB *obj_;//объект класса для тестирования
   MockDBConnection *mobj_;//мок-объект

   //Фикстура: создаем объект с мок-объектом
   void SetUp(){
      std::cout << "Test fixture is running" << std::endl;
      //Создаем объект
      mobj_ = new MockDBConnection;
      obj_ = new ClassThatUsesDB(mobj_);
   }

   //Тирдаун: очищаем ресурсы
   void TearDown(){
      std::cout << "Test teardown is running" << std::endl;
      delete mobj_;
      delete obj_; 
   }
};

//Тест-кейс 1
//Для метода openConnection() класса ClassThatUsesDB
//с корректным хостом, логином и паролем
TEST_F(Tests, testcase1){
   //Ожидаем, что метод open() будет запущен один раз
   EXPECT_CALL(*mobj_, open).Times(::testing::AtLeast(1));
   //Запускаем метод. Ожидаем, что вернется true 
   EXPECT_EQ(obj_->openConnection("localhost", "user1", "1234"), true);
}

//Тест-кейс 2
//Для метода openConnection() класса ClassThatUsesDB
//с некорректным хостом
TEST_F(Tests, testcase2){
   //Ожидаем, что метод open() будет запущен 0 раз
   EXPECT_CALL(*mobj_, open).Times(::testing::AtLeast(0));
   //Запускаем метод. Ожидаем, что вернется false 
   EXPECT_EQ(obj_->openConnection("localhost1", "user1", "1234"), false);
}

//Тест-кейс 3
//Для метода openConnection() класса ClassThatUsesDB
//с некорректным логином
TEST_F(Tests, testcase3){
   //Ожидаем, что метод open() будет запущен 0 раз
   EXPECT_CALL(*mobj_, open).Times(::testing::AtLeast(0));
   //Запускаем метод. Ожидаем, что вернется false
   EXPECT_EQ(obj_->openConnection("localhost", "user2", "1234"), false);
}

//Тест-кейс 4
//Для метода openConnection() класса ClassThatUsesDB
//с некорректным паролем
TEST_F(Tests, testcase4){
   //Ожидаем, что метод open() будет запущен 0 раз
   EXPECT_CALL(*mobj_, open).Times(::testing::AtLeast(0));
   //Запускаем метод. Ожидаем, что вернется false
   EXPECT_EQ(obj_->openConnection("localhost", "user", "12345"), false);
}

//Тест-кейс 5
//Для метода closeConnection() класса ClassThatUsesDB
//с успешным закрытием соедиенения
TEST_F(Tests, testcase5){
   //Ожидаем, что метод close() будет запущен 1 раз
   EXPECT_CALL(*mobj_, close).Times(::testing::AtLeast(1));
   //Запускаем метод. Ожидаем, что вернется true 
   EXPECT_EQ(obj_->closeConnection(true), true);
}

//Тест-кейс 6
//Для метода closeConnection() класса ClassThatUsesDB
//с неуспешным закрытием соедиенения
TEST_F(Tests, testcase6){
   //Ожидаем, что метод close() будет запущен 1 раз
   EXPECT_CALL(*mobj_, close).Times(::testing::AtLeast(1));
   //Запускаем метод. Ожидаем, что вернется false
   EXPECT_EQ(obj_->closeConnection(false), false);
}

//Тест-кейс 7
//Для метода useConnection() класса ClassThatUsesDB
//с успешнам запросом
TEST_F(Tests, testcase7){
   //Ожидаем, что метод execQuery() будет запущен 1 раз
   EXPECT_CALL(*mobj_, execQuery).Times(::testing::AtLeast(1));
   //Создаем вектор
   std::vector<std::string> v;
   obj_->useConnection("SELECT name FROM users", v);
   //Количество полученых знаечений больше 0
   EXPECT_TRUE(v.size() > 0);
}

//Тест-кейс 8
//Для метода useConnection() класса ClassThatUsesDB
//с неуспешнам запросом
TEST_F(Tests, testcase8){
   //Ожидаем, что метод execQuery() будет запущен 1 раз
   EXPECT_CALL(*mobj_, execQuery).Times(::testing::AtLeast(1));
   //Создаем вектор
   std::vector<std::string> v;
   obj_->useConnection("SELECT nameandother FROM users", v);
   //Количество полученых значений равно 0
   EXPECT_EQ(v.size(), 0);
}
