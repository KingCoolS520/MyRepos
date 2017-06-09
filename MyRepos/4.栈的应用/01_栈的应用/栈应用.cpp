#include <iostream>
#include <stack>
using namespace std;


bool isNumber(char c)
{
	return (c >= '0' && c <= '9');
}

// 输出
void outPut(char c)
{
	if (c != '\0')
	{
		cout << c;
	}
}

// 优先级
int priority(char c)
{
	int ret = 0;
	switch (c)
	{
	case '+':
	case '-':
		ret = 1;
		break;
	case '*':
	case '/':
		ret = 2;
		break;
	default:
		break;
	}
	return ret;
}

// 是否是运算符
bool isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isLeft(char c)
{
	return (c == '(');
}

bool isRight(char c)
{
	return (c == ')');
}

// 中缀转后缀表达式
void transform(const char *array)
{
	int i = 0;
	stack<char> st;
	while (array[i] != '\0')
	{
		// 判断是不是数字
		if (isNumber(array[i]))
		{
			// 输出字符
			outPut(array[i]);
		}
		// 运算符
		else if (isOperator(array[i]))
		{
			// 空栈
			if (!st.empty())
			{
				// 栈顶符号优先级不低
				while (!st.empty() && priority(st.top()) >= priority(array[i]))
				{
					// 输出
					outPut(st.top());
					// 弹出优先级>=的符号
					st.pop();
				}
			}
			// 符号进栈
			st.push(array[i]);
		}
		// 左括号
		else if (isLeft(array[i]))
		{
			// 进栈
			st.push(array[i]);
		}
		// 右括号
		else if (isRight(array[i]))
		{
			// 判断栈顶是不是左括号
			while (!isLeft(st.top()))
			{
				// 输出栈顶元素
				outPut(st.top());
				// 弹出栈顶元素
				st.pop();
			}
			// 弹出左括号
			st.pop();
		}
		else
		{
			cout << "error" << endl;
			break;
		}
		i++;
	}

	// 遍历结束
	if (array[i] == '\0')
	{
		while (!st.empty())
		{
			outPut(st.top());
			st.pop();
		}
	}
	else
	{
		cout << "没有遍历完成!!!" << endl;
	}
	cout << endl;
}

int express(int left, int right, char op)
{
	switch (op)
	{
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left * right;
	case '/':
		return left / right;
	default:
		break;
	}
	return -1;
}

// 后缀表达式的计算
int compute(const char* array)
{
	int i = 0;
	stack<int> st;
	while (array[i])
	{
		// 数字
		if (isNumber(array[i]))
		{
			// 进栈
			st.push(array[i] - '0');
		}
		// 符号
		else if (isOperator(array[i]))
		{
			// 右操作数
			int right = st.top();
			st.pop();
			// 左操作数
			int left = st.top();
			st.pop();
			// 计算
			int res = express(left, right, array[i]);
			// 结果压栈
			st.push(res);
		}
		else
		{
			cout << "error!!!!" << endl;
			break;
		}
		i++;
	}

	if (array[i] == '\0' && st.size() == 1)
	{
		return st.top();
	}
	// 错误值
	return -10000;
}

int main()
{
	transform("8+(3-1)*5");

	int resault = compute("831-5*+");
	cout << resault << endl;

	return 0;
}