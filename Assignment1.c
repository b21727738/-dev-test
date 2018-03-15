#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

FILE *OP;

struct cha {
	char *type;
	char *name;
	int hp;
	int damage;
	int xp;
	int dead;

};

struct FoM {
	char letter;
	char *name;
	int x;
	int y;
};

struct command {
	char *first;
	char *second;
	char *other;
};


int linecount(FILE *fp,int *ptr) {
	int line = 0;
	char ch;

	int i=0,itemp=0;	
	while(1)
	{
		ch = fgetc(fp);
		if (ch == EOF)
		{
			break;
		}
		else if(ch==10)
		{
			line++;
			i = 0;
		}
		i++;
		if (i>itemp) {
			itemp = i;
		}
	}
	*ptr = itemp;
	return line;
}

char *TaS(char *first, char *last) {
	int size = (last - first) + 1, i;
	char *string;
	string = malloc(size*sizeof(char));
	for (i = 0; i<size; i++) {
		string[i] = *(first + i);
	}
	string[i] = '\0';
	
	
	return string;
}

struct command readcom(char *line) {
	char *cPtr, *firstPtr, *secPtr, *otherPtr, *mPtr;
	cPtr = line;
	struct command ret;
	while (*cPtr != ' ') {
		cPtr = cPtr + 1;
	}
	firstPtr = TaS(line, cPtr - 1);
	mPtr = cPtr + 1;
	ret.first = firstPtr;
	
	do {
		cPtr = cPtr + 1;
	} while (*cPtr != ' ' || *cPtr == '\n');
	secPtr = TaS(mPtr, cPtr - 1);
	mPtr = cPtr+1;
	ret.second = secPtr;
	while (*cPtr != '\n') {
		cPtr = cPtr + 1;	
	}
	otherPtr = TaS(mPtr, cPtr - 1);
	mPtr = cPtr;
	ret.other = otherPtr;
	
	return ret;
}

struct cha readline(char *line) {
	struct cha subj;
	char *cPtr, *typPtr, *namPtr, *hpPtr, *damPtr, *mPtr;
	cPtr = line;
	while (*cPtr != ',') {
		cPtr = cPtr + 1;
	}
	typPtr = TaS(line, cPtr - 1);
	mPtr = cPtr + 1;
	subj.type = typPtr;
	do {
		cPtr = cPtr + 1;
	} while (*cPtr != ',');
	namPtr = TaS(mPtr, cPtr - 1);
	mPtr = cPtr + 1;
	subj.name = namPtr;
	do {
		cPtr = cPtr + 1;
	} while (*cPtr != ',');
	hpPtr = TaS(mPtr, cPtr - 1);
	mPtr = cPtr + 1;
	subj.hp = atoi(hpPtr);
	do {
		cPtr = cPtr + 1;
	} while (*cPtr != '\n');
	damPtr = TaS(mPtr, cPtr - 1);

	subj.damage = atoi(damPtr);
	subj.xp = 0;

	return subj;


}

char*** loadmap(int x, int y) {

	int i, j;
	char ***map;

	map = (char ***)malloc(2 * sizeof(char **));


	for (i = 0; i<2; i++) {
		map[i] = (char **)malloc(x*sizeof(char *));
		for (j = 0; j<x; j++) {
			map[i][j] = (char *)malloc(y*x*sizeof(char *));
		}
	}

	


	for (i = 0; i<x; i++) {
		for (j = 0; j<y; j++) {
			map[1][i][j] = '.';
			map[0][i][j] = '0';
		}
	}
	return map;
}

struct FoM foP(char *input) {
	struct FoM subj;
	char *cPtr, *mPtr, *letter, *x, *y;
	int x1, y1;
	cPtr = input;
	mPtr = cPtr;
	while (*cPtr != ' ') {
		cPtr = cPtr + 1;
	}

	letter = TaS(mPtr, cPtr - 1);
	mPtr = cPtr + 1;
	subj.name= letter;
	subj.letter = *letter;
	do {
		cPtr = cPtr + 1;
	} while (*cPtr != ' ');
	x = TaS(mPtr, cPtr - 1);
	x1 = atoi(x);
	mPtr = cPtr + 1;
	subj.x = x1;
	do {
		cPtr = cPtr + 1;
		if (*cPtr == '\0')
			break;
	} while (*cPtr != ' ');

	y = TaS(mPtr, cPtr - 1);
	y1 = atoi(y);
	mPtr = cPtr + 1;
	subj.y = y1;

	return subj;
}

