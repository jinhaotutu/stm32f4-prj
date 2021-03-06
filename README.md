# stm32标准工程介绍

---

## 功能说明

本工程是以STM32F4系列为基础，搭建的基本应用开发框架。

工程包含或将包含内容有：

- stm32f4库文件与相关关联文件
- 基本外设驱动文件
- 第三方开源库
- 应用自我编写开源库
- keil工程与stm32cubeide工程

在整个工程框架中保持底层框架不动，向上移植第三方开源库（freertos、lwip等），以及开发应用开源组件（iot相关）的形式来扩展工程的功能。

---

## 目录说明

```c
.
├─driver						// stm32外设驱动
├─fwlib							// stm32函数库
├─misis							// stm32配置文件
├─project						//工程文件，包含keil与stm32cubeide工程
│  └─stm32f4_first_demo
│      ├─Keil_MDK       
│      ├─STM32CubeIDE
│      └─user_code				//应用代码
├─startup						//启动文件
├─sys							//stm32基本资源配置文件
├─thirdlib						//第三方开源库，基本为日志库，后续增加os、lwip等等
│  ├─cJSON
│  └─EasyLogger
└─user							//应用中间组件代码
```



---

## 拓展说明

- 第一期：基本框架搭建，如上，可以用来直接基本该工程开发，所有软硬件进行分离，各部分进行分离，去耦合管理，方便后期拓展与移植。
- 第二期：移植freertos以及lwip，搭建基本网络框架，应用以socket等为主作为示例。
- 第三期：移植mqtt以及http等，搭建iot相关基本服务。
- 第四期：应用相关iot组件。
- 后续：加密数据，拓展格外功能，比如wifi、局域网、配网等。

---

ps：硬件资源需要自己搞定哦，有疑问的可以咨询本人哦



<img src="https://img-blog.csdnimg.cn/20200507175326677.JPG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3EzNjE3NTAzODk=,size_16,color_FFFFFF,t_70#pic_center" width=300 height=330> 

Tuu