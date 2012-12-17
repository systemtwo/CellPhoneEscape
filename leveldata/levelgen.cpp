#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


int main()
{
	int height, width;
	int vertGap = 2, horzGap = 0, gapHeight=3;
	int platform, density = 20;
	bool repeat = true, makePlayer = true;
	int temp;
	string name;
	ofstream outs;
	cout<<"Level Number?  ";
	cin >> name;
	
	while(true) {	
		repeat = true;
		name = "lv" + name + ".txt";
		cout<<"Ouput file name: "<<name << endl;
		outs.open(name.c_str());
		cout<<"Enter Level Height: ";
		cin >> height;
		cout<<"Enter Level Width: ";
		cin >>width;
		while(repeat==true) {
			makePlayer = true;
			outs << width << " " <<height<<endl;
			for(int row = 0; row < height; row++) {
				for(int col = 0; col < width; col++) {
					if((row==(height-1))||(row==0)||(col==0)||(col==width-1)) {
						outs << "1 ";
						cout<<"1 ";
					} else if(platform > 0) {
						platform --;
						outs <<"1 ";
						cout<<"1 ";
					} else {
						if((rand()%((height - row - 1) * (width - col - 1))==0) && (makePlayer == true)) {
							cout<<"-1 ";
							outs<<"-1 ";
							makePlayer = false;
						} else {
							outs << "0 ";
							cout<<"0 ";
						}
						if((rand()%density == 0) && ((vertGap == 0) || (vertGap == gapHeight)) && (horzGap == 0)){
							platform = (rand()%10+2);
							vertGap = gapHeight;
							horzGap = 2;
						}
						if(horzGap > 0) {
							horzGap--;
						}
					}
					
				}
				outs<<endl;
				cout<<endl;
				
				if(vertGap > 0) {
					vertGap --;
				}
				platform=0;
				
			}
			outs.close();
			cout<<"Enter 1 to re-generate, enter 2 to generate new dimensions\nEnter 3 to generate new file, 4 to exit\n";
			cin>>temp;
			switch(temp) {
				case 1: 
					break;
				case 2:
					repeat=false;
					break;
				case 3:
					repeat=false;
					cout<<"Level Number?  ";
					cin >> name;
					break;
				case 4:
					return 0;
				default:
					repeat=false;
					cout<<"Level Number?  ";
					cin >> name;
					break;
					
			}
		}
	}
}
