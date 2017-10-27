// Librairies
#include "TimeInterval.h"

/**
*	Constructeur de la classe TimeInterval
*	@param start
*			Tour de d�part de prise de photo
*	@param end
*			Tour de fin de prise de photo
*/
TimeInterval::TimeInterval(long start, long end)
{
	this->start = start;
	this->end = end;
}

/**
*	Destructeur de la classe TimeInterval
*/
TimeInterval::~TimeInterval()
{
}

/**
*	Getteur du tour de d�part
*	@return tour de d�part
*/
long TimeInterval::getStart() const
{
	return this->start;
}

/**
*	Getteur du tour de fin
*	@return tour de fin
*/
long TimeInterval::getEnd() const
{
	return this->end;
}

/**
*	Setteur du tour de d�part
*	@param start
*			tour de d�part
*/
void TimeInterval::setStart(long start)
{
	this->start = start;
}

/**
*	Setteur du tour de fin
*	@return end
*			tour de fin
*/
void TimeInterval::setEnd(long end)
{
	this->end = end;
}


