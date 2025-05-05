#include "used.hpp"
#include "gofor.cpp"
#include "mmsystem.h"
//#pragma comment(lib,"winmm.lib")
class NameBlock
{
protected:
	
	std::string label;
	bool ischd = 0 ;
	int cur_stamp = 0 ;
public:
	std::atomic<float> x , y , w , h , sp , dr ;
	
	NameBlock(std::string name )
	{
		this->x .store(100);
		this->y .store(100);
		this->w .store(90);
		this->h .store(30);
		this->sp.store(10);
		this->dr.store(0 * F_PI);
		this->label = name;
	}
	
	std::string getname(){return this->label;}
	void setchd(bool is){this->ischd = is;};
	bool isChd(){return ischd;};
	void moveprocess(int stamp )
	{
		if(ischd ==1 )return;
		// sp(px)/1000ms
		if(stamp - this->cur_stamp >= 10 )
		{
			this->cur_stamp = stamp;
			this->x.store(x.load() + static_cast<float>(cos(this->dr) * sp /100)); 
			this->y.store(y.load() + static_cast<float>(sin(this->dr) * sp /100)); 
			// TODO
			if(x.load() >= 1200 - w.load()
				|| x.load() <= 0)
			{
				dr.store(PI - dr.load());
			}
			if(y.load() >= 800 - h.load()
				|| y.load() <= 0)
			{
				dr.store(-dr.load());
			}
		}
	};
};

class ChoosedBroad
{
protected:
	
	// area 1: xyz |   color R G B       |
	int x1, y1, xx1, yy1, cr1 , cg1 , cb1 ;
	// area 2      |                     |
	int x2, y2, xx2, yy2, cr2 , cg2 , cb2 ;
	
public:
	std::vector<NameBlock*> chdName,allName,killedname;
	bool chOne(NameBlock *One)
	{
		for(int index ; allName.size() ; index ++)
		{
			
		}
		return 0;
	};
	bool delOne(NameBlock *One);
	bool getXyOne(int &x ,int &y ,NameBlock &One);
	NameBlock*  randchOne();
	
	void readfromfile() 
	{
		// read from file and store into a tmp vector
		std::vector<std::string> names , killednames;
		std::fstream file;
		file.open(NAME_PATH, std::ios::in);
		std::string line;
		while (std::getline(file, line)) {
			// std::cout<<line<<std::endl;
			if (!line.empty() && line.find_first_not_of(' ') != std::string::npos) {
				names.push_back(line);
			}
		}
		file.close();
		file.open(NAME_PATH2);
		while (std::getline(file,line)) {
			if (!line.empty() && line.find_first_not_of(' ') != std::string::npos) {
				killednames.push_back(line);
			}
		}
		// move names to NameBlock list
		for(std::string i : names){			
		NameBlock *nb_tmp = new NameBlock(i);
		this-> allName.push_back(nb_tmp);
		}
		for(std::string i : killednames){
			NameBlock *nb_tmp = new NameBlock(i);
			this-> killedname.push_back(nb_tmp);
		}
		// done
	};

	void initrand()
	{ 
	
		 srand((unsigned)time(NULL));
	for(NameBlock *nb_tmp : allName)
		{
			nb_tmp->sp.store(rand()%900+100);
			nb_tmp->dr.store(float(rand()%360) /PI /2.0f);
		}
	};
	
	void writedata()
	{
		// only write the data of killed(chdname) namelist
		std::ofstream file(NAME_PATH2, std::ios::out | std::ios::trunc);
		for (NameBlock *nb_tmp : this->chdName) {
			file << nb_tmp->getname() << "\n"; 
		}
		file.close();
	}; 
	
