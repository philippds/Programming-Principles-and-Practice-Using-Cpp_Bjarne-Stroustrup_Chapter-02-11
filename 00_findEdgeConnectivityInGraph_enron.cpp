/*
C++ Program to Find the Edge Connectivity of a Graph

This is a C++ Program to find edge connectivity of a graph.
An edge in an undirected connected graph is a bridge if removing it disconnects the graph.
For a disconnected undirected graph, definition is similar,
a bridge is an edge removing which increases number of connected components.
Here is source code of the C++ Program to Find the Edge Connectivity of a Graph.
The C++ program is successfully compiled and run on a Linux system.
*/

// A C++ program to find bridges in a given undirected graph
#include<iostream>
#include <list>
#include <vector>
#include <algorithm>
#define NIL -1
using namespace std;

// A class that represents an undirected graph
class Graph
{
	int V; // No. of vertices
	list<int> *adj; // A dynamic array of adjacency lists
	void bridgeUtil(int v, bool visited[], int disc[], int low[],
		int parent[]);
public:
	Graph(int V); // Constructor
	void addEdge(int v, int w); // function to add an edge to graph
	void bridge(); // prints all bridges
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v); // Note: the graph is undirected
}

void Graph::bridgeUtil(int u, bool visited[], int disc[], int low[],
	int parent[])
{
	// A static variable is used for simplicity, we can avoid use of static
	// variable by passing a pointer.
	static int time = 0;

	// Mark the current node as visited
	visited[u] = true;

	// Initialize discovery time and low value
	disc[u] = low[u] = ++time;

	// Go through all vertices aadjacent to this
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i; // v is current adjacent of u

					// If v is not visited yet, then recur for it
		if (!visited[v])
		{
			parent[v] = u;
			bridgeUtil(v, visited, disc, low, parent);

			// Check if the subtree rooted with v has a connection to
			// one of the ancestors of u
			low[u] = min(low[u], low[v]);

			// If the lowest vertex reachable from subtree under v is
			// below u in DFS tree, then u-v is a bridge
			if (low[v] > disc[u])
				cout << u << " " << v << endl;
		}

		// Update low value of u for parent function calls.
		else if (v != parent[u])
			low[u] = min(low[u], disc[v]);
	}
}

// DFS based function to find all bridges. It uses recursive function bridgeUtil()
void Graph::bridge()
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	int *disc = new int[V];
	int *low = new int[V];
	int *parent = new int[V];

	// Initialize parent and visited arrays
	for (int i = 0; i < V; i++)
	{
		parent[i] = NIL;
		visited[i] = false;
	}

	// Call the recursive helper function to find Bridges
	// in DFS tree rooted with vertex 'i'
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			bridgeUtil(i, visited, disc, low, parent);
}

