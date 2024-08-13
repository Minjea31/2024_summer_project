#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

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
    return stod(str);
}

// n���� ��ġ�� �׷��� �̵� ����� ����ϰ� ���� �ֱ� ��¥�� ��Ī�ϴ� �Լ�
void calculateMovingAverages(const vector<double>& values, const vector<string>& dates, int n) 
{
    if (values.size() < n) 
    {
        cout << "�����Ͱ� ������� �ʽ��ϴ�." << endl;
        return;
    }

    for (int i = values.size() - n; i >= 0; --i) 
    {
        double sum = accumulate(values.begin() + i, values.begin() + i + n, 0.0);
        double average = sum / n;
        // �ݿø��Ͽ� ������ ��ȯ
        int roundedAverage = round(average);
        cout << "���(" << dates[i] << "): " << roundedAverage << endl;
    }
}

int main() {
    // ���� ��θ� ���� �Է��ϼ���
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
    int n = 120; // �׷��� ũ��

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
        closeValues.push_back(stringToDouble(close));

        dates.push_back(date);
    }

    inputFile.close();

    // ������ n���� ��ġ�� �׷��� �̵� ��� ��� �� ��¥ ��Ī
    calculateMovingAverages(closeValues, dates, n);

    return 0;
}
