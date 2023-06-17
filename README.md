# 51单片机矩阵键盘(检测按键按下,长按,抬起)

## 矩阵键盘原理图如图所示
<<<<<<< HEAD

 ![image text] (https://github.com/zilboe/MatrixScanKey/blob/main/IMG/1684508182773.png)

## 最终检测效果

 ![image text] (https://github.com/zilboe/MatrixScanKey/blob/main/IMG/1684508231379.png)

## 多按键按下的结果

 ![image text] (https://github.com/zilboe/MatrixScanKey/blob/main/IMG/1684508293689.png)
=======
![image text](https://github.com/zilboe/MatrixScanKey/blob/main/IMG/1684508182773.png)

## 最终检测效果
![image text](https://github.com/zilboe/MatrixScanKey/blob/main/IMG/1684508231379.png)

## 多按键按下的结果
![image text](https://github.com/zilboe/MatrixScanKey/blob/main/IMG/1684508293689.png)
>>>>>>> df929c26deb9ebd51fb7bf8d90fa4ce40997f296

有个bug仍需要解决就是多按键按下后触发事件之后，抬起其中一个按键，**按道理应该有个先抬和后抬按键的事件触发，但是目前现在就是必须两个按键全都抬起后才能重新按下触发事件**，所以现在在解决这个问题

# 目前还在补充多按键中出现的bug
