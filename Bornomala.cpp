/*
	Bornomala Encryption & Decryption
	By Sazzad Saju
	CSE, Level 4 Semester 1,HSTU

	Description: This cipher takes a plain of any length, and a key with at least 8 character, a Upper case,
	a lower case and a digit within it. Then generate a key of same length as plaintext then apply operation
	associate with same indexed letter of the plaintext and of the key and thus generates a Cipher text.

*/
#include<bits/stdc++.h>
#include<iostream>
#include<string.h>
#include <fstream>
#include<stdlib.h>
#include<conio.h>
#include <Windows.h>
#include<vector>
using namespace std;

//read from file
string read_file(string filename){
    string line,str="";
	ifstream myfile (filename.c_str());
	if (myfile.is_open())
    {
		while ( getline (myfile,line) )
    	{
      		str=str+line+" ";
    	}
    	myfile.close();
    }
	else cout << "\n\t\tError: Unable to open file";
	return str;
}
string read2_file(string filename){
    string line,str="";
	ifstream myfile (filename.c_str());
	if (myfile.is_open())
    {
		while ( getline (myfile,line) )
    	{
      		str=str+line;
    	}
    	myfile.close();
    }
	else cout << "\n\t\tError: Unable to open file";
	return str;
}

//Keygeneration
string keygenerator(int mlength){
	int flag=1,klength,em;
	string K="";
	char ch;
	while(flag==1){
		vector<char> Kv; int popN=1;
		cout<<"\n\t\tEnter the key\n\t\t##---> ";
		ch = _getch();
		//Display star for input password
   		while(ch != 13){
   			if(ch != 8){
      			Kv.push_back(ch);
      			cout << '*';
      			ch = _getch();
      		}
      		else
      		{
      			Kv.pop_back();
      			cout <<"pop"<<popN<<" ";
      			ch = _getch();
      			popN++;
      		}
   		}
   		string pass(Kv.begin(), Kv.end());
   		K=pass;
   		//valid key checkpoint
		klength=K.size();
		if(klength<8){
			flag=1;
			cout<<"\n\t\tError: Key length must be equal or greater than eight digit";
		}
		else{
			em=0;
			int up=0,lw=0,dig=0;
			for(int i=0;i<klength;i++){
				if(K[i]== ' '){
					em=1;
				}
				else if(isupper(K[i]) != 0){
					up=1;
				}
				else if(islower(K[i]) != 0){
					lw=1;
				}
				else if(isdigit(K[i]) != 0){
					dig=1;
				}
			}
			if(em==1){
				cout<<"\n\t\tError: Space is not allowed in a key";
				em=0;	flag=1;
			}
			else if(up!=1){
				cout<<"\n\t\tError: Key must contain at least one upper case";
				up=0;	flag=1;
			}
			else if(lw!=1){
				cout<<"\n\t\tError: Key must contain at least one lower case";
				lw=0;	flag=1;
			}
			else if(dig!=1){
				cout<<"\n\t\tError: Key must contain at lease one digit";
				dig=0;	flag=1;
			}
			else{
				flag = 0;
			}
		}
	}
	//ascii-numeric summation
	int numb,countK=0;
	for(int i=0;i<klength;i++){
		numb= int(K[i]);
		if(numb>=48 && numb<=57){
			countK=countK+numb-48;
		}
		else{
			countK=countK+ int(K[i]);
		}
	}
	countK += mlength;

	//Key Enhancement
	if(mlength>klength){
		int rep = mlength/klength;
		int add = mlength - (rep*klength);
		if(rep>0){
			ostringstream os;
			for(int i = 0; i < rep; i++){
        		os << K;
        	}
        	K = os.str();
		}
		int i = 0;
		while(add>0){
			K = K+ K[i];
			add--;
			i++;
		}
	}
	else if(mlength<klength){
		mlength = klength;		//key remain same len. if 
	}							//message is smaller than key
	
	//Key substitution
	for(int i=0;i<mlength;i++){
		numb= int(K[i]);
		countK=(K[i]+countK)%95;
		numb=numb+countK;
		if(numb>126){
			numb=numb-95;
		}
		K[i]=numb;
	}
    
    //random-indexing
    int pos; char temp;
    srand(1);
    for(int i=0; i<mlength; i++){
    	pos = int (K[i]);
    	pos = (rand() % pos);
    	pos = pos % mlength;
    	temp = K[i];
    	K[i] = K[pos];
    	K[pos] = temp;
	}

return K;
}

