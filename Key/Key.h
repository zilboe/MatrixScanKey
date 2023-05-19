#ifndef __KEY_H__
#define __KEY_H__

#include "stdio.h"
#include "reg51.h"
#include "main.h"
#include "usart.h"
#define KEY_VALUE_MAX 2
#define     S1      0x77
#define     S2      0x7b
#define     S3      0x7d
#define     S4      0x7e
#define     S5      0xb7
#define     S6      0xbb
#define     S7      0xbd
#define     S8      0xbe
#define     S9      0xd7
#define     S10     0xdb
#define     S11     0xdd
#define     S12     0xde
#define     S13     0xe7
#define     S14     0xeb
#define     S15     0xed
#define     S16     0xee

typedef enum
{
    Key_Short_Press,//短按
    Key_Lift,//抬起
    Key_Long_Press,//长按
    Key_Compound_Press,//复合按键
    Key_None,//none
}key_state_e;

typedef struct keyBoard
{
    uint8_t key_value[KEY_VALUE_MAX];//键值
    uint8_t key_Number;//按键数量
    bool key_Action_Flag;//执行标志
    void (*key_func)(struct keyBoard *);//执行函数
    uint16_t key_Last_value;//上次键值
    key_state_e key_status;//当前状态
    uint16_t Key_Long_Count;//长按扫描计数
    bool key_long_press_action_flag;//长按操作的执行标志
    uint16_t key_long_scan_Count;//长按
}Key_Info_t;

/**
 * @brief 获取键值
 * @return 返回键值
 */
uint8_t getKeyValue(void);

/**
 * @brief 获取键值
 * @return 返回键值
 */
uint8_t getKeyValue2(void);

/**
 * @brief 键盘扫描初始化
 * @param key 结构体
 */
void ScanKeyInit(Key_Info_t *Key);

/**
 * @brief 键值处理
 * @param key 键值
 * @param keyboard 键盘结构体
 */
void KeyValueProcess(uint8_t key, Key_Info_t *keyboard);
/**
 * @brief 检查按键是否被抬起
 * @param keyvalue 键值
 * @return true 是 false 不是
*/
bool KeyIsUp(uint8_t keyvalue);

/**
 * @brief 检查按键是否刚按下
 * @param keyvalue 键值
 * @return true 刚按下 false 不是
 * 
*/
bool KeyIsClick(uint8_t keyvalue);

/**
 * @brief 检测按键是否处于按压
 * @param keyvalue 键值
 * @return true 是 false 不是
 */
bool KeyIsDown(uint8_t keyvalue);
/**
 * @brief 按下一瞬间的处理函数
 * @param key 存储键盘的结构体
 */
void KeyShortAction(Key_Info_t *key);
/**
 * @brief 长按事件处理
 * @param key 存储键盘的结构体
 */
void KeyLongAction(Key_Info_t *key);
/**
 * @brief 按键抬起的处理
 * @param key 存储键盘的结构体
 */
void KeyLiftAction(Key_Info_t *key);
/**
 * @brief 多按键的处理
 * @param key 存储键盘的结构体
 */
void KeyCompoundAction(Key_Info_t *key);
/**
 * @brief 按键事件的处理
 * @param key 存储键盘的结构体
 */
void keyFuncProcess(Key_Info_t *key);
#endif
