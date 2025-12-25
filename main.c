#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


typedef struct {
	char spelling[200];
	char meaning[200];
	char wrong_words_spelling[200];
	char wrong_words_meaning[200];
} Words;
Words dictionary[8000];


int wordsCount = 0,wrong_words_count = 0;
void speak(const char* word);
void clearScreen();		//NOTE:!!!!!!!!!!请转到函数根据编译器来修改清屏函数!!!!!!!!
void lower(char* word);
int load_words(const char* filepath);
int load_wrong_words(const char* filepath);
int find_word(const char* word);
int find_wrong_words(const char* word);
int compare_words(const void* a, const void* b);
int num();


int main(void) {
	int choose,random,choose_5,score = 0;
	char a,b,input_spelling[200],path[300],input_meaning[200],random_char[50];
	srand(time(NULL));
	printf("是否使用系统自带的四级词汇词典\n");
	scanf(" %c",&a);
	if (a == 'y') {
		strcpy(path,"cet4.txt");
		goto jump;		//这里使用的goto语句是为了在用户使用自带词典时跳过输入
	}
	printf("请输入词库所在地址\n");
	scanf("%s",path);
	jump: ;
	const char* mypath = path;
	printf("正在加载词典文件\n");
	wordsCount = load_words(mypath);
	wrong_words_count = load_wrong_words("wrong_words.txt");
	if (wordsCount > 0) {
		printf("成功加载文件,词库单词个数为%d\n",wordsCount);
	}
	Sleep(3000);
	clearScreen();
	while (1) {
		printf(
			"====================================\n"
			"           电子词典V1				 \n"
			"           请输入选项				 \n"

			"       1：查词           2：新增单词   \n"
			"       3：删除单词       4：修改单词    \n"
			"       5: 进行随机单词抽查             \n"
			"       6:进行考试					 \n"
			"       7:打开错题本                   \n"
			"       输入8以退出					 \n"
			"====================================\n"
		);
		scanf("%d", &choose);
		switch (choose) {		//分支设计
			case 1:		//查找模块
				do {
					int count = 0,index_1[10];
					clearScreen();
					printf("进入查词模式\n");
					speak("进入查词模式");
					printf("请选择你要进入的模式，英译汉(E)或是汉译英(C)\n");
					scanf(" %c",&a);
					if (a == 'E' || a == 'e') {
						printf("请输入你想查找的单词的英文：\n");
						scanf("%s", input_spelling);
						lower(input_spelling);
						int len = strlen(input_spelling);
						printf("你查找的单词可能是：\n");
						speak("你查找的单词可能是");
						for (int i = 0; i < wordsCount; i++) {
							if (strncmp(dictionary[i].spelling,input_spelling,len) == 0) {
								index_1[count] = i;
								printf("%d : %s\n",count+1,dictionary[i].spelling);
								count++;
								if (count == 10) {
									break;
								}
							}
						}
						if (count == 0) {
							clearScreen();
							printf("未找到\n");
							speak("未找到");
						}
						else{
							printf("你具体想查找哪个词\n");
							scanf("%d",&choose);
							clearScreen();
							printf("%s %s\n",dictionary[index_1[choose-1]].spelling,dictionary[index_1[choose-1]].meaning);
							speak(dictionary[index_1[choose-1]].spelling);
							speak(dictionary[index_1[choose-1]].meaning);
							printf("按下任意键以返回\n");
							getchar();getchar();
						}
					}
					else {
						printf("请输入你想查找的单词的中文：\n");
						scanf("%s", input_meaning);
						int len = strlen(input_meaning);
						printf("你查找的单词可能是：\n");
						speak("你查找的单词可能是");
						for (int i = 0; i < wordsCount; i++) {
							if (strncmp(dictionary[i].meaning,input_meaning,len) == 0) {
								index_1[count] = i;
								printf("%d :%s %s\n",count+1,dictionary[i].spelling,dictionary[i].meaning);
								count++;
								if (count == 10) {
									break;
								}
							}
						}
						if (count == 0) {
							clearScreen();
							printf("未找到\n");
							speak("未找到");
						}
						else {
							printf("你具体想查找哪个词\n");
							scanf("%d",&choose);
							clearScreen();
							printf("%s %s\n",dictionary[index_1[choose-1]].spelling,dictionary[index_1[choose-1]].meaning);
							speak(dictionary[index_1[choose-1]].spelling);
							speak(dictionary[index_1[choose-1]].meaning);
							printf("按下任意键以返回\n");
							getchar();getchar();
						}
					}
					clearScreen();
					printf("是否继续使用词典\n");
					scanf(" %c",&a);
					if (a == 'n') {
						clearScreen();
						exit(0);
					}
					clearScreen();
					printf("是否留在查词模式中\n");
					scanf(" %c",&a);
				}while (a == 'y');
				clearScreen();
				break;
			case 2:		//增词模块
				do {
					clearScreen();
					printf("进入增加单词模式\n");
					speak("进入增加单词模式,注意词库上限为8000\n");
					printf("请输入你想增加的单词的中文和英文：\n");
					printf("格式参考:apple 苹果\n");
					FILE* fp = fopen(path, "a");
					scanf("%s %s",input_spelling,input_meaning);
					strcpy(dictionary[wordsCount].spelling,input_spelling);
					strcpy(dictionary[wordsCount].meaning,input_meaning);
					fprintf(fp,"%s %s\n",dictionary[wordsCount].spelling,dictionary[wordsCount].meaning);
					fclose(fp);
					clearScreen();
					if (strcmp(dictionary[wordsCount].spelling,"") != 0) {
						printf("写入成功\n");
						speak("写入成功");
					}
					else {
						printf("写入失败请检查源码\n");
					}
					if (wordsCount > 7999) {		//防止溢出
						printf("数组溢出，错误\n");
					}
					wordsCount++;
					clearScreen();
					printf("是否继续使用词典\n");
					scanf(" %c",&a);
					if (a == 'n') {
						clearScreen();
						exit(0);
					}
					printf("是否留在增词模式中\n");
					scanf(" %c",&a);
				}while (a == 'y');
				clearScreen();
				break;
			case 3:		//删词模块
				do {
					clearScreen();
					printf("进入删除单词模式\n");
					speak("进入删除单词模式\n");
					printf("输入你想删除的单词\n");
					scanf("%s", input_spelling);
					int index_3 = find_word(input_spelling);
					if (index_3 == -1) {
						printf("未查找到相关单词\n");
						clearScreen();
						break;
					}
					else {
						printf("你要删除的单词是%s,排序是%d,确定删除吗\n",dictionary[index_3].spelling,index_3+1);
						speak("你要删除的单词是");
						speak(dictionary[index_3].spelling);
						scanf(" %c",&a);
						if (a == 'y') {
							for (int k = index_3; k < wordsCount; k++) {
								dictionary[k] = dictionary[k+1];
							}
							wordsCount--;
							printf("已在内存中删除\n");
							FILE* fp_3 = fopen(path, "w");
							if (fp_3 != NULL) {
								for (int k = 0; k < wordsCount; k++) {
									fprintf(fp_3, "%s %s\n",dictionary[k].spelling,dictionary[k].meaning);
								}
								fclose(fp_3);
								printf("删除完成\n");
								speak("删除完成");
							}
							else {
								printf("读取文件错误,请检查源码\n");
							}
						}
					}
					printf("是否继续使用词典\n");
					scanf(" %c",&a);
					if (a == 'n') {
						clearScreen();
						exit(0);
					}
					printf("是否留在删词模式中\n");
					scanf(" %c",&a);
				}while (a == 'y');
				clearScreen();
				break;
			case 4:		//替换模块
				do {
					FLAG4:		//这里使用的goto语句是为了跳出多层嵌套
					clearScreen();
					printf("进入修改单词模式\n");
					speak("进入修改单词模式");
					printf("输入你想替换的单词\n");
					speak("输入你想替换的单词");
					scanf("%s",input_spelling);
					int index_4 = find_word(input_spelling);
					if (index_4 == -1) {
						printf("未找到这个词,是否重新输入\n");
						scanf(" %c",&a);
						if (a == 'y') {
							goto FLAG4;		//这里使用的goto语句是为了跳出多层嵌套
						}
						else {
							break;
						}
					}
					printf("你要替换的单词是%s %s,是否正确\n",dictionary[index_4].spelling,dictionary[index_4].meaning);
					scanf(" %c",&a);
					if (a == 'y') {
							printf("输入你的目标单词\n");
							speak("输入你的目标单词");
							scanf("%s %s",input_spelling,input_meaning);
							strcpy(dictionary[index_4].spelling,input_spelling);
							strcpy(dictionary[index_4].meaning,input_meaning);
							printf("替换之后的词为:%s %s,是否正确\n",dictionary[index_4].spelling,dictionary[index_4].meaning);
							scanf(" %c",&a);
							if (a == 'y') {
								FILE* fp_4 = fopen(path, "w");
								if (fp_4 != NULL) {
									for (int k = 0; k < wordsCount; k++) {
										fprintf(fp_4,"%s %s\n",dictionary[k].spelling,dictionary[k].meaning);
									}
								}
								fclose(fp_4);
								printf("替换完成\n");
								speak("替换完成");
							}
							else {
								goto FLAG4;		//这里使用的goto语句是为了跳出多层嵌套
							}
					}
					else {
						break;
					}
					printf("是否继续使用词典\n");
					scanf(" %c",&a);
					if (a == 'n') {
						clearScreen();
						exit(0);
					}
					printf("是否留在替换单词模式中\n");
					scanf(" %c",&a);
				}while (a == 'y');
				clearScreen();
				break;
			case 5:		//练习模式代码
				do {
					clearScreen();
					printf("已进入练习模式\n");
					speak("已进入练习模式");
					printf("请输入你想练习的模式,英译汉请输入E，汉译英请输入C\n");
					scanf(" %c",&b);
					printf("请输入你想练习的题目数量\n");
					scanf("%d",&choose_5);
					clearScreen();
					if (b == 'E') {
						for (int k = 0; k < choose_5; k++) {
							random = num();
							strcpy(random_char,dictionary[random].spelling);
							printf("%s\n",random_char);
							speak(random_char);
							printf("请输入对应中文\n");
							scanf("%s",input_meaning);
							if (strstr(dictionary[random].meaning,input_meaning) != NULL) {
								printf("恭喜你答对了\n");
								speak("恭喜你答对了");
								printf("完整答案是%s\n",dictionary[random].meaning);
								speak("完整答案是");
								speak(dictionary[random].meaning);
							}
							else {
								printf("错误,正确答案为%s\n",dictionary[random].meaning);
								speak("很抱歉答案错误，正确答案是");
								speak(dictionary[random].meaning);
								if (find_wrong_words(dictionary[random].spelling) == -1) {
									FILE *wrong_words = fopen("wrong_words.txt","a");
									if (wrong_words_count < 8000) {
										strcpy(dictionary[wrong_words_count].wrong_words_spelling,dictionary[random].spelling);
										strcpy(dictionary[wrong_words_count].wrong_words_meaning,dictionary[random].meaning);
										wrong_words_count++;
									}
									if (wrong_words != NULL) {
										fprintf(wrong_words,"%s %s\n",dictionary[random].spelling,dictionary[random].meaning);
										fclose(wrong_words);
									}
									else {
										printf("文件打开错误，文件为空\n");
										speak("错误");
									}
								}
							}
							clearScreen();
						}
					}
					else {
						for (int k = 0; k < choose_5; k++) {
							random = num();
							strcpy(random_char,dictionary[random].meaning);
							printf("%s\n",random_char);
							speak(random_char);
							printf("请输入对应英文\n");
							scanf("%s",input_spelling);
							if (strcmp(dictionary[random].spelling,input_spelling) == 0) {
								printf("恭喜你答对了\n");
								speak("恭喜你答对了");
							}
							else {
								printf("错误,正确答案为%s",dictionary[random].spelling);
								speak("很抱歉答案错误，正确答案是");
								speak(dictionary[random].spelling);
								if (find_wrong_words(dictionary[random].spelling) == -1) {
									FILE *wrong_words = fopen("wrong_words.txt","a");
									if (wrong_words_count < 8000) {
										strcpy(dictionary[wrong_words_count].wrong_words_spelling,dictionary[random].spelling);
										strcpy(dictionary[wrong_words_count].wrong_words_meaning,dictionary[random].meaning);
										wrong_words_count++;
									}
									if (wrong_words != NULL) {
										fprintf(wrong_words,"%s %s\n",dictionary[random].spelling,dictionary[random].meaning);
										fclose(wrong_words);
									}
									else {
										printf("文件打开错误，文件为空\n");
										speak("错误");
									}
								}
							}
						}
					}
					printf("是否继续使用词典\n");
					scanf(" %c",&a);
					if (a == 'n') {
						clearScreen();
						exit(0);
					}
					printf("是否留在练习模式中\n");
					scanf(" %c",&a);
				}while (a == 'y');
				clearScreen();
				break;
			case 6:
				do {
					clearScreen();
					printf("已进入考试模式\n");
					speak("已进入考试模式");
					printf("请输入你想考试的模式,英译汉请输入E，汉译英请输入C\n");
					scanf(" %c",&b);
					printf("注意下面将给出20道题，每道题5分\n");
					Sleep(3000);
					clearScreen();
					if (b == 'E') {
						for (int k = 0; k < 20; k++) {
							random = num();
							strcpy(random_char,dictionary[random].spelling);
							printf("你目前的分数为%d\n",score);
							printf("%s\n",random_char);
							printf("请输入对应中文\n");
							scanf("%s",input_meaning);
							if (strstr(dictionary[random].meaning,input_meaning) != NULL) {
								printf("恭喜你答对了\n");
								speak("恭喜你答对了");
								score += 5;
							}
							else {
								printf("错误,正确答案为%s\n",dictionary[random].meaning);
								speak("很抱歉答案错误，正确答案是");
								speak(dictionary[random].meaning);
								if (find_wrong_words(dictionary[random].spelling) == -1) {
									FILE *wrong_words = fopen("wrong_words.txt","a");
									if (wrong_words_count < 8000) {
										strcpy(dictionary[wrong_words_count].wrong_words_spelling,dictionary[random].spelling);
										strcpy(dictionary[wrong_words_count].wrong_words_meaning,dictionary[random].meaning);
										wrong_words_count++;
									}
									if (wrong_words != NULL) {
										fprintf(wrong_words,"%s %s\n",dictionary[random].spelling,dictionary[random].meaning);
										fclose(wrong_words);
									}
									else {
										printf("文件打开错误，文件为空\n");
										speak("错误");
									}
								}
							}
							clearScreen();
						}
					}
					else {
						for (int k = 0; k < 20; k++) {
							random = num();
							strcpy(random_char,dictionary[random].meaning);
							printf("你目前的分数为%d\n",score);
							printf("%s\n",random_char);
							printf("请输入对应英文\n");
							scanf("%s",input_spelling);
							if (strcmp(dictionary[random].spelling,input_spelling) == 0) {
								printf("恭喜你答对了\n");
								speak("恭喜你答对了");
								score += 5;
							}
							else {
								printf("错误,正确答案为%s",dictionary[random].spelling);
								speak("很抱歉答案错误，正确答案是");
								speak(dictionary[random].spelling);
								if (find_wrong_words(dictionary[random].spelling) == -1) {
									FILE *wrong_words = fopen("wrong_words.txt","a");
									if (wrong_words_count < 8000) {
										strcpy(dictionary[wrong_words_count].wrong_words_spelling,dictionary[random].spelling);
										strcpy(dictionary[wrong_words_count].wrong_words_meaning,dictionary[random].meaning);
										wrong_words_count++;
									}
									if (wrong_words != NULL) {
										fprintf(wrong_words,"%s %s\n",dictionary[random].spelling,dictionary[random].meaning);
										fclose(wrong_words);
									}
									else {
										printf("文件打开错误，文件为空\n");
										speak("错误");
									}
								}
							}
						}
					}
					printf("是否继续使用词典\n");
					scanf(" %c",&a);
					if (a == 'n') {
						clearScreen();
						exit(0);
					}
					printf("是否留在考试模式中\n");
					scanf(" %c",&a);
				}while (a == 'y');
				clearScreen();
				break;
			case 7:
				do {
					clearScreen();
					printf("进入错题本\n");
					speak("进入错题本");
					clearScreen();
					printf("你需要进行朗读吗？\n");
					speak("你需要进行朗读吗");
					scanf(" %c",&a);
					if (a == 'n') {
						for (int k = 0; k < wrong_words_count; k++) {
							printf("%s %s\n",dictionary[k].wrong_words_spelling,dictionary[k].wrong_words_meaning);
						}
					}
					else {
						for (int k = 0; k < wrong_words_count; k++) {
							printf("%s %s\n",dictionary[k].wrong_words_spelling,dictionary[k].wrong_words_meaning);
							speak(dictionary[k].wrong_words_spelling);
							speak(dictionary[k].wrong_words_meaning);
						}
					}
					printf("是否继续使用词典\n");
					scanf(" %c",&a);
					if (a == 'n') {
						clearScreen();
						exit(0);
					}
					printf("是否留在考试模式中\n");
					scanf(" %c",&a);
				}while (a == 'y');
				clearScreen();
				break;
			case 8:clearScreen();		//退出
				speak("退出");
				exit(0);
			default:clearScreen();
				printf("输入错误,系统退出\n");
				speak("输入错误，系统退出");
				Sleep(3000);
				clearScreen();
				break;
		}
	}
}


