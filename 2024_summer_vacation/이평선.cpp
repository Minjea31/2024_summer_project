#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

// 종가에서 큰 따옴표와 쉼표를 제거하는 함수
string removeQuotesAndCommas(const string& str) 
{
    string result = str;
    result.erase(remove(result.begin(), result.end(), '\"'), result.end());
    result.erase(remove(result.begin(), result.end(), ','), result.end());
    return result;
}

// 문자열을 double로 변환하는 함수
double stringToDouble(const string& str) 
{
    return stod(str);
}

// n개씩 겹치는 그룹의 이동 평균을 계산하고 가장 최근 날짜와 매칭하는 함수
void calculateMovingAverages(const vector<double>& values, const vector<string>& dates, int n) 
{
    if (values.size() < n) 
    {
        cout << "데이터가 충분하지 않습니다." << endl;
        return;
    }

    for (int i = values.size() - n; i >= 0; --i) 
    {
        double sum = accumulate(values.begin() + i, values.begin() + i + n, 0.0);
        double average = sum / n;
        // 반올림하여 정수로 변환
        int roundedAverage = round(average);
        cout << "평균(" << dates[i] << "): " << roundedAverage << endl;
    }
}

int main() {
    // 파일 경로를 직접 입력하세요
    string filePath = "C:\\Users\\kimmi\\Desktop\\삼성전자.txt";
    ifstream inputFile(filePath);

    if (!inputFile.is_open()) 
    {
        cerr << "파일을 열 수 없습니다: " << filePath << endl;
        return 1;
    }

    string line;
    vector<double> closeValues;
    vector<string> dates;
    int n = 120; // 그룹의 크기

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

        // 큰 따옴표와 쉼표 제거 및 double로 변환하여 저장
        close = removeQuotesAndCommas(close);
        closeValues.push_back(stringToDouble(close));

        dates.push_back(date);
    }

    inputFile.close();

    // 종가의 n개씩 겹치는 그룹의 이동 평균 계산 및 날짜 매칭
    calculateMovingAverages(closeValues, dates, n);

    return 0;
}
