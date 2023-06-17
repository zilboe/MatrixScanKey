#include "Key.h"
#include "ds18b20.h"
Key_Info_t Key_Board;
extern uint32_t systicks;
extern uint32_t keyComNumber;
uint8_t key_row[4] = {0x7f, 0xbf, 0xdf, 0xef};
/**
 * @brief 按键信息的初始化
 * @param Key 存储按键的结构体
 *
 */
void ScanKeyInit(Key_Info_t *Key)
{
	Key->key_Number = 0;
	Key->key_Action_Flag = false;
	Key->key_func = keyFuncProcess;
	Key->key_Last_value = 0x00;
	Key->key_value[0] = 0x00;
	Key->key_value[1] = 0x00;
	Key->key_status = Key_None;
	Key->Key_Long_Count = 0;
	Key->key_long_scan_Count = 0;
}

bool KeyIsDown(uint8_t keyvalue)
{
	if (keyvalue != 0x00)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/**
 * @brief 检查按键是否刚按下
 * @param keyvalue 键值
 * @return true 刚按下 false 不是
 *
 */
bool KeyIsClick(uint8_t keyvalue)
{
	if (KeyIsDown(keyvalue))
	{
		if (Key_Board.key_value[0] == 0X00) /*不能判断last值，必须判断收录的值*/
			return true;
		else
			return false;
	}
	else
		return false;
}

/**
 * @brief 检查按键是否被抬起
 * @param keyvalue 键值
 * @return true 是 false 不是
 */
bool KeyIsUp(uint8_t keyvalue)
{
	if (KeyIsDown(keyvalue))
		return false;
	else
	{
		if (Key_Board.key_Last_value != 0x00)
			return true;
		else
			return false;
	}
}

void KeyValueProcess(uint8_t key, Key_Info_t *keyboard)
{
	if (key != 0x00)
	{
		if (KeyIsClick(key))
		{
			/* 刚按下的状态 */
			keyboard->key_value[keyboard->key_Number++] = key;
			keyboard->key_Last_value = 0x00;
			keyboard->key_Action_Flag = true;
			keyboard->key_status = Key_Short_Press;
			keyboard->Key_Long_Count = systicks;
		}
		else if (KeyIsDown(key) && keyboard->key_value[0] == key && keyboard->key_Number == 1)
		{
			/* 处理长按 */
			if (systicks - keyboard->Key_Long_Count > 1000) /* 2s */
			{
				keyboard->key_Last_value = keyboard->key_value[0];
				keyboard->key_status = Key_Long_Press;
				keyboard->key_Action_Flag = true;
			}
			else
			{
				keyboard->key_Last_value = keyboard->key_value[0];
				keyboard->key_Action_Flag = false;
			}
		}
		else if (KeyIsDown(key) && keyboard->key_value[0] != key && keyboard->key_Number == 1)
		{
			/* 复合按键 */
			keyboard->key_Last_value = keyboard->key_value[0];
			keyboard->key_value[1] = key;
			keyboard->key_Action_Flag = true;
			keyboard->key_status = Key_Compound_Press;
			keyboard->key_Number = 2;
		}
		/* 按下状态 + 按键与之前两个按键某一个相同 + 按键记录数已经到2 */
		else if(KeyIsDown(key)  && keyboard->key_Number == 2 && (key==keyboard->key_value[0] || key==keyboard->key_value[1]))
		{
			if (keyComNumber>10) /* 长时间检测到只有一个按键，确保另一个按键已被抬起，先处理抬起的按键 */
			{
				if(key == keyboard->key_value[0])	/* 第一个按键没松手 */
				{
					keyboard->key_value[1] = 0x00;
					keyboard->key_Number = 1;
					keyboard->key_status = Key_Lift;
					keyboard->key_Action_Flag = true;
				}
				else if(key == keyboard->key_value[1])	/* 第二个按键没松手 */
				{
					keyboard->key_value[0] = 0x00;
					keyboard->key_Number = 1;
					keyboard->key_status = Key_Lift;
					keyboard->key_Action_Flag = true;
				}
				else
				{
					return;
				}
			}
		}
	}
	else if (KeyIsUp(key))
	{
		/* 按键抬起 */
		keyboard->key_Last_value = key;
		keyboard->key_status = Key_Lift;
		keyboard->key_value[keyboard->key_Number--] = 0x00;
		keyboard->key_Action_Flag = true;
	}
	else
	{
		/* none */
		keyboard->key_Action_Flag = false;
		keyboard->key_value[0] = 0x00;
		keyboard->key_value[1] = 0x00;
		keyboard->key_status = Key_None;
		keyboard->key_Last_value = 0x00;
	}
}

void keyFuncProcess(Key_Info_t *key)
{
	if (key->key_Action_Flag == false)
		return;
	if (key->key_status == Key_Short_Press)
	{
		KeyShortAction(key);
	}
	else if (key->key_status == Key_Long_Press)
	{
		if ((systicks - key->key_long_scan_Count) > 1000)
		{
			key->key_long_press_action_flag = true;
		}
		if (key->key_long_press_action_flag == true) /* 长按不松手,每2s执行一次程序 */
		{
			KeyLongAction(key);
			key->key_long_press_action_flag = false;
			key->key_long_scan_Count = systicks;
		}
	}
	else if (key->key_status == Key_Lift)
	{
		KeyLiftAction(key);
	}
	else if (key->key_status == Key_Compound_Press)
	{
		KeyCompoundAction(key);
	}
}

void KeyShortAction(Key_Info_t *key)
{
	if (key->key_status != Key_Short_Press)
		return;
	switch (key->key_value[0])
	{
	case S1:
		//sendString("S1 is down\r\n");
		sendByte(TempValue);
		break;
	case S2:
		sendString("S2 is down\r\n");
		break;
	case S3:
		sendString("S3 is down\r\n");
		break;
	case S4:
		sendString("S4 is down\r\n");
		break;
	case S5:
		sendString("S5 is down\r\n");
		break;
	case S6:
		sendString("S6 is down\r\n");
		break;
	case S7:
		sendString("S7 is down\r\n");
		break;
	case S8:
		sendString("S8 is down\r\n");
		break;
	case S9:
		sendString("S9 is down\r\n");
		break;
	case S10:
		sendString("S10 is down\r\n");
		break;
	case S11:
		sendString("S11 is down\r\n");
		break;
	case S12:
		sendString("S12 is down\r\n");
		break;
	case S13:
		sendString("S13 is down\r\n");
		break;
	case S14:
		sendString("S14 is down\r\n");
		break;
	case S15:
		sendString("S15 is down\r\n");
		break;
	case S16:
		sendString("S16 is down\r\n");
		break;
	}
	key->key_status = Key_None;
}

void KeyLongAction(Key_Info_t *key)
{
	if (key->key_status != Key_Long_Press)
		return;
	switch (key->key_value[0])
	{
	case S1:
		sendString("S1 is LongPress\r\n");
		break;
	case S2:
		sendString("S2 is LongPress\r\n");
		break;
	case S3:
		sendString("S3 is LongPress\r\n");
		break;
	case S4:
		sendString("S4 is LongPress\r\n");
		break;
	case S5:
		sendString("S5 is LongPress\r\n");
		break;
	case S6:
		sendString("S6 is LongPress\r\n");
		break;
	case S7:
		sendString("S7 is LongPress\r\n");
		break;
	case S8:
		sendString("S8 is LongPress\r\n");
		break;
	case S9:
		sendString("S9 is LongPress\r\n");
		break;
	case S10:
		sendString("S10 is LongPress\r\n");
		break;
	case S11:
		sendString("S11 is LongPress\r\n");
		break;
	case S12:
		sendString("S12 is LongPress\r\n");
		break;
	case S13:
		sendString("S13 is LongPress\r\n");
		break;
	case S14:
		sendString("S14 is LongPress\r\n");
		break;
	case S15:
		sendString("S15 is LongPress\r\n");
		break;
	case S16:
		sendString("S16 is LongPress\r\n");
		break;
	}
	key->key_status = Key_None;
}

void KeyLiftAction(Key_Info_t *key)
{
	uint8_t keyvalue = 0x00;
	if (key->key_status != Key_Lift)
		return;
	if (key->key_value[1] == 0x00 && key->key_value[0] != 0x00)
		keyvalue = key->key_value[0];
	else if (key->key_value[1] != 0x00)
		keyvalue = key->key_value[1];
	switch (keyvalue)
	{
	case S1:
		//sendString("S1 is Lift\r\n");
		break;
	case S2:
		sendString("S2 is Lift\r\n");
		break;
	case S3:
		sendString("S3 is Lift\r\n");
		break;
	case S4:
		sendString("S4 is Lift\r\n");
		break;
	case S5:
		sendString("S5 is Lift\r\n");
		break;
	case S6:
		sendString("S6 is Lift\r\n");
		break;
	case S7:
		sendString("S7 is Lift\r\n");
		break;
	case S8:
		sendString("S8 is Lift\r\n");
		break;
	case S9:
		sendString("S9 is Lift\r\n");
		break;
	case S10:
		sendString("S10 is Lift\r\n");
		break;
	case S11:
		sendString("S11 is Lift\r\n");
		break;
	case S12:
		sendString("S12 is Lift\r\n");
		break;
	case S13:
		sendString("S13 is Lift\r\n");
		break;
	case S14:
		sendString("S14 is Lift\r\n");
		break;
	case S15:
		sendString("S15 is Lift\r\n");
		break;
	case S16:
		sendString("S16 is Lift\r\n");
		break;
	}
	key->key_status = Key_None;
}

void KeyCompoundAction(Key_Info_t *key)
{
	if (key->key_status != Key_Compound_Press)
		return;
	if ((key->key_value[0] == S1 && key->key_value[1] == S6) || (key->key_value[1] == S1 && key->key_value[0] == S6))
	{
		sendString("S1 And S2 Compound Press\r\n");
	}
	
	key->key_status = Key_None;
}

uint8_t getKeyValue(void)
{
	uint8_t i = 0;
	uint8_t keyValue = 0x00;
	for (i = 0; i < 4; i++)
	{
		P1 = key_row[i];
		if ((P1 & key_row[i]) != key_row[i])
		{
			keyValue = P1;
			goto k1;
		}
	}
k1:
	return keyValue;
}

uint8_t getKeyValue2(void)
{
	char i = 0;
	uint8_t keyValue = 0x00;
	for (i = 3; i > -1; i--)
	{
		P1 = key_row[i];
		if ((P1 & key_row[i]) != key_row[i])
		{
			keyValue = P1;
			goto k2;
		}
	}
k2:
	return keyValue;
}