vector<int> source_id{
	997,165,396,396,396,396,396,396,563,653,653,653,653,244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,
	244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,244,697,697,697,697,697,697,697,697,
	697,697,697,697,697,187,1007,1007,1007,1007,1007,1007,1007,1007,1007,1007,1007,185,243,243,243,236,236,236,236,
	236,236,236,187,187,187,856,856,396,396,396,396,396,396,396,196,196,196,196,196,196,196,196,244,187,187,370,279,
	279,279,279,279,433,433,689,689,73,904,904,904,904,904,904,516,516,66,648,648,826,826,826,826,689,689,689,689,689,
	689,689,689,689,689,689,689,689,689,689,689,666,666,997,853,853,853,853,853,853,853,853,853,853,853,853,853,853,
	853,853,853,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,300,300,629,629,629,
	421,421,421,421,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,432,432,432,432,432,432,432,432,382,597,597,
	597,597,597,597,597,597,997,597,597,597,597,597,597,850,597,597,336,985,985,985,850,850,850,334,334,1034,724,724,
	724,997,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,425,997,997,997,997,997,997,997,
	997,997,997,997,997,997,1097,997,997,997,997,997,997,997,997,997,997,997,997,997,997,997,997,997,997,997,997,997,
	997,732,997,997,997,997,997,374,374,997,997,997,997,396,396,997,1069,997,997,1097,1097,374,374,997,997,997,305,
	997,993,993,1008,1008,1008,1008,997,374,997,997,1008,1008,1008,1008,1008,1008,1008,1008,1008,1008,997,997,997,984,
	57,57,57,57,57,57,57,57,57,57,57,57,997,997,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,
	489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,489,997,489,997,997,1011,997,997,102,102,102,102,
	102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,
	102,102,102,102,102,157,1008,1008,1008,997,997,1015,997,997,997,997,396,396,826,826,826,826,826,16,16,16,16,16,16,
	16,16,16,16,16,16,16,714,997,997,997,997,997,997,997,997,997,997,997,997,997,735,735,735,735,735,735,689,689,689,
	689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,689,
	689,689,689,689,689,997,997,997,683,489,489,489,997,997,997,997,997,997,997,997,300,300,875,875,780,997,747,747,
	747,747,747,747,747,747,747,997,997,997,997,997,997,568,568,489,374,374,997,997,997,997,997,997,568,997,997,997,
	997,997,489,489,489,489,997,747,747,997,425,425,997,997,997,568,735,735,735,735,735,735,735,735,735,735,735,735,
	735,735,735,735,735,735,735,735,735,558,558,558,558,558,558,558,558,558,558,997,997,997,997,39,39,39,39,39,39,39,
	39,39,39,39,997,997,997,997,568,452,452,997,997,997,997,997,997,997,609,609,609,609,609,997,997,997,997,997,997,
	997,997,997,997,489,489,997,997,374,584,584,584,489,489,489,489,374,54,134,1008,1008,886,886,973,395,395,886,356,
	632,1006,1006,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,773,638,855,
	345,419,988,988,374,648,648,489,347,609,609,609,609,997,374,374,374,374,374,374,54,54,54,54,54,374,374,796,340,340,
	340,340,340,340,104,104,104,104,104,521,374,374,878,641,976,641,641,641,641,641,489,997,997,374,518,518,518,518,518,
	518,374,374,997,997,1074,738,738,738,738,738,738,833,833,833,833,833,833,833,833,833,833,833,833,833,833,833,833,833,
	833,833,833,425,425,425,425,425,425,425,425,425,425,425,425,487,487,487,997,997,374,778,489,489,489,489,489,997,924,
	924,924,924,924,997,997,689,689,689,689,489,803,803,803,803,803,803,997,94,997,1033,1033,1033,1033,1033,1033,1033,1033,
	1033,1033,1033,1033,1033,1033,1033,1033,1033,1033,1033,1033,16,16,16,16,16,16,16,16,16,997,997,489,997,161,453,453,
	453,453,453,453,453,453,453,453,453,453,453,453,453,453,453,453,453,453,453,453,453,997,997,997,443,443,443,443,997,
	526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,526,16,
	16,163,163,163,163,163,163,997,1008,1008,1008,1008,1008,1008,1008,1008,1008,1008,1008,1008,1008,1008,1008,16,489,489,
	997,997,1008,1008,1008,199,44,997,997,997,997,489,489,279,279,1031,1031,1031,1031,1031,1031,1031,1031,1031,1031,997,
	984,984,984,984,984,997,997,362,1069,85,997,489,850,1011,1011,1011,658,63,63,63,63,63,63,63,63,63,119,724,724,724,
	724,165,165,165,507,507,507,724,724,798,798,798,798,798,798,798,798,798,798,798,798,798,798,798,798,798,798,798,
	798,798,798,798,798,798,798,798,798,798,798,374,997,997,374,997,997,997,997,997,997,374,997,997,997,997,997,997,
	374,997,997,997,374,703,703,703,997,165,165,165,165,165,165,165,165,165,165,165,165,165,165,165,16,16,16,997,997,
	374,489,489,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,997,997,997,997,886,973,739,739,739,739,739,739,739,
	739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,739,592,
	730,730,886,886,748,748,483,724,665,665,526,526,526,526,526,526,526,526,526,526,526,797,797,797,174,174,174,174,
	174,174,174,174,174,174,174,174,730,648,425,573,66,1066,1066,1066,16,16,16,16,16,16,16,16,16,1087,724,724,724,
	638,724,724,421,811,475,911,724,724,599,599,599,724,619,619,851,997,997,425,425,997,997,997,997,997,997,997,997,
	997,997,997,997,997,997,997,997,997,747,747,747,747,747,747,747,747,747,747,747,747,747,747,747,997,855,855,855,
	1011,1011,997,997,374,374,374,374,374,997,997,997,997,997,850,850,850,850,850,997,997,997,997,997,997,797,997,997,
	997,997,997,997,374,502,502,997,997,489,997,374,997,997,16,16,16,16,16,16,16,16,374,997,997,374,997,997,997,997,
	997,997,997,997,1,997,997,997,997,997,997,997,997,997,425,425,425,425,425,425,997,997,1008,1008,997,489,489,489,
	489,997,997,997,997,33,850,850,374,374,997,374,997,374,997,692,692,692,692,692,997,997,997,332,332,332,332,332,
	332,332,332,332,332,332,332,332,332,833,833,833,833,833,833,833,833,833,833,833,251,251,251,251,251,251,251,251,
	251,251,251,251,251,251,460,429,997,374,374,374,176,374,374,997,997,997,997,997,997,997,1008,1008,1008,1008,1008,
	1008,1008,1008,374,374,374,997,997,997,997,374,997,375,997,997,374,374,489,489,489,489,489,489,489,489,489,997,
	374,997,997,489,489,997,997,374,997,811,165,165,16,16,16,16,997,984,997,997,997,997,997,997,724,724,724,724,997,
	997,997,997,997,16,16,826,826,826,826,340,374,374,689,374,997,724,997,374,997,786,521,997,374,850,850,850,850,
	850,850,850,997,997,997,374,374,997,374,997,997,374,957,957,957,957,957,957,458,458,374,997,997,374,997,374,374,
	374,374,997,374,997,997,723,997,997,997,16,16,16,16,16,16,16,16,16,16,16,826,826,826,826,826,826,826,826,826,
	826,826,826,826,826,826,16,16,16,16,811,811,811,811,811,811,811,811,872,872,872,872,872,872,872,872,872,872,872,
	872,872,872,872,872,872,872,872,16,922,922,922,997,997,1048,1048,1048,1048,1048,1048,1048,1048,1048,1048,1048,
	1048,1048,16,997,736,997,1069,489,997,997,689,689,1031,1031,1031,997,916,916,916,916,916,916,916,916,916,916,916,
	916,916,916,916,916,916,916,916,916,916,916,916,916,916,617,425,425,1031,1031,499,499,499,499,499,423,423,423,
	423,423,423,423,423,423,423,423,423,997,833,414,414,414,414,414,414,998,998,998,997,568,568,997,997,452,997,997,
	240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,489,997,997,295,295,295,997,997,
	656,656,656,71,71,997,997,242,242,242,242,242,242,723,997,425,306,616,616,616
};