//Decimal to hex conversion
string tohex(string s){
    ostringstream ret;
    unsigned int c;
    for (int i = 0; i < s.length(); ++i)
    {
        c = (unsigned int)(unsigned char)s[i];
        //ret << hex << setfill('0') <<c;		//for lower case
        ret<<hex<<setfill('0')<<uppercase<<c;	//for upper case
    }
    return ret.str();
}

//Hex to string conversion
string to_str(string str){
	string res;
	res.reserve(str.size() / 2);
	for (int i = 0; i < str.size(); i += 2)
	{
    	istringstream iss(str.substr(i, 2));
    	int temp;
    	iss >> std::hex >> temp;
    	res += static_cast<char>(temp);
	}
return res;
}

//hex string to decimal
string numToHex(int decimal)
{
	//Convert decimal to hexadecimal
  	string hexNum="";
  	int org_decimal = decimal;
  	if (decimal == 0)
    	hexNum += "0";
  	while(decimal > 0)
    {
      	if(decimal%16 > 9)
        	hexNum += (decimal%16)+55;
      	else
        	hexNum += (decimal%16)+48;
      	decimal /= 16;
    }
  	if (org_decimal < 16)
    	hexNum += "0";
  	return hexNum;
}

//Encryption func
string encrypt(string M, string K){
	int mlength, klength,mv,kv,pos,i;
	mlength= M.size();
	for(i=0;i<mlength;i++){
		mv=int(M[i]);
		kv=int(K[i]);
		pos=(mv+kv)%94;
		if(pos<32){
			pos=pos+94;
		}
		M[i]=pos;
	}
return M;
}

//Decryptio func
string decrypt(string M, string K){
	int mlength, klength,mv,kv,pos,i;
	mlength= M.size();
	for(i=0;i<mlength;i++){
		mv=int(M[i]);
		kv=int(K[i]);
		pos=mv-kv;
		while(pos<32){
			pos=pos+94;
		}
		M[i]=pos;
	}
return M;
}

//Auto copy encrypted/decrypted string to clipboard
void toClipboard(HWND hwnd, string s){
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size()+1);
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size()+1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}

//string to int
int to_int(string key){
	stringstream var(key);
	int x = 0;
	var>>x;
	return x;
}

//designing Thanks
void thanking (){
	system("cls");
	cout<<endl<<endl<<endl<<endl;
    char map4[12][70]={
		"\t.O°o. .o°O_____________________________________________O°o. .o°O.",
		"\t.°o.O.o° ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯.°o.O.o°",
		"\t                                                    ",
		"\t	___________.__                   __           ._.",
		"\t	\\__    ___/|  |__ _____    ____ |  | __  _____| |",
		"\t	  |    |   |  |  \\\\__  \\  /    \\|  |/ / /  ___/ |",
		"\t	  |    |   |   Y  \\/ __ \\|   |  \\    <  \\___ \\ \\|",
		"\t	  |____|   |___|  (____  /___|  /__|_ \\/____  >__",
		"\t	                \\/     \\/     \\/     \\/     \\/ \\/",
   	 	"\t                                                    ",
		"\t.O°o. .o°O______________________________________________O°o. .o°O.",
		"\t...°o.O.o° ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯.°o.O.o°..."
	};


	for( int i=0;i<12;i++){
		cout<<map4[i]<<endl;
	}
	cout<<"\n\n\t\t\t\t    ##---> ";
}

