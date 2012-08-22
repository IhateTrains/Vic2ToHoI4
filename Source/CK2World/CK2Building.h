#ifndef CK2BUILDING_H_
#define CK2BUILDING_H_



#include "..\Mappers.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class Object;
class CK2Character;


class CK2Building
{
	public:
		CK2Building(Object* obj);

		double			getFortLevel()						const { return fortLevel; };
		double			getLevyMultiplier()				const { return levyMultiplier; };
		double			getNumSoldiers()					const { return numSoldiers; };
		double			getTaxIncome()						const { return taxIncome; };
		string			getForbiddenReligion()			const { return forbiddenReligion; };
		string			getRequiredReligion()			const { return requiredReligion; };
		vector<string>	getAcceptableCultures()			const { return acceptableCultures; };
		vector<string>	getAcceptableCultureGroups()	const { return acceptableCultureGroups; };

	private:
		double	fortLevel;
		double	levyMultiplier;
		double	numSoldiers;
		double	taxIncome;
		
		string			forbiddenReligion;
		string			requiredReligion;
		vector<string>	acceptableCultures;
		vector<string>	acceptableCultureGroups;
};


class CK2BuildingFactory
{
	public:
		CK2BuildingFactory();
		
		void						addBuildingTypes(Object* obj);
		const CK2Building*	getBuilding(string type, const CK2Character* baronyHolder, const religionGroupMapping& religionGroupMap, const cultureGroupMapping& cultureGroupMap) const;

	private:
		map<string, const CK2Building*> buildings;
};


#endif // CK2BUILDING_H_