void speak(const char* word) {		//发音函数
    char command[512];

    // 原理：调用 PowerShell 发音，并用双引号把命令包起来，
    // 这样 CLion 的 Shell 就不会误把括号当成特殊字符处理了。
    sprintf(command, "powershell -c \"(New-Object -ComObject SAPI.SpVoice).Speak('%s')\"", word);

    system(command);
}
void lower(char* word) {
	int i = 0;
	while (word[i]) {
		word[i] = tolower(word[i]);
		i++;
	}
}
void clearScreen() {		//清屏函数
    system("clear");	//!!!我使用的是cygwin64编译器，所以这里使用的是system("clear"),如果使用win编译器请改成system("cls")!!!
}
int load_words(const char* filepath) {		//加载函数
	FILE* fp = fopen(filepath, "r");
	if (fp == NULL) {
		printf("错误：无法打开文件\n");
		return 0;
	}
	int i = 0;
	while (fscanf(fp, "%s", dictionary[i].spelling) != EOF) {
		lower(dictionary[i].spelling);
		char buffer[200];
		if (fgets(buffer, 200, fp) != NULL) {
			int start = 0;
			while (buffer[start] == ' ' || buffer[start] == '\t') {
				start++;
			}
			size_t len = strlen(buffer);
			if (len > 0 && buffer[len-1] == '\n') {
				buffer[len-1] = '\0';
			}
			strcpy(dictionary[i].meaning, &buffer[start]);
		}
		i++;
		if (i >= 8000) break;
	}
	fclose(fp);
	return i;
}
int load_wrong_words(const char* filepath) {		//加载错题函数
	FILE* fp = fopen(filepath, "r");
	if (fp == NULL) {
		printf("错误：无法打开文件\n");
		return 0;
	}
	int i = 0;
	while (fscanf(fp, "%s", dictionary[i].wrong_words_spelling) != EOF) {
		lower(dictionary[i].wrong_words_spelling);
		char buffer[200];
		if (fgets(buffer, 200, fp) != NULL) {
			int start = 0;
			while (buffer[start] == ' ' || buffer[start] == '\t') {
				start++;
			}
			size_t len = strlen(buffer);
			if (len > 0 && buffer[len-1] == '\n') {
				buffer[len-1] = '\0';
			}
			strcpy(dictionary[i].wrong_words_meaning, &buffer[start]);
		}
		i++;
		if (i >= 8000) break;
	}
	fclose(fp);
	return i;
}
int find_word(const char* word) {		//查找函数
	for (int i = 0; i < wordsCount; i++) {
		if (strcmp(dictionary[i].spelling, word) == 0) {
			return i;
		}
	}
	return -1;
}
int find_wrong_words(const char* word) {		//查找错题函数
	for (int i = 0; i < wrong_words_count; i++) {
		if (strcmp(dictionary[i].wrong_words_spelling, word) == 0) {
			return i;
		}
	}
	return -1;
}
int num() {		//随机函数
	int number = rand() % wordsCount;
	return number;
}