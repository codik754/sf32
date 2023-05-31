//Файл mockdbconnection.h
#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "dbconnection.h"

//Мок-класс для интерфейса DBConnection
class MockDBConnection : public DBConnection{
public:
   //Определяем МОК-методы
   MOCK_METHOD(bool, open, (const std::string &host, const std::string &user, const std::string &password), (override));
   MOCK_METHOD(bool, close, (bool), (override));
   MOCK_METHOD(void, execQuery, (const std::string &query, std::vector<std::string> &v), (override));
};
