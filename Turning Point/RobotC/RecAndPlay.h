char auto1String[301];
char a1PartOne[] = "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";//150 chars
char a1PartTwo[] = "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";//150 chars
char auto2String[301];
char a2PartOne[] = "placeholder";//150 chars
char a2PartTwo[] = "placeholder";//150 chars
char auto3String[301];
char a3PartOne[] = "placeholder";//150 chars
char a3PartTwo[] = "placeholder";//150 chars
char auto4String[301];
char a4PartOne[] = "placeholder";//150 chars
char a4PartTwo[] = "placeholder";//150 chars
char auto5String[301];
char a5PartOne[] = "placeholder";//150 chars
char a5PartTwo[] = "placeholder";//150 chars
char auto6String[301];
char a6PartOne[] = "placeholder";//150 chars
char a6PartTwo[] = "placeholder";//150 chars
char auto7String[301];
char a7PartOne[] = "placeholder";//150 chars
char a7PartTwo[] = "placeholder";//150 chars
char auto8String[301];
char a8PartOne[] = "placeholder";//150 chars
char a8PartTwo[] = "placeholder";//150 chars

void prepAutoString(int num) {
	switch(num) {
	case 1:
		strcat(auto1String,a1PartOne);
		strcat(auto1String,a1PartTwo);
		break;
	case 2:
		strcat(auto2String,a2PartOne);
		strcat(auto2String,a2PartTwo);
		break;
	case 3:
		strcat(auto3String,a3PartOne);
		strcat(auto3String,a3PartTwo);
		break;
	case 4:
		strcat(auto4String,a4PartOne);
		strcat(auto4String,a4PartTwo);
		break;
	case 5:
		strcat(auto5String,a5PartOne);
		strcat(auto5String,a5PartTwo);
		break;
	case 6:
		strcat(auto6String,a6PartOne);
		strcat(auto6String,a6PartTwo);
		break;
	case 7:
		strcat(auto7String,a7PartOne);
		strcat(auto7String,a7PartTwo);
		break;
	case 8:
		strcat(auto8String,a8PartOne);
		strcat(auto8String,a8PartTwo);
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
	case 3:
		return(auto3String);
		break;
	case 4:
		return(auto4String);
		break;
	case 5:
		return(auto5String);
		break;
	case 6:
		return(auto6String);
		break;
	case 7:
		return(auto7String);
		break;
	case 8:
		return(auto8String);
		break;
	}
	return NULL;
}