	void draw()
	{	
		for( NameBlock* nb_tmp : this->allName)
		{
		int x = nb_tmp->x.load();
		int y = nb_tmp->y.load();
		int w = nb_tmp->w.load();
		int h = nb_tmp->h.load();
		
		setfillcolor(RGB(50, 50, 50));
		bar(x, y, x + w, y + h);
		
		// figure out the size of fonts
		const float font_height = std::min(w, h) / 6.0f*5.0f;
		
		// set fonts
			if(nb_tmp->isChd() == 1) setfont(font_height+1, 0, "Noto Sans CJK");
			else	setfont(font_height, 0, "Noto Sans CJK SC");
		setbkmode(TRANSPARENT);
		setcolor(WHITE); 
		
		// figure out the pos of fonts
		std::string text = UTF8ToGBK(nb_tmp->getname().c_str());
		//std::string text = this->label;
		const int text_width = textwidth(text.c_str());
		const int text_height = textheight(text.c_str());
		
		// text pos
		const float text_x = x + (w - text_width) / 2;
		const float text_y = y + (h - text_height) / 2;
		
		// draw
		xyprintf(text_x, text_y, "%s", text.c_str());
		// std::cout<<text<<std::endl;
		//outtextxy(this->allName[0]->x.load(),this->allName[0]->y.load(),this->allName[0]->getname().c_str());
		}
	};
	
}chbroad;

class circlecatcher
{
protected:
	std::atomic<float> x , y , r ;
	int ix,iy,tx,ty,mx = 550,my = 370;
	int need;
	bool isShow = 0;
public:
	// cg
	void appear()
	{
		this->isShow = 1;
		x.store(ix);
		y.store(iy);
	};
	void bigshape()
	{
		std::thread ap([this](){
			thgofora(0,1300,800,this->r);
		});ap.join();
	};
	void catchnb()
	{
		std::thread cx([this](){
			thgofora(ix,tx,800,this->x);
		});
		
		std::thread cy([this](){
			thgofora(iy,ty,800,this->y);
		});
		
		std::thread sm([this](){
			thgofora(1300,50,800,this->r);
		});sm.join();cy.join();cx.join();
	};
	void letMid()
	{
		PlayAsync("wa.mp3");
		std::thread ccx([this](){
			thgofora(tx,mx+45,800,this->x);
		});
		std::thread ccy([this](){
			thgofora(ty,my+15,800,this->y);
		});
		std::thread bbx([this](){
			thgofora(chbroad.allName[need]->x.load(),mx,800,chbroad.allName[need]->x);
		});
		std::thread bby([this](){
			thgofora(chbroad.allName[need]->y.load(),my,800,chbroad.allName[need]->y);
		});bby.join();bbx.join();ccy.join();ccx.join();
		
		// big
		
		std::thread bg([this](){
			thgoforb(50,300,400,this->r);
		});
		std::thread bx([this](){
			thgoforb(chbroad.allName[need]->x.load(),mx-200,400,chbroad.allName[need]->x);
		});
		std::thread by([this](){
			thgoforb(chbroad.allName[need]->y.load(),my-50,400,chbroad.allName[need]->y);
		});
		std::thread bw([this](){
			thgoforb(chbroad.allName[need]->w.load(),490,400,chbroad.allName[need]->w);
		});
		std::thread bh([this](){
			thgoforb(chbroad.allName[need]->h.load(),130,400,chbroad.allName[need]->h);
		});bh.join();bw.join();by.join();bx.join();bg.join();
		
		api_sleep(3000);
		
		// big	 
		std::thread bg2([this](){
			thgoforb(300,10,300,this->r);
		});
		std::thread bx2([this](){
			thgoforb(chbroad.allName[need]->x.load(),10,300,chbroad.allName[need]->x);
		});
		std::thread by2([this](){
			thgoforb(chbroad.allName[need]->y.load(),10,300,chbroad.allName[need]->y);
		});
		std::thread bw2([this](){
			thgoforb(chbroad.allName[need]->w.load(),10,300,chbroad.allName[need]->w);
		});
		std::thread bh2([this](){
			thgoforb(chbroad.allName[need]->h.load(),10,300,chbroad.allName[need]->h);
		});bh2.join();bw2.join();by2.join();bx2.join();bg2.join();
	};
	void returnshape()
	{
		this->isShow =0;
		chbroad.allName[need]->w.store(90);
		chbroad.allName[need]->h.store(30);
	};
	void playcg(int need)
	{
		//get the initpos in need 
		 ix = 0;
		 iy = 0;
		 tx = chbroad.allName[need]->x.load()+45;
		 ty = chbroad.allName[need]->y.load()+15;
		chbroad.allName[need]->setchd(true);
		this->need = need;
		this->appear();
		this->bigshape();
		this->catchnb();
		this->letMid();
		this->returnshape();
		chbroad.allName[need]->setchd(false);
	};
	void draw()
	{
		if(isShow==1)
		circle(x.load(),y.load(),r.load());
	}
}circatcher;
