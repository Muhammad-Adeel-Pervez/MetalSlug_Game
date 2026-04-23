#pragma once

// =============================================
// Helper Functions 
// =============================================
float squareRoot(float n);


// =============================================
// VECTOR2D
// =============================================
class Vector2D {
public:
    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);
    void move(float dx, float dy);
    float distanceTo(Vector2D other);
    Vector2D rangeTo(Vector2D other);
};


// =============================================
// ENTITY (Abstract)
// =============================================
class Entity {
protected:
    Vector2D position;
    float hp;
    bool isAlive;
    char* name;

public:
    Entity();
    virtual ~Entity();

    Vector2D getPosition() const;
    float getHp() const;
    bool getIsAlive() const;
    char* getName() const;

    void setPosition(Vector2D pos);
    void setHp(float hp);
    void setIsAlive(bool alive);
    void setName(char* name);

    void takeDamage(float dmg);
    void checkHealth();

    virtual void draw() = 0;
};


// =============================================
// GAME ACTOR (Abstract)
// =============================================
class GameActor : public Entity {
protected:
    float direction;
    float gravity;
    bool isOnGround;

public:
    GameActor();
    virtual ~GameActor();

    float getDirection() const;
    float getGravity() const;
    bool getIsOnGround() const;

    void setDirection(float dir);
    void setGravity(float g);
    void setIsOnGround(bool onGround);

    virtual void move(float dx, float dy);
    virtual void jump();
    void applyGravity();
    void checkGroundCollision();

    virtual void draw() = 0;
};


// =============================================
// WEAPON (Abstract)
// =============================================
class Weapon {
protected:
    int ammo;
    float range;
    float damage;
    float fireRate;

public:
    Weapon();
    virtual ~Weapon();

    int getAmmo() const;
    float getRange() const;
    float getDamage() const;
    float getFireRate() const;

    void setAmmo(int ammo);
    void setRange(float range);
    void setDamage(float damage);
    void setFireRate(float rate);

    virtual void fire() = 0;
    virtual void draw() = 0;
};


// =============================================
// GRENADE (Abstract)
// =============================================
class Grenade : public Weapon {
protected:
    float blastRadius;

public:
    Grenade();
    virtual ~Grenade();

    float getBlastRadius() const;
    void setBlastRadius(float radius);

    virtual void fire() = 0;
    virtual void draw() = 0;
};


// =============================================
// HAND GRENADE
// =============================================
class HandGrenade : public Grenade {
public:
    HandGrenade();
    void fire() override;
    void draw() override;
};


// =============================================
// FIRE BOMB GRENADE
// =============================================
class FireBombGrenade : public Grenade {
public:
    FireBombGrenade();
    void fire() override;
    void draw() override;
};


// =============================================
// VEHICLE (Abstract)
// =============================================
class Vehicle : public Entity {
protected:
    float hp;

public:
    Vehicle();
    virtual ~Vehicle();

    float getHp() const;
    void setHp(float hp);
    void showDamage();

    virtual void draw() = 0;
};


// =============================================
// METAL SLUG
// =============================================
class MetalSlug : public Vehicle {
public:
    MetalSlug();
    void draw() override;
};


// =============================================
// SLUG FLYER
// =============================================
class SlugFlyer : public Vehicle {
public:
    SlugFlyer();
    void draw() override;
};


// =============================================
// SLUG MARINER
// =============================================
class SlugMariner : public Vehicle {
public:
    SlugMariner();
    void draw() override;
};


// =============================================
// AMPHIBIOUS SLUG
// =============================================
class AmphibiousSlug : public Vehicle {
public:
    AmphibiousSlug();
    void draw() override;
};


// =============================================
// INVENTORY
// =============================================
class Inventory {
private:
    Weapon* primaryWeapon;
    Weapon* pistol;
    int grenadeCount;
    int grenadeType;
    int primaryAmmo;

public:
    Inventory();
    ~Inventory();

