#include "Plankton.h"


Plankton::Plankton(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_):Organism(location_,radOfDisp_,radOfview_,
		lifeTime_, 2)
{
	if ((radOfView > 4) || (radOfView < 2) ||
		(radOfDisp > 3) || (radOfDisp < 1) ||
		(lifeTime > 5) || (lifeTime < 3) ||
		(radOfDisp > radOfView))
	{
		throw Exception(1);
	}
}


Plankton::~Plankton()
{}

void Plankton::move(std::map<Organism&, int> neighbors, coordinates sizeAqua)
{
	if (neighbors.size() != 0)
	{
		float maxDist = 0;
		coordinates newLoc(location.first, location.second);
		for (int i = (-1)*radOfDisp; i <= radOfDisp; i++)
		{
			if ((location.first + i <= sizeAqua.first) && (location.first + i >= 0))
			{
				for (int j = (-1)*radOfDisp; j <= radOfDisp; j++)
				{
					if ((location.second + j <= sizeAqua.second) && (location.second + j >= 0))
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
							newLoc = coordinates(location.first + i, location.second + j);
						}
					}
				}
			}
		}
		moveDisl(newLoc);
	}
	else
	{
		/*int newx = rand() % radOfDisp;
		if (newx > sizeAqua.first)
		{
			newx = sizeAqua.first;
		}
		int newy = rand() % radOfDisp;
		if (newy > sizeAqua.second)
		{
			newy = sizeAqua.second;
		}
		moveDisl(coordinates(location.first + newx, location.second + newy)); */
	}
}