void put(char *input, char ***map) {
	
	char *cPtr, *mPtr, *command;
	struct FoM temp;
	int count = 0;
	cPtr = input;
	mPtr = input;
	do {
		
		if (*cPtr == ' '){
			if (count == 2) {
				
				command = TaS(mPtr, cPtr);
				
				mPtr = cPtr + 1;
				count = 0;
				temp = foP(command);
				map[1][temp.x][temp.y] = temp.letter;
			}
			else {
				count = count + 1;
			}
		}
		
		cPtr = cPtr + 1;
		
		if(*cPtr == 0)
			break;
	} while (*cPtr != '\0');
	
	command = TaS(mPtr, cPtr);
	temp = foP(command);
	map[1][temp.x][temp.y] = temp.letter;

}

void showm(char ***map,int x,int y){
	int i,j;
	for (i=0;i<x;i++){
		fprintf(OP,"\n");
		for (j=0;j<y;j++){
			fprintf(OP,"%c ",map[1][i][j]);
		}
	}
	fprintf(OP,"\n");
}

void showh (struct cha hero) {
	if (hero.type[0]=='H') {
	
	fprintf(OP,"%s HP: %d XP: %d\n",hero.name,hero.hp,hero.xp);
	
	}
}

void showmonster (struct cha monster) {
	if (monster.type[0]=='M') {
	
	fprintf(OP,"%s HP: %d\n",monster.name,monster.hp);
}
}

void secmap(struct cha *chars,char ***map,int size,int x , int y) {
	int i,j,z;
	for (i=0;i<x;i++){
		for (j=0;j<y;j++){
			if (map[1][i][j] != '.') {
				for (z=0;z<size;z++) {
					if (map[1][i][j] == chars[z].name[0]){
						map[0][i][j] = z;
						break;
					}
				}
			}
		}
	}
}