    Weapon* getPrimaryWeapon() const;
    Weapon* getPistol() const;
    int getGrenadeCount() const;
    int getGrenadeType() const;
    int getPrimaryAmmo() const;

    void setPrimaryWeapon(Weapon* w);
    void setGrenadeCount(int count);
    void setGrenadeType(int type);
    void setPrimaryAmmo(int ammo);

    void addWeapon(Weapon* w);
    void removeWeapon();
    void addAmmo(int amount);
    void addGrenades(int count);
    bool hasWeapon();
    Weapon* getCurrentWeapon();
    void switchWeapon();
};


// =============================================
// CHARACTER (Abstract)
// =============================================
class Character : public GameActor {
protected:
    int lives;
    bool isUndead;
    bool isMummy;
    bool isInjured;
    bool isCritical;
    int stateTimer;
    int damageStateTimer;
    float saturation;
    Inventory inventory;

public:
    Character();
    virtual ~Character();

    int getLives() const;
    bool getIsUndead() const;
    bool getIsMummy() const;
    bool getIsInjured() const;
    bool getIsCritical() const;
    int getStateTimer() const;
    int getDamageStateTimer() const;
    float getSaturation() const;
    Inventory& getInventory();

    void setLives(int lives);
    void setIsUndead(bool undead);
    void setIsMummy(bool mummy);
    void setIsInjured(bool injured);
    void setIsCritical(bool critical);
    void setStateTimer(int timer);
    void setDamageStateTimer(int timer);
    void setSaturation(float sat);

    void takeDamage(float dmg) ;
    void showDamage();
    void respawn();
    void switchCharacter();
    void checkState();
    void freePOW();
    void spawnFusionCompanion();
    void eat(int amount);

    virtual void specialPowerUp() {}
    virtual void draw() override = 0;
};


// =============================================
// SOLDIER (Abstract)
// =============================================
class Soldier : public Character {
protected:
    float fireRate;
    int grenadeCount;
    int ammo;
    Weapon* weapon;
    Vehicle* vehicle;

public:
    Soldier();
    virtual ~Soldier();

    float getFireRate() const;
    int getGrenadeCount() const;
    int getAmmo() const;
    Weapon* getWeapon() const;
    Vehicle* getVehicle() const;

    void setFireRate(float rate);
    void setGrenadeCount(int count);
    void setAmmo(int ammo);
    void setWeapon(Weapon* w);
    void setVehicle(Vehicle* v);

    void shoot();
    void throwGrenade();
    void meleeAttack();
    void pickupWeapon(Weapon* w);
    void enterVehicle(Vehicle* v);
    void exitVehicle();

    virtual void specialPowerUp() override {}
    virtual void draw() override = 0;
};


// =============================================
// MARCO
// =============================================
class Marco : public Soldier {
private:
    float fireRateMultiplier;
    bool dualFireActive;
    float dualFireTimer;

public:
    Marco();

    float getFireRateMultiplier() const;
    bool getDualFireActive() const;
    float getDualFireTimer() const;

    void setFireRateMultiplier(float m);
    void setDualFireActive(bool active);
    void setDualFireTimer(float timer);

    void specialPowerUp() override;
    void meleeAttack();
    void shoot();
    void draw() override;
};


// =============================================
// TARMA
// =============================================
class Tarma : public Soldier {
private:
    float vehicleFireRateMultiplier;
    float vehicleDurabilityMultiplier;
    bool immunityActive;
    float immunityTimer;
    float footSpeedMultiplier;
    float footHPMultiplier;

public:
    Tarma();

    float getVehicleFireRateMultiplier() const;
    float getVehicleDurabilityMultiplier() const;
    bool getImmunityActive() const;
    float getImmunityTimer() const;
    float getFootSpeedMultiplier() const;
    float getFootHPMultiplier() const;

    void setVehicleFireRateMultiplier(float m);
    void setVehicleDurabilityMultiplier(float m);
    void setImmunityActive(bool active);
    void setImmunityTimer(float timer);
    void setFootSpeedMultiplier(float m);
    void setFootHPMultiplier(float m);

