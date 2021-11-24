#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <string.h>
#include <bits/stdc++.h> 


#define ANSI_COLOR_RED     "\x1b[1;31m"
#define ANSI_COLOR_GREEN   "\x1b[1;32m"
#define ANSI_COLOR_YELLOW  "\x1b[1;33m"
#define ANSI_COLOR_BLUE    "\x1b[1;34m"
#define ANSI_COLOR_BRIGHT_BLUE    "\x1b[1;34m"
#define ANSI_COLOR_MAGENTA "\x1b[1;35m"
#define ANSI_COLOR_BRIGHT_MAGENTA "\x1b[1;35m"
#define ANSI_COLOR_CYAN    "\x1b[1;36m"
#define ANSI_COLOR_GREY    "\x1b[1;37m"
#define ANSI_COLOR_BLACK    "\x1b[1;30m"
#define ANSI_COLOR_ORANGE  "\x1b[43m"
#define ANSI_COLOR_RESET   "\x1b[0m"




using namespace std;
using namespace Json;


void parse_json();
void ascii_print(string crypto, string currency, double real_price, double real_change);



//callback function
size_t got_data(char *buffer, size_t itemsize, size_t nitems){
	
	//opens data.json and writes data we collected to it.
	size_t bytes = itemsize *nitems;

	ofstream out_file;

	out_file.open("data.json");
	
	for (int i = 0; i < bytes; i++){
		out_file <<("%c", buffer[i]);

	}
	out_file.close();
	
	parse_json();


	return bytes;
}


int main(int argc, char *argv[]){
	
	char base_url[] = "https://api.cryptonator.com/api/ticker/";

	strcat(base_url,argv[1]);
	strcat(base_url,"-");
	strcat(base_url,argv[2]);
	


	
	//starts curl
	CURL *curl = curl_easy_init();
	
	//if curl fails to start
	if (!curl){
		fprintf(stderr,"init failed\n");
		return EXIT_FAILURE;
	}

	//get the info from the api?
	curl_easy_setopt(curl, CURLOPT_URL, base_url);

	//calls the callback function
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, got_data);

	
	//checks download
	CURLcode result = curl_easy_perform(curl);
	
	if (result != CURLE_OK){
		fprintf(stderr, "download problem %s\n",curl_easy_strerror(result));
	}
	
	
	curl_easy_cleanup(curl);

	return 0;

}

