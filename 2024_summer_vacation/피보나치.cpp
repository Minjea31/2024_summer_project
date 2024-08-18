#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>
#include <iomanip>

using namespace std;

int main()
{
    string filePath = "C:\\Users\\kimmi\\Desktop\\�ֽ�\\�Ｚ����.txt";
    ifstream inputFile(filePath);

    if (!inputFile.is_open())
    {
        cerr << "������ �� �� �����ϴ�: " << filePath << endl;
        return 1;
    }

    string inputDate;
    cout << "���� ��¥�� �Է��ϼ��� (��: 2024/05/10): ";
    cin >> inputDate;

    string line;
    int maxClose = INT_MIN;
    int minClose = INT_MAX;

    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string date, close, high, low;

        // ��¥ �б�
        getline(ss, date, '\t');

        // ���� ��¥ ������ �����͸� ó��
        if (date >= inputDate)
        {
            // ���� �б�
            getline(ss, close, '\t');

            // ū ����ǥ ����
            close.erase(remove(close.begin(), close.end(), '\"'), close.end());

            // ��ǥ ����
            close.erase(remove(close.begin(), close.end(), ','), close.end());

            // ������ ������ ��ȯ
            int closePrice = stoi(close);

            // �ִ� ���� �ּ� �� ����
            if (closePrice > maxClose)
            {
                maxClose = closePrice;
            }
            if (closePrice < minClose)
            {
                minClose = closePrice;
            }
        }
    }

    inputFile.close();

    if (maxClose == INT_MIN || minClose == INT_MAX)
    {
        cout << "���� ��¥ ������ �����͸� ã�� �� �����ϴ�." << endl;
    }
    else
    {
        // �ִ� ���� - �ּ� ���� ���
        int diff = maxClose - minClose;

        // ������ �� ���
        int high_23_6_per = maxClose - static_cast<int>(diff * 0.236);
        int high_38_2_per = maxClose - static_cast<int>(diff * 0.382);
        int high_50_per = maxClose - static_cast<int>(diff * 0.5);
        int high_61_8_per = maxClose - static_cast<int>(diff * 0.618);
        int high_78_6_per = maxClose - static_cast<int>(diff * 0.786);

        // ���
        cout << "�ִ� ����: " << maxClose << endl;
        cout << "�ּ� ����: " << minClose << endl;
        cout << "23.6%: " << high_23_6_per << endl;
        cout << "38.2%: " << high_38_2_per << endl;
        cout << "50%: " << high_50_per << endl;
        cout << "61.8%: " << high_61_8_per << endl;
        cout << "78.6%: " << high_78_6_per << endl;
    }

    return 0;
}