//padding
string padding(string C,string K){
	//length formatting
	string tempS;
	char temp;
	int len,elen,klen,pad,i,j,t;
	len = C.size();
	klen = K.size();
	elen = len;
	while((elen%8) != 0){
		C = C+ "~";
		elen = elen+1;
	}
	pad = elen-len;
	//further key enhancement
	if(klen<elen){
		int p2 = pad;
		i = 0;
		while(p2>0){
			K = K + K[i];
			i++;
			p2--;
		}
	}
	else if(klen>elen){
		K.erase(klen,elen);
	}
	//Key-triggered indexing
	for(i=elen-1;i>=0;i--){
		t = int (K[i]);
		j = t % elen;
		temp = C[i];
		C[i] = C[j];
		C[j] = temp;
	}
	//hexadecimal conversion
	C = tohex(C);
	//Blending characters
	int fl=0,k;
	j=0;
	for(i=0; i<C.size(); i+=2){
		if((C[i] == '7') && (C[i+1] == 'E')){
			if(fl %2 == 0){
				k = int (K[j]);
				k = rand() % k;
				k = k % 32;
				tempS = numToHex(k);
				C[i] = tempS[1];
				C[i+1] = tempS[0];
				j += 1;
				fl +=1;
			}
			else{
				k = int (K[j]);
				k = rand() % k;
				k = k % 256;
				if(k<126) k = k+130;
				tempS = numToHex(k);
				C[i] = tempS[1];
				C[i+1] = tempS[0];
				j += 1;
				fl += 1;
			}
		}
	}
	return C;
}
//returning padding bytes
int pad_bytes(string C){
	int i,pad=0,len;
	unsigned int x;
	string tempS="";
	for(i=0;i<C.size();i +=2){
		tempS = tempS + C[i] + C[i+1];
    	stringstream ss;
    	ss << hex << tempS;
    	ss >> x;
    	tempS = "";
    	if(x<32 || x>125){
    		pad += 1;
		}
	}

return pad;
}
//normalizing
string normalizing(string C,string K){
	//character separation
	int i,pad=0,len,klen;
	unsigned int x;
	string tempS="";
	for(i=0;i<C.size();i +=2){
		tempS = tempS + C[i] + C[i+1];
    	stringstream ss;
    	ss << hex << tempS;
    	ss >> x;
    	tempS = "";
    	if(x<32 || x>125){
    		C[i] = '7';
    		C[i+1] = 'E';
    		pad += 1;
		}
	}
	//ascii conversion
	C = to_str(C);
	//further key enhancement
	len = C.size();
	klen = K.size();
	int t,j;
	char temp;
	if(klen<len){
		int p2 = pad;
		i = 0;
		while(p2>0){
			K = K + K[i];
			i++;
			p2--;
		}
	}
	else if(klen>len){
		K.erase(klen,len);
	}
	//Key-triggered rev. indexing
	for(i=0;i<len;i++){
		t = int (K[i]);
		j = t % len;
		temp = C[i];
		C[i] = C[j];
		C[j] = temp;
	}
	//length formating
	C.erase((len-pad), len);
return C;
}

