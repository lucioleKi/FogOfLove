#pragma once
#include "Enums.h"
#include "Scene.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

struct PT {
	int in;
	Choice c;
	std::vector<std::string> effects{};
};

Scene readEffects(Scene s, std::vector<std::string> effects);
PT readPT(int begin, int end, Choice c, std::vector<std::string> effects);

PT readChoser(int begin, int index, Choice c, std::vector<std::string> effects);


/*


23	F	F	F	F	M	B	2	NM	PA	1
24	F	F	F	F	M	PL	2	DR	Sweet	PA	2	F
25	F	F	F	M	PL	0	PA	3	F	NM	PA	1	F
26	PL	PT	2	1	F	PT	2	-1	CH	-1	DR	Serious	OT	-1	F	PT	2	1	SI	Equal Partners	OT	1	F	PT	0	-1	CH	-1	OT	1	DR	Serious	F
27	PT	0	-1	PT	1	1	F	PT	0	-1	F	PT	0	1	F	PT	1	-1	PT	0	1	F	M	B	3	F	NM	B	-1	F
28	PT	3	-1	F	PT	4	1	F	PT	3	1	F	M	PL	2	D	Honorable Exit	DR	Serious	PA	2	D	Honorable Exit	F
*/