#include "stdafx.h"
#include "SelectStage2P.h"
#include "Util_Core.h"
#include "ResourceManager.h"
#include "SelectBackgorund2P.h"
#include "GameMouseCursor.h"


SelectStage2P::SelectStage2P()
{
}


SelectStage2P::~SelectStage2P()
{
}

///////////////////////////////////////


void SelectStage2P::Start_Update()
{

}


void SelectStage2P::End_Debug_Update()
{

}

void SelectStage2P::Loading()
{
	Create_Actor<SelectBackgorund2P>();
	Create_Actor<GameMouseCursor>();
}
