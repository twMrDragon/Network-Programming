# Week13

## week1301

準備 Ubuntu 22

執行到 page 7. 執行後截圖上傳

本週講義<br>
https://drive.google.com/file/d/1ompgN220bVBq35s940tKjjQCLPw3daBx/view?usp=sharing

## week1302

page 13

執行 daytime client/server<br>
執行截圖

## week1303

請逐行詳細說明 server 端程式意義 (Q3..)

## week1304

請逐行詳細說明 client 端程式意義 (Q3..)

## week1305

製作 2 個虛擬機 A, B<br>
client 在 A, Server 在 B<br>
client 問 server 時間 (類似 page 43, 但在不同 IP 虛擬機)<br>
執行後截圖上傳

## week 1306

使用兩個虛擬機(或者在同一台虛擬機開啟兩個 terminal)，要在 command 指定 IP<br>
一個當 server, 一個當 client<br>
當 CLIENT 端使用者輸入不同訊息，SERVER 回應不同訊息<br>
CLIENT: Hello~<br>
SERVER: Hi~<br>
CLIENT: Good!<br>
SERVER: Thanks!<br>
CLIENT: How are you?<br>
SERVER: I am fine. How are you.<br>
CLIENT: How old are you?<br>
SERVER: I am twenty years old.<br>

將 client/server 執行結果截圖上傳

## week 1307

開啟兩個虛擬機，一個當 Server，一個當 Client<br>
在 client 執行後提示訊息:<br>
輸入英文字母資料，<br>
client 程式存成檔案 client.txt<br>
例如輸入<br>
this is a book<br>
that is a cat<br>

將檔案加密後，傳輸到 server<br>
加密方法是 英文字母向右移 5 位<br>

server 端接收檔案資料後，解密後存成 server.txt<br>

將 client.c / server.c code 貼上

## week1308

利用 UDP 寫程式，從 Client 端傳輸一個超過 255byte 的檔案，到 Server 端<br>
輸入檔案名稱<br>
每次要傳 255 byte<br>
傳 fileLength/255 +1 次<br>

貼上 client.c / server.c code
