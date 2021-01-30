#include "simpleDB.h"
using namespace std;

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>         // EXIT_...
#include <windows.h>        // GetCommandLineW, CommandLineToArgvW
#include <memory>
#include <iostream>
#include <locale>
#include <string>
#include <codecvt>

class Buf_out: public std::stringbuf {
 public:
 int sync() override {
 fputs( str().c_str(), stdout );
 str( "" );
 return 0;
 }
};

class Buf_in: public std::stringbuf {
 public:
 int sync() override {
     char s[80];
fgets( s, sizeof (str()), stdin );
 str( "" );
 return 0;
 }
};






//int wmain(int argc, wchar_t * argv[]){
    int main(){
//setlocale(LC_ALL, "");
//        _setmode(_fileno(stdout), _O_U8TEXT);
//        _setmode(_fileno(stdin), _O_U8TEXT);
//        _setmode(_fileno(stderr), _O_U8TEXT);

//        std::ios_base::sync_with_stdio(false);

//        std::locale utf8( std::locale(), new std::codecvt_utf8_utf16<wchar_t> );
//        std::wcout.imbue(utf8);

//        std::wstring w(L"Bilişim Sistemleri Mühendisliğine Giriş");
//        std::wcout << w << '\n';


//        system("mode con cols=100 lines=50"); //размер окна, вывод нужного количества строк в консоль (видимых)
//           HANDLE  hout = GetStdHandle(STD_OUTPUT_HANDLE);
//           COORD  size{ 100,100 };//символов строки, строк (если больше чем видимых, скрываются под ползунком прокрутки)
//           SetConsoleScreenBufferSize(hout, size);//размер буфера
//           ////////////////////Меняем шрифт для отображения символов Unicode, можно пропустить - если у вас установлен нужный
//           CONSOLE_FONT_INFOEX cfi; //https://docs.microsoft.com/en-us/windows/console/console-font-infoex
//           cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
//           cfi.nFont = 0;
//           cfi.dwFontSize.X = 8;
//           cfi.dwFontSize.Y = 14;
//           cfi.FontFamily = FF_DONTCARE;
//           cfi.FontWeight = FW_NORMAL;//400;
//           wcscpy_s(cfi.FaceName, L"Lucida Console");
//           SetCurrentConsoleFontEx(hout, false, &cfi);
//           ////////////////////

//           std::wcout <<L"Unicode -- English -- Русский -- Ελληνικά -- Español." << std::endl;
//               // или
//               wprintf(L"%s", L"Unicode -- English -- Русский -- Ελληνικά -- Español.\n");





 SetConsoleOutputCP(CP_UTF8);
 Buf_out bufout;
 std::cout.rdbuf( &bufout );

 string oper;
 while (1) {
  cout << "1 - Просмотр существующиx записей:\n"
       << "2 - Ввод новой записи:\n"
       << "3 - Редактирование существующей записи:\n"
       << "4 - Удаление записи:\n"
       << "5 - Завершить работу:\n\n"
       << "Введите операцию: "<<flush;
  cout<<endl;
  cin >> oper;
  regex regexpr("[123456]");
  if (regex_match(oper, regexpr)) {
   if (oper == "1") view_data();
   if (oper == "2") input_data();
   if (oper == "3") edit_data();
   if (oper == "4") remove_data();
   if (oper == "5") return 0;
  } else {
 cout << "Повторите ввод  "<<flush;
 cout<<endl;
    }
 }
}
