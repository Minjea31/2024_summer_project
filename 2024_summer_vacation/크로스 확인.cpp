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

// �������� ū ����ǥ�� ��ǥ�� �����ϴ� �Լ�
string removeQuotesAndCommas(const string& str)
{
    string result = str;
    result.erase(remove(result.begin(), result.end(), '\"'), result.end());
    result.erase(remove(result.begin(), result.end(), ','), result.end());
    return result;
}

// ���ڿ��� double�� ��ȯ�ϴ� �Լ�
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

// n���� ��ġ�� �׷��� �̵� ����� ����ϰ� ����� �迭�� �����ϴ� �Լ�
vector<pair<string, int>> calculateMovingAverages(const vector<double>& values, const vector<string>& dates, int n)
{
    vector<pair<string, int>> movingAverages;
    if (values.size() < n)
    {
        cout << "�����Ͱ� ������� �ʽ��ϴ�." << endl;
        return movingAverages;
    }

    // �̵� ����� ����� �� �ִ� ����
    for (size_t i = 0; i <= values.size() - n; ++i)
    {
        double sum = accumulate(values.begin() + i, values.begin() + i + n, 0.0);
        double average = sum / n;
        // �ݿø��Ͽ� ������ ��ȯ
        int roundedAverage = round(average);
        // ����� ����ϴ� ������ ���� ������ ��¥�� ����Ͽ� ����� ����
        movingAverages.push_back({ dates[i], roundedAverage });
    }

    return movingAverages;
}

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
    vector<double> closeValues;
    vector<string> dates;
    int n1, n2;

    // �ܱ� �׷��� ũ�� �Է� �ޱ�
    cout << "�ܱ� �׷��� ũ�⸦ �Է��ϼ���: ";
    cin >> n1;

    // ��� �׷��� ũ�� �Է� �ޱ�
    cout << "��� �׷��� ũ�⸦ �Է��ϼ���: ";
    cin >> n2;

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

        // ū ����ǥ�� ��ǥ ���� �� double�� ��ȯ�Ͽ� ����
        close = removeQuotesAndCommas(close);

        // ������ ����ó��
        if (date.empty() || close.empty())
        {
            cerr << "�߸��� �����Ͱ� �߰ߵǾ����ϴ�: " << line << endl;
            continue;
        }

        closeValues.push_back(stringToDouble(close));
        dates.push_back(date);
    }

    inputFile.close();

    // �� �׷��� �̵� ��� ��� �� ��� ����
    vector<pair<string, int>> movingAverages1 = calculateMovingAverages(closeValues, dates, n1);
    vector<pair<string, int>> movingAverages2 = calculateMovingAverages(closeValues, dates, n2);

    // ��¥���� �� �׷��� ����� ������ map
    map<string, pair<int, int>> results;

    // �ܱ� �׷� ����� map�� ����
    for (const auto& pair : movingAverages1)
    {
        results[pair.first].first = pair.second;
    }

    // ��� �׷� ����� map�� ����
    for (const auto& pair : movingAverages2)
    {
        results[pair.first].second = pair.second;
    }

    // ���ũ�ν��� ����ũ�ν� ��¥�� ������ ����
    vector<string> goldenCrossDates;
    vector<string> deathCrossDates;

    // �� �׷��� ��� ��Ұ� �ٲ�� ��¥�� �м�
    auto prevIt = results.begin();
    auto currIt = next(prevIt);

    for (; currIt != results.end(); ++prevIt, ++currIt)
    {
        bool wasLess = prevIt->second.first < prevIt->second.second;
        bool isLess = currIt->second.first < currIt->second.second;

        if (!wasLess && isLess)
        {
            // ���ũ�ν�: �ܱ� ����� ��� ��պ��� �۴ٰ� Ŀ��
            goldenCrossDates.push_back(currIt->first);
        }
        else if (wasLess && !isLess)
        {
            // ����ũ�ν�: �ܱ� ����� ��� ��պ��� ũ�ٰ� �۾���
            deathCrossDates.push_back(currIt->first);
        }
    }

    // ��� ���
    cout << "���ũ�ν� ��¥:" << endl;
    for (const auto& date : deathCrossDates)
    {
        cout << date << endl;
    }

    cout << "����ũ�ν� ��¥:" << endl;
    for (const auto& date : goldenCrossDates)
    {
        cout << date << endl;
    }

    return 0;
}
