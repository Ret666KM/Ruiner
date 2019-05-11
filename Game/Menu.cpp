#include "Header.h"

void Profile::info(std::string str)
	{
	system("cls");
	char ch1[11] = { 205,205,205,205,205,205,205,205,205,205,'\0' };
	char ch2[11] = { 177,177,177,177,177,177,177,177,177,177,'\0' };
	std::cout << (char)201 << ch1 << (char)203 << ch1 << ch1 << (char)203 << ch1 << (char)187 << std::endl;
	std::cout << (char)186 << ch2 << (char)186 << str << (char)186 << ch2 << (char)186 << std::endl;
	std::cout << (char)200 << ch1 << (char)202 << ch1 << ch1 << (char)202 << ch1 << (char)188 << std::endl;
	std::cout << " Name: " << "\t\t" << (*currentRobot).getName() << std::endl;
	std::cout << " Health: " << '\t' << (*currentRobot).getTotalHealth() << std::endl;
	std::cout << " Strenght: " << '\t' << (*currentRobot).getStrenght() << std::endl;
	std::cout << " Protection: " << '\t' << (*currentRobot).getProtection() << std::endl;
	std::cout << " Agility: " << '\t' << (*currentRobot).getAgility() << std::endl;
	std::cout << " " << ch1 << (char)205 << ch1 << ch1 << (char)205 << ch1 << " " << std::endl;
	std::cout << " You have " << (*currentRobot).getPoint() << " points" << std::endl;
	std::cout << " " << ch1 << (char)205 << ch1 << ch1 << (char)205 << ch1 << " " << std::endl;
	}

void Profile::menu(std::string str)
	{
	system("cls");
	char ch1[15] = { 205,205,205,205,205,205,205,205,205,205,205,205,205,205,'\0' };
	char ch2[15] = { 177,177,177,177,177,177,177,177,177,177,177,177,177,177,'\0' };
	std::cout << (char)201 << ch1 << ch1 << (char)203 << ch1 << (char)203 << ch1 << ch1 << (char)187 << std::endl;
	std::cout << (char)186 << ch2 << ch2 << (char)186 << str << (char)186 << ch2 << ch2 << (char)186 << std::endl;
	std::cout << (char)200 << ch1 << ch1 << (char)202 << ch1 << (char)202 << ch1 << ch1 << (char)188 << std::endl;

	if (str == "   HOMEPAGE   ")
		{
		std::cout << " 1. Campaign" << "\t 2. Training" << "\t 3. Store" << "\t 4. Robots" << "\t 0. Back" << std::endl;
		}

	else if (str == "   ROBOSTORE  ")
		{
		std::cout << " 1. Weak robot (3 points)\t= $300" << "\n 2. Medium robot (6 points)\t= $600" << "\n 3. Strong robot (9 points)\t= $900" << "\n 0. Back" << std::endl;
		}

	else if (str == "     STORE    ")
		{
		showStore(filter);
		}

	else if (str == "    STORAGE   ")
		{
		showStorage();
		}

	else if (str == "    ROBOTS    ")
		{
		showRobots();
		}

	else if (str == "   TRAINING   ")
		{
		showEnemies();
		}

	std::cout << " " << ch1 << ch1 << (char)205 << ch1 << (char)205 << ch1 << ch1 << " " << std::endl;
	std::cout << " Robot: " << (*this->currentRobot).getName() << "\t XP: " << (*currentRobot).getExperience() << "/1000\t Points: " << (*currentRobot).getPoint() << "\t Money: " << this->money << std::endl;
	std::cout << " " << ch1 << ch1 << (char)205 << ch1 << (char)205 << ch1 << ch1 << " " << std::endl;
	}

