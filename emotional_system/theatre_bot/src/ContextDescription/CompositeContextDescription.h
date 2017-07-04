///////////////////////////////////////////////////////////
//  CompositeContextDescription.h
//  Implementation of the Class CompositeContextDescription
//  Created on:      04-dic-2014 04:41:41 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(COMPOSITECONTEXTDESCRIPTION_H_)
#define COMPOSITECONTEXTDESCRIPTION_H_

#include "AbstractContextDescription.h"
#include "ContextType.h"

#include <vector>
#include <iostream>

using std::vector;

class CompositeContextDescription : public AbstractContextDescription
{

public:
	CompositeContextDescription();
	virtual ~CompositeContextDescription();
	void addNextContext(AbstractContextDescription * new_context);
	int getNumberOfContext();
	vector<AbstractContextDescription*> getSubContext();
	vector<AbstractContextDescription*> * getSubContextPointer();
	void setContextType(ContextType context_type);
	ContextType getContextType();
	void setEmotionalSynch(bool emotional_synch);
	bool getEmotionalSynch();
	void setActionsSynch(bool actions_synch);
	bool getActionsSynch();
	int getCountActions();
	void addCountActions();
private:
	/**
	 * List of all the contexts that are dirived from here
	 */
	vector<AbstractContextDescription*> context_list;
	ContextType context_type;
	bool emotional_synch;
	bool actions_synch;
	//This variable says which is the current action that is being executed, it only works for sequential context
	int current_action;
};
#endif // !defined(COMPOSITECONTEXTDESCRIPTION_H_)
