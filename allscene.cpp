#include"allscene.h"
#include"stdafx.h"
void allscene() {
	//����
	ScreenManager::setup();
	
	Bitmap* beijin = Bitmap::getBitmap("����.txt");

	//plantbackground(beijin);



	Bitmap* bitasd;
	bitasd = Bitmap::getBitmap("������֤.txt");
	DisplayObject b = { 56,56,100,70, Bitmap::getBitmap("������֤.txt") };//���꣬�� ��
	b.backwritedata2(2, 1);
	//b.showdata2indata();
	//changebackground(bitasd);
	while (1) {
		//jianyan::data_to_data(bitasd);
		b.jump();
	}

}