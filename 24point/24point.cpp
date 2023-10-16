/*#include <iostream>
#include <cmath>
#include <string>
using namespace std;

const double Threshold = 1E-6;
const int CardsNumber = 4;
const int ResultValue = 24;
double number[CardsNumber];
string result[CardsNumber];

bool PointsGame(int n)
{
	if (n == 1)
	{
		// ���ڸ�����������о�����������һ����С����1E-6�����ݲ�ֵ
		// ����2.6������������ν�������ת��Ϊ����������
		if (fabs(number[0] - ResultValue) < Threshold)//�������24
		{
			cout << result[0] << endl;//������ʽ
			return true;
		}
		else
		{
			return false;
		}
	}

	for (int i = 0; i < n; i++)//��һ����(����ʱ������������滻)
	{
		for (int j = i + 1; j < n; j++)//�ڶ�����(����ʱ�����һ�����滻)
		{
			
			double a, b;//��ż������
			string expa, expb;//��ű��ʽ��������

			a = number[i];
			b = number[j];
			number[j] = number[n - 1];//ȥ���ڶ�����

			expa = result[i];
			expb = result[j];
			result[j] = result[n - 1];//���ʽȥ��

			result[i] = '(' + expa + '+' + expb + ')';
			number[i] = a + b;//ȥ����һ����
			if (PointsGame(n - 1))
				return true;

			result[i] = '(' + expa + '-' + expb + ')';
			number[i] = a - b;
			if (PointsGame(n - 1))
				return true;

			result[i] = '(' + expb + '-' + expa + ')';
			number[i] = b - a;
			if (PointsGame(n - 1))
				return true;

			result[i] = '(' + expa + '*' + expb + ')';
			number[i] = a * b;
			if (PointsGame(n - 1))
				return true;

			if (b != 0)
			{
				result[i] = '(' + expa + '/' + expb + ')';
				number[i] = a / b;
				if (PointsGame(n - 1))
					return true;
			}
			if (a != 0)
			{
				result[i] = '(' + expb + '/' + expa + ')';
				number[i] = b / a;
				if (PointsGame(n - 1))
					return true;
			}

			number[i] = a;//������ѭ���Ľ������������������һ����
			number[j] = b;
			result[i] = expa;
			result[j] = expb;
		}
	}
	return false;
}

int main()
{
	int x;
	for (int i = 0; i < CardsNumber; i++)
	{
		char buffer[20];
		cout << "the " << i << "th number:";
		cin >> x;
		number[i] = x;
		_itoa_s(x, buffer, 10);
		result[i] = buffer;
	}
	if (PointsGame(CardsNumber))
	{
		cout << "Success." << endl;
	}
	else
	{
		cout << "Fail." << endl;
	}
}*/


#include <iostream>
#include <vector>
#include <string>
using namespace std;

const double TARGET = 24;
const double EPSILON = 1e-6;

bool isCloseEnough(double a, double b) {
	return std::abs(a - b) < EPSILON;
}

bool solve24(std::vector<double>& nums,std::vector<string >& strRets) 
{
	if (nums.size() == 1) {
		 bool blequ = isCloseEnough(nums[0], TARGET);
		 if (blequ)
		 {
			 cout << strRets[0] << endl;
		 }
		 return blequ;
	}

	int n = nums.size();
	for (int i = 0; i < n; ++i) 
	{
		for (int j = 0; j < n; ++j) 
		{
			if (i != j) 
			{
				std::vector<double> next_nums;
				std::vector<string> next_string;
				for (int k = 0; k < n; ++k) 
				{
					if (k != i && k != j) 
					{
						next_nums.push_back(nums[k]);

						next_string.push_back(strRets[k]);
						
						
					}
				}
				

				for (int op = 0; op < 4; ++op) 
				{
					string strtmp;
					bool blpush = false;
					if (op == 0) { // addition
						next_nums.push_back(nums[i] + nums[j]);
						strtmp = "(" + strRets[i] + " + " + strRets[j] + ")";
						blpush = true;
					}
					else if (op == 1) { // subtraction
						next_nums.push_back(nums[i] - nums[j]);
						strtmp = "(" + strRets[i] + " - " + strRets[j] + ")";
						blpush = true;
					}
					else if (op == 2) { // multiplication
						next_nums.push_back(nums[i] * nums[j]);
						strtmp = "(" + strRets[i] + " * " + strRets[j] + ")";
						blpush = true;
					}
					else if (op == 3 && !isCloseEnough(nums[j], 0)) { // division
						next_nums.push_back(nums[i] / nums[j]);
						strtmp = "(" + strRets[i] + " / " + strRets[j] + ")";
						blpush = true;
					}

					if (!blpush)
					{
						continue;
					}

					next_string.push_back(strtmp);

					//strRet += strtmp;
				
					if (solve24(next_nums, next_string)) {
						return true;
					}

					next_string.pop_back();
					//strRet = strRet.substr(0, strRet.size() - strtmp.size());
					next_nums.pop_back();
				}
			}
		}
	}

	return false;
}

int main() {
	std::vector<double> nums = { 2, 2, 13, 12 }; // Example numbers
	std::vector<string>strRets;
	for (int i = 0; i < nums.size(); ++i)
	{
		strRets.push_back(to_string((int)nums[i]));
	}
	if (solve24(nums, strRets))
	{
		std::cout << "There exists a solution for 24!" << std::endl;
	}
	else 
	{
		std::cout << "No solution found for 24." << std::endl;
	}

	return 0;
}