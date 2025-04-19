#include "used.hpp"

class NameBlock
{
protected:
public:
	
};

class ChoosedBroad
{
protected:
	std::vector<NameBlock*> chdName,allName;
	
	// area 1 
	int x1, y1, xx1, yy1, cr1 , cg1 , cb1 ;
	
public:
	
	bool chOne(NameBlock &One);
	bool delOne(NameBlock &One);
	bool getXyOne(int &x ,int &y ,NameBlock &One);
}chbroad;


