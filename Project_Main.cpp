#include <iostream>
#include"Project_Submission.h"
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

int screen_x = 1600;
int screen_y = 900;

float squareRoot(float n)
{
    float x = n;
    float y = 1;
    float e = 0.000001f; 

    while (x - y > e)
    {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}


Vector2D::Vector2D(float x, float y): x(x), y(y) {}

void Vector2D::move(char** lvl, float& offset_x, float speed, const int cell_size,
	int& Pheight, int& Pwidth, int& player_direction, bool& ismoving)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) {

		player_direction = -1;
		offset_x = ((this->x + speed + Pwidth) / cell_size);

		int top = this->y / cell_size;
		int bottom = (this->y + Pheight - 10) / cell_size;

		if ((lvl[top][static_cast<int>(offset_x)] != '#') && (lvl[bottom][static_cast<int>(offset_x)] != '#')) {

			this->x += speed;
			ismoving = true;

		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left)) {
		player_direction = 1;
		offset_x = ((this->x - speed) / cell_size);
		int top = this->y / cell_size;
		int bottom = (this->y + Pheight - 10) / cell_size;
		if ((lvl[top][static_cast<int>(offset_x)] != '#') && (lvl[bottom][static_cast<int>(offset_x)] != '#')) {
			this->x -= speed;
			ismoving = true;
		}
	}
	else {
		ismoving = false;
	}
	return ;
}


float Vector2D :: distanceTo(Vector2D other) {
	float dx = this->x  - other.x ;
    float dy = this->y - other.y ;

    float num; 
    num = dx * dx + dy * dy ;
    
    return squareRoot(num);
}

Vector2D Vector2D::rangeTo(Vector2D other) {
    float dx = (this->x >= other.x) ?
               (this->x - other.x) : 
               (other.x - this->x);

    float dy = (this->y >= other.y) ?
               (this->y - other.y) :
               (other.y - this->y);

    return Vector2D(dx,dy);

}



// =============================================
// ENTITY
// =============================================
Vector2D Entity::getPosition() const
{
    return position;
}

float Entity::getHp() const
{
    return hp;
}

bool Entity::getIsAlive() const
{
    return isAlive;
}

char* Entity::getName() const
{
    return name;
}


void Entity::setPosition(Vector2D pos)
{
    position = pos;
}

void Entity::setHp(float hp)
{
    this->hp = hp;
}

void Entity::setIsAlive(bool alive)
{
    isAlive = alive;
}

void Entity::setName(char* name)
{
    this->name = name;
}



// =============================================
// GAME ACTOR
// =============================================
float GameActor::getDirection() const
{
    return direction;
}

float GameActor::getGravity() const
{
    return gravity;
}

bool GameActor::getIsOnGround() const
{
    return isOnGround; 
}


void GameActor::setDirection(float dir)
{
    direction = dir;
}

void GameActor::setGravity(float g)
{
    gravity = g;
}

void GameActor::setIsOnGround(bool onGround)
{
    isOnGround = onGround;
}



// =============================================
// WEAPON
// =============================================
int Weapon::getAmmo() const
{
    return ammo;
}

float Weapon::getRange() const
{
    return range;
}

float Weapon::getDamage() const
{
    return damage; 
}

float Weapon::getFireRate() const
{
    return fireRate;
}


void Weapon::setAmmo(int ammo)
{
    this->ammo = ammo; 
}

void Weapon::setRange(float range)
{
    this->range = range;
}

void Weapon::setDamage(float damage)
{
    this->damage = damage;
}

void Weapon::setFireRate(float rate)
{
    fireRate = rate;
}



// =============================================
// GRENADE
// =============================================
float Grenade::getBlastRadius() const
{
    return blastRadius;
}

void Grenade::setBlastRadius(float radius)
{
    blastRadius = radius;
}



// =============================================
// VEHICLE
// =============================================
float Vehicle::getHp() const
{
    return hp;
}

void Vehicle::setHp(float hp)
{
    this->hp = hp;
}



// =============================================
// INVENTORY
// =============================================
Weapon* Inventory::getPrimaryWeapon() const
{
    return primaryWeapon;
}

Weapon* Inventory::getPistol() const
{
    return pistol;
}

int Inventory::getGrenadeCount() const
{
    return grenadeCount; 
}

int Inventory::getGrenadeType() const
{
    return grenadeType; 
}

int Inventory::getPrimaryAmmo() const
{
    return primaryAmmo;
}


void Inventory::setPrimaryWeapon(Weapon* w)
{
    primaryWeapon = w;
}

void Inventory::setGrenadeCount(int count)
{
    grenadeCount = count; 
}

void Inventory::setGrenadeType(int type)
{
    grenadeType = type;
}

void Inventory::setPrimaryAmmo(int ammo)
{
    primaryAmmo = ammo;
}



// =============================================
// CHARACTER
// =============================================
int Character::getLives() const
{
	return lives;
}

