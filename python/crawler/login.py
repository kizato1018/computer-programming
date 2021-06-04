import requests
import pprint
import json
import re

if __name__ == "__main__":
    # step 1: 指定url
    json_url = ' https://www.pixiv.net/ajax/top/illust?mode=all&lang=zh_tw'
    cookie = 'first_visit_datetime_pc=2021-06-03+16:57:34; p_ab_id=6; p_ab_id_2=0; p_ab_d_id=1324809154; yuid_b=NhE4BxA; __utmz=235335808.1622707054.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); __utmc=235335808; __utma=235335808.1025102245.1622707054.1622707054.1622707054.1; _gid=GA1.2.1053496890.1622707056; _ga=GA1.2.1025102245.1622707054; PHPSESSID=69268787_BrvpqlFrrtgakBDZVHYUDw2o0JRPBHtO; device_token=74a765f0f315a6bddd7e987e6497ae5f; privacy_policy_agreement=3; c_type=20; privacy_policy_notification=0; a_type=0; b_type=1; ki_r=; ki_s=; _im_vid=01F78EMJTZCA7VHB9CDMRQ3HFE; _im_uid.3929=b.d1a7c882d50de8ba; __gads=ID=62c246332f93262d-22857a6f2bc9003a:T=1622707688:S=ALNI_MYpj_v9QJGk8nmyJoNx2tHysg48Rw; __utmv=235335808.|2=login ever=yes=1^3=plan=normal=1^5=gender=male=1^6=user_id=69268787=1^9=p_ab_id=6=1^10=p_ab_id_2=0=1^11=lang=zh_tw=1; ki_t=1622707068595;1622707068595;1622711469989;1;10; __cf_bm=e69aa93ffe06e338a611d220e59cecf675a8ecb7-1622715251-1800-AU3B2WC/t8XkvnIC6zpTOb7GZm6o/JUp1tLeRYgAGLQvmIIvc24LSz1R+mrzkfIWuKXaiCJo3LXBnHFRrmsXNcTLtIupsKz8NcICmAsQff3a; _gat_UA-1830249-3=1; tag_view_ranking=RTJMXD26Ak~_hSAdpN9rx~5qQ60nSYiM~tJInOhigyo~ORgpNmUHU2~8bco711WIM~8WDaOcMTH-~GNEIewX58Y~WMqI_4YLfc~HGziQYKsiX~_EOd7bsGyl~dg_40nEhSE~F269zeh88s~Lt-oEicbBr~RvAGyC8a50~R5clk_detG~QliAD3l3jr~o0i73bCUgW~LK401HJLtl~h7pIblggQz~SHyuthIzEJ~bXMh6mBhl8~qCPn3MsdVD~f4V1aCLsyM~4iy0PVelRF~k3AcsamkCa~I8PKmJXPGb~yc4Cp8UYCr~qpeZSmEVVP~z5F58NU9bR~9ODMAZ0ebV~dHhPEViT17~eRHUOfrCWe~2NjFAa7LLT~PXSGQo51fD~dVuj_Sdwlo~nRp2ZLPLbj~bXJo2dvuZs~m3EJRa33xU~zIv0cf5VVk~1GBicHu4Rs~-Pl_yN8N1A~xaAwxLKhPs~Ce-EdaHA-3; __utmt=1; tags_sended=1; categorized_tags=CADCYLsad0~RsIQe1tAR0~bXMh6mBhl8~m3EJRa33xU; __utmb=235335808.2.10.1622711469'
    json_url_headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.77 Safari/537.36',
        'referer':'https://www.pixiv.net/',
        'sec-fetch-dest':'document',
        'sec-fetch-mode':'navigate',
        'sec-fetch-site':'same-origin',
        'sec-fetch-user':'1',
        'upgrade-insecure-requests':'1',
        'accept':'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
        'accept-encoding':'gzip, deflate, br',
        'accept-language':'zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7',
        'cache-control':'max-age=0',
        'cookie': cookie
    }
    # step 2:發起請求
    json_res_data = requests.get(json_url, headers = json_url_headers)

    # step 3: 解析json資料
    res_json = json_res_data.json()
    res_json_body = res_json['body']['thumbnails']['illust']                       # 獲取json中的body內容
    item_list = list(res_json_body)                           # 獲取body中的所有的key，即圖片id
    origin_url_list = []                                    # 儲存所有的原圖地址
    origin_title_list = []

    # pprint.pprint(id_list)
    # print(str(id_list[0]))
    # step 4: 構造原圖地址
    for item in item_list:
        # 獲取title
        # print(idlist['title'])
        # origin_title_list.append(item['title'])
        # 通過獲取縮圖地址構造原圖地址
        # thumbnail_url = item['url']          
        # origin_specail_part = re.findall('img/(.*?)_p0',thumbnail_url)[0]
        # origin_url_list.append("https://i.pximg.net/img-original/img/%s_p0.jpg" % origin_specail_part)
        # origin_url_list.append(item['url'])
        origin_url = item['url']
        origin_url_headers = {
            'referer': 'https://www.pixiv.net/artworks/%s' % str(item['id']),
            'user-agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.125 Safari/537.36'
        }
        # 發起請求
        img_res = requests.get(origin_url, headers=origin_url_headers)
        img_res_data = img_res.content
        img_res_code = img_res.status_code
        if img_res_code == 200:                 # 如果請求成功
            # 儲存圖片
            img_save_name = str(item['id'])+".png"
            with open("./img/"+img_save_name, 'wb') as fp:
                fp.write(img_res_data)
                msg = img_save_name+"儲存成功！"
                print(msg)
        else:                                   # 否則輸出狀態碼
            msg = "下載失敗！狀態碼為："+ img_res_code
            print(msg)

    # # step 4: 遍歷origin_url_list爬取圖片
    # i = -1
    # for item in origin_url_list:
    #     # 更新id列表索引
    #     i = i+1

    #     # 獲取地址
    #     origin_url = item
    #     # 設定headers
    #     origin_url_headers = {
    #         'referer': 'https://www.pixiv.net/artworks/%s' % str(id_list[i]),
    #         'user-agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.125 Safari/537.36'
    #     }
    #     # 發起請求
    #     img_res = requests.get(origin_url, headers=origin_url_headers)
    #     img_res_data = img_res.content
    #     img_res_code = img_res.status_code

    #     if img_res_code == 200:                 # 如果請求成功
    #         # 儲存圖片
    #         img_save_name = str(origin_title_list[i])+".png"
    #         with open("./img/"+img_save_name, 'wb') as fp:
    #             fp.write(img_res_data)
    #             msg = img_save_name+"儲存成功！"
    #             print(msg)
    #     else:                                   # 否則輸出狀態碼
    #         msg = "下載失敗！狀態碼為："+ img_res_code
    #         print(msg)

    # origin_url_headers = {
    #     'referer': 'https://www.pixiv.net/artworks/90283276',
    #     'user-agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.125 Safari/537.36'
    # }
    # # 發起請求
    # img_res = requests.get(origin_url, headers=origin_url_headers)
    # img_res_data = img_res.content
    # img_res_code = img_res.status_code

    # if img_res_code == 200:                 # 如果請求成功
    #     # 儲存圖片
    #     img_save_name = str(origin_title_list[i])+".png"
    #     with open("./img/"+img_save_name, 'wb') as fp:
    #         fp.write(img_res_data)
    #         msg = img_save_name+"儲存成功！"
    #         print(msg)
    # else:                                   # 否則輸出狀態碼
    #     msg = "下載失敗！狀態碼為："+ img_res_code
    #     print(msg)