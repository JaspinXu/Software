/*
 * @Author: JaspinXu sea.xuo@gmail.com
 * @Date: 2024-05-04 10:32:52
 * @LastEditors: JaspinXu sea.xuo@gmail.com
 * @LastEditTime: 2024-06-13 10:51:04
 * @FilePath: \LCD_testd:\Shiroe-master\Shiroe-master\Software\include\bilibili.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef BILIBILI_H
#define BILIBILI_H
#include "head.h"
#include <ArduinoJson.h> //引用两个需要的库
#include <HTTPClient.h>

class Bilibili
{
public:
    String UID;
    long fans;
    int follow;
    String name;
    String face;
    uint8_t level;
    String sign;
    int archive_count;
    long likes;
    bool update();

private:
    void ParseData(String url);

    String GitURL(String uid);
};
extern Bilibili bilibili;

#endif
