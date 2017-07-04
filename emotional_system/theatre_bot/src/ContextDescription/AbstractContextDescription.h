///////////////////////////////////////////////////////////
//  AbstractContextDescription.h
//  Implementation of the Class AbstractContextDescription
//  Created on:      04-dic-2014 04:41:41 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(ABSTRACTCONTEXTDESCRIPTION_H_)
#define ABSTRACTCONTEXTDESCRIPTION_H_

#include "ContextPriority.h"


class AbstractContextDescription
{

public:
	AbstractContextDescription();
	virtual ~AbstractContextDescription();
	void setPredecessor(AbstractContextDescription *predecessor);
	void setIsPrimaryContext(bool is_primary_context);
	bool getIsPrimaryContext();
	AbstractContextDescription * getPredecessor();
	void setIsEmotional(bool is_emotional);
	bool getIsEmotional();
protected:
	ContextPriority context_priority;
	AbstractContextDescription *predecessor;
	bool is_primary;
	/*
	 * Tell if the action is emotional or mandatory
	 */
	bool is_emotional;
};
#endif // !defined(ABSTRACTCONTEXTDESCRIPTION_H_)
