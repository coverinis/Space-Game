/*
* FILE          : Level1.cpp
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Level 1
*/
#define _USE_MATH_DEFINES
#define DEBUG
#include "Level1.h"
#include "GameStateManager.h"
#include <cmath> 


Level1::Level1()
{
	audio_[1].Load("space-engine.wav");
	playtime[1] = 11 * 1000;
	audio_[2].Load("warpdrive02.wav");
	audio_[3].Load("explosion-4.wav");
}


Level1::~Level1()
{
}

/*
* FUNCTION    : Load
* DESCRIPTION : Initial load of assests
* PARAMETERS  : void
* RETURNS     : void
*/
void Level1::Load()
{
	switch ((rand() % 3) + 1)
	{
	case 1:
		/*
		* Fortress Instrumental by Pipe Choir is licensed under a Attribution License.
		* Based on a work at www.pipechoir.com
		* Permissions beyond the scope of this license may be available at www.pipechoir.com or contact artist via email.
		*/
		audio_[0].Load("Fortress_Instrumental.wav");
		playtime[0] = 248 * 1000;
		break;
	case 2:
		/*
		* Spacerace (ID 462) by Lobo Loco is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 License.
		*/
		audio_[0].Load("Spacerace.wav");
		playtime[0] = 431 * 1000;
		break;
	case 3:
		/*
		* Fairlight by Parvus Decree is licensed under a Attribution-NonCommercial-ShareAlike License.
		*/
		audio_[0].Load("Fairlight.wav");
		playtime[0] = 188 * 1000;
		break;
	default:
		break;
	}
	//Play Sound
	audio_[0].Play();
	time[0] = timeGetTime();

	grid_ = new ScreenGrid(ship_x_,ship_y_);
	scene_asset_manager_ = new AssetManager(L"SectorBackground.bmp", render_manager,0,1,0,0.78);

	//Add Planets
	for (int i = 0; i < grid_->grid_space.size(); ++i)
	{
		for (int j = 0; j < grid_->grid_space[0].size(); ++j)
		{
			switch ((int)grid_->grid_space[i][j][2])
			{
			case NONE:
				break;
			case PLANET1:
				objects_.push_back(GameObject(
					new AssetManager(L"Planet1.bmp", render_manager, 0, 1, 0, 0.78),
					grid_->grid_space[i][j][0],
					grid_->grid_space[i][j][1],
					0)
				);
				break;
			case PLANET2:
				objects_.push_back(GameObject(
					new AssetManager(L"Planet2.bmp", render_manager, 0, 1, 0, 0.78),
					grid_->grid_space[i][j][0],
					grid_->grid_space[i][j][1],
					0)
					);
				break;
			case PLANET3:
				objects_.push_back(GameObject(
					new AssetManager(L"Planet3.bmp", render_manager, 0, 1, 0, 0.78),
					grid_->grid_space[i][j][0],
					grid_->grid_space[i][j][1],
					0)
					);
				break;
			default:
				break;
			}
		}
	}

	//Add Ship
	objects_.push_back(GameObject(
		new AssetManager(L"ShipBase.bmp", render_manager, 0, 1, 0, 0.2),
		grid_->grid_space[ship_x_][ship_y_][0],
		grid_->grid_space[ship_x_][ship_y_][1],
		0)
	);
	objects_.push_back(GameObject(
		new AssetManager(L"ShipDetail.bmp", render_manager, 0, 1, 0, 0.2),
		grid_->grid_space[ship_x_][ship_y_][0],
		grid_->grid_space[ship_x_][ship_y_][1],
		0)
	);

	//Add Enemy
	if (ship_x_ == 0)
	{
		objects_.push_back(GameObject(
			new AssetManager(L"EnemyShip.bmp", render_manager, 0, 0, 1, 0.78),
			grid_->grid_space[9][ship_y_][0],
			grid_->grid_space[9][ship_y_][1],
			0)
		);
	}
	else if(ship_x_ == 9)
	{
		objects_.push_back(GameObject(
			new AssetManager(L"EnemyShip.bmp", render_manager, 0, 0, 1, 0.78),
			grid_->grid_space[0][ship_y_][0],
			grid_->grid_space[0][ship_y_][1],
			0)
		);
	}
	else if (ship_y_ == 0)
	{
		objects_.push_back(GameObject(
			new AssetManager(L"EnemyShip.bmp", render_manager, 0, 0, 1, 0.78),
			grid_->grid_space[ship_x_][9][0],
			grid_->grid_space[ship_x_][9][1],
			0)
		);
	}
	else if (ship_y_ == 9)
	{
		objects_.push_back(GameObject(
			new AssetManager(L"EnemyShip.bmp", render_manager, 0, 0, 1, 0.78),
			grid_->grid_space[ship_x_][0][0],
			grid_->grid_space[ship_x_][0][1],
			0)
		);
	}
}

