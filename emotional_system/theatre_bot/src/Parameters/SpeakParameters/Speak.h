///////////////////////////////////////////////////////////
//  Speak.h
//  Implementation of the Class Speak
//  Created on:      04-dic-2014 04:42:42 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(SPEAK_H_)
#define SPEAK_H_

#include "../Parameter.h"

/**
 * I don't know a lot of this part, but I know that it could be have many things
 * as pitch, etc.
 */
class Speak : public Parameter
{

public:
	Speak();
	virtual ~Speak();
	void setText(std::string text);
	std::string getText();

private:
	std::string text;

};
#endif // !defined(SPEAK_H_)
