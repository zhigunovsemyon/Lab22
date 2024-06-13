#include <stdio.h>
#include <stdint.h>

#define MAXLEN 256
#define SCANF_SPEC_S "%255s"

enum Switches
{
	QUIT,
	KEYBOARD,
	READ_FILE,
	REMOVE,
	RM_PARENTHESES,
	COUNT_SPACE,
	RM_COMMENT_BLOCK,
	PRINT
};

void GetAndReadFile(char String[]);
uint8_t Switcher(char String[]);
uint64_t FileLen(FILE* f, uint32_t maxLen);
uint32_t CountMaxSpace(char String[]);
void RemoveParentheses(char String[]);
void RemoveCommentBlock(char String[]);
