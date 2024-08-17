#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>

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
    try
    {
        return stod(str);
    }
    catch (const invalid_argument&)
    {
        cerr << "Invalid argument for stod: " << str << endl;
        return 0.0;
    }
    catch (const out_of_range&)
    {
        cerr << "Out of range argument for stod: " << str << endl;
        return 0.0;
    }
}

// n개씩 겹치는 그룹의 이동 평균을 계산하고 결과를 배열에 저장하는 함수
vector<pair<string, int>> calculateMovingAverages(const vector<double>& values, const vector<string>& dates, int n)
{
    vector<pair<string, int>> movingAverages;
    if (values.size() < n)
    {
        cout << "데이터가 충분하지 않습니다." << endl;
        return movingAverages;
    }

    // 이동 평균을 계산할 수 있는 범위
    for (size_t i = 0; i <= values.size() - n; ++i)
    {
        double sum = accumulate(values.begin() + i, values.begin() + i + n, 0.0);
        double average = sum / n;
        // 반올림하여 정수로 변환
        int roundedAverage = round(average);
        // 평균을 계산하는 구간의 가장 오래된 날짜를 사용하여 결과를 저장
        movingAverages.push_back({ dates[i], roundedAverage });
    }

    return movingAverages;
}

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
    vector<double> closeValues;
    vector<string> dates;
    int n1, n2;

    // 단기 그룹의 크기 입력 받기
    cout << "단기 그룹의 크기를 입력하세요: ";
    cin >> n1;

    // 장기 그룹의 크기 입력 받기
    cout << "장기 그룹의 크기를 입력하세요: ";
    cin >> n2;

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

        // 데이터 예외처리
        if (date.empty() || close.empty())
        {
            cerr << "잘못된 데이터가 발견되었습니다: " << line << endl;
            continue;
        }

        closeValues.push_back(stringToDouble(close));
        dates.push_back(date);
    }

    inputFile.close();

    // 두 그룹의 이동 평균 계산 및 결과 저장
    vector<pair<string, int>> movingAverages1 = calculateMovingAverages(closeValues, dates, n1);
    vector<pair<string, int>> movingAverages2 = calculateMovingAverages(closeValues, dates, n2);

    // 날짜별로 두 그룹의 평균을 저장할 map
    map<string, pair<int, int>> results;

    // 단기 그룹 결과를 map에 저장
    for (const auto& pair : movingAverages1)
    {
        results[pair.first].first = pair.second;
    }

    // 장기 그룹 결과를 map에 저장
    for (const auto& pair : movingAverages2)
    {
        results[pair.first].second = pair.second;
    }

    // 골든크로스와 데드크로스 날짜를 저장할 벡터
    vector<string> goldenCrossDates;
    vector<string> deathCrossDates;

    // 두 그룹의 평균 대소가 바뀌는 날짜를 분석
    auto prevIt = results.begin();
    auto currIt = next(prevIt);

    for (; currIt != results.end(); ++prevIt, ++currIt)
    {
        bool wasLess = prevIt->second.first < prevIt->second.second;
        bool isLess = currIt->second.first < currIt->second.second;

        if (!wasLess && isLess)
        {
            // 골든크로스: 단기 평균이 장기 평균보다 작다가 커짐
            goldenCrossDates.push_back(currIt->first);
        }
        else if (wasLess && !isLess)
        {
            // 데드크로스: 단기 평균이 장기 평균보다 크다가 작아짐
            deathCrossDates.push_back(currIt->first);
        }
    }

    // 결과 출력
    cout << "골든크로스 날짜:" << endl;
    for (const auto& date : deathCrossDates)
    {
        cout << date << endl;
    }

    cout << "데드크로스 날짜:" << endl;
    for (const auto& date : goldenCrossDates)
    {
        cout << date << endl;
    }

    return 0;
}
