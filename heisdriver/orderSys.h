#include "elev.h"
#include <stdio.h>

static int order_list[4] = {-1};
static bool request_up[4] = {0};	//siste element er ubrukt
static bool request_down[4] = {0};	//første element er ubrukt

void order_update(int floor){
	for(int i = 0; i<4; i++){
		if(order_list[i]==floor){
			return;
		}
		else if(order_list[i]==-1){
			order_list[i]=floor;
		}
	}

};

void order_executed(int floor){
	request_down[floor] = 0;
	request_up[floor] = 0;
	for(int i = 0;i<4;i++){
		if(order_list[i]==floor && i!=3){
			order_list[i] = -1;
			for(int j = i, j<3;j++){
				temp = order_list[j+1];
				order_list[j+1] = order_list[j];
				order_list[j] = temp;
			}
				
		}
		else if(order_list[i]==floor){
			order_list[i] = -1;
		}
			}
	}
};


void order_clear(){
	for(int i = 0; i<4; i++){
		order_list[i]=-1;
		request_up[i]=0;
		request_down[i]=0;
	}

};
int get_new_desitination():
bool ordered_dir(floor, dir)

