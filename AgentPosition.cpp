//#include "AgentPosition.h"
//#include"DxLib.h"
//
//AgentPosition::AgentPosition(int n,Vector2 size,PlayerData *p) {
//	int time = 0;
//
//	while (n >= 1) {
//		int xr;
//		int yr;
//		Vector2 v;
//		bool hit = true;
//		while (hit) {
//			bool bo = true;
//			xr = GetRand(-1 + (size.x / 2));
//			yr = GetRand(-1 + (size.y / 2));
//			v.x = xr;
//			v.y = yr;
//			for (int i = 0; i < time; i++) {
//				if (p[i % 2].position[i * 2].x == v.x && p[i % 2].position[i * 2].y == v.y) {
//					bo = false;
//					break;
//				}
//			}
//			hit = !bo;
//		}
//
//		p[time % 2].position.push_back(v);
//		v.y = size.y - yr - 1;
//		p[1 - (time % 2)].position.push_back(v);
//		if (n >= 2) {
//			v.x = size.x - xr - 1;
//			p[(time % 2)].position.push_back(v);
//			v.y = yr;
//			p[1 - (time % 2)].position.push_back(v);
//		}
//		time++;
//		n -= 2;
//	}
//}