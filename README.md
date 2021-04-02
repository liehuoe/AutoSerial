# AutoSerial

实现通过命令行的方式调用串口程序并自动登录

```shell
serialClient.exe -serial -sercfg <串口配置> [-c<COM口>] [-u<username>] [-p<password>]

#for example:
serialClient.exe -serial -sercfg 115200,8,n,1,X -cCOM3 -uroot -ppassword
```
