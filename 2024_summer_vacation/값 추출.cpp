#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() 
{
    string filePath = "C:\\Users\\kimmi\\Desktop\\삼성전자.txt";
    ifstream inputFile(filePath);

    if (!inputFile.is_open()) 
    {
        cerr << "파일을 열 수 없습니다: " << filePath << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) 
    {
        stringstream ss(line);
        string date, close, high, low;

        // 날짜 읽기
        getline(ss, date, '\t');

        // 종가 읽기
        getline(ss, close, '\t');

        // 고가 읽기
        getline(ss, high, '\t');

        // 저가 읽기
        getline(ss, low, '\t');

        // 큰 따옴표 제거
        close.erase(remove(close.begin(), close.end(), '\"'), close.end());

        // 쉼표 제거
        close.erase(remove(close.begin(), close.end(), ','), close.end());

        cout << date << "\t" << close << endl;
    }

    inputFile.close();
}
