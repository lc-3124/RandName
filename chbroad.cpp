#include "used.hpp"

class NameBlock
{
protected:
	std::atomic<float> x , y , w , l ;
	
public:
	
};

class ChoosedBroad
{
protected:
	std::vector<NameBlock*> chdName,allName;
	
	// area 1: xyz |   color R G B       |
	int x1, y1, xx1, yy1, cr1 , cg1 , cb1 ;
	// area 2      |                     |
	int x2, y2, xx2, yy2, cr2 , cg2 , cb2 ;
	
public:
	
	bool chOne(NameBlock &One);
	bool delOne(NameBlock &One);
	bool getXyOne(int &x ,int &y ,NameBlock &One);
}chbroad;