vector<int> target_id{
	697,797,851,997,797,425,1008,16,816,973,5,886,253,587,391,52,790,80,311,245,913,870,315,159,982,123,195,309,690,
	8,283,482,832,418,1091,1096,48,925,64,623,277,457,350,14,761,739,1063,820,554,429,663,657,187,408,629,346,810,174,
	686,803,483,997,664,172,69,294,986,328,744,444,810,730,1014,973,490,713,997,632,727,856,88,996,951,954,196,657,483,
	954,632,918,405,663,526,803,358,174,1026,911,629,799,828,61,877,144,873,58,947,475,1016,763,96,54,282,658,30,136,
	850,936,276,42,83,310,1016,384,66,702,1002,1066,252,251,215,165,872,983,396,922,390,731,358,212,1038,869,428,332,
	16,851,890,129,997,716,765,1087,147,855,846,657,468,973,375,659,730,435,661,143,628,551,471,104,314,611,431,994,563,
	627,725,139,50,940,155,596,680,178,879,1064,231,813,574,447,81,638,247,346,483,1077,908,25,6,483,959,432,970,164,955,
	93,480,493,533,441,911,1045,330,1061,82,601,95,186,520,812,183,903,492,289,681,165,348,478,354,655,498,1021,522,1073,
	587,604,32,769,331,945,921,1055,1094,101,963,268,850,136,332,818,927,724,619,554,196,658,850,1057,38,580,736,416,1083,
	246,966,91,229,373,506,704,607,205,154,214,1072,488,709,132,851,162,163,396,466,922,251,146,197,425,918,267,374,383,
	954,600,422,797,1008,747,1005,895,405,1038,689,434,467,490,526,536,544,578,135,835,609,636,665,550,720,730,770,772,
	1000,809,842,852,663,859,651,920,957,973,1046,1068,1073,1074,1073,1079,473,474,125,233,553,556,41,1052,285,776,645,
	1070,266,874,833,850,136,332,396,451,425,985,16,872,72,438,476,973,173,433,915,1035,767,419,310,445,319,6,1078,1017,
	535,554,165,609,922,584,637,1003,443,179,988,789,107,405,851,997,396,135,954,358,1038,797,16,1046,466,566,826,132,
	1019,531,56,258,225,722,375,425,872,616,448,539,627,67,651,0,149,150,151,19,11,47,120,114,250,255,290,13,307,1097,
	316,576,620,621,750,302,158,570,1099,823,817,944,455,909,906,454,286,777,1025,808,65,753,0,826,135,1038,325,358,
	963,274,301,211,346,689,747,54,104,16,609,851,782,1053,134,317,826,170,891,103,104,1038,165,54,609,973,483,629,
	54,252,1066,429,850,658,31,388,855,410,800,301,618,770,728,440,997,811,953,232,1090,855,28,1080,425,526,729,658,
	985,466,546,876,797,208,801,706,527,635,602,502,409,67,949,697,902,228,142,625,1055,335,595,372,400,90,650,142,
	374,338,248,49,988,420,298,690,143,659,460,321,858,278,973,589,855,834,1085,396,358,851,997,922,163,803,663,1075,
	188,174,803,403,977,543,429,124,296,957,661,734,323,735,393,956,963,561,837,551,657,560,784,979,21,588,284,240,
	938,590,797,1005,124,686,775,541,39,100,201,217,267,396,407,422,425,466,486,490,502,526,635,651,663,665,679,713,
	747,1095,564,138,884,87,894,191,203,928,930,688,819,435,479,663,526,707,997,267,284,590,422,688,169,547,662,935,
	1042,865,956,501,788,806,179,17,796,147,187,846,663,851,997,789,489,826,963,749,332,738,943,361,260,264,39,4,1008,
	230,537,683,826,872,165,629,500,990,184,353,615,782,104,165,3,562,446,886,748,973,425,236,584,268,755,1093,75,838,
	105,152,160,204,937,227,273,256,304,831,380,416,465,472,517,571,9,523,629,176,235,658,327,375,851,630,509,1023,
	1006,469,922,1046,165,375,408,787,1098,914,814,555,1092,927,385,92,738,332,1071,76,851,1089,237,23,359,606,425,738,
	741,752,841,54,1097,746,821,850,62,62,1076,583,976,792,729,707,345,404,698,641,693,729,546,695,413,346,640,219,386,
	1073,577,741,845,332,927,220,12,46,540,332,740,899,827,10,216,416,505,900,965,967,1024,703,313,689,938,118,466,851,
	963,526,749,922,865,651,1003,1038,689,179,730,437,133,868,591,249,783,663,811,356,614,434,121,692,791,805,166,439,
	424,710,251,1008,703,833,479,997,663,526,851,396,269,53,371,972,430,654,932,406,1047,176,794,128,324,713,484,329,
	464,981,442,189,1049,880,436,759,332,1008,396,663,425,1039,797,833,850,392,616,111,496,475,966,999,523,1086,1056,
	700,965,992,961,978,910,888,905,860,824,802,755,687,585,477,557,571,115,548,20,1029,396,405,425,16,122,554,657,
	435,855,846,388,375,659,1084,800,269,143,196,784,829,624,446,252,629,483,707,1059,639,137,213,379,550,474,184,575,
	251,466,146,997,851,467,333,851,129,811,141,197,212,764,192,918,997,358,405,600,466,689,689,876,1005,942,364,1080,
	881,943,554,1073,376,701,941,269,565,969,933,156,668,669,670,672,673,674,675,676,677,822,923,177,626,470,830,1010,
	213,137,1073,1074,425,1069,251,608,265,431,725,409,89,131,939,887,694,952,921,885,369,609,143,690,581,948,104,1008,
	425,855,603,743,298,334,538,962,262,485,684,919,1050,1065,490,100,713,848,463,696,281,280,180,893,795,140,1041,491,
	1001,497,896,843,1036,991,299,657,288,781,401,27,719,810,975,153,287,886,960,494,116,433,881,16,1012,312,979,930,
	836,1082,751,332,845,1015,16,782,1053,134,318,826,171,892,103,1080,721,615,1038,54,609,871,851,428,559,58,275,78,
	34,811,869,953,232,1090,855,28,1080,526,729,658,985,466,546,876,997,547,859,519,844,567,653,244,587,391,52,790,80,
	311,245,913,870,315,159,982,123,195,309,690,8,283,482,418,1091,1096,48,925,64,623,277,457,350,14,761,1063,820,997,
	946,437,748,395,886,395,196,271,376,997,396,425,797,918,851,405,663,1008,803,358,174,526,396,425,526,396,425,797,
	918,851,405,663,1008,803,358,662,854,268,1028,629,516,648,198,252,136,983,922,390,731,358,212,890,129,995,162,2,
	866,300,1022,771,667,1044,421,68,206,112,762,712,1021,619,724,334,1069,717,724,396,1008,1055,412,360,99,259,440,
	130,342,357,685,239,398,322,212,890,703,647,99,259,440,130,342,357,685,239,398,322,212,890,703,797,647,1085,188,
	1027,779,563,1043,760,1059,815,649,524,926,362,958,646,867,708,660,122,97,261,397,723,76,974,1026,1030,379,766,
	1005,931,486,525,934,495,549,292,735,425,1060,389,35,8,512,1088,883,67,433,51,268,135,55,625,872,987,194,15,167,
	79,741,655,845,870,92,752,1032,62,861,840,223,532,542,222,917,528,363,340,1089,237,23,359,606,459,950,747,797,
	613,24,213,638,622,721,113,614,582,1054,314,881,378,1079,774,450,898,534,529,791,166,439,924,805,96,70,707,689,
	251,1004,845,387,136,425,703,833,16,466,922,1038,635,251,16,136,387,425,466,845,922,1004,635,1038,833,332,16,136,
	387,425,466,689,845,922,1004,703,635,1038,568,568,26,241,37,745,1033,1081,210,634,85,117,503,726,1018,109,17,410,
	420,500,609,842,988,1046,515,291,586,839,297,625,715,40,108,568,929,224,60,263,1011,462,847,234,718,631,175,365,
	1048,682,221,110,77,410,559,207,971,593,352,572,399,989,721,615,399,989,148,145,912,334,196,29,877,889,367,804,
	366,705,218,568,598,789,489,318,584,318,1038,1080,584,742,22,1062,268,43,793,423,605,768,527,374,786,234,7,414,
	870,845,751,200,339,703,716,437,785,643,326,257,381,402,320,825,18,1069,683,1062,458,586,957,1068,86,1040,126,
	45,190,449,461,1058,1097,368,754,699,293,513,652,500,272,990,600,1076,234,518,377,230,976,62,443,355,990,1008,
	600,1076,234,425,377,184,230,976,62,922,443,355,1006,254,835,385,608,695,413,693,729,546,308,402,1051,826,16,
	990,1008,600,1076,234,425,584,165,377,184,230,976,62,922,443,355,1006,1006,1008,234,425,127,968,466,1008,851,
	396,425,918,1038,689,997,990,135,16,988,918,349,425,579,1097,756,356,862,417,747,671,678,530,757,668,669,670,
	672,673,674,676,677,864,594,1037,758,411,105,427,508,514,456,633,711,642,733,737,303,226,845,850,918,511,864,
	435,829,907,426,252,344,343,1067,857,193,1009,394,612,481,724,36,238,980,270,870,845,751,200,339,703,168,341,
	1069,182,545,964,414,847,849,866,209,59,84,202,74,380,337,552,105,860,351,569,897,416,1013,160,306,106,415,901,
	863,697,1020,141,554,664,69,644,691,850,713,433,429,460,504,807,181,180,994,563,510,996,98,882,731,125,396,997,851
};


// Driver program to test above function
int main()
{

	// Create graphs given in above diagrams
	cout << "\nBridges in first graph \n";
	Graph g1(1801);
	for (int i = 0; i < 1801; i++) {
		g1.addEdge(source_id[i], target_id[i]);
	}
	g1.bridge();
		
	return 0;
	//press ctrl+f5 to keep window open
}