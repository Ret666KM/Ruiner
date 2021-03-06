﻿#include "Header.h"

/********************************
          Функции Fight
********************************/

Fight::Fight()
	{  //  Конструктор по-умолчанию
	}

Fight::Fight(Basic& data)
	{  //  Конструктор врага
	this->attacker = data;
	this->HP = data.getTotalHealth();
	this->dodgeChance = data.getAgility() * AGILITY_MULTIPLIER;
	}

Fight::Fight(Player& data)
	{  //  Конструктор игрока
	this->attacker = data;
	this->HP = data.getTotalHealth() + data.getArmor();
	this->dodgeChance = data.getAgility() * AGILITY_MULTIPLIER;
	}

int Fight::getHP()
	{  //  Отображение здоровья
	return this->HP;
	}

std::string Fight::getFighterName()
	{  //  Отображение имени
	return this->attacker.getName();
	}

void Fight::strike(Fight& data)
	{  //  Нанесение урона
	data.takeDamage(this->attacker.getTotalDamage());
	}

void Fight::takeDamage(const int& value)
	{  //  Получение урона
	int hitFactor;
	srand(time(NULL));
	hitFactor = rand() % 101;

	if (hitFactor > this->dodgeChance)
		{
		this->HP = this->HP - value;
		mciSendString("play audio/hit.wav", NULL, 0, NULL);
		std::cout << "* * * " << getFighterName() << " RECEIVED " << value << " POINTS DAMAGE! * * *" << std::endl;
		}

	else
		{
		std::cout << "* * * DODGE! * * *" << std::endl;
		}

	std::this_thread::sleep_for(std::chrono::seconds(1));
	}

/********************************
          Битва роботов
********************************/

bool Profile::fight(Basic &data)
	{
	mciSendString("stop audio/start.mp3", NULL, 0, NULL);
	Fight player(*this->currentRobot);
	Fight enemy(data);
	int x, y, result;
	bool exodus;
	mciSendString("play audio/fight.mp3 repeat", NULL, 0, NULL);
		
	std::thread th([&]()
		{  //  Поток битвы врага
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		while (enemy.getHP() > 0 && player.getHP() > 0)
			{
			fightPanel(player, enemy, x, y);
			std::this_thread::sleep_for(std::chrono::seconds(5));
			enemy.strike(player);
			}

		exodus = (exodus != true) ? false : exodus;
		} );
	
	while (enemy.getHP() > 0 && player.getHP() > 0)
		{
		x = rand() % 101;
		y = rand() % 101;
		fightPanel(player, enemy, x, y);
		result = cinDebug();

		if (x + y == result)
			{
			player.strike(enemy);
			}
		else
			{
			std::cout << "* * * MISS! * * *" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}
	
	exodus = (exodus != false) ? true : exodus;
	th.join();

	mciSendString("stop audio/fight.mp3", NULL, 0, NULL);
	return exodus;
}