    void specialPowerUp() override;
    void enterVehicle(Vehicle* v);
    void onVehicleDestroyed();
    void draw() override;
};


// =============================================
// ERI
// =============================================
class Eri : public Soldier {
private:
    float grenadeMultiplier;
    float blastRadiusMultiplier;
    bool doubleThrowActive;
    float doubleThrowTimer;

public:
    Eri();

    float getGrenadeMultiplier() const;
    float getBlastRadiusMultiplier() const;
    bool getDoubleThrowActive() const;
    float getDoubleThrowTimer() const;

    void setGrenadeMultiplier(float m);
    void setBlastRadiusMultiplier(float m);
    void setDoubleThrowActive(bool active);
    void setDoubleThrowTimer(float timer);

    void specialPowerUp() override;
    void throwGrenade();
    void meleeAttack();
    void draw() override;
};


// =============================================
// FIO
// =============================================
class Fio : public Soldier {
private:
    float ammoMultiplier;
    float fireRateMultiplier;
    bool superchargedActive;
    float superchargedTimer;

public:
    Fio();

    float getAmmoMultiplier() const;
    float getFireRateMultiplier() const;
    bool getSuperchargedActive() const;
    float getSuperchargedTimer() const;

    void setAmmoMultiplier(float m);
    void setFireRateMultiplier(float m);
    void setSuperchargedActive(bool active);
    void setSuperchargedTimer(float timer);

    void specialPowerUp() override;
    void pickupWeapon(Weapon* w);
    void draw() override;
};


// =============================================
// FUSION COMPANION
// =============================================
class FusionCompanion : public Soldier {
public:
    FusionCompanion();

    void takeDamage(float dmg)  {}
    void showDamage() {}
    void draw() override;
};


// =============================================
// ENEMY (Abstract)
// =============================================
class Enemy : public GameActor {
protected:
    int id;
    float hp;
    int scoreValue;
    float damage;
    float speed;
    bool isAggro;
    int spawnBatchSize;
    Character* target;

public:
    Enemy();
    virtual ~Enemy();

    int getId() const;
    float getHp() const;
    int getScoreValue() const;
    float getDamage() const;
    float getSpeed() const;
    bool getIsAggro() const;
    int getSpawnBatchSize() const;

    void setId(int id);
    void setHp(float hp);
    void setScoreValue(int score);
    void setDamage(float dmg);
    void setSpeed(float speed);
    void setIsAggro(bool aggro);
    void setSpawnBatchSize(int size);

    void takeDamage(float dmg) ;
    void kill();
    void detectPlayer(Character* c);
    void moveTowardTarget();

    virtual void attack() = 0;
    virtual void draw() = 0;
};


// =============================================
// COLLECTIBLE (Abstract)
// =============================================
class Collectible : public Entity {
public:
    Collectible();
    virtual ~Collectible();

    virtual void onCollect() = 0;
    virtual void draw() = 0;
};


// =============================================
// FOOD
// =============================================
class Food : public Collectible {
private:
    float saturationValue;

public:
    Food();
    Food(float saturationValue);

    float getSaturationValue() const;
    void setSaturationValue(float value);

    void onCollect() override;
    void draw() override;
};


// =============================================
// POW PRISONER
// =============================================
class POWPrisoner : public Collectible {
public:
    POWPrisoner();
    void onCollect() override;
    void draw() override;
};


// =============================================
// SUPPLY CRATE
// =============================================
class SupplyCrate : public Collectible {
private:
    Weapon* weapon;
    int ammo;
    int grenadeCount;

public:
    SupplyCrate();
    virtual ~SupplyCrate();

    Weapon* getWeapon() const;
    int getAmmo() const;
    int getGrenadeCount() const;

    void setWeapon(Weapon* w);
    void setAmmo(int ammo);
    void setGrenadeCount(int count);

    void onCollect() override;
    void draw() override;
};