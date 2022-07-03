#include "Log.h"

Log::Log(char mode)
{
	if (mode == 'r') {
		ifs.open(LOGFILE);
	}
	else if (mode == 'w') {
		ofs.open(LOGFILE);
		ofs << database.limit_turn << std::endl;
		for (auto i : database.points) {
			for (auto j : i) {
				ofs << j << ",";
			}
			ofs << std::endl;
		}
	}
}

void Log::write()
{
	for (auto i : database.tiled) {
		for (auto j : i) {
			ofs << j << ",";
		}
		ofs << std::endl;
	}
	
}

void Log::read()
{
	
	
}
