#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() 
{
    string filePath = "C:\\Users\\kimmi\\Desktop\\�Ｚ����.txt";
    ifstream inputFile(filePath);

    if (!inputFile.is_open()) 
    {
        cerr << "������ �� �� �����ϴ�: " << filePath << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) 
    {
        stringstream ss(line);
        string date, close, high, low;

        // ��¥ �б�
        getline(ss, date, '\t');

        // ���� �б�
        getline(ss, close, '\t');

        // �� �б�
        getline(ss, high, '\t');

        // ���� �б�
        getline(ss, low, '\t');

        // ū ����ǥ ����
        close.erase(remove(close.begin(), close.end(), '\"'), close.end());

        // ��ǥ ����
        close.erase(remove(close.begin(), close.end(), ','), close.end());

        cout << date << "\t" << close << endl;
    }

    inputFile.close();
}
