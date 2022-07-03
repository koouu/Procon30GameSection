#include "readjson.h"


//読み込むjson
#define JSONIN "recieve.json"
#define JSONOUT "send.json"
#define JSONBEFORE "bee.json"

void readjson::write(std::vector<Action> action)
{
	std::ofstream ofs;
	ofs.open(JSONOUT);
	char dc = '"';
	ofs << "{" << std::endl;
	ofs << "	" << dc << "actions" << dc << ": [" << std::endl;
	for (int i = 0; i < action.size(); i++) {
		ofs << "		" << "{" << std::endl;
		ofs << "			" << dc << "agentID" << dc << ": " << action[i].agentID<<"," << std::endl;
		ofs << "			" << dc << "type" << dc << ": " <<dc<< action[i].type <<dc<< "," << std::endl;
		ofs << "			" << dc << "dx" << dc << ": " << action[i].direction.x << "," << std::endl;
		ofs << "			" << dc << "dy" << dc << ": " << action[i].direction.y << std::endl;
		ofs << "		" << "}";
		if (i != action.size() - 1)ofs << ",";
		ofs << std::endl;
	}
	ofs << "	" << "]" << endl;
	ofs << "}";
	ofs.close();
	
	//ここでjson書き出す予定
}

int readjson::readBefore()
{
	int set = 2;//これをかえることで


	std::ifstream ifs(JSONBEFORE, std::ios::in);
	if (ifs.fail()) {
		std::cerr << "failed to read test.json" << std::endl;
		exit(1);
	}
	const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();

	// JSONデータを解析する。
	picojson::value v;
	const std::string err = picojson::parse(v, json);

	picojson::array& arr = v.get<picojson::array>();
	picojson::object arrObj = arr[set].get<picojson::object>();
	limit_turn = arrObj["turns"].get<double>();
	teamID = arrObj["teamID"].get<double>();
	turnMillis = arrObj["turnMillis"].get<double>();
	intervalMillis = arrObj["intervalMillis"].get<double>();
	
	return teamID;
	/*limit_turn = 30;
	return 290;*/
}



void readjson::read()
{
	//json読み込んでDataBase作る

	int width;
	int height;
	vector<vector<int>> points;
	long long startedAtUnixTime;
	int turn;
	vector<vector<int>> tiled;
	vector<Team> teams;
	vector<Agent> actions;

	std::ifstream ifs(JSONIN, std::ios::in);
	if (ifs.fail()) {
		std::cerr << "failed to read test.json" << std::endl;
		exit(1);
	}
	const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();

	// JSONデータを解析する。
	picojson::value v;
	const std::string err = picojson::parse(v, json);

	picojson::object& obj = v.get<picojson::object>();

	width = obj["width"].get<double>();
	height = obj["height"].get<double>();
	picojson::array& point2 = obj["points"].get<picojson::array>();
	picojson::array& tile = obj["tiled"].get<picojson::array>();
	for (picojson::array::iterator it = point2.begin(); it != point2.end(); it++) {
		picojson::array& point = it->get<picojson::array>();
		vector<int> temp;
		for (double i = 0; i < point.size(); i++) {
			temp.push_back(point[i].get<double>());
		}
		
		points.emplace_back(temp);
	}
	for (picojson::array::iterator it = tile.begin(); it != tile.end(); it++) {
		picojson::array& point = it->get<picojson::array>();
		vector<int> temp;
		for (double i = 0; i < point.size(); i++) {
			temp.push_back(point[i].get<double>());
		}

		tiled.emplace_back(temp);
	}
	startedAtUnixTime = obj["startedAtUnixTime"].get<double>();
	turn = obj["turn"].get<double>();
	picojson::array& team = obj["teams"].get<picojson::array>();
//	picojson::object& teamObj;
	for (int i = 0; i < team.size(); i++) {
		picojson::object teamObj=team[i].get<picojson::object>();
		Team teamData;
		teamData.teamID = teamObj["teamID"].get<double>();
		picojson::array& agentsArr = teamObj["agents"].get<picojson::array>();

		for (picojson::array::iterator it = agentsArr.begin(); it != agentsArr.end(); it++) {
			
			picojson::object& agents = it->get<picojson::object>();
			
				Agent agentData;
				agentData.agentID = agents["agentID"].get<double>();
				agentData.x = agents["x"].get<double>()-1;//1から
				agentData.y = agents["y"].get<double>()-1;
				teamData.agents.push_back(agentData);
			

		}
		teamData.tilePoint = teamObj["tilePoint"].get<double>();
		teamData.areaPoint = teamObj["areaPoint"].get<double>();
		teams.push_back(teamData);
	}
	/*picojson::array& action = obj["actions"].get<picojson::array>();
	for (int i = 0; i < action.size(); i++) {
		picojson::object teamObj = action[i].get<picojson::object>();
		Agent act;
		picojson::array& agentsArr = teamObj["agents"].get<picojson::array>();
		for (picojson::array::iterator it = agentsArr.begin(); it != agentsArr.end(); it++) {
			picojson::array& agents = it->get<picojson::array>();
			for (int j = 0; j < agents.size(); j++) {
				picojson::object agent = agents[j].get<picojson::object>();
				Agent agentData;
				agentData.agentID = agent["agentID"].get<double>();
				agentData.x = agent["x"].get<double>();
				agentData.y = agent["y"].get<double>();
				teamData.agents.push_back(agentData);
			}

		}
		teamData.tilePoint = teamObj["tilePoint"].get<double>();
		teamData.areaPoint = teamObj["areaPoint"].get<double>();
		teams.push_back(teamData);
	}*/
	//limit_turn = 0;
	DataBase& database = DataBase::GetInstance();
	database.getDataBase(width, height, points, startedAtUnixTime, turn, tiled, teams, actions, limit_turn);
	database.turnMillis = turnMillis;
	database.intervalMillis = intervalMillis;
}