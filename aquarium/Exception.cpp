#include "Exception.h"



Exception::Exception(int err)
{
	switch (err)
	{
	case 1:
		error = "\n\n\nWrond range of values!\n\n(For Planktons:\nradOfView: 2-4\n radOfDisp: 2 - 3\n lifeTime: 3 - 8 days\nFor Herbivores:\nradOfView: 6-8\n radOfDisp: 4 - 6\n lifeTime: 20 - 30 days\n eatTime: 4 - 5 days\nFor Predators:\nradOfView: 6-10\n radOfDisp: 6 - 7\n	lifeTime: 15 - 20 days\n eatTime : 4 - 7 days)";
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