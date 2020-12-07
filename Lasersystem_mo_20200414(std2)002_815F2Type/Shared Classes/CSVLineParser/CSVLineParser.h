#pragma once

#include <vector>
#include <string>
using namespace std;

class CCSVColumn
{
public:
	CCSVColumn(string sDisplay);
	CCSVColumn(string sActual, string sDisplay): m_sActual(sActual), m_sDisplay(sDisplay) {}
private:
	string m_sDisplay;
	string m_sActual;
	friend class CCSVLineParser;
};

class CCSVLineParser
{
public:
	CCSVLineParser(string sFullString = "");
	~CCSVLineParser(void);
	size_t size(void);
	string GetAt(int intIndex, bool bActual = false);
	void SetFullString(string sLine);
	void SetAt(int intIndex, string & sColumn);
	string GetFullString(bool bActual = true);
	bool swapColumn(int intCol1, int intCol2);
	class Range
	{
	public:
		Range() : sText("Out of range") {};
		string sText;
	};
private:
	void Read(string sFullString);
	vector<CCSVColumn> m_vecElements;
	static void PreReadForQuote(string &sColumn, string &sFullString, string sDelimiter, int &intQuoteNumber);
	friend class CCSVColumn;
};
