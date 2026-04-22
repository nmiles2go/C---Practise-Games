/*
	

	Copyright 201# - 2025 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	1. Redistributions or derivations of source code must retain the above
	copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce
	the above copyright notice. This list of conditions and the following
	disclaimer must be reproduced in the documentation and/or other
	materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived
	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <iostream>
using namespace std::chrono_literals;

class GameOfLife : public olc::PixelGameEngine
{
public:
	GameOfLife()
	{
		sAppName = "Game Of Life Basic";
	}

private:
	int *m_output;
	int *m_state;

protected:
	// Called by olcConsoleGameEngine
	virtual bool OnUserCreate()
	{
		m_output = new int[ScreenWidth() * ScreenHeight()];
		m_state = new int[ScreenWidth() * ScreenHeight()];

		memset(m_output, 0, ScreenWidth() * ScreenHeight() * sizeof(int));
		memset(m_state, 0, ScreenWidth() * ScreenHeight() * sizeof(int));

		
		auto set = [&](int x, int y, std::string s)
		{
			int p = 0;

			for(char i:s)
			{
				m_state[y*ScreenWidth()+x+p] = i == '#' ? 1 : 0;
				p++;
			}
		};

		// for (int i = 0; i < ScreenWidth()*ScreenHeight(); i++)
		// 	m_state[i] = rand() % 2;

		//R-Pentomino
		// set(80, 50, "..##.");
		// set(80, 51, ".##..");
		// set(80, 52, "..#..");


		// Yin and Yang

		set(50, 28,  "...........................####......................");
		set(50, 30,  "........................##########...................");
		set(50, 32,  ".......................#################.............");
		set(50, 34,  ".....................#####################...........");
		set(50, 36,  "...................#########################.........");
		set(50, 38,  ".....#............#######....#################.......");
		set(50, 40,  "....#.............######......#################......");
		set(50, 42,  "...#..............#######....###################.....");
		set(50, 44,  "..#................##############################....");
		set(50, 46,  "..#..................############################....");
		set(50, 48,  "..#....................##########################....");
		set(50, 50,  "..#........................######################....");
		set(50, 52,  "..#..........................####################....");
		set(50, 54,  "...#...........................#################.....");
		set(50, 56,  "....#...............####........###############......");
		set(50, 58,  ".....#.............######.......##############.......");
		set(50, 60,  ".......#............####........############.........");
		set(50, 62,  ".........#.....................###########...........");
		set(50, 64,  "............#................##########..............");                
		set(50, 66,  "...............#............########.................");
		set(50, 68,  ".........................########....................");


		//Gosper Glider Gun
		// set(60, 45, "........................#............");
		// set(60, 46, "......................#.#............");
		// set(60, 47, "............##......##............##.");
		// set(60, 48, "...........#...#....##............##.");
		// set(60, 49, "##........#.....#...##...............");
		// set(60, 50, "##........#...#.##....#.#............");
		// set(60, 51, "..........#.....#.......#............");
		// set(60, 52, "...........#...#.....................");
		// set(60, 53, "............##.......................");


		// set(20, 45, "........................#............");
		// set(20, 46, "......................#.#............");
		// set(20, 47, "............##......##............##.");
		// set(20, 48, "...........#...#....##............##.");
		// set(20, 49, "##........#.....#...##...............");
		// set(20, 50, "##........#...#.##....#.#............");
		// set(20, 51, "..........#.....#.......#............");
		// set(20, 52, "...........#...#.....................");
		// set(20, 53, "............##.......................");
		// //Infinite Growth
		//set(20, 50, "########.#####...###......#######.#####");

		return true;
	}

	

	// Called by Pixel Game Engine
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		std::this_thread::sleep_for(50ms);

		// if (PixelGameEngine::GetKeyMap[VK_SPACE].bReleased)
		// 	return true;
		
		auto cell = [&](int x, int y)
		{
			return m_output[y * ScreenWidth() + x];
		};

		// Store output state
		for (int i = 0; i < ScreenWidth()*ScreenHeight(); i++)
			m_output[i] = m_state[i];
				
		for (int x = 1; x < ScreenWidth() - 1; x++)
			for (int y = 1; y < ScreenHeight() - 1; y++)
			{
				// The secret of artificial life =================================================
				int nNeighbours =	cell(x - 1, y - 1) + cell(x - 0, y - 1) + cell(x + 1, y - 1) +
									cell(x - 1, y + 0) +          0         + cell(x + 1, y + 0) +
									cell(x - 1, y +	1) + cell(x + 0, y + 1) + cell(x + 1, y + 1);

				if (cell(x, y) == 1)
					m_state[y*ScreenWidth() + x] = nNeighbours == 2 || nNeighbours == 3;
				else
					m_state[y*ScreenWidth() + x] = nNeighbours == 3;
				// ===============================================================================


				if (cell(x, y) == 1)
					Draw(x, y, olc::YELLOW);
				else
					Draw(x, y, olc::DARK_CYAN);
			}

		return true;
	}
};


int main()
{
	// Seed random number generator
	srand(clock());

	// Use olcConsoleGameEngine derived app
	GameOfLife game;
	game.Construct(160, 100, 8, 8);
	game.Start();

	return 0;
}
