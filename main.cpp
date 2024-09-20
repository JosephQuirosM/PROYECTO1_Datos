#include <locale>
#include "Menu.h"

int main(){	
	setlocale(LC_CTYPE, "Spanish");
	Menu menu;
	menu.runMenu(); 
	return 0;
}