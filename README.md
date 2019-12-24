# GControl
自绘控件
mfc一些常用控件的美化

## 已经完成的控件  
* [基于内存模板的dialog](./GControl/GControl/GControl/gdialog.h)
* [static控件](./GControl/GControl/GControl/gstatic.h)
* [listbox控件](./GControl/GControl/GControl/glistbox.h)
* [combobox控件](./GControl/GControl/GControl/gcombobox.h)
* [edit控件](./GControl/GControl/GControl/gedit.h)
* [push button](./GControl/GControl/GControl/gbutton.h) (普通的按钮, 无文字, 仅仅贴图, 需要`normal, hover, pressed三个图片`，最少也得有个`normal图`哇)
* [radio button](./GControl/GControl/GControl/gbutton.h)
* [checkbox](./GControl/GControl/GControl/gbutton.h)
* [groupbox](./GControl/GControl/GControl/ggroupbox.h)

## 温馨提示
* 该控件库需要Gdiplus, 请记得初始化Gdiplus
* 使用时仅仅需要该项目最里层的那个目录`[GCtontrol]`，在自己的项目中仅仅需要包含 [#include "GControl/gcontrol.h"](./GControl/GControl/GControl/gcontrol.h)
* 请使用命名空间 `GCtrl::XXX`，不要使用`using namespace GCtrl`, 我个人讨厌`using namespace`
* 你可以修改我的代码，但是请保留每个文件最上面的注释，该注释里写的是版权，作者名，也就是我的名字

## `最后希望我的这些小东西可以给你们一些便利(*￣︶￣)`

by 龚志慧  
latest  modify 2019.12.24