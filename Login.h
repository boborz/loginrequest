//
//  Login.h
//  运动会管理系统
//
//  Created by Aaron on 28/12/2017.
//  Copyright © 2017 Aaron. All rights reserved.
//

#ifndef Login_h
#define Login_h

#include <stdio.h>

#define LOGIN_SUCCESSFUL 1
#define LOGIN_FAILED 0

/**
 *  加密传输原理
 *
 *  在注册时就采用 MD5 签名的方式在本地进行签名，将签名发送给服务器保存后存入数据库
 *  因此除了在注册时那几秒外，用户的账号密码除了用户自己任何人都不知道，包括服务器
 *  在登录时，将用户输入的用户密码直接进行 MD5 签名，然后在字符串后拼接时间戳
 *  将拼接好的新字符串再一次签名，与时间戳一起发送给服务器。
 *  服务器接收到签名数据和时间戳之后，使用同样的方法验证签名的正确性，同时在验证之前
 *  可以先对时间戳进行查重、过期校验等操作，服务端代码见论文正文。
 *
 *  需要注意的是，生产环境中早已不适合使用 MD5 算法进行加密，现阶段 MD5 只适合用于
 *  校验签名。就算是 SHA1 加密也被 Google 公司撞库破解，所以在生产环境中推荐采
 *  用 SHA256 搭配加盐进行加密。
 *  加盐通常采用一种 SecretKey 的方式，公司内部规定一串密钥，可以是某位程序员
 *  滚键盘得到，也可以是一些乱码文字，但一定不能是有意义的字符或数字，容易被攻击者
 *  猜测。有了 SecretKey 之后我们就可以按照上述文字提到的拼接字符串对其整个串再一次
 *  签名，随后发送到服务器用同样的步骤进行校验。此处同样需要注意的是，对于前端 app，
 *  所有代码都暴露的情况下，如果依然采用这种方案，那么应该在校验服务器设置一个白名单，
 *  只有来自可信的服务器的请求才会给予校验。
 */
int loginWith(char * username, char * password);

#endif /* Login_h */