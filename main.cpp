#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct RGB
{
	int RED;
	int GREEN;
	int BLUE;
};

enum class BlindnessType
{
	Deuteranopia, //MEANING: hard to see reds, appearing brown or black, purple/blue also look red/black
	Protanopia, //MEANING: hard to distinguish between red-green, as well as orange-brown-yellow
	Tritanopia, //MEANING: hard to distinguish between blue-green, as well as between yellow-red
	Default //MEANING: no blindness, default
};

struct TypeReturn
{
	vector<BlindnessType> TYPES;
	vector<int> DIFF;
};

string CheckColor(int red, int green, int blue);
bool CheckWhite();
bool CheckBlack();
int ClampInt(int base, int min, int max);
void AskInput(RGB& input);
void ReturnColors();
TypeReturn GetBlindType();
string GetEnumName(BlindnessType typeinput);

RGB clr;
RGB clr2;

int checkamt = 0;
vector<string> colors;

int main()
{
	AskInput(clr);
	return 0;
}

string CheckColor(int red, int green, int blue)
{
	if ((red - green) > 50 && (red - blue) > 50 && !CheckBlack() && !CheckWhite())
	{
		return "Red";
	}
	else if ((green - red) > 50 && (green - blue) > 50 && !CheckBlack() && !CheckWhite())
	{
		return "Green";
	}
	else if ((blue - red) > 50 && (blue - green) > 50 && !CheckBlack() && !CheckWhite())
	{
		return "Blue";
	}
	else if ((red - green) < 50 && (red - blue) > 50 && !CheckBlack() && !CheckWhite())
	{
		return "Yellow";
	}
	else if ((green - red) > 50 && (green - blue) < 50 && !CheckBlack() && !CheckWhite())
	{
		return "Cyan";
	}
	else if ((blue - red) < 50 && (blue - green) > 50 && !CheckBlack() && !CheckWhite())
	{
		return "Pink";
	}
	else if (CheckBlack())
	{
		return "Black";
	}
	else if (CheckWhite())
	{
		return "White";
	}
	else
	{
		return "White";
	}
}

bool CheckWhite()
{
	if (clr.RED >= 224 && clr.GREEN >= 224 && clr.BLUE >= 224)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CheckBlack()
{
	if (clr.RED <= 32 && clr.GREEN <= 32 && clr.BLUE <= 32)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int ClampInt(int base, int min, int max)
{
	if (base > max)
	{
		return max;
	}
	else if (base < min)
	{
		return min;
	}
	else
	{
		return base;
	}
}

void AskInput(RGB& inputtype)
{
	if (checkamt == 1)
	{
		cout << "Please input your 2nd color code in RGB!\n";
	}
	else
	{
		cout << "Please input your 1st color code in RGB!\n";
	}
	cin >> inputtype.RED >> inputtype.GREEN >> inputtype.BLUE;
	inputtype.RED = ClampInt(inputtype.RED, 0, 255);
	inputtype.GREEN = ClampInt(inputtype.GREEN, 0, 255);
	inputtype.BLUE = ClampInt(inputtype.BLUE, 0, 255);
	cout << "RED: " << inputtype.RED << " GREEN: " << inputtype.GREEN << " BLUE: " << inputtype.BLUE << endl;
	cout << "Your Color is " << CheckColor(inputtype.RED, inputtype.GREEN, inputtype.BLUE) << "!\n";
	colors.push_back(CheckColor(inputtype.RED, inputtype.GREEN, inputtype.BLUE));
	checkamt++;
	if (checkamt < 2)
	{
		AskInput(clr2);
	}
	else
	{
		ReturnColors();
	}
}

void ReturnColors()
{
	if (GetBlindType().TYPES.empty())
	{
		cout << "Most people with common color blindness should be able to see your colors just fine!\n";
	}
	else
	{
		cout << "Your colors may be hard to see for those with the following Color Blindnesses:\n";
		for (BlindnessType typeouter : GetBlindType().TYPES)
		{
			cout << GetEnumName(typeouter) << "\n";
		}
	}
	cout << "The difference between your colors is:\n";
	for (int numout : GetBlindType().DIFF)
	{
		cout << numout << " ";
	}
	return;
}

TypeReturn GetBlindType()
{
	TypeReturn tempreturn;
	if (colors.at(0) == "Red" || colors.at(1) == "Red" || colors.at(0) == "Pink" || colors.at(1) == "Pink")
	{
		tempreturn.TYPES.push_back(BlindnessType::Deuteranopia);
	}
	if (colors.at(0) == "Red" || colors.at(1) == "Red" || colors.at(0) == "Green" || colors.at(1) == "Green" || colors.at(0) == "Yellow" || colors.at(1) == "Yellow")
	{
		tempreturn.TYPES.push_back(BlindnessType::Protanopia);
	}
	if (colors.at(0) == "Green" || colors.at(1) == "Green" || colors.at(0) == "Yellow" || colors.at(1) == "Yellow")
	{
		tempreturn.TYPES.push_back(BlindnessType::Tritanopia);
	}
	tempreturn.DIFF.push_back(clr.RED - clr2.RED);
	tempreturn.DIFF.push_back(clr.GREEN - clr2.GREEN);
	tempreturn.DIFF.push_back(clr.BLUE - clr2.BLUE);
	return tempreturn;
}

string GetEnumName(BlindnessType typeinput)
{
	switch (typeinput)
	{
		case BlindnessType::Default:
			return "Default";
			break;
		case BlindnessType::Deuteranopia:
			return "Deuteranopia";
			break;
		case BlindnessType::Protanopia:
			return "Protanopia";
			break;
		case BlindnessType::Tritanopia:
			return "Tritanopia";
			break;
		default:
			return "Default";
			break;
	}
}
