#include "Header.h"

/********************************
          Функции Basic
********************************/

Basic::Basic()
	{  //  Конструктор по-умолчанию
	}

Basic::Basic(Robot &data)
	{  //  Конструктор роботов
	this->node = data;
	setTotalHealth();
	setTotalDamage();
	setCost();
	}

void Basic::setStrenght(const int& value)
	{  //  Установление показателя силы
	this->node.strength = value;
	setTotalDamage();
	}

void Basic::setProtection(const int& value)
	{  //  Установление показателя защиты
	this->node.protection = value;
	setTotalHealth();
	}

void Basic::setAgility(const int& value)
	{  //  Установление показателя ловкости
	this->node.agility = value;
	}

void Basic::setName(const std::string& str)
	{  //  Установление имени робота
	this->node.name = str;
	}

void Basic::setCost()
	{  //  Установление ценности робота
	this->cost = COST_MULTIPLIER * (getStrenght() + getProtection() + getAgility());
	}

void Basic::setTotalDamage()
	{  //  Установление урона
	this->totalDamage = this->node.strength * STRENGHT_MULTIPLIER + this->node.damage;
	}

void Basic::setTotalHealth()
	{  //  Установление полного здоровья
	this->totalHealth = this->node.protection * PROTECTION_MULTIPLIER + this->node.health;
	}

int Basic::getStrenght()
	{  //  Отображение показателя силы
	return this->node.strength;
	}

int Basic::getProtection()
	{  //  Отображение показателя защиты
	return this->node.protection;
	}

int Basic::getAgility()
	{  //  Отображение показателя ловкости
	return this->node.agility;
	}

int Basic::getHealth()
	{  //  Отображение здоровья
	return this->node.health;
	}

std::string Basic::getName()
	{  //  Отображение имени робота
	return this->node.name;
	}

int Basic::getCost()
	{  //  Отображение ценности робота
	return this->cost / 2;
	}

int Basic::getTotalHealth()
	{  //  Отображение полного здоровья
	return this->totalHealth;
	}

int Basic::getTotalDamage()
	{  //  Отображение урона
	return this->totalDamage;
	}

/********************************
          Функции Boss
********************************/

std::string Boss::getReplica(const int& i)
	{  //  Отображение реплики
	return this->replicas[i];
	}

void Boss::setReplica(const std::string& str)
	{  //  Установление реплики
	this->replicas.push_back(str);
	}

/********************************
         Функции Player
********************************/

Player::Player()
	{  //  Конструктор по-умолчанию
	}

Player::Player(int points)
	{  //  Конструктор робота игрока
	setPoint(points);
	setStrenght(0);
	setProtection(0);
	setAgility(0);
	setName("Unnamed");
	this->experience = 0;
	this->outfit = { { 0, 0, 0, 0, "head" , "" }, 
					 { 0, 0, 0, 0, "body" , "" }, 
					 { 0, 0, 0, 0, "hands", "" }, 
					 { 0, 0, 0, 0, "legs" , "" } };
	}

void Player::setPoint(int& value)
	{  //  Добавление очков
	this->point = value;
	}

void Player::setExperience(const int& value)
	{  //  Добавление опыта
	this->experience += value;
	}

void Player::setOutfit(const Item &data)
	{  //  Добавление экипировки
	if (this->outfit.head.type == data.type)
		{
		this->outfit.head = data;
		}
	else if (this->outfit.body.type == data.type)
		{
		this->outfit.body = data;
		}
	else if (this->outfit.hands.type == data.type)
		{
		this->outfit.hands = data;
		}
	else if (this->outfit.legs.type == data.type)
		{
		this->outfit.legs = data;
		}
	}

int Player::getPoint()
	{  //  Отображение количества очков
	return this->point;
	}

int Player::getExperience()
	{  //  Отображение опыта
	return this->experience;
	}

Equipment Player::getOutfit()
	{  //  Отображение снаряжения
	return this->outfit;
	}

int Player::getCost()
	{  //  Отображение ценности с учётом экипировки
	return (this->cost + this->outfit.head.cost + this->outfit.body.cost + 
			this->outfit.hands.cost + this->outfit.legs.cost) / 2;
	}

int Player::getArmor()
	{  //  Отображение показателя брони
	return this->outfit.head.armorEffect + this->outfit.body.armorEffect + 
		   this->outfit.hands.armorEffect + this->outfit.legs.armorEffect;
	}

bool Player::outfitIsEmpty()
	{  //  Проверка на наличие экипировки
	return (this->outfit.head.name == "" && this->outfit.body.name == "" && 
			this->outfit.hands.name == "" && this->outfit.legs.name == "");
	}

int Player::getAgility()
	{  //  Отображение показателя ловкости с учётом экипировки
	return this->node.agility + this->outfit.head.agilityEffect + this->outfit.body.agilityEffect + 
		   this->outfit.hands.agilityEffect + this->outfit.legs.agilityEffect;
	}

int Player::getTotalDamage()
	{  //  Отображение урона с учётом экипировки
	return this->totalDamage = this->node.strength * STRENGHT_MULTIPLIER + this->node.damage 
							 + this->outfit.head.damageEffect + this->outfit.body.damageEffect 
							 + this->outfit.hands.damageEffect + this->outfit.legs.damageEffect;
	}

/********************************
        Запуск приложения
********************************/

void Application::run()
	{
	Profile game;
	int choice;
	mciSendString("play audio/run.mp3 repeat", NULL, 0, NULL);
	
	while (true)
		{
		system("cls");
		int i = 0;
		std::cout << " 0. New game" << std::endl;

		for (auto it : gameList)
			{
			std::cout << " " << i + 1 << ". " << it.getNameProfile() << std::endl;
			++i;
			}

		std::cout << "\n Your choice: ";
		choice = cinDebug();
		
		if (choice == 0)
			{
			std::cout << "\n Enter profile's name: ";
			std::string name;
			std::cin >> name;
			game.setNameProfile(name);
			mciSendString("play audio/set_name.wav", NULL, 0, NULL);
			Player player(3);
			game.setCurrentRobot(player);
			game.edit(" Create a new robot ");
			game.setPlayerList(player);
			this->gameList.push_back(game);
			break;
			}
		else if (gameList.size() != 0 && choice <= gameList.size() + 1)
			{
			auto it = next(gameList.begin(), choice);
			game = *it;
			break;
			}
		else
			{
			std::cout << " ***ERROR***\n There is no such choice!\n " << std::endl;
			system("pause");
			}
		}
	
	mciSendString("stop audio/run.mp3", NULL, 0, NULL);
	game.start();
	}

/****************************************************************
            Отладчик при вводе неверного типа данных
****************************************************************/

int cinDebug()
	{
	int choice;
	std::cin >> choice;
	mciSendString("play audio/choice.wav", NULL, 0, NULL);

	if (!std::cin)
		{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return -1;
		}
	else
		{
		return choice;
		}
	}

/********************************
     Точка старта программы
********************************/

int main()
	{
	srand(time(0));
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_RED);
	Application app;
	app.run();
	system("pause");
	return 0;
	}