void Profile::store()
	{
	filter = "";
	int choice = 1;

	while (choice)
		{
		menu("     STORE    ");
		std::cout << " 1. Buy/sell outfit" << "\t 2. Buy/sell robots" << "\t 3. Filter" << "\t 0. Back\n\n" << " Your choice: ";
		choice = cinDebug();

		switch (choice)
			{
			case 0:
				{
				std::cout << "\n Are you sure?\n\n" << " 0. Yes\n" << " 1. No\n\n" << " Your choice: ";
				choice = cinDebug();
				break;
				}

			case 1:
				{
				while (choice)
					{
					menu("     STORE    ");
					std::cout << " 1. Buy outfit" << "\t 2. Sell outfit" << "\t 0. Back\n\n" << " Your choice: ";
					choice = cinDebug();

					switch (choice)
						{
						case 0:
							{
							break;
							}
					
						case 1:
							{
							int i;
							menu("     STORE    ");
							std::cout << " Enter item's ID: ";
							i = cinDebug();

							if (i <= 0 || i > this->storeVector.size())
								{
								std::cout << " ***ERROR***\n There is no such ID!\n " << std::endl;
								system("pause");
								break;
								}

							else if (this->money < this->storeVector.at(i - 1).cost)
								{
								std::cout << "\n Insufficient funds!" << std::endl;
								system("pause");
								break;
								}

							setStorageList(this->storeVector[i - 1]);
							this->money -= this->storeVector[i - 1].cost;
							break;
							}
						case 2:
							{
							if (this->storageList.empty() == true && (*this->currentRobot).outfitIsEmpty() == true)
							{
								std::cout << "\n Storage is empty!" << std::endl;
								system("pause");
								break;
							}
							
							int i;
							menu("    STORAGE   ");
							std::cout << " 1. Wearing now" << "\t 2. In baggage" << "\t 0. Back\n\n" << " Your choice: ";
							choice = cinDebug();
							
							switch (choice)
								{
								case 0:
									{
									break;
									}
							
								case 1:
									{
									std::cout << " Enter item's ID: ";
									i = cinDebug();

									if (i <= 0 || i > this->getOutfitVector().size())
									{
										std::cout << " ***ERROR***\n There is no such ID!\n " << std::endl;
										system("pause");
										break;
									}

									this->money += this->getOutfitVector()[i - 1]->cost / 2;
									Item a = { 0, 0, 0, 0, this->getOutfitVector()[i - 1]->type, "" };
									(*this->currentRobot).setOutfit(a);
									this->setOutfitVector();
									break;
									}

								case 2:
									{
									std::cout << " Enter item's ID: ";
									i = cinDebug();

									if (i <= 0 || i > this->storageList.size())
									{
										std::cout << " ***ERROR***\n There is no such ID!\n " << std::endl;
										system("pause");
										break;
									}

									auto it = next(this->storageList.begin(), i - 1);
									this->money += (*it).cost / 2;
									this->storageList.erase(it);
									break;
									}

								default:
									{
									std::cout << " ***ERROR***\n There is no such choice!\n " << std::endl;
									system("pause");
									break;
									}
								}
							break;
							}
						default:
							{
							std::cout << " ***ERROR***\n There is no such choice!\n " << std::endl;
							system("pause");
							break;
							}
						}
					}
				choice = 1;
				break;
				}

			case 2:
				{
				while (choice)
					{
					menu("    ROBOTS    ");
					std::cout << " 1. Buy robot" << "\t 2. Sell robot" << "\t 0. Back\n\n" << " Your choice: ";
					choice = cinDebug();

					switch (choice)
						{
						case 0:
							{
							break;
							}
					
						case 1:
							{
							int i;
							menu("   ROBOSTORE  ");
							std::cout << " Your choice: ";
							i = cinDebug();

							if (i < 1 && i > 3)
							{
								std::cout << " ***ERROR***\n There is no such ID!\n " << std::endl;
								system("pause");
								break;
							}

							else if (this->money < i * 3 * COST_MULTIPLIER)
							{
								std::cout << "\n Insufficient funds!" << std::endl;
								system("pause");
								break;
							}

							Player player(i * 3), *tempPlayer = (this->currentRobot);
							setCurrentRobot(player);
							edit(" Create a new robot ");
							setPlayerList(*(this->currentRobot));
							this->money -= (*this->currentRobot).getCost();
							setCurrentRobot(*tempPlayer);
							tempPlayer = nullptr;
							break;
							}

						case 2:
							{
							if (this->playerList.size() <= 1)
							{
								std::cout << "\n You'll haven't robots!" << std::endl;
								system("pause");
								break;
							}

							int i;
							menu("    ROBOTS    ");
							std::cout << " Enter robot's ID: ";
							i = cinDebug();

							if (i <= 0 || i > this->playerList.size())
							{
								std::cout << " ***ERROR***\n There is no such ID!\n " << std::endl;
								system("pause");
								break;
							}

							auto it = next(this->playerList.begin(), i - 1);
							this->money += (*it).getCost();
							this->playerList.erase(it);
							break;
							}

						default:
							{
							std::cout << " ***ERROR***\n There is no such choice!\n " << std::endl;
							system("pause");
							break;
							}
						}
					}
				choice = 2;
				break;
				}

			case 3:
				{
				std::cout << " Filter: ";
				std::cin >> filter;
				filter = (filter == "clear") ? "" : filter;
				break;
				}

			default:
				{
				std::cout << " ***ERROR***\n There is no such choice!\n " << std::endl;
				system("pause");
				break;
				}
			}
		}
	}


