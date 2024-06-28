#include "bilibili.h"

HTTPClient http;    
String url_bilibili = "";   

bool Bilibili::update()
{
        ParseData(GitURL(UID));
        return true;
}
 
String Bilibili::GitURL(String uid)    //获取API链接
{
  url_bilibili =  "https://api.bilibili.com/x/web-interface/card?mid=497309258";
  return url_bilibili;
}
 
void Bilibili::ParseData(String url)
{  
    DynamicJsonDocument doc(3072); 
    http.begin(url);   
    
    int httpGet = http.GET();   
    if(httpGet > 0)
    {
        if(httpGet == HTTP_CODE_OK)  
        {
            String json = http.getString();    //获得响应体信息
            deserializeJson(doc, json);    //Json解析
            
            fans=doc["data"]["card"]["fans"].as<long>();
            face=doc["data"]["card"]["face"].as<String>();
            name=doc["data"]["card"]["name"].as<String>();
            level=doc["data"]["card"]["level_info"]["current_level"].as<uint8_t>();
            follow=doc["data"]["card"]["attention"].as<int>();
            likes=doc["data"]["like_num"].as<long>();
            archive_count=doc["data"]["archive_count"].as<int>();
            sign=doc["data"]["card"]["sign"].as<String>();
        }
    }
    http.end();

}
Bilibili bilibili;