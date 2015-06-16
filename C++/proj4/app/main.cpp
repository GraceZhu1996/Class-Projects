// main.cpp
//
// ICS 46 Spring 2015
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.
#include <iostream>
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "TripReader.hpp"
#include <map>

using namespace std;


std::function<double(const RoadSegment&)> shortestpath = [](RoadSegment rs){return rs.miles;};
std::function<double(const RoadSegment&)> shortesttime = [](RoadSegment rs){return rs.milesPerHour/ rs.miles;};

void printTime(double t)
{
	int hr = 0, min = 0;
	float sec = 0;
	hr = t / 3600;
	min = ((t / 3600 - hr) * 60);
	sec = ((t/60 - min) * 60);

	if(hr != 0)
	{
		cout << hr << " hrs ";
	}
	if(min != 0 || hr != 0)
	{
		cout << min << " mins ";
	}

	printf("%2.2f secs", sec );
}

int main()
{

	InputReader reader = InputReader(cin);
	RoadMapReader rm;
	RoadMap roadmap = rm.readRoadMap(reader);
	
	TripReader tr;
	std::vector<Trip> trips = tr.readTrips(reader);

	struct roadInfo
	{
		int vertex;
		string name;
		RoadSegment info;
	};


	map<int, int> result;
	for (std::vector<Trip>::iterator i = trips.begin(); i != trips.end(); i++)
	{
		vector<roadInfo> returntrip;
		if (i->metric == TripMetric::Distance)
		{
			result = roadmap.findShortestPaths(i->startVertex, shortestpath);
		}
		else
		{
			result = roadmap.findShortestPaths(i->startVertex, shortesttime);
		}

		int next = i->endVertex;
		roadInfo end = roadInfo{i->endVertex, roadmap.vertexInfo(i->endVertex), roadmap.edgeInfo(result[i->endVertex], i->endVertex)};
		returntrip.push_back(end);

		float totaldistance = end.info.miles;
		double totalmph = 0;
		do
		{
			int temp = next;
			next = result[next];
			returntrip.push_back(roadInfo{next, roadmap.vertexInfo(next), roadmap.edgeInfo(next, temp)});
			if (next != i->startVertex)
			{
				totaldistance += roadmap.edgeInfo(next, temp).miles;
			}
		}while(next != i->startVertex);

		if (i->metric == TripMetric::Distance)
		{
			cout << "Shortest distance from " << roadmap.vertexInfo(returntrip.back().vertex) <<
			 " to " << roadmap.vertexInfo(returntrip.front().vertex) << endl;

			for(int i = returntrip.size() - 1; i >= 0; i--)
			{
				if (i == returntrip.size() - 1)
					cout << "\t Begin at "<< returntrip[i].name << endl;
				else
					cout << "\t Continue to "<< returntrip[i].name << " (" << returntrip[i].info.miles << " miles)" << endl;
			}
			printf("Total Distance: %2.1f miles\n", totaldistance);
		}
		else
		{
			cout << "Shortest driving time from " << roadmap.vertexInfo(returntrip.back().vertex) <<
			 " to " << roadmap.vertexInfo(returntrip.front().vertex) << endl;

			for(int i = returntrip.size() - 1; i >= 0; i--)
			{
				double m = returntrip[i].info.miles;
				double mph = returntrip[i].info.milesPerHour;
				double t = m/mph * 3600; //In seconds

				if (i == returntrip.size() - 1)
				{
					cout << "\t Begin at " <<  returntrip[i].name << endl;
					continue;
				}
				else
					cout << "\t Continue to ";
				totalmph += t;
				cout << returntrip[i].name << " (" << m << " miles @ " << mph << " mph = ";
				printTime(t);
				printf(")\n");
			}
			printf("Total time: ");
			printTime(totalmph);
			printf("\n");
		}


		printf("\n");
	}


	 // RoadMapWriter rw;
	 // rw.writeRoadMap(cout, roadmap);
    return 0;
}

