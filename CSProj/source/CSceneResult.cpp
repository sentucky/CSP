#include"CSceneResult.h"




CSceneResult::CSceneResult()
{
}

CSceneResult::~CSceneResult()
{
}

void CSceneResult::init()
{
}
void CSceneResult::release()
{
}			
void CSceneResult::update()
{
	CHECK_UPDATE;


}

void CSceneResult::draw()
{
	CHECK_DRAW;
}			
CSceneBase* CSceneResult::nextScene()
{
	return this;
}
