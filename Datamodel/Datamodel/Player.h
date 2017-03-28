#pragma once

#include <string>


class Player
{
public:
	Player(std::string name);
	void reset();
	int getBalance() const;
	int getTotal() const;
	int getExtraSpins() const;
	std::string getName() const;
	void setBalance(int newBalance);
	void addBalanceToTotal();
	void setExtraSpins(int newSpins);


private:

	int total, balance, extraSpins;
	std::string name;



};

