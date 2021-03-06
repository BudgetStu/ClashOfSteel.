#pragma once
#ifndef __PLAY_SCENE_2_
#define __PLAY_SCENE_2_

#include "Bullet.h"
#include "Scene.h"
#include "Button.h"
#include "Label.h"
#include "ETank.h"
#include "eTurret.h"
#include "Target.h"
#include "PlayerTank.h"
#include "pTurret.h"
#include <vector>

#include "Tile.h"
#include "TiledLevel.h"


class pTurret;

class PlayScene2 : public Scene
{
public:
	PlayScene2();
	~PlayScene2();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	float GameTimer = 0;
	float GunCD = 0;
	float StageEndCD = 0;
	float ChangeGun = 0;
	float fire = 0;
	int EnemiesDestroyed = 0;
	int TotalBullets = 0;
	int TotalEBullets = 0;
	int TotalFire = 0;
	int TotalExtraBullets = 0;
	int totalEnemies =18;
	int totalBuildings=23;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;

	glm::vec2 m_Position;
	SDL_Point m_mousePosition;


	//Tiles
	void m_setGridEnabled(bool state) const;
	std::vector<Tile*> m_pGrid;
	std::vector<NavigationObject*>m_pMap;
	void m_buildGrid();
	//Map
	TileC* Bg;
	TileC* m_field[23];
	TileC* extraDrop;
	//convenience functions
	Tile* m_getTile(int col, int row) const;
	Tile* m_getTile(glm::vec2 grid_position) const;


	//Labels
	Label* m_Inst[5];

	//Enemy
	ETank* m_pEnemyTank[18];
	eTurret* m_pETurret[18];
	void m_move();
	//Player
	PlayerTank* m_pPlayerTank;
	pTurret* m_pPlayerTurret;
	pTurret* m_pExtraTurret;
	//Bullets
	std::vector<Bullet*>m_pBullet;
	std::vector<Bullet*>m_pExtraBullet;
	std::vector<TileC*>m_pFire;
	std::vector<Bullet*>m_pEnemyBullet;
	void aoeDamage(Bullet* The);

	void m_CheckShipLOS(NavigationObject* object);

	// UI Items

};
#endif 
