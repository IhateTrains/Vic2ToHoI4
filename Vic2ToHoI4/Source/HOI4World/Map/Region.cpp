#include "Region.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::Region::Region(std::istream& theStream)
{
	registerKeyword("id", [this](std::istream& theStream) {
		const commonItems::singleInt idString(theStream);
		ID = idString.getInt();
	});
	registerKeyword("name", [this](std::istream& theStream) {
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("provinces", [this](std::istream& theStream) {
		const commonItems::intList provinceNumbers(theStream);
		provinces = provinceNumbers.getInts();
	});
	registerKeyword("static_modifiers", [this](std::istream& theStream) {
		const commonItems::assignments staticModifierStrings(theStream);
		staticModifiers = staticModifierStrings.getAssignments();
	});
	registerKeyword("naval_terrain", [this](std::istream& theStream) {
		const commonItems::singleString terrainString(theStream);
		navalTerrain = terrainString.getString();
	});
	registerKeyword("weather", [this](std::istream& theStream) {
		const commonItems::stringOfItem weatherString(theStream);
		weather = weatherString.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}