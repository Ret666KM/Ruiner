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

/*********************************************************
* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
**********************************************************
            **  **      **    ***  **       **
            **  **      **  ***    ****   ****
        **************  *****      ** ** ** **
            **  **      ***        **  ***  **
        **************  *****      **       **
            **  **      **  ***    **       **
            **  **      **    ***  **       **
**********************************************************
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
**********************************************************/

const int PROTECTION_MULTIPLIER = 30;
const int STRENGHT_MULTIPLIER = 5;
const int AGILITY_MULTIPLIER = 8;
const int COST_MULTIPLIER = 100;
const int NUMBER_OF_CLANS = 7;

int cinDebug();  //  Отладчик при вводе неверного типа данных

/********************************
      Характеристики робота
********************************/

struct Robot
	{
	int strength;
	int protection;
	int agility;
	int health = 100;
	int damage = 10;
	std::string name;
	};

/*********************************
       Характеристики вещи
**********************************/

struct Item
	{
	int agilityEffect;
	int damageEffect;
	int armorEffect;
	int cost;
	std::string type;
	std::string name;
	};

/*********************************
        Снаряжение робота
*********************************/

struct Equipment
	{
	Item head;
	Item body;
	Item hands;
	Item legs;
	};

/******************************************************************
   Базовый (виртуальный) класс, на котором строятся игрок и враги
******************************************************************/

class Basic
	{
	public:
		Basic();
		Basic(Robot& data);
		void setAgility(const int& value);
		void setStrenght(const int& value);
		void setProtection(const int& value);
		void setName(const std::string& str);
		void setTotalHealth();
		void setTotalDamage();
		void setCost();
		int getHealth();
		int getStrenght();
		int getProtection();
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

/*********************************
      Класс роботов игрока
*********************************/

class Player : public Basic
	{
	public:
		Player();
		Player(int points);
		void setPoint(int& value);
		void setOutfit(const Item& data);
		void setExperience(const int& value);
		int getArmor();
		int getPoint();
		int getExperience();
		int getCost() override;
		int getAgility() override;
		int getTotalDamage() override;
		bool outfitIsEmpty();
		Equipment getOutfit();
	private:
		Equipment outfit;
		int experience;
		int point;
	};

/*********************************
      Класс врагов-боссов
*********************************/

class Boss : public Basic
	{
	public:
		std::string getReplica(const int& i);
		void setReplica(const std::string& str);
	private:
		std::vector<std::string> replicas;
	};

/*********************************
      Класс боевой системы
*********************************/

class Fight
	{
	public:
		Fight();
		Fight(Basic& data);    //  Конструктор врага
		Fight(Player& data);   //  Конструктор игрока
		void strike(Fight& data);
		void takeDamage(const int& value);
		std::string getFighterName();
		int getHP();
	private:
		int HP;
		int dodgeChance;
		Basic attacker;
	};

/******************************************************************
            Класс, включаещий в себя весь интерфейс
******************************************************************/

class Profile
	{
	public:
		Profile();
		void info(const std::string& str);  //  Строка характеристик робота
		void edit(const std::string& str);  //  Редактор робота
		void menu(const std::string& str);  //  Строка меню
		void fightPanel(Fight& _player, Fight& _enemy, const int& _x, const int& _y);
		void distributeSkills();
		void start();   //  Запуск меню игры
		void store();   //  Вкладка меню "Магазин"
		void robots();  //  Вкладка меню "Роботы"
		void setMobsVector();
		void setStoreVector();
		void setOutfitVector();
		void setStorageList(Item& item);
		void setPlayerList(Player& data);
		void setBossesStack(Basic& data);
		void setCurrentRobot(Player& data);
		void setNameProfile(const std::string& name);
		void showStore(const std::string& filter);
		void putOutfitRobot(const Item& data);
		void showStorage();
		void showRobots();
		void showEnemies();
		bool fight(Basic &data);
		Player getCurrentRobot();
		std::string getNameProfile();
		std::list<Player> getPlayerList();
		std::stack<Basic> getBossesStack();
		std::vector<Basic> getMobsVector();
		std::vector<Item> getStoreVector();
		std::vector<Item*> getOutfitVector();
		std::list<Item> getStorageList();	
	private:
		std::vector<Item*> outfitVector;
		std::vector<Item> storeVector;
		std::vector<Basic> mobsVector;
		std::stack<Basic> bossesStack;
		std::list<Player> playerList;
		std::list<Item> storageList;
		std::list<Item> itemsList;
		std::string nameProfile;
		Player *currentRobot;
		std::string filter;
		int money;
	};

/*********************************
         Класс приложения
*********************************/

class Application
	{
	public:
		void run();
	private:
		std::list<Profile> gameList;
	};

