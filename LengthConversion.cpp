#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

typedef map<string, double> Str2Dbl;

string GetPluralForm(const string& strSingluar)
{
	// special treatment for FOOT
	if (strSingluar == "foot")
		return "feet";

	size_t pos = strSingluar.find("ch");
	if ((pos != string::npos) &&
		(pos == strSingluar.length() - 2))
		return (strSingluar + "es");
	else
		return (strSingluar + "s");
}

void AddRadixConversionRule(const string& strLine, Str2Dbl& radix2Val)
{
	stringstream ss;
	ss << strLine;

	double dLVal, dRVal;
	string strLRadix, strRRadix, strEqual;
	ss >> dLVal >> strLRadix >> strEqual >> dRVal >> strRRadix;
	// singluar form val
	radix2Val[strLRadix] = dRVal;
	// also set its plural formal val
	string strPlural = GetPluralForm(strLRadix);
	radix2Val[strPlural] = dRVal;
}

double ParseFormular(const string& strFormular, Str2Dbl& radix2Val)
{
	stringstream ss;
	ss << strFormular;

	double dResult = 0; // init state
	string strOp = ""; // init state
	double dVal;
	string strRadix;
	do {
		ss >> dVal >> strRadix;
		// only the first operand may encounter empty operator
		if (strOp == "+" || strOp == "")
			dResult += dVal * radix2Val[strRadix];
		else
			dResult -= dVal * radix2Val[strRadix];
		// reset op
		strOp.clear();
		ss >> strOp;
	} while (!strOp.empty());

	return dResult;
}

int main()
{
	fstream inf("input.txt", ios::in);
	if (!inf) return -1;
	// read in rules and store 
	string strLine;
	Str2Dbl radix2Val;
	while (getline(inf, strLine))
	{
		if (!strLine.empty())
			AddRadixConversionRule(strLine, radix2Val);
		else
			break;
	}
	
	fstream outf("output.txt", ios::out);
	if (!outf) return -1;
	// header lines
	outf << "squalfof@gmail.com\n";
	outf << "\n";
	// read in formular and calc
	while (getline(inf, strLine))
	{
		double dResult = ParseFormular(strLine, radix2Val);
		outf << dResult << " m\n";
	}

	outf.close();
	inf.close();

	return 0;
}
