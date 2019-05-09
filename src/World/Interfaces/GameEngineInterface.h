#pragma once

class InputInterface;
class FrameInterface;
class UIInterface;
class MapInterface;

class GameEngineInterface
{
protected:
    FrameInterface & fFrameI;
    InputInterface & fInputI;
    UIInterface & fUiI;
    MapInterface & fMapI;
    
public:
    GameEngineInterface(FrameInterface & f, InputInterface & i, MapInterface & m, UIInterface & u)
    : fFrameI(f), fInputI(i), fUiI(u), fMapI(m) {}

	virtual ~GameEngineInterface() {}

	virtual FrameInterface & getFrameInterface() { return fFrameI; }
	virtual InputInterface & getInputInterface() { return fInputI; }
	virtual UIInterface & getUIInterface() { return fUiI; }
	virtual MapInterface & getMapInterface() { return fMapI; }
};