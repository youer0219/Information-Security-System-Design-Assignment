
# 核心参考文章
- [连接 USB 设备](https://learn.microsoft.com/zh-cn/windows/wsl/connect-usb)
- [WSL2连接USB设备（以USRP B210为例）](https://www.cnblogs.com/n0ne/p/18297345)

# 具体步骤
- 先决条件
    - 运行 Windows 11（内部版本 22000 或更高版本）
    - 需要具有 x64 处理器的计算机。 （x86 和 Arm64 目前不支持 usbipd win）。
    - WSL 已安装并使用最新版本进行设置。
    - Linux 发行版已安装并设置为 WSL 2

- 打开`终端管理员`，运行下面的命令安装 USBIPD (也可以参考[连接 USB 设备](https://learn.microsoft.com/zh-cn/windows/wsl/connect-usb)文章中的安装方法)
```
winget install --interactive --exact dorssel.usbipd-win
```

- 附加USB设备
    - 通过以`管理员模式`打开 PowerShell 并输入以下命令，列出所有连接到 Windows 的 USB 设备。
    ```
    usbipd list
    ```
    ![参考图片](https://i-blog.csdnimg.cn/direct/e517ae34d52f4a7c83106a84c37cdf58.png)
    - 在附加 USB 设备之前，必须使用命令 usbipd bind 来共享设备，从而允许它附加到 WSL。 这需要管理员权限。 选择要在 WSL 中使用的设备总线 ID，然后运行以下命令。 运行命令后，请再次使用命令 usbipd list 验证设备是否已共享。
        ```
        usbipd bind --busid 2-1
        ```
        - 这里首先要判断 你要共享的USB是哪个设备总线ID。我这里的是`2-1`，对应`096e:0321  USB 大容量存储设备`
        - 如何判断成功共享：再次运行`usbipd list`命令。注意最左侧`STATE`是不是`Shared`，如果是，说明共享成功
        ![参考图片](https://i-blog.csdnimg.cn/direct/3dce59aedb96417782572e69e9df0523.png)
    - 继续执行下面的命令`usbipd attach --wsl --busid 2-1`
        - 这里的`2-1`要换成自己的设备总线ID
        - ​​![](https://i-blog.csdnimg.cn/direct/e07fb47f19594215a96825b87d3ff6e4.png)
    - 在`Ubuntu`中运行`lsusb`命令
        - 没有这个命令就去问AI怎么安装……
        - 出现下图中间那个说明连接成功
        ![](https://i-blog.csdnimg.cn/direct/4e5b3ad9182442cd9b46b9c8321a7f12.png)
        - 根据你的应用程序，你可能需要配置 udev 规则以允许非根用户访问设备。(我直接是root用户，没有经过这一步骤)
        - 请最好不要关闭WSL命令提示符
        - 同时，请注意，只要 USB 设备连接到 WSL，Windows 将无法使用它。所以如果你在Windows下找不到这个U盘的提示，也可以间接说明你连接成功

- 结果验证
    - 只要出现下面两行说明连接是没有问题的，如果连接失败就是代码的问题
        ```
        open device success!
        open session success!
        ```
        - 代码问题解决方法：检查你的芯片，如果是EU的芯片就需要用老师最新发的那个安装包
    - 完全成功的结果参考
    ```
    open device success!
    open session success!
    pOutRand:
    3128121f e765993e b7b6169b a0447cf6
    SDF_GenerateRandom success!
    SDF_ImportRootKeyAndDeviceSN success
    SN:hs_00000000000014208
    CosVer: 4.2.08
    ImportKeyPair success
    EccBackUpKeyPair success
    ExportKeyPair success
    SGD_SM3Hash success
    SM2EncDec success
    SM2SignVer success
    SGD_SM1_ECB Encrypt datasize: 4000000 Bytes used time: 1664913 us
    SGD_SM1_ECB Encrypt average speed: 19220223 bps
    SGD_SM1_ECB Decrypt datasize: 4000000 Bytes used time: 1651084 us
    SGD_SM1_ECB Decrypt average speed: 19381206 bps
    SM1_ENC_DEC_ECB success.
    SGD_SM1_CBC Encrypt datasize: 4000000 Bytes used time: 1711877 us
    SGD_SM1_CBC Encrypt average speed: 18692931 bps
    SGD_SM1_CBC Decrypt datasize: 4000000 Bytes used time: 1692697 us
    SGD_SM1_CBC Decrypt average speed: 18904741 bps
    SM1_ENC_DEC_CBC success.
    SGD_SM1_OFB Encrypt datasize: 4000000 Bytes used time: 1448136 us
    SGD_SM1_OFB Encrypt average speed: 22097372 bps
    SGD_SM1_OFB Decrypt datasize: 4000000 Bytes used time: 1446069 us
    SGD_SM1_OFB Decrypt average speed: 22128957 bps
    SM1_ENC_DEC_OFB success.
    SGD_SM4_ECB Encrypt datasize: 4000000 Bytes used time: 1794267 us
    SGD_SM4_ECB Encrypt average speed: 17834580 bps
    SGD_SM4_ECB Decrypt datasize: 4000000 Bytes used time: 1797626 us
    SGD_SM4_ECB Decrypt average speed: 17801255 bps
    SM4_ENC_DEC_ECB success.
    SGD_SM4_CBC Encrypt datasize: 4000000 Bytes used time: 1872762 us
    SGD_SM4_CBC Encrypt average speed: 17087061 bps
    SGD_SM4_CBC Decrypt datasize: 4000000 Bytes used time: 1865848 us
    SGD_SM4_CBC Decrypt average speed: 17150378 bps
    SM4_ENC_DEC_CBC success.
    SGD_SM4_OFB Encrypt datasize: 4000000 Bytes used time: 1478838 us
    SGD_SM4_OFB Encrypt average speed: 21638610 bps
    SGD_SM4_OFB Decrypt datasize: 4000000 Bytes used time: 1465698 us
    SGD_SM4_OFB Decrypt average speed: 21832601 bps
    SM4_ENC_DEC_OFB success.
    SGD_IPSEC_SM1 Encrypt datasize: 4024000 Bytes used time: 2126279 us
    SGD_IPSEC_SM1 Encrypt average speed: 15140063 bps
    SGD_IPSEC_SM1 Decrypt datasize: 4024000 Bytes used time: 2128484 us
    SGD_IPSEC_SM1 Decrypt average speed: 15124379 bps
    SM1_ENC_DEC_IPSEC success.
    SGD_IPSEC_SM4 Encrypt datasize: 4024 Bytes used time: 2334 us
    SGD_IPSEC_SM4 Encrypt average speed: 13792630 bps
    SGD_IPSEC_SM4 Decrypt datasize: 4024 Bytes used time: 2192 us
    SGD_IPSEC_SM4 Decrypt average speed: 14686131 bps
    SM4_ENC_DEC_IPSEC success.    
    ```


---

对于 龙脉芯片

- 不要在Windows下运行证书工具，会占用该U盘导致无法连接WSL
    - 报错信息
        ```
        PS C:\Users\xlm20> usbipd attach --wsl --busid 2-1
        usbipd: info: Using WSL distribution 'Ubuntu' to attach; the device will be available in all WSL 2 distributions.
        usbipd: info: Using IP address 172.27.64.1 to reach the host.
        WSL wsl: �hKm0R localhost �NtM�n
                                        �FO*g\��P0R WSL0NAT !j_
                                                            N�v WSL
        WSL N/ec localhost �Nt0
        WSL
        WSL usbip: error: Attach Request for 2-1 failed - Device busy (exported)
        usbipd: warning: The device appears to be used by Windows; stop the software using the device, or bind the device using the '--force' option.
        usbipd: error: Failed to attach device with busid '2-1'.
        ```
- 明确问题出在返回的设备名称为空上
    ```
    root@Youer:~/bestidiocs2024/ch06/参考/longmaiskf0016-stu/samples/skf/linux_mac/encrypt# ./encryptTest
    Calling SKF_EnumDev...
    SKF_EnumDev result: 0 (Success)
    Enumerated device name: ''
    Calling SKF_ConnectDev...
    SKF_ConnectDev result: 167772166 (Invalid parameter)
    Error at line 173 in function SKF_ConnectDev, call failed with error code: 167772166 (Invalid parameter)
    ```
- 明确了这个函数只能返回空值。怀疑是本身不支持！

- 问官方去了
![](https://i-blog.csdnimg.cn/direct/31d01c40b9774619af49389f00c1b7bf.png)
