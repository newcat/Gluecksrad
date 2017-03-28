#include "Player.h"


Player::Player(std::string name_)
{
	name = name_;

	balance = 0;
	total = 0;
	extraSpins = 0;

}

int Player::getTotal() const {
	return total;
}

int Player::getBalance() const {
	return balance;
}

int Player::getExtraSpins() const {
	return extraSpins;
}

std::string Player::getName() const {
	return name;
}

void Player::reset(){
	balance = 0;
	extraSpins = 0;
}

void Player::setBalance(int newBalance) {
	balance = newBalance;
}

void Player::addBalanceToTotal() {
	total += balance;
	balance = 0;
}

void Player::setExtraSpins(int newSpins) {
	extraSpins = newSpins;
}