void Profile::robots()
	{
	int choice = 1;

	while (choice)
		{
		menu("    ROBOTS    ");
		std::cout << " 1. Choose" << "\t 2. Edit" << "\t 3. Put on/take off outfit" << "\t 0. Back\n\n" << " Your choice: ";
		choice = cinDebug();

		switch (choice)
			{
			case 0:
				{
				std::cout << "\n Are you sure?\n\n" << " 0. Yes\n" << " 1. No\n\n" << " Your choice: ";
				choice = cinDebug();
				break;
				}

			case 1:
				{
				int i;
				menu("    ROBOTS    ");
				std::cout << " Enter robot's ID: ";
				i = cinDebug();
				if (i <= 0 || i > this->playerList.size())
					{
					std::cout << " ***ERROR***\n There is no such ID!\n " << std::endl;
					system("pause");
					break;
					}
				auto it = next(this->playerList.begin(), i - 1);
				setCurrentRobot(*it);
				break;				
				}

			case 2:
				{
				int i;
				menu("    ROBOTS    ");
				std::cout << " Enter robot's ID: ";
				i = cinDebug();

				if (i <= 0 || i > this->playerList.size())
					{
					std::cout << " ***ERROR***\n There is no such ID!\n " << std::endl;
					system("pause");
					break;
					}

				auto it = next(this->playerList.begin(), i - 1);
				Player *tempPlayer = (this->currentRobot);
				setCurrentRobot(*it);
				edit("   Editing a robot   ");
				setCurrentRobot(*tempPlayer);
				tempPlayer = nullptr;
				break;
				}

			case 3:
				{
				if (this->storageList.empty() == true && (*this->currentRobot).outfitIsEmpty() == true)
					{
					std::cout << "\n Storage is empty!" << std::endl;
					system("pause");
					break;
					}

				int i;
				menu("    STORAGE   ");
				std::cout << " 1. Put on" << "\t 2. Take off" << "\t 0. Back\n\n" << " Your choice: ";
				choice = cinDebug();

				switch (choice)
					{
					case 0:
						{
						break;
						}
					case 1:
						{
						std::cout << " Enter item's ID: ";
						i = cinDebug();

						if (i <= 0 || i > this->storageList.size())
						{
							std::cout << " ***ERROR***\n There is no such ID!\n " << std::endl;
							system("pause");
							break;
						}

						auto it = next(this->storageList.begin(), i - 1);
						putOutfitRobot(*it);
						(*this->currentRobot).setOutfit(*it);
						this->setOutfitVector();
						this->storageList.erase(it);
						break;
						}

					case 2:
					{
						std::cout << " Enter item's ID: ";
						i = cinDebug();

						if (i <= 0 || i > this->getOutfitVector().size())
						{
							std::cout << " ***ERROR***\n There is no such ID!\n " << std::endl;
							system("pause");
							break;
						}

						Item a = { 0, 0, 0, 0, this->getOutfitVector()[i - 1]->type, "" };
						putOutfitRobot(a);
						(*this->currentRobot).setOutfit(a);
						this->setOutfitVector();
						break;
					}

					default:
						{
						std::cout << " ***ERROR***\n There is no such choice!\n " << std::endl;
						system("pause");
						break;
						}
					}
				break;
				}

			default:
				{
				std::cout << " ***ERROR***\n There is no such choice!\n " << std::endl;
				system("pause");
				break;
				}
			}
		}
	}

