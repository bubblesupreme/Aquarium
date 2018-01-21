#include "Exception.h"



Exception::Exception(int err)
{
	switch (err)
	{
	case 1:
		error = "\n\n\nWrond range of values!\n\n(For Planktons:\nradOfView: 2-4\n radOfDisp: 1 - 3\n lifeTime: 3 - 5 days\nFor Herbivores:\nradOfView: 6-9\n radOfDisp: 4 - 6\n lifeTime: 8 - 11 days\n eatTime: 4 - 5 days\nFor Predators:\nradOfView: 6-8\n radOfDisp: 6 - 7\n	lifeTime: 3 - 5 days\n eatTime : 2 - 3 days)";
		break;
	case 3:
		error = "\n\n\nAquarium died";
		break;
	case 4:
		error = "\n\n\nAquarium is crowd";
		break;
	default:
		break;
	}
}


Exception::~Exception()
{
}

const char* Exception::what() const noexcept
{
	return error;
}