bool Character::getIsUndead() const
{
	return isUndead;
}

bool Character::getIsMummy() const
{
	return isMummy;
}

bool Character::getIsInjured() const
{
	return isInjured;
}

bool Character::getIsCritical() const
{
	return isCritical;
}

int Character::getStateTimer() const
{
	return stateTimer;
}

int Character::getDamageStateTimer() const
{
	return damageStateTimer;
}

float Character::getSaturation() const
{
	return saturation;
}

Inventory& Character::getInventory()
{
	return inventory;
}


void Character::setLives(int lives)
{
	this->lives = lives;
}

void Character::setIsUndead(bool undead)
{
	isUndead = undead;
}

void Character::setIsMummy(bool mummy)
{
	isMummy = mummy;
}

void Character::setIsInjured(bool injured)
{
	isInjured = injured;
}

void Character::setIsCritical(bool critical)
{
	isCritical = critical; 
}

void Character::setStateTimer(int timer)
{
	stateTimer = timer;
}

void Character::setDamageStateTimer(int timer)
{
	damageStateTimer = timer;
}

void Character::setSaturation(float sat)
{
	saturation = sat;
}



// =============================================
// SOLDIER
// =============================================
float Soldier::getFireRate() const
{
	return fireRate; 
}

int Soldier::getGrenadeCount() const
{
	return grenadeCount;
}

int Soldier::getAmmo() const
{
	return ammo;
}

Weapon* Soldier::getWeapon() const
{
	return weapon;
}

Vehicle* Soldier::getVehicle() const
{
	return vehicle;
}


void Soldier::setFireRate(float rate)
{
	fireRate = rate;
}

void Soldier::setGrenadeCount(int count)
{
	grenadeCount = count;
}

void Soldier::setAmmo(int ammo)
{
	this->ammo = ammo;
}

void Soldier::setWeapon(Weapon* w)
{
	weapon = w;
}

void Soldier::setVehicle(Vehicle* v)
{
	vehicle = v;
}



// =============================================
// MARCO
// =============================================
float Marco::getFireRateMultiplier() const
{
	return fireRateMultiplier;
}

bool Marco::getDualFireActive() const
{
	return dualFireActive;
}

float Marco::getDualFireTimer() const
{
	return dualFireTimer;
}


void Marco::setFireRateMultiplier(float m)
{
	fireRateMultiplier = m;
}

void Marco::setDualFireActive(bool active)
{
	dualFireActive = active;
}

void Marco::setDualFireTimer(float timer)
{
	dualFireTimer = timer;
}



// =============================================
// TARMA
// =============================================
float Tarma::getVehicleFireRateMultiplier() const
{
	return vehicleFireRateMultiplier;
}

float Tarma::getVehicleDurabilityMultiplier() const
{
	return vehicleDurabilityMultiplier;
}

bool Tarma::getImmunityActive() const
{
	return immunityActive;
}

float Tarma::getImmunityTimer() const
{
	return immunityTimer;
}

float Tarma::getFootSpeedMultiplier() const
{
	return footSpeedMultiplier;
}

float Tarma::getFootHPMultiplier() const
{
	return footHPMultiplier;
}


void Tarma::setVehicleFireRateMultiplier(float m)
{
	vehicleFireRateMultiplier = m;
}

void Tarma::setVehicleDurabilityMultiplier(float m)
{
	vehicleDurabilityMultiplier = m;
}

void Tarma::setImmunityActive(bool active)
{
	immunityActive = active;
}

void Tarma::setImmunityTimer(float timer)
{
	immunityTimer = timer;
}

void Tarma::setFootSpeedMultiplier(float m)
{
	footSpeedMultiplier = m;
}

void Tarma::setFootHPMultiplier(float m)
{
	footHPMultiplier = m;
}



// =============================================
// ERI
// =============================================
float Eri::getGrenadeMultiplier() const
{
	return grenadeMultiplier;
}

float Eri::getBlastRadiusMultiplier() const
{
	return blastRadiusMultiplier; 
}

bool Eri::getDoubleThrowActive() const
{
	return doubleThrowActive;
}

float Eri::getDoubleThrowTimer() const
{
	return doubleThrowTimer;
}


void Eri::setGrenadeMultiplier(float m)
{
	grenadeMultiplier = m;
}

void Eri::setBlastRadiusMultiplier(float m)
{
	blastRadiusMultiplier = m;
}

void Eri::setDoubleThrowActive(bool active)
{
	doubleThrowActive = active;
}

void Eri::setDoubleThrowTimer(float timer)
{
	doubleThrowTimer = timer;
}



// =============================================
// FIO
// =============================================
float Fio::getAmmoMultiplier() const
{
	return ammoMultiplier;
}

float Fio::getFireRateMultiplier() const
{
	return fireRateMultiplier;
}

bool Fio::getSuperchargedActive() const
{
	return superchargedActive;
}