void Profile::start()
{
	mciSendString("play audio/start.mp3 repeat", NULL, 0, NULL);
	setCurrentRobot(playerList.front());
	int choice = 1;

	while (choice)
		{
		menu("   HOMEPAGE   ");
		std::cout << " Your choice: ";
		choice = cinDebug();
		switch (choice)
			{
			case 0:
				{
				mciSendString("stop audio/start.mp3", NULL, 0, NULL);
				break;
				}
			case 1:
				{
				mciSendString("stop audio/start.mp3", NULL, 0, NULL);
				system("pause");
				mciSendString("play audio/start.mp3 repeat", NULL, 0, NULL);
				break;
				}
			case 2:
				{
				menu("   TRAINING   ");
				int i;
				std::cout << " Select enemy!\n" << " If you want to return, enter '0'.\n\n" << " Your choice: ";
				i = cinDebug();
				
				if (i)
					{
					bool currentFight = fight(this->mobsVector[i - 1]);

					if (currentFight)
						{
						std::cout << "\n * * * YOU'RE WIN! * * *" << std::endl;
						int reward = this->mobsVector[i - 1].getCost();
						this->money += reward;
						this->currentRobot->setExperience(reward);
						}

					else
						{
						std::cout << "\n * * * YOU'RE LOSE! * * *" << std::endl;
						}

					system("pause");
					}

				mciSendString("play audio/start.mp3 repeat", NULL, 0, NULL);
				break;
				}
			case 3:
				{
				store();
				break;
				}
			case 4:
				{
				robots();
				break;
				}
			default:
				{
				std::cout << " ***ERROR***\n There is no such choice!\n " << std::endl;
				system("pause");
				break;
				}
			}
		}
	}

void Profile::edit(std::string str)
	{
	int choice = 1;
	while (choice)
		{
		info(str);
		std::cout << " What will you do?\n\n" << " 0. Finish\n" << " 1. Change name\n" << " 2. Edit skills\n\n" << " Your choice: ";
		choice = cinDebug();
		std::cout << std::endl;

		switch (choice)
			{
			case 0:
				{
				if ((*currentRobot).getPoint() > 0)
					{
					std::cout << " You still have unused points!\n " << std::endl;
					system("pause");
					choice = 1;
					break;
					}
				std::cout << " Are you sure that you want to finish?\n\n" << " 0. Yes\n" << " 1. No\n\n" << " Your choice: ";
				choice = cinDebug();
				break;
				}

			case 1:
				{
				info("    Name change     ");
				std::cout << " Enter new name: ";
				std::string name;
				std::cin >> name;
				(*currentRobot).setName(name);
				mciSendString("play audio/set_name.wav", NULL, 0, NULL);
				break;
				}

			case 2:
				{
				distributeSkills();
				break;
				}

			default:
				{
				std::cout << " ***ERROR***\n There is no such choice!\n " << std::endl;
				system("pause");
				break;
				}
			}
		}
	}

void Profile::fightPanel(Fight &_player, Fight &_enemy, int &_x, int &_y)
{
	system("cls");
	char ch1[11] = { 205,205,205,205,205,205,205,205,205,205,'\0' };
	std::cout << ch1 << ch1 << " \t\t\t\t" << ch1 << ch1 << std::endl;
	std::cout << _player.getFighterName() << ": " << _player.getHP() << " HP\t\t\t\t\t" << _enemy.getFighterName() << ": " << _enemy.getHP() << " HP" << std::endl;
	std::cout << ch1 << ch1 << " \t\t\t\t" << ch1 << ch1 << std::endl << std::endl;
	std::cout << _x << " + " << _y << std::endl << std::endl << std::endl;
}