int main(){
	int mlength;
    int flag=1;char dh;
    string M,K,choi,choice="0",yn="y";
    while(flag==1){
    	system("cls");
        cout<<endl<<endl;
		char map1[25][60]={
			"		_______________________________________",
 			"	      / \\                                      \\.",
			"	     |   | ______ _______ ___      ___ ______  |.",
			"	      \\__|/  ____|  ____  \\  \\    /  /|  ___ \\ |.",
			"		 || |    | |___/ / \\  \\__/  / | |__/ / |.",
			"		 || |____|   _  |   \\_    _/  |  ___/  |.",
			"		 |\\______|__/ \\__\\    |__|    |_| TOOLS|.",
 			"		 |                                     |.",
    		"		 |  1) Encryption                      |.",
   			"		 |  2) Decryption                      |.",
    		"		 |  3) Exit                            |.",
    		"		 |                                     |.",
    		"		 |             Disclaimer              |.",
    		"		 | To encrypt or decrypt chosen key    |.",
    		"		 | must have this validity: 1.At least |.",
    		"		 | 8characters 2.No space 3.Contain one|.",
    		"		 | uppercase one lowercase and a digit |.",
    		"		 |                                     |.",
    		"		 |   __________________________________|___",
    		"		 |  /                                     /.",
    		"		 \\_/Enter Your Choice____________________/."
		};

		for(int i=0;i<23;i++){
			cout<<map1[i]<<endl;
		}
		cout<<"\t\t ##---> ";
		cin>>choice;
		//Encryption is chosen
        if(choice=="1"){
        	do{
        		system("cls");
        		cout<<"\n\n";
    			char map4[6][50]={
					"   	      ___________________________________",
					"   	    / \\***********Encryption*************\\.",
					"   	   |   |                                 |.",
					"   	    \\__| 1) Enter The Message            |.",
					"   	       | 2) Browse The File              |.",
					"   	       | Enter Your Choice               |."
				};

				for( int i=0;i<6;i++){
					cout<<map4[i]<<endl;
				}
				cout<<"\n\n\t       ##---> ";
        		cin>>choi;
        		while(choi!= "1" and choi != "2"){
        			cout<<"\t\tWrong choice, try again\n\t\t##---> ";
					cin>>choi;
				}
        		if(choi =="1"){
        			cout<<"\n\t\t==> ";
        			cin.ignore(80, '\n');
					getline(cin,M);

				}
				else if(choi=="2"){
					string filename;
					cout<<"\n\t\tEnter File Name i.e-> C:\\Users\\sazzaad\\Desktop\\test2.txt\n\t\t==> ";
					cin>>filename;
					M= read_file(filename);
				}
				mlength = M.size();
				K = keygenerator(mlength);
				M = encrypt(M,K);
				M = padding(M,K);
				cout<<"\n\n\n\t\tCiphertext: \n\t\t";
				for(int i = 1; i<=M.size(); i++){
						cout<<M[i-1];
						if((i%16)==0){
							cout<<"\n\t\t";
						}
				}
				HWND hwnd = GetDesktopWindow();
				toClipboard(hwnd, M);
				cout<<"\n\t\tCiphertext is coppied to clipboard!"<<endl;
				cout<<"\n";
    			char map5[5][50]={
					"		|***********Encryption*************|.",
    				"		|   _______________________________|___",
    				"		|  /                                  /.",
    				"		\\_/Encryption Again? (y/n)___________/."
				};

				for( int i=0;i<5;i++){
					cout<<map5[i]<<endl;
				}
				cout<<"\t         ##---> ";
        		cin>>yn;
        		while(yn != "y" and yn!="Y" and yn !="n" and yn !="N"){
        			cout<<"\t\t"<<yn<<" is not a valid option. Try again (y/n): ";
        			cin>>yn;
				}
			}while(yn != "n" and yn !="N");
		}
		else if(choice=="2"){
        	do{
        		system("cls");
        		cout<<"\n\n";
    			char map4[6][50]={
					"   	      ___________________________________",
					"   	    / \\***********Decryption*************\\.",
					"   	   |   |                                 |.",
					"   	    \\__| 1) Enter The Message            |.",
					"   	       | 2) Browse The File              |.",
					"   	       | Enter Your Choice               |."
				};

				for( int i=0;i<6;i++){
					cout<<map4[i]<<endl;
				}
				cout<<"\n\n\t       ##---> ";
        		cin>>choi;
        		while(choi!= "1" and choi != "2"){
        			cout<<"\t\tWrong choice, try again\n\t\t##---> ";
					cin>>choi;
				}
        		if(choi =="1"){
        			cout<<"\n\t\t==> ";
        			cin.ignore(80, '\n');
					getline(cin,M);
				}
				else if(choi=="2"){
					string filename;
					cout<<"\n\t\tEnter File Name i.e-> C:\\Users\\sazzaad\\Desktop\\test3.txt\n\t\t==> ";
					cin>>filename;
					M= read2_file(filename);

				}
				mlength = M.size();
				mlength = mlength/2;
				int pad = pad_bytes(M);
				mlength = mlength-pad;
				K = keygenerator(mlength);
				M = normalizing(M,K);
				M = decrypt(M,K);
				cout<<"\n\n\n\t\tPlaintext Message:\n\t\t"<<M<<endl;
				HWND hwnd = GetDesktopWindow();
				toClipboard(hwnd, M);
				cout<<"\n\t\tPlaintext is coppied to clipboard!"<<endl;

				cout<<"\n";
    			char map5[5][50]={
					"		|***********Decryption*************|.",
    				"		|   _______________________________|___",
    				"		|  /                                  /.",
    				"		\\_/Decryption Again? (y/n)___________/."
				};

				for( int i=0;i<5;i++){
					cout<<map5[i]<<endl;
				}
				cout<<"\t         ##---> ";
        		cin>>yn;
        		while(yn != "y" and yn!="Y" and yn !="n" and yn !="N"){
        			cout<<"\t\t"<<yn<<" is not a valid option. Try again (y/n): ";
        			cin>>yn;
				}
			}while(yn != "n" and yn !="N");
		}
		else if(choice=="3"){
			thanking();
			flag=0;
			getch();
		}
	}
	return 0;
}
