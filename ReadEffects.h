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
7	PT	1	1	F	PT	2	1	F	PT	0	1	F	PT	5	1	F	M	B	2	F
8	PT	5	-1	PT	4	1	F	PT	4	-1	PT	5	1	F	PT	2	2	F	M	B	2	F	NM	PL	-1	F
9	PT	2	-1	F	PT	0	-1	F	PT	0	1	F	PT	1	-1	F
10	PT	5	-1	F	PT	3	-1	F	PT	2	1	F	M	B	2	RI	Unconditional love	F
11	PT	2	1	F	PT	0	1	F	PT	3	1	F	PT	1	-1	PT	2	-1	F	M	PL	2	DS	1	OT	2	F	NM	B	-1	F
12	PT	1	-1	F	PT	5	1	F	PT	1	1	F	M	B	2	F	NM	PA	1	F
13	PT	3	-1	F	PT	1	1	PT	2	1	F	PT	2	-1	F	PT	2	-1	PT	3	1	F	ME	ABC	B	2	D	B	3	CAB	B	1	CCD	B	1	CD-AB	B	-3	E	B	-2	F
14	PT	5	1	F	PT	2	1	F	PT	0	1	F	PT	3	1	F
15	PT	3	-1	OT	1	F	PT	0	-1	DR	Serious	OT	-1	F	PT	2	-1	PL	-1	F
16	PT	1	-1	F	PT	2	1	F	PT	1	1	F	CBC	B	2	R	F	MC	PL	-1	DR	Drama	PA	-1	F
17	PT	3	-1	F	PT	3	1	F	PT	1	-1	F	PT	2	1	F	CAB	B	2	F	MC	B	2	F	MD	B	2	F	E	B	-1	F
18	F	F	F	F	MAB	PL	2	PA	3	F	CAB	B	1	F	CAB-CDP	B	-2	F	CCD-ABP	PL	-3	DR	Drama	PA	-2	F	CD-CP	PL	DR	Drama	F	MC	B	2	F	MD	PL	4	F
19	PT	0	1	CH	SI	Dominant	F	PT	5	1	OT	3	F	PT	5	-1	CH	-1	OT	-2	SI	ANY	F
20	MIRROR	PT	3	-1	F	MIRROR	PT	0	1	F	MIRROR	PT	3	1	F	MIRROR	PT	1	1	F	M	B	2	NM	B	-1	F
21	PT	2	1	F	PT	0	-1	F	PT	3	1	F	M	B	2	F
22	PT	3	-1	PT	5	1	F	PT	1	-1	PT	2	-1	PL	-2	F
23	F	F	F	F	M	B	2	NM	PA	1
24	F	F	F	F	M	PL	2	DR	Sweet	PA	2	F
25	F	F	F	M	PL	0	PA	3	F	NM	PA	1	F
26	PL	PT	2	1	F	PT	2	-1	CH	-1	DR	Serious	OT	-1	F	PT	2	1	SI	Equal Partners	OT	1	F	PT	0	-1	CH	-1	OT	1	DR	Serious	F
27	PT	0	-1	PT	1	1	F	PT	0	-1	F	PT	0	1	F	PT	1	-1	PT	0	1	F	M	B	3	F	NM	B	-1	F
28	PT	3	-1	F	PT	4	1	F	PT	3	1	F	M	PL	2	D	Honorable Exit	DR	Serious	PA	2	D	Honorable Exit	F
*/