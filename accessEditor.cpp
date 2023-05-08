#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string group = "Пользователи";  // Группа на которую будет распространяться защита файлов

void authorization(ifstream&);
void readFileNames(ifstream&, vector<string>&);
void mainMenu(vector<string>&);
void enableProtection(vector<string>&);
void disableProtection(vector<string>&);

int main() {
    cout << "AccessEditor v1.0.\n";
    system("chcp 1251");
    ifstream readTemplate("template.tbl");
    vector<string> fileNames;
    authorization(readTemplate);
    readFileNames(readTemplate, fileNames);
    mainMenu(fileNames);
    system("PAUSE");
    return 0;
}

// Авторизация по паролю
void authorization(ifstream& readTemplate) {
  hash<string> hashPassword;
  string inputPassword;
  size_t templatePassword;
  readTemplate >> templatePassword;
  cout << "\n\nEnter password: ";
  cin >> inputPassword;
  while (hashPassword(inputPassword) != templatePassword) {  // Сравнение хэша введеного пароля с хэшом правильного пароля
    cout << "Invalid password. Try again."
         << "\n\nEnter password: ";
    cin >> inputPassword;
  }
  cout << "Correct password.\n\n\n";
  return;
}

// Чтение имен файлов из template.tbl
void readFileNames(ifstream& readTemplate, vector<string>& fileNames) {
  string name;
  getline(readTemplate, name);
  while (!readTemplate.eof()) {  // Чтение имен пока не будет достигнут конец файла
    getline(readTemplate, name);
    fileNames.push_back(name);
  }
  readTemplate.close();
}

// Главное меню программы
void mainMenu(vector<string>& fileNames) {
  int check;
  cout << "Actions:\n"
       << "1. Enable protection\n"
       << "2. Disable protection\n"
       << "Choose an action: ";
  cin >> check;  // Выбор действия
  cout << "\n\n\n";
  if (check == 1) {
    enableProtection(fileNames);
  } else if (check == 2) {
    disableProtection(fileNames);
  } else {
    cout << "Incorrect number. Try again.";
  }
  cout << "\n\n\n";
}

// Включение защиты
void enableProtection(vector<string>& fileNames) {
  char Path[MAX_PATH];
  GetCurrentDirectory(MAX_PATH, (TCHAR*)Path);  // Получение полного пути текущего файла
  for (auto& name : fileNames) {
    cout << "icacls " + string(Path) + "\\" + name + " /deny " + group + ":F" << endl;
    string Cmd = "icacls " + string(Path) + "\\" + name + " /deny " + group + ":F";  // Команда для включения защиты
    system(Cmd.c_str());  // Выполнение команды
  }
  cout << "Protection is enabled";
  return;
}

// Включение защиты
void disableProtection(vector<string>& fileNames) {
  char Path[MAX_PATH];
  GetCurrentDirectory(MAX_PATH, (TCHAR*)Path);  // Получение полного пути текущего файла
  for (auto& name : fileNames) {
    string Cmd = "icacls " + string(Path) + "\\" + name + " /remove " + group;  // Команда для включения защиты
    cout << Cmd.c_str() << '\n';
    system(Cmd.c_str());  // Выполнение команды
  }
  cout << "Protection is disabled";
  return;
}
