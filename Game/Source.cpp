#include "Header.h"

Basic::Basic()
	{
	}

Basic::Basic(Robot &data)
	{ // Пример описания
	this->node = data;
	setTotalHealth();
	setTotalDamage();
	setCost();
	}

void Basic::setStrenght(int value)
	{
	this->node.strength = value;
	setTotalDamage();
	}

void Basic::setProtection(int value)
	{
	this->node.protection = value;
	setTotalHealth();
	}

void Basic::setAgility(int value)
	{
	this->node.agility = value;
	}

void Basic::setTotalHealth()
	{
	this->totalHealth = this->node.protection * PROTECTION_MULTIPLIER + this->node.health;
	}

void Basic::setTotalDamage()
	{
	this->totalDamage = this->node.strength * STRENGHT_MULTIPLIER + this->node.damage;
	}

void Basic::setName(std::string str)
	{
	this->node.name = str;
	}

void Basic::setCost()
	{
	this->cost = COST_MULTIPLIER * (getStrenght() + getProtection() + getAgility());
	}

int Player::getArmor()
{
	return this->outfit.head.armorEffect + this->outfit.body.armorEffect + this->outfit.hands.armorEffect + this->outfit.legs.armorEffect;
}

int Player::getAgility()
{
	return this->node.agility + this->outfit.head.agilityEffect + this->outfit.body.agilityEffect + this->outfit.hands.agilityEffect + this->outfit.legs.agilityEffect;
}

int Player::getTotalDamage()
{
	return this->totalDamage = this->node.strength * STRENGHT_MULTIPLIER + this->node.damage + this->outfit.head.damageEffect + this->outfit.body.damageEffect + this->outfit.hands.damageEffect + this->outfit.legs.damageEffect;
}

int Basic::getStrenght()
	{
	return this->node.strength;
	}

int Basic::getProtection()
	{
	return this->node.protection;
	}

int Basic::getAgility()
	{
	return this->node.agility;
	}

int Basic::getHealth()
	{
	return this->node.health;
	}

std::string Basic::getName()
	{
	return this->node.name;
	}

int Basic::getCost()
	{
	return this->cost / 2;
	}

int Player::getCost()
{
	return (this->cost + this->outfit.head.cost + this->outfit.body.cost + this->outfit.hands.cost + this->outfit.legs.cost) / 2;
}

bool Player::outfitIsEmpty()
{
	if (this->outfit.head.name == "" && this->outfit.body.name == "" && this->outfit.hands.name == "" && this->outfit.legs.name == "")
		{
		return true;
		}
	else
		{
		return false;
		}
}

Equipment Player::getOutfit()
{
	return this->outfit;
}

int Basic::getTotalHealth()
	{
	return this->totalHealth;
	}

int Basic::getTotalDamage()
	{
	return this->totalDamage;
	}


std::string Boss::getReplica(int &i)
	{
	return this->replicas[i];
	}

void Boss::setReplica(std::string str)
	{
	this->replicas.push_back(str);
	}

Player::Player()
	{
	}

Player::Player(int points)
	{
	setPoint(points);
	setStrenght(0);
	setProtection(0);
	setAgility(0);
	setName("Unnamed");
	this->experience = 0;
	this->outfit = { { 0, 0, 0, 0, "head", ""}, { 0, 0, 0, 0, "body", ""}, { 0, 0, 0, 0, "hands", ""}, { 0, 0, 0, 0, "legs", ""} };
	}

void Player::setOutfit(Item &data)
	{
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

void Player::setExperience(int value)
	{
	this->experience += value;
	}

void Player::setPoint(int value)
	{
	this->point = value;
	}

int Player::getExperience()
	{
	return this->experience;
	}

int Player::getPoint()
	{
	return this->point;
	}

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