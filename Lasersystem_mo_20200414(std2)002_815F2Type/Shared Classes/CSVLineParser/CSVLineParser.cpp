#include "StdAfx.h"
#include ".\csvlineparser.h"

//===============================================================================
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//===============================================================================

CCSVColumn::CCSVColumn(string sDisplay) : m_sDisplay(sDisplay)
{
	int intStartPosition=0, intQuoteLocation;

	if ((int)sDisplay.find(',') >= 0)
		m_sActual += "\"";

	while ((intQuoteLocation = (int)sDisplay.find('"', intStartPosition)) >= 0)
	{
		m_sActual += string(sDisplay, intStartPosition, intQuoteLocation);
		m_sActual += '"';
		intStartPosition = intQuoteLocation+1;
	}
	m_sActual += string(sDisplay, intStartPosition, (int)sDisplay.size());

	if ((int)sDisplay.find(',') >= 0)
		m_sActual += "\"";
}

CCSVLineParser::CCSVLineParser(string sFullString)
{
	Read(sFullString);
}

CCSVLineParser::~CCSVLineParser(void)
{
}

void CCSVLineParser::SetFullString(string strLine)
{
	Read(strLine);
}

void CCSVLineParser::Read(string sFullString)
{
	int intFindLocation, intStartLocation, intQuoteNumber;
	string sRemaining = sFullString, sDelimiter, sActual, sDisplay, sColumn;
	char tmp[200];

	m_vecElements.clear();

	if (sRemaining.empty())
		return;


	if  (sRemaining.at(0) != '"')
		sDelimiter = ",";
	else
	{
		sDelimiter = "\",";
		sRemaining.erase(0, 1);
	}

	intStartLocation = 0;
	PreReadForQuote(sColumn, sRemaining, sDelimiter, intQuoteNumber);
	while ((intFindLocation = (int)sRemaining.find(sDelimiter)) >= 0)
	{
		sDisplay= string(sRemaining, 0, intFindLocation);
		sDisplay = sColumn + sDisplay;
		sRemaining.erase(0, intFindLocation+sDelimiter.size());
		if (sDelimiter.size() > 1)
			intQuoteNumber += 2;
		sActual =string(sFullString, intStartLocation, (int)sDisplay.size()+intQuoteNumber);
		strcpy(tmp, sActual.c_str());

		m_vecElements.push_back(CCSVColumn(sActual, sDisplay));
		intStartLocation += (int)sDisplay.size()+intQuoteNumber+1;
		// looking for next delimiter
		if  (*sRemaining.begin() != '"')
			sDelimiter = ",";
		else
		{
			sDelimiter = "\",";
			sRemaining.erase(0, 1);
		}
		PreReadForQuote(sColumn, sRemaining, sDelimiter, intQuoteNumber);
	}
	// grab the last column
	if (sDelimiter.size() > 1)
	{
		sRemaining.erase(sRemaining.size()-1 , sRemaining.size()-1);
		intQuoteNumber += 2;
	}
	sDisplay = sColumn + sRemaining;
	sActual =string(sFullString, intStartLocation, (int)sDisplay.size()+intQuoteNumber);
	m_vecElements.push_back(CCSVColumn(sActual, sDisplay));

	return;
}

size_t CCSVLineParser::size(void)
{
	return m_vecElements.size();
}


string CCSVLineParser::GetAt(int intIndex, bool bActual)
{
	if (intIndex < 0 || intIndex >= (int)m_vecElements.size())
		throw Range();

	return bActual ? m_vecElements[intIndex].m_sActual : m_vecElements[intIndex].m_sDisplay;
}

void CCSVLineParser::PreReadForQuote(string &sColumn, string &sFullString, string sDelimiter, int &intQuoteNumber)
{
	int intQuoteLocation, intDelimiterLocation;
	char chararQuote[] = "\"\"";
	string sPrefix;

	sColumn = "";
	intQuoteNumber = 0;

	if (sFullString.empty() || sDelimiter.empty())
		return;

	intQuoteLocation = (int)sFullString.find(chararQuote);
	intDelimiterLocation = (int)sFullString.find(sDelimiter);

	while (intQuoteLocation >= 0 && (intQuoteLocation < intDelimiterLocation || intDelimiterLocation < 0))
	{
		sPrefix = sFullString;
		sPrefix.erase(intQuoteLocation+1 , sPrefix.size()-1 );
		sFullString.erase(0, intQuoteLocation+sizeof(chararQuote)/sizeof(char)-1);
		sColumn += sPrefix;
		intQuoteLocation = (int)sFullString.find(chararQuote);
		intDelimiterLocation = (int)sFullString.find(sDelimiter);
		intQuoteNumber++;
	}
	return;
}

void CCSVLineParser::SetAt(int intIndex, string & sColumn)
{
	if (intIndex < 0)
		throw Range();

	// automatically expand to the column
	while ((int)m_vecElements.size() < intIndex+1)
		m_vecElements.push_back(CCSVColumn(""));
	m_vecElements[intIndex] = CCSVColumn(sColumn);
}

string CCSVLineParser::GetFullString(bool bActual)
{
	string sFullString;

	for (int intColumnCount = 0; intColumnCount < (int)size(); intColumnCount++)
	{
		if (intColumnCount > 0)
			sFullString += ',';

		if (bActual)
			sFullString += m_vecElements[intColumnCount].m_sActual;
		else
			sFullString += m_vecElements[intColumnCount].m_sDisplay;
	}
	return sFullString;
}

// column has to exist.
bool CCSVLineParser::swapColumn(int intCol1, int intCol2)
{
	if (intCol1 < 0 || intCol2 < 0 || intCol1 >= (int)size() || intCol2 >= (int)size())
		return false;

	if (intCol1 == intCol2)
		return true;

	swap(m_vecElements[intCol1], m_vecElements[intCol2]);
	string a=m_vecElements[intCol1].m_sDisplay, b=m_vecElements[intCol2].m_sDisplay;
	return true;
}
