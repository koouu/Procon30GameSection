#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <boost/any.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost;

//namespace json_builder {
	string toJson(any value) {
		if (value.type() == typeid(vector<any>)) {
			string result_str;
			vector<any> vec = any_cast<vector<any>>(value);
			for (int i = 0; i < vec.size(); i++) {
				result_str += toJson(vec[i]);
				if (i < vec.size() - 1) result_str += ",";
			}
			result_str = str(format("[%s]") % result_str);
			return result_str;
		}
		else if (value.type() == typeid(map<string, any>)) {
			string result_str;
			map<string, any> m = any_cast<map<string, any>>(value);
			string key;
			any value;
			int i = 0;
			BOOST_FOREACH(tie(key, value), m) {
				result_str += str(format("\"%s\":%s") % key % toJson(value));
				if (++i < m.size()) result_str += ",";
			}
			result_str = str(format("{%s}") % result_str);
			return result_str;
		}
		else if (value.type() == typeid(string)) {
			return str(format("\"%s\"") % any_cast<string>(value));
		}
		else if (value.type() == typeid(int)) {
			return str(format("\"%d\"") % any_cast<int>(value));
		}
		else if (value.type() == typeid(double)) {
			return str(format("\"%d\"") % any_cast<double>(value));
		}
	}

//}