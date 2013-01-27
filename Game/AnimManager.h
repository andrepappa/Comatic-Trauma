<<<<<<< HEAD
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class AnimManager
{
	public:
		static std::vector<sf::IntRect*> GetSubRects(int w, int h, int amount, int cols, int startCol, int startRow)
		{
			std::vector<sf::IntRect*> Rects;

			for(int i = 0; i < amount; i++)
			{
				sf::IntRect* iR = new sf::IntRect((i%cols)*w + (startCol*w), h*((int)(i/cols)) + (h*startRow), w, h);
				Rects.push_back(iR);
			}

			return Rects;
		}

		int AddAnim(std::vector<sf::IntRect*> AnimFrames, int FrameRate)
		{
			Anim* A = new Anim();
			A->FrameDelay = FrameRate;
			A->Frames = AnimFrames;
			
			Anims.push_back(A);
			return Anims.size()-1;
		}

		int CurFrame(int Index)
		{
			return Anims[Index]->CurFrame();
		}

		sf::IntRect* GetFrame(int Index)
		{
			return Anims[Index]->GetFrame();
		}

		bool NewFrame(int Index)
		{
			return Anims[Index]->NewFrame();
		}

		void Update()
		{
			for(unsigned int i = 0; i < Anims.size(); i++)
				Anims[i]->Tick();
		}

	private:
		class Anim
		{
			private:
				int CurrentFrame;
				int LastFrame;
				sf::Clock Timer;

			public:
				Anim()
				{
					CurrentFrame = 0;
					FrameDelay = 0;
					Timer.restart();
				}

				int FrameDelay;
				std::vector<sf::IntRect*> Frames;

				int CurFrame(){ return CurrentFrame; }
				sf::IntRect* GetFrame(){ return Frames[CurrentFrame]; }
				bool NewFrame(){ return LastFrame != CurrentFrame; }

				void Tick()
				{
					if(Timer.getElapsedTime().asMilliseconds() >= FrameDelay)
					{
						LastFrame = CurrentFrame;
						Timer.restart();
						CurrentFrame++;
						if(CurrentFrame >= Frames.size())
							CurrentFrame = 0;
					}
				}
		};

		std::vector<Anim*> Anims;
=======
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class AnimManager
{
	public:
		static std::vector<sf::IntRect*> GetSubRects(int w, int h, int amount, int cols, int startCol, int startRow)
		{
			std::vector<sf::IntRect*> Rects;

			for(int i = 0; i < amount; i++)
			{
				sf::IntRect* iR = new sf::IntRect((i%cols)*w, h*((int)(i/cols)) + (h*startRow), w, h);
				Rects.push_back(iR);
			}

			return Rects;
		}

		void ChangeFrameTime(int Index, int FrameTime)
		{
			Anims[Index]->FrameDelay = FrameTime;
		}

		int AddAnim(std::vector<sf::IntRect*> AnimFrames, int FrameRate)
		{
			Anim* A = new Anim();
			A->FrameDelay = FrameRate;
			A->Frames = AnimFrames;
			
			Anims.push_back(A);
			return Anims.size()-1;
		}

		int CurFrame(int Index)
		{
			return Anims[Index]->CurFrame();
		}

		sf::IntRect* GetFrame(int Index)
		{
			return Anims[Index]->GetFrame();
		}

		bool NewFrame(int Index)
		{
			return Anims[Index]->NewFrame();
		}

		void Update()
		{
			for(unsigned int i = 0; i < Anims.size(); i++)
				Anims[i]->Tick();
		}

	private:
		class Anim
		{
			private:
				int CurrentFrame;
				int LastFrame;
				sf::Clock Timer;

			public:
				Anim()
				{
					FrameDelay = 0;
					Timer.restart();
				}

				int FrameDelay;
				std::vector<sf::IntRect*> Frames;

				int CurFrame(){ return CurrentFrame; }
				sf::IntRect* GetFrame(){ return Frames[CurrentFrame]; }
				bool NewFrame(){ return LastFrame != CurrentFrame; }

				void Tick()
				{
					if(Timer.getElapsedTime().asMilliseconds() >= FrameDelay)
					{
						LastFrame = CurrentFrame;
						Timer.restart();
						CurrentFrame++;
						if(CurrentFrame >= Frames.size())
							CurrentFrame = 0;
					}
				}
		};

		std::vector<Anim*> Anims;
>>>>>>> Kommit græiset
};