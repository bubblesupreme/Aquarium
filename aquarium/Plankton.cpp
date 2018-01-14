#include "Plankton.h"


Plankton::Plankton(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int starvation_):Organism(location_,radOfDisp_,radOfview_,
		lifeTime_, starvation_)
{}


Plankton::~Plankton()
{}

void Plankton::move(std::map<Organism&, int> neighbors)
{
	if (neighbors.size() != 0)
	{
		float maxDist = 0;
		coordinates newCoord(location.first, location.second);
		for (int i = (-1)*radOfDisp; i <= radOfDisp; i++)
		{
			for (int j = (-1)*radOfDisp; j <= radOfDisp; j++)
			{
				int distance = 0;
				for (auto it = neighbors.begin(); it != neighbors.end(); it++)
				{
					distance = distance + fabs(it->first.getLocation().first - location.first + i)
						+ fabs(it->first.getLocation().second - location.second + j);
				}
				if (distance > maxDist)
				{
					maxDist = distance;
					newCoord = coordinates(location.first + i, location.second + j);
				}
			}
		}
		moveDisl(newCoord);
	}
	else
	{
		
		//move(coordinates(location.first + rand() % radOfDisp, location.second + rand() % radOfDisp));
	}
}

