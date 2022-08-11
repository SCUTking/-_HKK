#include"allscene.h"
#include"stdafx.h"
void allscene() {
	//函数
	ScreenManager::setup();
	
	Bitmap* beijin = Bitmap::getBitmap("背景.txt");

	//plantbackground(beijin);



	Bitmap* bitasd;
	bitasd = Bitmap::getBitmap("人物验证.txt");
	DisplayObject b = { 56,56,100,70, Bitmap::getBitmap("人物验证.txt") };//坐标，宽 高
	b.backwritedata2(2, 1);
	//b.showdata2indata();
	//changebackground(bitasd);
	while (1) {
		//jianyan::data_to_data(bitasd);
		b.jump();
	}

}