void Profile::distributeSkills()
	{
	std::string choice = "";
	int skill, point = (*currentRobot).getPoint();

	while (choice != "0")
		{
		info("   Skills change    ");
		std::cout << " ***HELP***\n Distribute points between skills. If you want to increase or reduce skill" << std::endl;
		std::cout << " enter the first letter of skill and sign. For instance S+ or A-.\n\n If you want to complete the distribution - enter '0'.\n\n" << " Your choice: ";
		std::cin >> choice;
		choice[0] = toupper(choice[0]);

		if (choice[0] == 'S')
			{
			skill = (*currentRobot).getStrenght();

			if (choice[1] == '+' && skill < 10 && point > 0)
				{
				(*currentRobot).setStrenght(++skill);
				(*currentRobot).setPoint(--point);
				mciSendString("play audio/skill_up.wav", NULL, 0, NULL);
				}

			else if (choice[1] == '-' && skill > 0)
				{
				(*currentRobot).setStrenght(--skill);
				(*currentRobot).setPoint(++point);
				mciSendString("play audio/skill_down.wav", NULL, 0, NULL);
				}
			}
		else if (choice[0] == 'P')
			{
			skill = (*currentRobot).getProtection();

			if (choice[1] == '+' && skill < 10 && point > 0)
				{
				(*currentRobot).setProtection(++skill);
				(*currentRobot).setPoint(--point);
				mciSendString("play audio/skill_up.wav", NULL, 0, NULL);
				}

			else if (choice[1] == '-' && skill > 0)
				{
				(*currentRobot).setProtection(--skill);
				(*currentRobot).setPoint(++point);
				mciSendString("play audio/skill_down.wav", NULL, 0, NULL);

				}
			}

		else if (choice[0] == 'A')
			{
			skill = (*currentRobot).getAgility();

			if (choice[1] == '+' && skill < 10 && point > 0)
				{
				(*currentRobot).setAgility(++skill);
				(*currentRobot).setPoint(--point);
				mciSendString("play audio/skill_up.wav", NULL, 0, NULL);
				}

			else if (choice[1] == '-' && skill > 0)
				{
				(*currentRobot).setAgility(--skill);
				(*currentRobot).setPoint(++point);
				mciSendString("play audio/skill_down.wav", NULL, 0, NULL);
				}
			}
		}
	mciSendString("play audio/choice.wav", NULL, 0, NULL);
	(*currentRobot).setCost();
	}

void Profile::setStorageList(Item & item)
	{
	this->storageList.push_back(item);
	}

std::list<Player> Profile::getPlayerList()
	{
	return this->playerList;
	}

std::stack<Basic> Profile::getBossesStack()
	{
	return this->bossesPlayerStack;
	}

std::vector<Basic> Profile::getMobsVector()
	{
	return this->mobsVector;
	}

void Profile::showStore(std::string &filter)
	{
	std::cout << " ID: \tAg-ty: \tDmg: \tArmor: \tCost: \tType: \t\tName:" << std::endl;

	for (int i = 0; i < this->storeVector.size(); ++i)
		{
		if (filter == "" || storeVector[i].type == filter)
			{
			std::cout << " " << i+1 << " \t" << storeVector[i].agilityEffect << " \t" << storeVector[i].damageEffect << " \t" << storeVector[i].armorEffect;
			std::cout << " \t" << storeVector[i].cost << " \t" << storeVector[i].type << " \t\t" << storeVector[i].name << std::endl;
			}
		}
	}

