#ifndef CONFIGREADER_H__
#define CONFIGREADER_H__

#include <vector>
#include <fstream> //std::ifstream
#include "CommonTypes.h"
#include "AgentRecord.h"
#include "SmartException.h"

//assuming configuration file is valid and is written like this: 
//section and keys (by order): type, room, floor, log, config
/*
Example:
[a unique device instance identification string]
type = device-type
room = room-identification
floor = floor-designation
log = log name to be used by the device. (zlog logger)
config = a device specific configuration string
*/

namespace smartHouse {


class ConfigReader
{
public:
	ConfigReader();
	~ConfigReader();
	
	void ReadConfigFile(const string& fileName);
	std::vector<AgentRecord>& GetRecordVec();
	
private:
	string Trim(const string& str);
	string ExtractKeyValue(const string& s, const string& k, bool* isKey);

private:
	std::vector<AgentRecord> m_recordVec;
};


}
#endif