void parse_json(){

	//parses and makes varible data from data.json 
	Value data; 
	
	ifstream data_file("data.json", ifstream::binary);
	data_file >> data; 

	string crypto = data["ticker"]["base"].asString();


	string price = data["ticker"]["price"].asString();
	double real_price = stold(price);
	
	string currency = data["ticker"]["target"].asString();
	string change = data["ticker"]["change"].asString();
	double real_change = stold(change);
	
	if(data["ticker"]["price"] <= 0){
		cout<<"invalid currency or coin";
	}
	
	else{




		
		if(crypto == "BTC"){
			cout<<ANSI_COLOR_YELLOW<<R"(______ _ _            _       
| ___ (_) |          (_)      
| |_/ /_| |_ ___ ___  _ _ __  
| ___ \ | __/ __/ _ \| | '_ \ 
| |_/ / | || (_| (_) | | | | |
\____/|_|\__\___\___/|_|_| |_|)"<<ANSI_COLOR_RESET;

		}
			
			
		if(crypto == "ETC"){
			cout<<ANSI_COLOR_GREY<<R"( _____ _   _                                    
|  ___| | | |                                   
| |__ | |_| |__   ___ _ __ ___ _   _ _ __ ___   
|  __|| __| '_ \ / _ \ '__/ _ \ | | | '_ ` _ \  
| |___| |_| | | |  __/ | |  __/ |_| | | | | | | 
\____/ \__|_| |_|\___|_|  \___|\__,_|_| |_| |_|)"<<ANSI_COLOR_RESET;

		}
		
		if(crypto == "LTC"){
			cout<<ANSI_COLOR_BLUE<<R"( _     _ _                 _       
| |   (_) |               (_)      
| |    _| |_ ___  ___ ___  _ _ __  
| |   | | __/ _ \/ __/ _ \| | '_ \ 
| |___| | ||  __/ (_| (_) | | | | |
\_____/_|\__\___|\___\___/|_|_| |_|)"<<ANSI_COLOR_RESET;

		}																					

		if(crypto == "XMR"){
			cout<<ANSI_COLOR_YELLOW<<R"(___  ___                           
|  \/  |                           
| .  . | ___  _ __   ___ _ __ ___  
| |\/| |/ _ \| '_ \ / _ \ '__/ _ \ 
| |  | | (_) | | | |  __/ | | (_) |
\_|  |_/\___/|_| |_|\___|_|  \___/ )"<<ANSI_COLOR_RESET;

		}		
		
		if(crypto == "DOGE"){
			cout<<ANSI_COLOR_YELLOW<<R"(______                           _       
|  _  \                         (_)      
| | | |___   __ _  ___  ___ ___  _ _ __  
| | | / _ \ / _` |/ _ \/ __/ _ \| | '_ \ 
| |/ / (_) | (_| |  __/ (_| (_) | | | | |
|___/ \___/ \__, |\___|\___\___/|_|_| |_|   
             __/ |                       
            |___/     )"<<ANSI_COLOR_RESET;

		}	
		if(crypto == "ADA"){
			cout<<ANSI_COLOR_BRIGHT_BLUE<<R"( _____               _                   
/  __ \             | |                  
| /  \/ __ _ _ __ __| | __ _ _ __   ___  
| |    / _` | '__/ _` |/ _` | '_ \ / _ \ 
| \__/\ (_| | | | (_| | (_| | | | | (_) |
 \____/\__,_|_|  \__,_|\__,_|_| |_|\___/)"<<ANSI_COLOR_RESET;

		}																				
		if(crypto == "DOT"){
			cout<<ANSI_COLOR_BRIGHT_MAGENTA<<R"(______     _ _             _       _   
| ___ \   | | |           | |     | |  
| |_/ /__ | | | ____ _  __| | ___ | |_ 
|  __/ _ \| | |/ / _` |/ _` |/ _ \| __|
| | | (_) | |   < (_| | (_| | (_) | |_ 
\_|  \___/|_|_|\_\__,_|\__,_|\___/ \__|)"<<ANSI_COLOR_RESET;

		}																				

		if(crypto == "XLM"){
			cout<<ANSI_COLOR_GREY<<R"(  _____ _       _ _            
 /  ___| |     | | |           
 \ `--.| |_ ___| | | __ _ _ __ 
  `--. \ __/ _ \ | |/ _` | '__|
 /\__/ / ||  __/ | | (_| | |   
 \____/ \__\___|_|_|\__,_|_|)"<<ANSI_COLOR_RESET;

		}	
		if(crypto == "NANO"){
			cout<<ANSI_COLOR_CYAN<<R"( _   _                   
| \ | |                  
|  \| | __ _ _ __   ___  
| . ` |/ _` | '_ \ / _ \ 
| |\  | (_| | | | | (_) |
\_| \_/\__,_|_| |_|\___/ )"<<ANSI_COLOR_RESET;

		}																				
		if(crypto == "DASH"){
			cout<<ANSI_COLOR_CYAN<<R"(______          _     
|  _  \        | |    
| | | |__ _ ___| |__  
| | | / _` / __| '_ \ 
| |/ / (_| \__ \ | | |
|___/ \__,_|___/_| |_|)"<<ANSI_COLOR_RESET;

		}	
		if(crypto == "SOL"){
			cout<<ANSI_COLOR_MAGENTA<<R"( _____       _                   
/  ___|     | |                  
\ `--.  ___ | | __ _ _ __   __ _ 
 `--. \/ _ \| |/ _` | '_ \ / _` |
/\__/ / (_) | | (_| | | | | (_| |
\____/ \___/|_|\__,_|_| |_|\__,_|)"<<ANSI_COLOR_RESET;

		}	

		ascii_print(crypto,currency,real_price,real_change);

			
			
			
		}
	
}
	

void ascii_print(string crypto, string currency, double real_price, double real_change){

	cout<<"\n"<<ANSI_COLOR_CYAN<<"Cryptocurrency: "<<crypto <<ANSI_COLOR_RESET<< "\n";
		
	cout<<ANSI_COLOR_GREEN<<"Currency: "<<currency <<ANSI_COLOR_RESET<< "\n";
		
	cout<<ANSI_COLOR_RED<<"Price: "<<"$"<<fixed<<setprecision(2) <<real_price <<ANSI_COLOR_RESET<< "\n";
		
		
	cout<<ANSI_COLOR_YELLOW<<"Change: "<<fixed <<setprecision(4) <<real_change<<"%" <<ANSI_COLOR_RESET<< "\n";	
}


