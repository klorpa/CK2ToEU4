#include "Tributary.h"
#include "ParserHelpers.h"
#include "CommonRegexes.h"

CK2::Tributary::Tributary(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void CK2::Tributary::registerKeys()
{
	registerKeyword("tributary_type", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString typeStr(theStream);
		tributaryType = typeStr.getString();
	});
	registerKeyword("tributary", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt tributaryInt(theStream);
		tributaryID = tributaryInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}