void Profile::showStorage()
	{
	std::cout << "=== Wearing now ===\n" << std::endl;

	if ((*this->currentRobot).outfitIsEmpty() == false)
		{
		std::cout << " ID: \tAg-ty: \tDmg: \tArmor: \tCost: \tType: \t\tName:" << std::endl;

		if ((*this->currentRobot).getOutfit().head.name != "")
			{
			std::cout << " " << 1 << " \t" << (*this->currentRobot).getOutfit().head.agilityEffect << " \t" << (*this->currentRobot).getOutfit().head.damageEffect << " \t" << (*this->currentRobot).getOutfit().head.armorEffect;
			std::cout << " \t" << (*this->currentRobot).getOutfit().head.cost / 2 << " \t" << (*this->currentRobot).getOutfit().head.type << " \t\t" << (*this->currentRobot).getOutfit().head.name << std::endl;
			}

		if ((*this->currentRobot).getOutfit().body.name != "")
			{
			std::cout << " " << 2 << " \t" << (*this->currentRobot).getOutfit().body.agilityEffect << " \t" << (*this->currentRobot).getOutfit().body.damageEffect << " \t" << (*this->currentRobot).getOutfit().body.armorEffect;
			std::cout << " \t" << (*this->currentRobot).getOutfit().body.cost / 2 << " \t" << (*this->currentRobot).getOutfit().body.type << " \t\t" << (*this->currentRobot).getOutfit().body.name << std::endl;
			}

		if ((*this->currentRobot).getOutfit().hands.name != "")
			{
			std::cout << " " << 3 << " \t" << (*this->currentRobot).getOutfit().hands.agilityEffect << " \t" << (*this->currentRobot).getOutfit().hands.damageEffect << " \t" << (*this->currentRobot).getOutfit().hands.armorEffect;
			std::cout << " \t" << (*this->currentRobot).getOutfit().hands.cost / 2 << " \t" << (*this->currentRobot).getOutfit().hands.type << " \t\t" << (*this->currentRobot).getOutfit().hands.name << std::endl;
			}

		if ((*this->currentRobot).getOutfit().legs.name != "")
			{
			std::cout << " " << 4 << " \t" << (*this->currentRobot).getOutfit().legs.agilityEffect << " \t" << (*this->currentRobot).getOutfit().legs.damageEffect << " \t" << (*this->currentRobot).getOutfit().legs.armorEffect;
			std::cout << " \t" << (*this->currentRobot).getOutfit().legs.cost / 2 << " \t" << (*this->currentRobot).getOutfit().legs.type << " \t\t" << (*this->currentRobot).getOutfit().legs.name << std::endl;
			}
		}

	std::cout << std::endl;
	std::cout << "=== In baggage ===\n" << std::endl;

	if (this->storageList.empty() == false)
		{
		int i = 1;
		std::cout << " ID: \tAg-ty: \tDmg: \tArmor: \tCost: \tType: \t\tName:" << std::endl;

		for (auto it : this->storageList)
			{
			std::cout << " " << i << " \t" << it.agilityEffect << " \t" << it.damageEffect << " \t" << it.armorEffect;
			std::cout << " \t" << it.cost / 2 << " \t" << it.type << " \t\t" << it.name << std::endl;
			++i;
			}
		}

	std::cout << std::endl;
	}

void Profile::showRobots()
	{
	int i = 1;
	std::cout << " ID: \tS: \tP: \tA: \tHP: \tArmor: \tDmg: \tCost: \tName:" << std::endl;

	for (auto it : this->playerList)
		{
		std::cout << " " << i << " \t" << it.getStrenght() << " \t" << it.getProtection() << " \t" << it.getAgility() << " \t" << it.getTotalHealth();
		std::cout << " \t" << it.getArmor() << " \t" << it.getTotalDamage() << " \t" << it.getCost() << " \t" << it.getName() << std::endl;
		++i;
		}
	}

void Profile::showEnemies()
{
	std::cout << " ID: \tDmg: \tHP: \tClan:" << std::endl;

	for (int i = 0; i < this->mobsVector.size(); ++i)
	{
		std::cout << " " << i + 1 << " \t" << this->mobsVector[i].getTotalDamage() << " \t" << this->mobsVector[i].getTotalHealth() << " \t" << this->mobsVector[i].getName() << std::endl;
	}
}

std::vector<Item> Profile::getStoreVector()
	{
	return this->storeVector;
	}

std::vector<Item*> Profile::getOutfitVector()
{
	return this->outfitVector;
}

std::list<Item> Profile::getStorageList()
	{
	return this->storageList;
	}

Profile::Profile()
	{
	this->money = 500;
	this->bossesPlayerStack;
	setMobsVector();
	setStoreVector();
	
	}