void attack(struct cha *chars,char ***map,int x,int y,char *type) {
	int i,j,z,tempx,tempy;
	for (i=0;i<x;i++){
		for (j=0;j<y;j++){
			if (map[1][i][j] != '.') {
				if (*type == *chars[map[0][i][j]].type) {
				if ((i-1<x && j<y) && (( i-1 >= 0)&&  (j >= 0)) && map[1][i-1][j] != '.') {
					tempx = i - 1;
					tempy = j;
					if(*chars[map[0][tempx][tempy]].type != *chars[map[0][i][j]].type) {
					
					chars[map[0][tempx][tempy]].hp = chars[map[0][tempx][tempy]].hp - chars[map[0][i][j]].damage;
					if (chars[map[0][tempx][tempy]].hp <= 0) {
						chars[map[0][tempx][tempy]].hp = 0;
						map[1][tempx][tempy] = '.';
						map[0][tempx][tempy] = '0';
						chars[map[0][i][j]].xp = chars[map[0][i][j]].xp + 1;
					}
				}
				} 
				if ((i-1<x && j+1<y) && ((i-1 >= 0)&& (j + 1 >=0)) && map[1][i-1][j+1] != '.') {
					tempx = i - 1;
					tempy = j + 1;
					if(*chars[map[0][tempx][tempy]].type != *chars[map[0][i][j]].type) {
						
					chars[map[0][tempx][tempy]].hp = chars[map[0][tempx][tempy]].hp - chars[map[0][i][j]].damage;
					if (chars[map[0][tempx][tempy]].hp <= 0) {
						chars[map[0][tempx][tempy]].hp = 0;
						map[1][tempx][tempy] = '.';
						map[0][tempx][tempy] = '0';
						chars[map[0][i][j]].xp = chars[map[0][i][j]].xp + 1;
					}
				}
				}
				if ((i<x && j+1<y) && ((i >= 0)&& (j + 1) >= 0) &&map[1][i][j+1] != '.') {
					tempx = i ;
					tempy = j + 1;
					if(*chars[map[0][tempx][tempy]].type != *chars[map[0][i][j]].type) {
					chars[map[0][tempx][tempy]].hp = chars[map[0][tempx][tempy]].hp - chars[map[0][i][j]].damage;
					if (chars[map[0][tempx][tempy]].hp <= 0) {
						chars[map[0][tempx][tempy]].hp = 0;
						map[1][tempx][tempy] = '.';
						map[0][tempx][tempy] = '0';
						chars[map[0][i][j]].xp = chars[map[0][i][j]].xp + 1;
					}
				}
				}
				if ((i+1<x && j+1<y) && ((i+1 >= 0) && (j + 1 >= 0)) && map[1][i+1][j+1] != '.') {
					tempx = i + 1;
					tempy = j + 1;
					if(*chars[map[0][tempx][tempy]].type != *chars[map[0][i][j]].type) {
					chars[map[0][tempx][tempy]].hp = chars[map[0][tempx][tempy]].hp - chars[map[0][i][j]].damage;
					if (chars[map[0][tempx][tempy]].hp <= 0) {
						chars[map[0][tempx][tempy]].hp = 0;
						map[1][tempx][tempy] = '.';
						map[0][tempx][tempy] = '0';
						chars[map[0][i][j]].xp = chars[map[0][i][j]].xp + 1;
					}
					}
				}
				
				if ((i+1<x && j<y) && ((i+1 >= j)&& (j >= 0)) && map[1][i+1][j] != '.') {
					tempx = i + 1 ;
					tempy = j ;
					if(*chars[map[0][tempx][tempy]].type != *chars[map[0][i][j]].type) {
					chars[map[0][tempx][tempy]].hp = chars[map[0][tempx][tempy]].hp - chars[map[0][i][j]].damage;
					if (chars[map[0][tempx][tempy]].hp <= 0) {
						chars[map[0][tempx][tempy]].hp = 0;
						map[1][tempx][tempy] = '.';
						map[0][tempx][tempy] = '0';
						chars[map[0][i][j]].xp = chars[map[0][i][j]].xp + 1;
					}
				}
				}
				if ((i+1<x && j-1<y) && ((i+1 >= 0)&& (j - 1 >= 0)) &&map[1][i+1][j-1] != '.') {
					tempx = i + 1  ;
					tempy = j - 1;
					if(*chars[map[0][tempx][tempy]].type != *chars[map[0][i][j]].type) {
					chars[map[0][tempx][tempy]].hp = chars[map[0][tempx][tempy]].hp - chars[map[0][i][j]].damage;
					if (chars[map[0][tempx][tempy]].hp <= 0) {
						chars[map[0][tempx][tempy]].hp = 0;
						map[1][tempx][tempy] = '.';
						map[0][tempx][tempy] = '0';
						chars[map[0][i][j]].xp = chars[map[0][i][j]].xp + 1;
					}
				}
				}
				if ((i<x && j-1<y) && ((i >= 0)&& (j - 1 >= 0)) &&map[1][i][j-1] != '.') {
					tempx = i  ;
					tempy = j - 1;
					if(*chars[map[0][tempx][tempy]].type != *chars[map[0][i][j]].type) {
					chars[map[0][tempx][tempy]].hp = chars[map[0][tempx][tempy]].hp - chars[map[0][i][j]].damage;
					if (chars[map[0][tempx][tempy]].hp <= 0) {
						chars[map[0][tempx][tempy]].hp = 0;
						map[1][tempx][tempy] = '.';
						map[0][tempx][tempy] = '0';
						chars[map[0][i][j]].xp = chars[map[0][i][j]].xp + 1;
					}
				}
				}
				if ((i-1<x && j-1<y) && ((i - 1 >= 0)&& (j - 1 >= 0)) &&map[1][i - 1][j-1] != '.') {
					tempx = i - 1 ;
					tempy = j - 1;
					if(*chars[map[0][tempx][tempy]].type != *chars[map[0][i][j]].type) {
					chars[map[0][tempx][tempy]].hp = chars[map[0][tempx][tempy]].hp - chars[map[0][i][j]].damage;
					if (chars[map[0][tempx][tempy]].hp <= 0) {
						chars[map[0][tempx][tempy]].hp = 0;
						map[1][tempx][tempy] = '.';
						map[0][tempx][tempy] = '0';
						chars[map[0][i][j]].xp = chars[map[0][i][j]].xp + 1;
					}
					}
				}
				}
			} 
			}
		}
	}
	
void move (struct cha *chars,char ***map,int x,int y,char *input) {
	char *cPtr, *mPtr, *command;
	struct FoM temp;
	int count = 0,i,j,mark,dead,im,jm;
	cPtr = input;
	mPtr = input;
	do {
		
		if (*cPtr == ' ') {
			if (count == 2) {
				
				command = TaS(mPtr, cPtr);
				
				mPtr = cPtr + 1;
				count = 0;
				temp = foP(command);
				dead = 1;
				for (i=0;i<x;i++){
					for (j=0;j<y;j++) {
						if (map[0][i][j] != '0') {
						if (chars[map[0][i][j]].name[0] == temp.letter) {
							mark = map[0][i][j];
							dead = 0;
							im = i;
							jm = j;
							break ;
						}
					}
				}
				}
				
				if (dead == 1){
					fprintf(OP,"%s can't move. Dead.\n",temp.name);
					
				} else {
					if (!( ((temp.x < x )&& (temp.y < y)) && ((temp.x >= 0 )&& (temp.y >= 0)))) {
						fprintf(OP,"%s can't move. There is a wall.\n",temp.name);
					} else {
						if (map[1][temp.x][temp.y] != '.') {
							fprintf(OP,"%s can''t move. Place is occupied.\n",temp.name);
						} else {
							map[1][im][jm] = '.';
							map[0][im][jm] = '0';
							map[1][temp.x][temp.y] = temp.letter;
							map[0][temp.x][temp.y] = mark;
						}
					}
				}
				
			}
			else {
				count = count + 1;
			}
		}
		cPtr = cPtr + 1;
	} while (*cPtr != '\0');
				command = TaS(mPtr, cPtr);
				
				mPtr = cPtr + 1;
				count = 0;
				temp = foP(command);
				dead = 1;
				for (i=0;i<x;i++){
					for (j=0;j<y;j++) {
						if (map[0][i][j] != '0') {
						if (chars[map[0][i][j]].name[0] == temp.letter) {
							mark = map[0][i][j];
							dead = 0;
							im = i;
							jm = j;
							break ;
						}
					}
				}
				}
				
				if (dead == 1){
					fprintf(OP,"%s can't move. Dead.\n",temp.name);
					
				} else {
					if (!( ((temp.x < x )&& (temp.y < y)) && ((temp.x >= 0 )&& (temp.y >= 0)))) {
						fprintf(OP,"%s can't move. There is a wall.\n",temp.name);
					} else {
						if (map[1][temp.x][temp.y] != '.') {
							fprintf(OP,"%s can't move. Place is occupied.\n",temp.name);
						} else {
							map[1][im][jm] = '.';
							map[0][im][jm] = '0';
							map[1][temp.x][temp.y] = temp.letter;
							map[0][temp.x][temp.y] = mark;
						}
					}
				}
			
	
}


