#include "StateHistory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
#include "StateBuildings.h"



HoI4::StateHistory::StateHistory(std::istream& theStream)
{
	registerKeyword("owner", [this](std::istream& theStream) {
		commonItems::singleString ownerString(theStream);
		owner = ownerString.getString();
	});
	registerKeyword("buildings", [this](std::istream& theStream) {
		HoI4::StateBuildings theBuildings(theStream);
		civFactories = theBuildings.getCivFactories();
		milFactories = theBuildings.getMilFactories();
		dockyards = theBuildings.getDockyards();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}