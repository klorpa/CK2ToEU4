#include "PersonalityScraper.h"
#include "../../Configuration/Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include <set>

void mappers::PersonalityScraper::scrapePersonalities(const Configuration& theConfiguration)
{
	LOG(LogLevel::Info) << "-> Examiming Personalities";
	registerKeys();
	std::set<std::string> fileNames;
	Utils::GetAllFilesInFolder(theConfiguration.getCK2Path() + "/common/traits/", fileNames);
	for (const auto& fileName: fileNames) {
		if (fileName.find("txt") == std::string::npos) continue;
		parseFile(theConfiguration.getCK2Path() + "/common/traits/" + fileName);
	}
	clearRegisteredKeywords();
	LOG(LogLevel::Info) << ">> " << personalities.size() << " personalities scrutinized.";
}

void mappers::PersonalityScraper::scrapePersonalities(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void mappers::PersonalityScraper::registerKeys()
{
	registerRegex("[A-Za-z0-9_-]+", [this](const std::string& personalityName, std::istream& theStream) {
		commonItems::ignoreItem(personalityName, theStream);
		personalities.insert(std::pair(counter, personalityName));
		++counter;
	});
	registerRegex("[A-Za-z0-9\\_.:-]+", commonItems::ignoreItem);
}


std::optional<std::string> mappers::PersonalityScraper::getPersonalityForID(int ID) const
{
	const auto& personItr = personalities.find(ID);
	if (personItr != personalities.end()) return personItr->second;
	return std::nullopt;
}