/*
* FUNCTION    : Unload
* DESCRIPTION : Remove rendered objects from memory
* PARAMETERS  : void
* RETURNS     : void
*/
void Level1::Unload()
{
	objects_.clear();
	objects_.swap(std::vector<GameObject>());
	delete grid_;
	delete scene_asset_manager_;
}

/*
* FUNCTION    : Render
* DESCRIPTION : Draw the list of sprites in appropriat grid spaces
* PARAMETERS  : void
* RETURNS     : void
*/
void Level1::Render()
{
	render_manager->ClearScreen(0, 0, 0.25);
	scene_asset_manager_->Draw();
	for (int i = 0; i < objects_.size(); ++i)
	{
		objects_[i].asset_manager_->Draw(
			objects_[i].x,
			objects_[i].y,
			objects_[i].angle
		);
	}
}

/*
* FUNCTION    : Update
* DESCRIPTION : Update positions of ship
* PARAMETERS  : void
* RETURNS     : void
*/
void Level1::Update(float x, float y)
{
	//Check sound loop
	if (timeGetTime()-time[0] >= playtime[0])
	{
		audio_[0].Stop();
		audio_[0].Play();
		time[0] = timeGetTime();
	}
	if (timeGetTime() - time[1] >= playtime[0])
	{
		audio_[1].Stop();
		audio_[1].Play();
		time[1] = timeGetTime();
	}
	//Check if points have changed
	if (objects_[objects_.size() - 2].x != x - O_CENTER_X && objects_[objects_.size() - 2].y != y - O_CENTER_Y)
	{
		audio_[1].Play();
		//get previouse coordinates
		float ship_x = objects_[objects_.size() - 2].x;
		float ship_y = objects_[objects_.size() - 2].y;

		//calculate vector
		float dx = (x - O_CENTER_X) - ship_x;
		float dy = (y - O_CENTER_Y) - ship_y;
		float length = sqrtf(dx*dx + dy*dy);

		//Calculate ship angle
		objects_[objects_.size() - 2].angle = atan2(dy, dx) * 180 / M_PI;
		objects_[objects_.size() - 3].angle = atan2(dy, dx) * 180 / M_PI;

		//Get unit vector
		dx /= length;
		dy /= length;

		//Get ship velocity
		dx *= SHIP_SPEED;
		dy *= SHIP_SPEED;

		//TODO Out of bound reload

		//Update ship coordinates
		if (ship_x != (x - O_CENTER_X) && ship_y != (y - O_CENTER_Y))
		{
			//move coordinates x
			if (ship_x < (x - O_CENTER_X))
			{
				ship_x += dx;
				if (ship_x >(x - O_CENTER_X))
				{
					ship_x = (x - O_CENTER_X);
				}
			}
			else
			{
				ship_x += dx;
				if (ship_x < (x - O_CENTER_X))
				{
					ship_x = (x - O_CENTER_X);
				}
			}

			//move coordinates y
			if (ship_y < (y - O_CENTER_Y))
			{
				ship_y += dy;
				if (ship_y >(y - O_CENTER_Y))
				{
					ship_y = (y - O_CENTER_Y);
				}
			}
			else
			{
				ship_y += dy;
				if (ship_y < (y - O_CENTER_Y))
				{
					ship_y = (y - O_CENTER_Y);
				}
			}
		}

		//Calcuate enemy ship angles
		dx = (objects_[objects_.size() - 2].x + O_CENTER_X) - (objects_[objects_.size() - 1].x + O_CENTER_X);
		dy = (objects_[objects_.size() - 2].y + O_CENTER_Y) - (objects_[objects_.size() - 1].y + O_CENTER_Y);
		objects_[objects_.size() - 1].angle = (atan2(dy, dx) * 180 / M_PI) - 180;
		length = sqrtf(dx*dx + dy*dy);
		dx /= length;
		dy /= length;

		//Move ship
		//Layer 1
		objects_[objects_.size() - 2].x = ship_x;
		objects_[objects_.size() - 3].x = ship_x;

		//Layer2
		objects_[objects_.size() - 2].y = ship_y;
		objects_[objects_.size() - 3].y = ship_y;

		//Move Enemy Ship
		if (length <= 200 && length > 150)
		{
			objects_[objects_.size() - 1].x += dx * ENEMY_SPEED * 1.25;
			objects_[objects_.size() - 1].y += dy * ENEMY_SPEED * 1.25;
		}
		else if (length <= 150 && length > 100)
		{
			objects_[objects_.size() - 1].x += dx * ENEMY_SPEED * 1.75;
			objects_[objects_.size() - 1].y += dy * ENEMY_SPEED * 1.75;
		}
		else if (length <= 100 && length > 50)
		{
			objects_[objects_.size() - 1].x += dx * ENEMY_SPEED * 2;
			objects_[objects_.size() - 1].y += dy * ENEMY_SPEED * 2;
		}
		else if (length <= 50)
		{
			objects_[objects_.size() - 1].x += dx * ENEMY_SPEED * 2.25;
			objects_[objects_.size() - 1].y += dy * ENEMY_SPEED * 2.25;
		}
		else
		{
			objects_[objects_.size() - 1].x += dx * ENEMY_SPEED;
			objects_[objects_.size() - 1].y += dy * ENEMY_SPEED;
		}

		//Colision Check
		if (length < 25)
		{
			ship_x_ = 0;
			ship_y_ = 4;
			Unload();
			//Play sound
			audio_[0].Stop();
			audio_[3].Stop();
			audio_[3].Play();
			Load();
			throw std::exception(END_GAME.c_str());
		}

		//New Level Check
		if (objects_[objects_.size() - 2].x + 75 > D_WIDTH)
		{
			//Converte to grid
			ship_x_ = 0;
			ship_y_ = 4;
			Unload();
			//Play sound
			audio_[0].Stop();
			audio_[2].Stop();
			audio_[2].Play();
			Load();
			throw std::pair<int,int>(0 + O_CENTER_X ,O_HEIGHT * ship_y_ + O_CENTER_Y);
		}
		else if (objects_[objects_.size() - 2].x + 25 < 0)
		{
			//Converte to grid
			ship_x_ = 9;
			ship_y_ = 4;
			Unload();
			//Play sound
			audio_[0].Stop();
			audio_[2].Stop();
			audio_[2].Play();
			Load();
			throw std::pair<int, int>(O_WIDTH*ship_x_ - O_CENTER_X, O_HEIGHT*ship_y_ + O_CENTER_Y);
		}
		else if (objects_[objects_.size() - 2].y + 75 > D_HEIGHT)
		{
			//Converte to grid
			ship_x_ = 4;
			ship_y_ = 0;
			Unload();
			//Play sound
			audio_[0].Stop();
			audio_[2].Stop();
			audio_[2].Play();
			Load();
			throw std::pair<int, int>(O_WIDTH*ship_x_ + O_CENTER_X, 0 + O_CENTER_Y);
		}
		else if (objects_[objects_.size() - 2].y + 25 < 0)
		{
			//Converte to grid
			ship_x_ = 4;
			ship_y_ = 9;
			Unload();
			//Play sound
			audio_[0].Stop();
			audio_[2].Stop();
			audio_[2].Play();
			Load();
			throw std::pair<int, int>(O_WIDTH*ship_x_ + O_CENTER_X, O_HEIGHT*ship_y_ - O_CENTER_Y);
		}
	}
	else
	{
		audio_[1].Stop();
	}
}