void Profile::setStoreVector()
	{
	this->storeVector = { {  2, 0, 1, 300,  "head",  "Copper Helmet"      },
						  {  2, 0, 2, 400,  "body",  "Copper Armor"       },
						  {  2, 1, 1, 350,  "hands", "Copper Gauntlets"   },
						  {  2, 1, 1, 350,  "legs",  "Copper Boots"       },
						  {  1, 1, 2, 600,  "head",  "Iron Helmet"        },
						  {  1, 1, 3, 700,  "body",  "Iron Armor"         },
						  {  1, 2, 2, 650,  "hands", "Iron Gauntlets"     },
						  {  1, 2, 2, 650,  "legs",  "Iron Boots"         },
						  {  0, 1, 4, 1100, "head",  "Titanium Helmet"    },
						  {  0, 2, 5, 1300, "body",  "Titanium Armor"     },
						  {  0, 3, 4, 1250, "hands", "Titanium Gauntlets" },
						  {  0, 3, 4, 1250, "legs",  "Titanium Boots"     },
						  { -1, 5, 3, 1400, "head",  "Chromic Helmet"     },
						  { -3, 5, 5, 1600, "body",  "Chromic Armor"      },
						  { -1, 8, 4, 1500, "hands", "Chromic Gauntlets"  },
						  { -1, 8, 4, 1500, "legs",  "Chromic Boots"      },
						  { -2, 2, 5, 1750, "head",  "Tungsten Helmet"    },
						  { -4, 2, 8, 2000, "body",  "Tungsten Armor"     },
						  { -3, 3, 6, 1800, "hands", "Tungsten Gauntlets" },
						  { -3, 3, 6, 1800, "legs",  "Tungsten Boots"     } };
	}


void Profile::setMobsVector()
	{
	std::vector<Robot> enemies = { { 1, 1, 1, 100, 10, "Renegade" },
								   { 2, 4, 2, 150, 15, "Guardian" },
								   { 3, 3, 2, 150, 15, "Observer" },
								   { 3, 6, 4, 200, 20, "Armadillo"},
								   { 6, 2, 5, 200, 20, "Hunter"   },
								   { 7, 3, 8, 250, 25, "Assassin" },
								   { 9, 6, 3, 250, 25, "Panzer"   } };
		
	for (int i = 0; i < NUMBER_OF_CLANS; ++i)
		{
		Basic current(enemies[i]);
		this->mobsVector.push_back(current);
		}
	}

void Profile::setOutfitVector()
{
	if ((*this->currentRobot).getOutfit().head.name != "")
	{
		this->outfitVector.push_back(new Item((*this->currentRobot).getOutfit().head));
	}

	if ((*this->currentRobot).getOutfit().body.name != "")
	{
		this->outfitVector.push_back(new Item((*this->currentRobot).getOutfit().body));
	}

	if ((*this->currentRobot).getOutfit().hands.name != "")
	{
		this->outfitVector.push_back(new Item((*this->currentRobot).getOutfit().hands));
	}

	if ((*this->currentRobot).getOutfit().legs.name != "")
	{
		this->outfitVector.push_back(new Item((*this->currentRobot).getOutfit().legs));
	}
}

void Profile::putOutfitRobot(Item &data)
	{
	if ((*this->currentRobot).getOutfit().head.type == data.type)
		{
		if ((*this->currentRobot).getOutfit().head.name != "")
			{
			this->storageList.push_back((*this->currentRobot).getOutfit().head);
			}
		}

	else if ((*this->currentRobot).getOutfit().body.type == data.type)
		{
		if ((*this->currentRobot).getOutfit().body.name != "")
			{
			this->storageList.push_back((*this->currentRobot).getOutfit().body);
			}
		}

	else if ((*this->currentRobot).getOutfit().hands.type == data.type)
		{
		if ((*this->currentRobot).getOutfit().hands.name != "")
			{
			this->storageList.push_back((*this->currentRobot).getOutfit().hands);
			}
		}

	else if ((*this->currentRobot).getOutfit().legs.type == data.type)
		{
		if ((*this->currentRobot).getOutfit().legs.name != "")
			{
			this->storageList.push_back((*this->currentRobot).getOutfit().legs);
			}
		}
	}

std::string Profile::getNameProfile()
	{
	return this->nameProfile;
	}

Player Profile::getCurrentRobot()
	{
	return *(this->currentRobot);
	}

void Profile::setCurrentRobot(Player &data)
	{
	this->currentRobot = &data;
	}

void Profile::setPlayerList(Player &data)
	{
	this->playerList.push_back(data);
	}

void Profile::setBossesStack(Basic &data)
	{
	this->bossesPlayerStack.push(data);
	}

void Profile::setNameProfile(std::string &name)
	{
	this->nameProfile = name;
	}