float Fio::getSuperchargedTimer() const
{
	return superchargedTimer;
}


void Fio::setAmmoMultiplier(float m)
{
	ammoMultiplier = m;
}

void Fio::setFireRateMultiplier(float m)
{
	fireRateMultiplier = m;
}

void Fio::setSuperchargedActive(bool active)
{
	superchargedActive = active;
}

void Fio::setSuperchargedTimer(float timer)
{
	superchargedTimer = timer;
}



// =============================================
// ENEMY
// =============================================
int Enemy::getId() const
{
	return id;
}

float Enemy::getHp() const
{
	return hp;
}

int Enemy::getScoreValue() const
{
	return scoreValue; 
}

float Enemy::getDamage() const
{
	return damage;
}

float Enemy::getSpeed() const
{
	return speed;
}

bool Enemy::getIsAggro() const
{
	return isAggro;
}

int Enemy::getSpawnBatchSize() const
{
	return spawnBatchSize;
}


void Enemy::setId(int id)
{
	this->id = id;
}

void Enemy::setHp(float hp)
{
	this->hp = hp;
}

void Enemy::setScoreValue(int score)
{
	scoreValue = score;
}

void Enemy::setDamage(float dmg)
{
	damage = dmg;
}

void Enemy::setSpeed(float speed)
{
	this->speed = speed;
}

void Enemy::setIsAggro(bool aggro)
{
	isAggro = aggro;
}

void Enemy::setSpawnBatchSize(int size)
{
	spawnBatchSize = size;
}



// =============================================
// FOOD
// =============================================
float Food::getSaturationValue() const
{
	return saturationValue;
}

void Food::setSaturationValue(float value)
{
	saturationValue = value;
}



// =============================================
// SUPPLY CRATE
// =============================================
Weapon* SupplyCrate::getWeapon() const
{
	return weapon;
}

int SupplyCrate::getAmmo() const
{
	return ammo;
}

int SupplyCrate::getGrenadeCount() const
{
	return grenadeCount;
}


void SupplyCrate::setWeapon(Weapon* w)
{
	weapon = w;
}

void SupplyCrate::setAmmo(int ammo)
{
	this->ammo = ammo;
}

void SupplyCrate::setGrenadeCount(int count)
{
	grenadeCount = count;
}





// prototypes
void draw_player(RenderWindow& window, Sprite& playerSprite, float player_x, float player_y);
void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size);

int main()
{
	RenderWindow window(VideoMode(screen_x, screen_y), "Metal Slug", Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	/////////////////////////////////////////////////////////////////
	// a cell is 64 by 64 pixels
	// 'g' = grass tile

	const int cell_size = 64;
	const int height = 14;
	const int width = 110;

	char** lvl = NULL;

	lvl = new char* [height];
	for (int i = 0; i < height; i += 1)
	{
		lvl[i] = new char[width] {'\0'};
	}

	lvl[11][5] = 'g';
	lvl[11][6] = 'g';
	lvl[11][7] = 'g';
	lvl[11][8] = 'g';

	Texture wallTex1;
	Sprite wallSprite1;

	wallTex1.loadFromFile("metal_slug/Sprites/blocks/grass_block_side.png");
	wallSprite1.setTexture(wallTex1);

	////////////////////////////////////////////////////////
	float player_x = 380;
	float player_y = 610;	// row 11 * 64 - Pheight = 704 - 94

	float max_speed = 5;
	float velocityX = 0;
	float acceleration = 0.5;

	float scale_x = 0.2;
	float scale_y = 0.2;

	int raw_img_x = 593;
	int raw_img_y = 470;

	int Pheight = raw_img_y * scale_y;	
	int Pwidth = raw_img_x * scale_x;	

	Texture playerTex;
	Sprite playerSprite;

	playerTex.loadFromFile("metal_slug/Sprites/Character.png");
	playerSprite.setTexture(playerTex);
	playerSprite.setScale(scale_x, scale_y);

	////////////////////////////////////////////////////////

	Event ev;
	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
			{
				window.close();
			}

			if (ev.type == Event::KeyPressed)
			{
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			velocityX += acceleration;
			if (velocityX > max_speed) velocityX = max_speed;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			velocityX -= acceleration;
			if (velocityX < -max_speed) velocityX = -max_speed;
		}
		else
		{
			velocityX = 0;
		}

		player_x += velocityX;

		window.clear();

		display_level(window, height, width, lvl, wallSprite1, cell_size);
		draw_player(window, playerSprite, player_x, player_y);

		window.display();
	}

	return 0;
}


// functions

void draw_player(RenderWindow& window, Sprite& playerSprite, float player_x, float player_y)
{
	playerSprite.setPosition(player_x, player_y);
	window.draw(playerSprite);
}

void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size)
{
	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{
			if (lvl[i][j] == 'g')
			{
				wallSprite1.setPosition(j * cell_size, i * cell_size);
				window.draw(wallSprite1);
			}
		}
	}
}
