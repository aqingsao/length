
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef map<string, double> Str2Dbl;
typedef vector<string> StrVec;


void   GetPluralForm(const string& strSingluar, StrVec& strVec);
void   AddRadixConversionRule(const string& strLine, Str2Dbl& radix2Val);
double ParseFormular(const string& strFormular, Str2Dbl& radix2Val);

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
		outf << setiosflags(ios::fixed) << setprecision(2) << dResult << " m\n";
	}

	outf.close();
	inf.close();

	return 0;
}


void GetPluralForm(const string& strSingluar, StrVec& strVec)
{
	strVec.clear();
	// special treatment for FOOT/INCH/MICRON
	if (strSingluar == "foot")
		strVec.push_back("feet");
	else if (strSingluar == "inch")
		strVec.push_back("inches");
	else if (strSingluar == "micron")
	{
		strVec.push_back("microns");
		strVec.push_back("micra");
	}
	else
		strVec.push_back(strSingluar + "s");
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
	StrVec vstrPlurals;
	GetPluralForm(strLRadix, vstrPlurals);
	for (int i = 0; i < vstrPlurals.size(); i++)
		radix2Val[ vstrPlurals[i] ] = dRVal;
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
