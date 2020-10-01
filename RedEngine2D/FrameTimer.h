#pragma once
#ifndef FRAME_TIMER
#define FRAME_TIMER

#define FPS 30

class FrameTimer
{
public:

	FrameTimer()
	{
		currentGameFrame = 0;
	}

	void Update()
	{
		currentGameFrame++;

		if (currentGameFrame > FPS)
		{
			currentGameFrame = 0;
		}
	}

	int GetFrame()
	{
		return currentGameFrame;
	}


private:

	int currentGameFrame;

};


#endif // !FRAME_TIMER
