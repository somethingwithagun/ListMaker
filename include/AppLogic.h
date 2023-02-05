#pragma once
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <ctime>
#include <filesystem>
#include <vector>

int Magic(std::string InFilePath, std::string aOrderType, std::string aSortType, std::string aname, std::string aOutPath);
void CheckIsPrev(std::string aOrderType, std::string aSortType);
int Numerate(std::string InFilePath);
void Order();
void Sort(std::string aSortType);
void Name(std::string aname);
void Print(std::string aOutFilePath);
const std::string currentDateTime();
bool IsKeyWord(std::string KeyWord);
void Log();
std::string SetPreviousValue(std::string type);
std::string AnExt(std::string x);