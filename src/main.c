#include "main.h"
/*
В заданном тексте удалить все части текста, заключенные в	*
скобки (вместе со скобками).								*
Примечание: в тексте "(1333(ыва)" удалится всё

Дан текст. Определить наибольшее количество подряд идущих	*
пробелов в нем.												*

Исключить из строки группы символов, расположенные между	*
символами «*//*», «*//*» включая границы.Предполагается,	* 
что нет вложенных скобок.									*
*/
int main(void)
{
	char String[MAXLEN];
	*String = 0; //Установка первым символом терминального
	do
	{
		switch (Switcher(String))
		{
		case QUIT: //q
			return 0;

		case KEYBOARD://k
			puts("Введите текст:");
			fgets(String, MAXLEN, stdin);
			if (*String == '\n')	//Если пользователь нажал Enter, не введя ничего
				*String = 0;		//строка зануляется
			break;

		case READ_FILE: //f
			GetAndReadFile(String);
			break;

		case REMOVE: //d
			*String = 0; //Установка первым символом терминального
			break;

		case RM_PARENTHESES: //( )
			RemoveParentheses(String);
			break;

		case COUNT_SPACE: //s
			printf("Максимальное число пробелов: %u\n", 
				CountMaxSpace(String));
			break;

		case RM_COMMENT_BLOCK: //c
			RemoveCommentBlock(String);
			break;

		case PRINT: //p
			puts(String);
			break;

		default:
			break;
		}
		putchar('\n');
	} while (1);
}

//Удаление блока /**/
void RemoveCommentBlock(char String[])
{	//j указывает на новый номер ячейки, i -- старый, open -- флаг открытой скобки
	uint16_t j, i, open;
	for (open = 0, j = 0, i = 0; String[i]; ++i) //Цикл прододжается на протяжении строки
	{
		//Если флаг открытой скобки сброшен, и встречена открывающая скобка
		if (!open && String[j] == '/' && String[j + 1] == '*')
			open++;//Флаг поднимается

		//Если флаг открытой скобки поднят, и встречена закрывающая скобка
		if (open && String[i] == '*' && String[i + 1] == '/')
			open--, i += 2;//Флаг спускается, символ переключается

		if (!open)	//Если скобки не открыты
		{
			if (i != j)// номера ячеек не равны
				String[j] = String[i];//содержимое одной копируется в другую
			j++;//j смещается всегда, когда скобки закрыты
		}
	}
	String[j] = 0;//перестановка терминального символа на новое место
}

//Удаление блока в скобках ()
void RemoveParentheses(char String[])
{
		//"Перемотка" строки до начала блока
		for (; *String != '('; String++)
			if (!(*String))	//Если встречен конец файла,
				return;		// то функция завершается

		/*Дальнейший код выполняется только если строка ещё существует,
		и текущий первый симол -- открывающая скобка*/
		uint16_t i = 1;
		for (; String[i] != ')'; i++)
			if (!String[i])	//Если встречен конец файла,
				return;		//то функция завершнается

		/*Дальнейший код выполняется только если встречена закрывающая скобка*/
		//i содержит в себе размер блока в скобках c закрывающей скобкой, 
		// String[0] равен открывающей скобке
		//String[i] равен закрывающей скобке
		uint16_t j = 0;
		do
		{
			String[j] = String[i + 1];
			if (!String[j]) /*Если был скопирован терминальный символ*/
				return RemoveParentheses(String);	//Осуществляется повторная проверка
			i++, j++;
		} while (1);
}

//Подсчёт максимальной последовательности пробелов в строке String
uint8_t CountMaxSpace(char String[])
{
	uint32_t max = 0, count = 0;
	for (uint32_t i = 0; String[i]; ++i)//Цикл перебирает строку, пока она не закончится
	{
		if (String[i] != ' ')
			continue;
		
		/*else*/
		do//Если символ оказался пробелом,
		{// перебор осуществляется этим циклом, вместо внешнего
			count++;	//Временный счётчик увеличивается
			i++;		//Счётчик строки также увеличивается
		} while (String[i] == ' ');

		//После окончание цикла счёта пробелов, сравнивается с максимальным,
		if (count > max)
			max = count;// присваивается, если больше
		count = 0;//Временный счётчик сбрасывается
	}
	return max;//После всех циклов, максимальное значение возвращается
}

//Выбор режима работы
uint8_t Switcher(char String[])
{
	printf("%s%s%s",
		"Для выхода нажмите q\n",
		"Чтобы ввести текст вручную, введите k\n",
		"Чтобы прочитать текст из файла, введите f\n");
	if (*String)	//Если в памяти есть строка
	{
		printf("%s%s%s%s%s",
			"Чтобы вывести текст, введите p\n",
			"Чтобы удалить весь текст, введите d\n",
			"Чтобы удалить текст внутри скобок, введите ( или )\n",
			"Чтобы удалить текст внутри блока /* */, введите c\n",
			"Чтобы сосчитать наибольшую последовательность пробелов, введите s\n");
	}
	do
	{
		switch (getchar())
		{
		case 'q':
		case 'Q':
			getchar();//Удаление новой строки из ввода
			return QUIT;
		case 'k':
		case 'K':
			getchar();//Удаление новой строки из ввода
			return KEYBOARD;
		case 'f':
		case 'F':
			getchar();//Удаление новой строки из ввода
			return READ_FILE;
		case 'd':
		case 'D':
			getchar();//Удаление новой строки из ввода
			if (*String)
				return REMOVE;
			break;
		case 'p':
		case 'P':
			getchar();//Удаление новой строки из ввода
			if (*String)
				return PRINT;
			break;
		case '(':
		case ')':
			getchar();//Удаление новой строки из ввода
			if (*String)
				return RM_PARENTHESES;
			break;
		case 's':
		case 'S':
			getchar();//Удаление новой строки из ввода
			if (*String)
				return COUNT_SPACE;
			break;
		case 'c':
		case 'C':
			getchar();//Удаление новой строки из ввода
			if (*String)
				return RM_COMMENT_BLOCK;
			break;
		default:
			break;
		}
	} while (1);
}

//Подсчёт длинны файла, сравнение с максимальным
uint32_t FileLen(FILE* f, uint32_t maxLen)
{
	fseek(f, SEEK_SET, SEEK_END);//Перемотка в конец
	uint32_t len = ftell(f);	 //Чтение размера файла
	rewind(f);					 //Перемотка обратно в начало
	return (len < maxLen) ? 	 //Если полученный размер больше максимального
		len : maxLen;			 //передаётся максимальный
}

//Процедура спрашивает у пользователя файл, читает его в строку String
void GetAndReadFile(char String[])
{
	FILE* f;
	printf("Введите открываемый файл: ");
	scanf(SCANF_SPEC_S, String);
	f = fopen(String, "rb");
	if (!f)
	{
		puts("Не удалось открыть файл!");
		*String = 0; //Установка первым символом терминального
		return;
	}
	//Определение размера загружаемой строки между размером файла и максимальным
	uint32_t len = FileLen(f, MAXLEN - 1);	
	fread(String, sizeof(char), len, f);	//Чтение в буфер
	String[len] = 0;						//Зануление конца
	fclose(f);								//Закрытие файла
	return;
}