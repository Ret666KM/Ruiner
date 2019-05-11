#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <time.h> 
#include <thread>
#include <chrono>
#include <limits>
#include <vector>
#include <stack>
#include <list>

#pragma comment(lib,"Winmm.lib")

#undef max

const int PROTECTION_MULTIPLIER = 30;
const int STRENGHT_MULTIPLIER = 5;
const int AGILITY_MULTIPLIER = 8;
const int COST_MULTIPLIER = 100;
const int NUMBER_OF_CLANS = 7;

int cinDebug();

struct Robot
	{
	int strength;
	int protection;
	int agility;
	int health = 100;
	int damage = 10;
	std::string name;
	};

struct Item
	{
	int agilityEffect;
	int damageEffect;
	int armorEffect;
	int cost;
	std::string type;
	std::string name;
	};

struct Equipment
{
	Item head;
	Item body;
	Item hands;
	Item legs;
};

class Basic
	{
	public:
		Basic();
		Basic(Robot &data);
		void setStrenght(int value);
		void setProtection(int value);
		void setAgility(int value);
		void setName(std::string str);
		void setTotalHealth();
		void setTotalDamage();
		void setCost();
		int getStrenght();
		int getProtection();
		int getHealth();
		int getTotalHealth();
		virtual int getCost();
		virtual int getAgility();
		virtual int getTotalDamage();
		std::string getName();

	protected:
		Robot node;
		int totalHealth;
		int totalDamage;
		int cost;
	};

class Player : public Basic
	{
	public:
		Player();
		Player(int points);
		void setOutfit(Item &data);
		void setExperience(int value);
		void setPoint(int value);
		int getArmor();
		int getCost() override;
		int getAgility() override;
		int getTotalDamage() override;
		int getExperience();
		int getPoint();
		bool outfitIsEmpty();
		Equipment getOutfit();
		
	private:
		Equipment outfit;
		int experience;
		int point;
	};

class Boss : public Basic
	{
	public:
		std::string getReplica(int &i);
		void setReplica(std::string str);

	private:
		std::vector<std::string> replicas;
	};


class Fight
	{
	public:
		Fight();
		Fight(Basic &data);
		Fight(Player &data);
		int getHP();
		void strike(Fight &data);
		void takeDamage(int value);
		std::string getFighterName();

	private:
		int HP;
		int dodgeChance;
		Basic attacker;
	};


class Profile
	{
	public:
		Profile();
		void info(std::string str);
		void menu(std::string str);
		void edit(std::string str);
		void fightPanel(Fight &_player, Fight &_enemy, int &_x, int &_y);
		void distributeSkills();
		void start();
		void store();
		void robots();
		void setMobsVector();
		void setStoreVector();
		void setOutfitVector();
		void setPlayerList(Player &data);
		void setBossesStack(Basic &data);
		void setCurrentRobot(Player &data);
		void setNameProfile(std::string &name);
		void setStorageList(Item &item);
		void putOutfitRobot(Item &data);
		void showStore(std::string &filter);
		void showStorage();
		void showRobots();
		void showEnemies();
		bool fight(Basic &data);
		Player getCurrentRobot();
		std::list<Player> getPlayerList();
		std::stack<Basic> getBossesStack();
		std::vector<Basic> getMobsVector();
		std::vector<Item> getStoreVector();
		std::vector<Item*> getOutfitVector();
		std::list<Item> getStorageList();
		std::string getNameProfile();
			
	private:
		std::list<Player> playerList;
		std::vector<Basic> mobsVector;
		std::stack<Basic> bossesPlayerStack;
		std::vector<Item*> outfitVector;
		std::vector<Item> storeVector;
		std::list<Item> storageList;
		std::list<Item> itemsList;
		std::string nameProfile;
		Player *currentRobot;
		std::string filter;
		int money;
	};

class Application
	{
	public:
		void run();

	private:
		std::list<Profile> gameList;
	};

