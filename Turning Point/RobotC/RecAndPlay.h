#include "Mainboi.c"
// Each string should be about 1200 characters. divided by 4 (1 for each control type state), characters processed each tick. multiplied by the length of each tick which is 50ms, and divide that by 1000 to convert it to seconds.
//((Total Characters/Unique charaters)*recordWait)/1000= time (in seconds)
//In this case, ((50/1)*50ms)/1000ms=15s

/*Prepped the autonomous to only have two options, but eight parts for the 1200 characters.
*Also removed the extra statements from the autonomous task, and the LCD display.
*Our problem now is the strings aren't consistent in their printing patterns. It doesn't always print in the same order. Occasionally a character will switch with another.
* So making the 'i' skip 4 characters will not work as long as this issue occurs.
*/
char auto1String[301]="";
char a1PartOne[] = "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";//150 chars
char a1PartTwo[] = "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";//150 chars
char a1PartThree[] = "";
char a1PartFour[] = "";
char a1PartFive[] = "";
char a1PartSix[] = "";
char a1PartSeven[] = "";
char a1PartEight[] = "";
char auto2String[301]="";
char a2PartOne[] = "placeholder";//150 chars
char a2PartTwo[] = "placeholder";//150 chars
char a2PartThree[] = "";
char a2PartFour[] = "";
char a2PartFive[] = "";
char a2PartSix[] = "";
char a2PartSeven[] = "";
char a2PartEight[] = "";
//Removed recDebug statements, trying to save memory.
void prepAutoString(int num) {
	switch(num) {
	case 1:
		strcat(auto1String,a1PartOne);
		strcat(auto1String,a1PartTwo);
		strcat(auto1String,a1PartThree);
		strcat(auto1String,a1PartFour);
		strcat(auto1String,a1PartFive);
		strcat(auto1String,a1PartSix);
		strcat(auto1String,a1PartSeven);
		strcat(auto1String,a1PartEight);
		break;
	case 2:
		strcat(auto2String,a2PartOne);
		strcat(auto2String,a2PartTwo);
		strcat(auto2String,a2PartThree);
		strcat(auto2String,a2PartFour);
		strcat(auto2String,a2PartFive);
		strcat(auto2String,a2PartSix);
		strcat(auto2String,a2PartSeven);
		strcat(auto2String,a2PartEight);
		break;
	}
}

char *getAutoString(int num) {
	switch(num) {
	case 1:
		return(auto1String);
		break;
	case 2:
		return(auto2String);
		break;
	}
	return NULL;
}
