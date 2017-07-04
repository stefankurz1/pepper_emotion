///////////////////////////////////////////////////////////
//  CompositeActionDescription.h
//  Implementation of the Class CompositeActionDescription
//  Created on:      04-dic-2014 04:40:56 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(COMPOSITEACTIONDESCRIPTION_H_)
#define COMPOSITEACTIONDESCRIPTION_H_

#include "AbstractActionDescription.h"

#include<vector>

class CompositeActionDescription : public AbstractActionDescription
{

public:
	CompositeActionDescription();
	virtual ~CompositeActionDescription();
	AbstractContextDescription * analyze();
	void setEmotionSynch(bool emotion_synch);
	bool getEmotionSynch();
	void setActionsSynch(bool actions_synch);
	bool getActionsSynch();
protected:
	virtual bool MandatoryParameterVerification(Json::Value parameter) = 0;
	virtual bool OptionalParameterVerification(Json::Value parameter) = 0;
	std::map<std::string,AbstractActionDescription *> actions;
	bool emotion_synch;
	bool actions_synch;
	ContextType context_type;
};
#endif // !defined(COMPOSITEACTIONDESCRIPTION_H_)
