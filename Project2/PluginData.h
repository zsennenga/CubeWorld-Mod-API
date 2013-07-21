#include <string>

#ifndef PluginData_H
#define PluginData_H

using namespace std;

class PluginData
{
private:
	bool activated;
	string pluginName;
	string pluginDll;
	string pluginAuthor;
	string pluginDescription;

public:
	PluginData::PluginData(string pluginDataFile)	{
		
	}

	void setActivated(bool activation)	{
		this->activated = activation;
	}

	bool getActivated()	{
		return activated;
	}

	void getPluginData(string * retData)	{
		retData[0] = pluginName;
		retData[1] = pluginDll;
		retData[2] = pluginAuthor;
		retData[3] = pluginDescription;
	}
	PluginData::PluginData()	{
	}
};

#endif