from email.mime.text import MIMEText#專門傳送正文
from email.mime.multipart import MIMEMultipart#傳送多個部分
from email.mime.application import MIMEApplication#傳送附件
import smtplib#傳送郵件
import csv

# 開啟 CSV 檔案
csvfile = open('錄取通知.csv', newline='', encoding="utf-8")

# 讀取 CSV 檔案內容
members = csv.reader(csvfile)


file = '股員名單.pdf' #附件路徑

send_user = 'kizato1018@gmail.com'   #發件人
password = 'Smile13428967'   #授權碼/密碼
server_address = 'smtp.gmail.com'   #伺服器地址
smtp= smtplib.SMTP(server_address,587)  # 連線伺服器，SMTP_SSL是安全傳輸
smtp.ehlo()
smtp.starttls()
smtp.login(send_user, password)

subject = '2021師大資工營錄取結果通知'  #郵件主題
# email_text = '這是菜鳥教程Python 郵件傳送測試……'   #郵件正文

mail_type = '1'    #郵件型別
part_attach1 = MIMEApplication(open(file,'rb').read())   #開啟附件
part_attach1.add_header('Content-Disposition','attachment',filename=file) #為附件命名



for member in members:
    # print(member)
    receive_users = member[2]   #收件人，可為list
    html = """
    <html>

    <head>
    <meta http-equiv=Content-Type content="text/html; charset=big5">
    <meta name=Generator content="Microsoft Word 15 (filtered)">
    <style>
    <!--
    /* Font Definitions */
    @font-face
        {font-family:新細明體;
        panose-1:2 2 5 0 0 0 0 0 0 0;}
    @font-face
        {font-family:"Cambria Math";
        panose-1:2 4 5 3 5 4 6 3 2 4;}
    @font-face
        {font-family:Calibri;
        panose-1:2 15 5 2 2 2 4 3 2 4;}
    @font-face
        {font-family:微軟正黑體;
        panose-1:2 11 6 4 3 5 4 4 2 4;}
    @font-face
        {font-family:"\@微軟正黑體";}
    @font-face
        {font-family:"\@新細明體";
        panose-1:2 1 6 1 0 1 1 1 1 1;}
    /* Style Definitions */
    p.MsoNormal, li.MsoNormal, div.MsoNormal
        {margin:0cm;
        margin-bottom:.0001pt;
        font-size:12.0pt;
        font-family:"Calibri",sans-serif;}
    p.MsoHeader, li.MsoHeader, div.MsoHeader
        {mso-style-link:"頁首 字元";
        margin:0cm;
        margin-bottom:.0001pt;
        layout-grid-mode:char;
        font-size:10.0pt;
        font-family:"Calibri",sans-serif;}
    p.MsoFooter, li.MsoFooter, div.MsoFooter
        {mso-style-link:"頁尾 字元";
        margin:0cm;
        margin-bottom:.0001pt;
        layout-grid-mode:char;
        font-size:10.0pt;
        font-family:"Calibri",sans-serif;}
    a:link, span.MsoHyperlink
        {color:blue;
        text-decoration:underline;}
    a:visited, span.MsoHyperlinkFollowed
        {color:#954F72;
        text-decoration:underline;}
    p.MsoListParagraph, li.MsoListParagraph, div.MsoListParagraph
        {margin-right:0cm;
        margin-left:0cm;
        font-size:12.0pt;
        font-family:"新細明體",serif;}
    span.grame
        {mso-style-name:grame;}
    span.a
        {mso-style-name:"頁首 字元";
        mso-style-link:頁首;}
    span.a0
        {mso-style-name:"頁尾 字元";
        mso-style-link:頁尾;}
    .MsoChpDefault
        {font-family:"Calibri",sans-serif;}
    /* Page Definitions */
    @page WordSection1
        {size:595.3pt 841.9pt;
        margin:72.0pt 90.0pt 72.0pt 90.0pt;
        layout-grid:18.0pt;}
    div.WordSection1
        {page:WordSection1;}
    /* List Definitions */
    ol
        {margin-bottom:0cm;}
    ul
        {margin-bottom:0cm;}
    -->
    </style>

    </head>

    <body lang=ZH-TW link=blue vlink="#954F72" style='text-justify-trim:punctuation'>

    <div class=WordSection1 style='layout-grid:18.0pt'>

    <p class=MsoNormal><b><span lang=EN-US style='font-size:13.5pt;font-family:
    "微軟正黑體",sans-serif;color:black'>2021</span></b><b><span style='font-size:13.5pt;
    font-family:"微軟正黑體",sans-serif;color:black'>師大資工營錄取結果通知</span></b></p>

    <p class=MsoNormal><span lang=EN-US style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;
    color:black'>&nbsp;</span></p>

    <p class=MsoNormal><span style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;
    color:black'>"""+member[0]+"""<span lang=EN-US>&nbsp;</span>您好：</span></p>

    <p class=MsoNormal><span lang=EN-US style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;
    color:black'>&nbsp;</span></p>

    <p class=MsoNormal style='text-indent:24.0pt'><span style='font-size:10.0pt;
    font-family:"微軟正黑體",sans-serif;color:black'>這裡是<span lang=EN-US>2021</span>師大資工營總籌股，<span
    style='background:white'>首先感謝你參與面試，你的分發結果為</span></span><span style='font-size:
    10.0pt;font-family:"微軟正黑體",sans-serif;color:red;background:white'>"""+member[1]+"""</span><span
    style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;color:black;background:
    white'>股。</span></p>

    <p class=MsoNormal style='text-indent:24.0pt'><span style='font-size:10.0pt;
    font-family:"微軟正黑體",sans-serif;color:black;background:white'>以下事項請注意：</span></p>

    <p class=MsoListParagraph style='margin-left:72.0pt;text-indent:-24.0pt'><span
    lang=EN-US style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;color:black'>1.<span
    style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    </span></span><span style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;
    color:black;background:white'>以下連結為"""+member[1]+"""股的群組及全體資工營的群組，<b>請立刻加入</b>，並注意裡面的訊息。</span></p>

    <p class=MsoListParagraph style='margin-left:72.0pt;text-indent:-24.0pt'><span
    lang=EN-US style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;color:black'>2.<span
    style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    </span></span><span style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;
    color:#222222;background:white'>附件一為所有工人名單，請參閱，若資料有誤請盡速回報總籌股。</span></p>

    <p class=MsoListParagraph style='margin-left:96.0pt;text-indent:-24.0pt'><span
    lang=EN-US style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;color:black'>a、<span
    style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span></span><span
    style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;color:black'>"""+member[1]+"""股群組：</span><span
    lang=EN-US><a
    href=\""""+member[3]+"""\"
    target="_blank"><span style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;
    color:#954F72'>"""+member[3]+"""</span></a></span></p>

    <p class=MsoListParagraph style='margin-left:96.0pt;text-indent:-24.0pt'><span
    lang=EN-US style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;color:black'>b、<span
    style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp; </span></span><span
    style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;color:black;background:
    white'>全體工人群組：</span><span lang=EN-US><a href="http://line.me/ti/g/G0uB_zqgdv"
    target="_blank"><span style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;
    color:#1155CC'>http://line.me/ti/g/G0uB_zqgdv</span></a></span></p>

    <p class=MsoListParagraph style='margin-left:96.0pt;text-indent:-24.0pt'><span
    lang=EN-US style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;color:black'>c、<span
    style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span></span><span
    style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;color:black;background:
    white'>全體工人臉書社團：</span><span lang=EN-US><a
    href="https://www.facebook.com/groups/849993532210470" target="_blank"><span
    style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;color:#1155CC'>https://www.facebook.com/groups/849993532210470</span></a></span></p>
    """+("""
    <p class=MsoListParagraph style='margin-left:72.0pt;text-indent:-24.0pt'><span
    lang=EN-US style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;color:black'>3.<span
    style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    </span></span><b><span style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;
    color:black;background:white'>"""+member[4]+"""</span></b></p>
    """ if len(member[4]) > 5 else "")+"""
    <p class=MsoNormal><span lang=EN-US style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;
    color:black'>&nbsp;</span></p>

    <p class=MsoNormal><span lang=EN-US style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;
    color:black'>2021</span><span style='font-size:10.0pt;font-family:"微軟正黑體",sans-serif;
    color:black'>師大資工營總籌股　施育衡、康馨儒、蕭瀜</span></p>

    </div>

    </body>

    </html>

    """


    #構造一個郵件體：正文 附件
    msg = MIMEMultipart()
    msg['Subject']=subject    #主題
    msg['From']=send_user      #發件人
    msg['To']=receive_users           #收件人

    #構建正文
    part_text=MIMEText(html, "html", "utf-8")
    msg.attach(part_text)             #把正文加到郵件體裡面去

    #構建郵件附件
    #file = file           #獲取檔案路徑
    msg.attach(part_attach1)   #新增附件


    # 傳送郵件 SMTP

    smtp.sendmail(send_user, receive_users, msg.as_string())  # 傳送郵件
    print(member)
    print('郵件傳送成功！')