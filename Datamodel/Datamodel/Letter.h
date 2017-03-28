#pragma once
class Letter
{
public:
	Letter();
	Letter(char letter);	
	bool isVisible() const;	
	void setVisible(bool visible);
	char getChar() const;
	~Letter(void);
private:
	char letter_;
	bool visible_;

};

