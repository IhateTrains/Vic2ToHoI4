/*Copyright (c) 2018 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "Ideas.h"
#include "IdeaGroup.h"
#include "../Configuration.h"
#include "ParadoxParserUTF8.h"
#include <fstream>



HoI4::Ideas::Ideas()
{
	importIdeologicalIdeas();
	importManpowerIdeas();
}


void HoI4::Ideas::importIdeologicalIdeas()
{
	auto fileObject = parser_UTF8::doParseFile("ideologicalIdeas.txt");
	if (fileObject)
	{
		auto ideologyObjects = fileObject->getLeaves();
		for (auto ideologyObject: ideologyObjects)
		{
			std::string ideaName = ideologyObject->getKey();
			ideologicalIdeas.insert(make_pair(ideaName, ideologyObject->getLeaves()));
		}
	}
}


void HoI4::Ideas::importManpowerIdeas()
{
	registerKeyword(std::regex("ideas"), [this](const std::string& unused, std::istream& theStream){
		auto equals = getNextTokenWithoutMatching(theStream);
		auto leftBrace = getNextTokenWithoutMatching(theStream);
	});
	registerKeyword(std::regex("\\}"), [this](const std::string& unused, std::istream& theStream){});
	registerKeyword(std::regex("[a-zA-Z_]+"), [this](const std::string& ideaGroupname, std::istream& theStream){
		manpowerIdeas = std::make_unique<IdeaGroup>(ideaGroupname, theStream);
	});

	parseFile("manpowerIdeas.txt");
}


void HoI4::Ideas::output(std::set<std::string> majorIdeologies) const
{
	outputIdeologicalIdeas(majorIdeologies);
	outputManpowerIdeas();
}


void HoI4::Ideas::outputIdeologicalIdeas(std::set<std::string> majorIdeologies) const
{
	std::ofstream ideasFile("output/" + Configuration::getOutputName() + "/common/ideas/convertedIdeas.txt");
	ideasFile << "ideas = {\n";
	ideasFile << "\tcountry = {\n";
	for (auto majorIdeology: majorIdeologies)
	{
		auto ideologicalIdea = ideologicalIdeas.find(majorIdeology);
		if (ideologicalIdea != ideologicalIdeas.end())
		{
			for (auto idea: ideologicalIdea->second)
			{
				ideasFile << *idea;
				ideasFile << "\n";
			}
		}
	}
	ideasFile << "\t}\n";
	ideasFile << "}";
	ideasFile.close();
}


void HoI4::Ideas::outputManpowerIdeas() const
{
	std::ofstream ideasFile("output/" + Configuration::getOutputName() + "/common/ideas/_manpower.txt");
	ideasFile << "ideas = {\n";
	ideasFile << *manpowerIdeas;
	ideasFile << "}";
}