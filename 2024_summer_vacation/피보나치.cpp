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
    string filePath = "C:\\Users\\kimmi\\Desktop\\주식\\삼성전자.txt";
    ifstream inputFile(filePath);

    if (!inputFile.is_open())
    {
        cerr << "파일을 열 수 없습니다: " << filePath << endl;
        return 1;
    }

    string inputDate;
    cout << "기준 날짜를 입력하세요 (예: 2024/05/10): ";
    cin >> inputDate;

    string line;
    int maxClose = INT_MIN;
    int minClose = INT_MAX;

    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string date, close, high, low;

        // 날짜 읽기
        getline(ss, date, '\t');

        // 기준 날짜 이후의 데이터만 처리
        if (date >= inputDate)
        {
            // 종가 읽기
            getline(ss, close, '\t');

            // 큰 따옴표 제거
            close.erase(remove(close.begin(), close.end(), '\"'), close.end());

            // 쉼표 제거
            close.erase(remove(close.begin(), close.end(), ','), close.end());

            // 종가를 정수로 변환
            int closePrice = stoi(close);

            // 최대 값과 최소 값 갱신
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
        cout << "기준 날짜 이후의 데이터를 찾을 수 없습니다." << endl;
    }
    else
    {
        // 최대 종가 - 최소 종가 계산
        int diff = maxClose - minClose;

        // 비율별 값 계산
        int high_23_6_per = maxClose - static_cast<int>(diff * 0.236);
        int high_38_2_per = maxClose - static_cast<int>(diff * 0.382);
        int high_50_per = maxClose - static_cast<int>(diff * 0.5);
        int high_61_8_per = maxClose - static_cast<int>(diff * 0.618);
        int high_78_6_per = maxClose - static_cast<int>(diff * 0.786);

        // 출력
        cout << "최대 종가: " << maxClose << endl;
        cout << "최소 종가: " << minClose << endl;
        cout << "23.6%: " << high_23_6_per << endl;
        cout << "38.2%: " << high_38_2_per << endl;
        cout << "50%: " << high_50_per << endl;
        cout << "61.8%: " << high_61_8_per << endl;
        cout << "78.6%: " << high_78_6_per << endl;
    }

    return 0;
}