int main(int argc, char *argv[]) {
	char *inp, ***map;
	char *kelam;
	FILE *chPtr,*comPtr,*tPtr,*tPtr2;
	int counter,lcha=0,lcom=0,i,mapx,mapy,maxchar;
	tPtr = fopen(argv[1],"r");
	lcha = linecount(tPtr,&maxchar) + 1;
	struct cha *all = malloc(lcha * sizeof(struct cha));
	fclose(tPtr);
	tPtr=0;
	tPtr2=0;
	tPtr2 = fopen(argv[2],"r");
	lcom = linecount(tPtr2,&maxchar) + 1;
	fclose(tPtr2);
	kelam = malloc(maxchar*sizeof(char));
	struct command *call = malloc(lcom * sizeof(struct command));
 	if ((OP = fopen(argv[3],"w"))==NULL) {
		printf("File could not be opened");
	}
	if ((chPtr = fopen(argv[1], "r")) == NULL) {
		fprintf(OP,"File could not be opened\n");
	}
	else {
		counter = 0;
		do {
			inp = fgets(kelam, 200, chPtr);
			if (inp != NULL) {
				all[counter] = readline(inp);
				counter = counter + 1;
			}
		} while (inp != NULL);
		fclose(chPtr);
	}
	if ((comPtr = fopen(argv[2], "r")) == NULL) {
		fprintf(OP,"File could not be opened\n");
	}
	else {
		counter = 0;
		do {
			inp = fgets(kelam, 200, comPtr);
			if (inp != NULL) {
				call[counter] = readcom(inp);
				counter = counter + 1;
			}
		} while (inp != NULL);
		fclose(comPtr);
	}
	for (i=0;i<counter;i++){
		if (call[i].first[0] ==  'L') {
			map = loadmap(atoi(call[i].second),atoi(call[i].other));
			mapx = atoi(call[i].second);
			mapy = atoi(call[i].other);
		}
		if (call[i].first[0] == 'P') {
			put(call[i].other,map);
			secmap(all,map,lcha,mapx,mapy);
		}
		if (call[i].first[0] == 'S'){
			int j;
			if (call[i].second[1] == 'A') {
				fprintf(OP,"MAP STATUS ");
				showm(map,mapx,mapy);
				fprintf(OP,"\n");
			}
			if (call[i].second[0] == 'H') {
				fprintf(OP,"HERO STATUS\n");
				for (j=0;j<lcha-1;j++) {
					showh(all[j]);
				}
				fprintf(OP,"\n");
			}
			if (call[i].second[1] == 'O') {
				fprintf(OP,"MONSTER STATUS\n");
				for (j=0;j<lcha-1;j++) {
					showmonster(all[j]);
				}
				fprintf(OP,"\n");
			}
		}
		if (call[i].first[0] == 'A'){
			
			if (call[i].second[0] == 'H'){
				fprintf(OP,"HEROES ATTACKED\n\n");
				attack(all,map,5,5,"HERO");
			}
			if (call[i].second[0] == 'M'){
				fprintf(OP,"MONSTERS ATTACKED\n\n");
				attack(all,map,5,5,"MONSTER");
			}
			}
		if (call[i].first[0] == 'M') {
			if (call[i].second[0] == 'H') {
				fprintf(OP,"HEROS MOVED\n");
				move(all,map,mapx,mapy,call[i].other);
				fprintf(OP,"\n");
			}
		}
		}


	return 0;
}
