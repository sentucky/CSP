#ifndef ___CCOCKPIT___
#define ___CCOCKPIT___

#include"common.h"

class CTaskList;

class CCockpit:public CObjBase
{
public:
	CCockpit();
	~CCockpit();
	CCockpit::CCockpit(const CCockpit& src);

	void draw();
	void update();


private:
	CTaskList* _TaskDraw;
	CTaskList* _TaskUpdate;
};

CCockpit::CCockpit()
	:_TaskDraw(NULL),
	_TaskUpdate(NULL)
{
}

CCockpit::~CCockpit()
{
}

CCockpit::CCockpit(const CCockpit& src)
	:_TaskDraw(NULL),
	_TaskUpdate(NULL)
{
}


void CCockpit::draw()
{
}

void CCockpit::update()
{
}

#endif