
# 访问大模型API
## 阅读技术文档！
- 首要的任务就是找到官方的技术文档，因为所有内容都会在你要访问的大模型的官方网站中包括，比如
    - 通义千问(阿里云)的大模型服务平台：[百炼API技术文档](https://help.aliyun.com/zh/model-studio/getting-started/what-is-model-studio?spm=5176.29619931.J_AHgvE-XDhTWrtotIBlDQQ.10.1f3459fcUxplap)
    - KIMI的大模型服务平台:[Moonshot技术文档](https://platform.moonshot.cn/docs/api/chat#%E5%85%AC%E5%BC%80%E7%9A%84%E6%9C%8D%E5%8A%A1%E5%9C%B0%E5%9D%80)
    - 文心一言(百度智能云)的大模型服务平台:[千帆大模型平台技术文档](https://cloud.baidu.com/doc/AppBuilder/s/6lq7s8lli)

## 访问大模型 

我们一般分两种访问，一种是直接调用大模型API，另一种是先新建一个大模型的应用，再访问这个应用(比如文心一言)。后者不太好用，前者再细分下去又有很多种方法了，比如openai，比如http等等。

### 通过python的openai库(OpenAI Python SDK)访问通义千问大模型
我们以通义千问举例，通过python直接调用通义千问大模型API。参考[首次调用通义千问API](https://help.aliyun.com/zh/model-studio/getting-started/first-api-call-to-qwen?spm=a2c4g.11186623.help-menu-2400256.d_0_1_0.223fb0a8OSK8f9)步骤即可。

#### 具体过程
- 参考上面的文章注册账号，获得`密钥`
- 将密钥配置到环境变量中(Linux系统)
    ```
    # 用您的 DashScope API Key 代替 你的实际密钥
    echo "export DASHSCOPE_API_KEY='你的实际密钥'" >> ~/.bashrc
    # 使变更生效
    source ~/.bashrc
    # 可以新打开一个终端窗口，检查环境变量是否生效
    echo $DASHSCOPE_API_KEY
    ```
    - 期待的输出`sk-…………………`
- 检查python版本，Python需要为3.8及以上
    ```
    # 如果运行失败，您可以将python3替换成python再运行
    python3 -V
    ````
- 下载安装模型调用SDK
    ```
    pip3 install -U openai
    ```
- 新建python脚本hello_qwen.py
    ```
    nano hello_qwen.py
    ```
- 将文档中的python代码拷贝进入：
    ```python
    import os
    from openai import OpenAI

    try:
        client = OpenAI(
            # 若没有配置环境变量，请用百炼API Key将下行替换为：api_key="sk-xxx",
            api_key=os.getenv("DASHSCOPE_API_KEY"),
            base_url="https://dashscope.aliyuncs.com/compatible-mode/v1",
        )

        completion = client.chat.completions.create(
            model="qwen-plus",  # 模型列表：https://help.aliyun.com/zh/model-studio/getting-started/models
            messages=[
                {'role': 'system', 'content': 'You are a helpful assistant.'},
                {'role': 'user', 'content': '你是谁？'}
                ]
        )
        print(completion.choices[0].message.content)
    except Exception as e:
        print(f"错误信息：{e}")
        print("请参考文档：https://help.aliyun.com/zh/model-studio/developer-reference/error-code")
    ```
- 运行python脚本
    ```
    python3 hello_qwen.py
    ```
- 期待的输出(结果不一定一模一样)
    ```
    root@Youer:~/TestInClass/apitest# python3 hello_qwen.py
    我是Qwen，由阿里云开发的超大规模语言模型。我被设计用于生成各种类型的文本，如文章、故事、诗歌等，并能根据不同的场景和需求进行对话、提供信息或完成任务。很高兴为您服务！
    ```

#### 更进一步
- 我们可以学习一下官方的python脚本是怎么写的
    - 分析哪些项是必须的，不可更改的
    - 哪些项是可以修改的，比如，我们可以更改`model`属性，改为自己想要访问的模型，[具体模型列表](https://help.aliyun.com/zh/model-studio/getting-started/models)
- 同时，可以参考[API文档](https://help.aliyun.com/zh/model-studio/developer-reference/use-qwen-by-calling-api?spm=a2c4g.11186623.help-menu-2400256.d_3_3_0.3eaf47bbBn4ElU)去学习一下有什么其他功能:
    - 比如流式输出`stream`，比如采样温度`temperature`
    - 这些属性有不懂的可以[直接问通义千问](https://lxblog.com/qianwen/share?shareId=1ff434a2-3114-4f20-9a56-8ae0e3364ce0)


### 通过HTTP访问通义千问大模型
- 对于我使用的Godot而言，官方不支持python语言，c#我也不会写，所以只能通过HTTP方式来访问大模型
- 通过HTTP访问本质上就是构造格式正确的HTTP请求，接受并正确解析HTTP响应，这就是两个问题
    - 一：如何构造正确的HTTP请求与正确解析HTTP响应
    - 二：如何发送HTTP请求并接受HTTP响应
- 第二个问题一般的游戏引擎软件(godot)或python等语言都支持，所以关键在于第一个问题。
- 解决方法还是看官方文档，比如下面的代码:
    ```
    curl -X POST https://dashscope.aliyuncs.com/compatible-mode/v1/chat/completions \
    -H "Authorization: Bearer $DASHSCOPE_API_KEY" \
    -H "Content-Type: application/json" \
    -d '{
        "model": "qwen-plus",
        "messages": [
            {
                "role": "system",
                "content": "You are a helpful assistant."
            },
            {
                "role": "user", 
                "content": "你是谁？"
            }
        ]
    }'
    ```
- 了解HTTP结构的或者[询问AI](https://lxblog.com/qianwen/share?shareId=256216d2-8a01-441b-9ed8-ec31afca1449)后不难知道如何用python构造HTTP请求
    ```
    这段代码使用了`curl`命令来发送一个HTTP POST请求到指定的URL，请求包含了几个部分：请求方法（POST）、请求头部（Headers）和请求体（Body）。下面是请求的结构分析

    ### 请求结构分析

    1. **请求方法**：
    - `POST`：表示向指定资源提交数据，请求服务器进行处理（例如提交表单或上传文件）。数据被包含在请求体中。

    2. **请求URL**：
    - `https://dashscope.aliyuncs.com/compatible-mode/v1/chat/completions`：这是请求的目标地址。

    3. **请求头部**：
    - `Authorization: Bearer $DASHSCOPE_API_KEY`：用于认证，`$DASHSCOPE_API_KEY`是一个环境变量，代表了访问API所需的密钥。
    - `Content-Type: application/json`：指明了请求体的格式是JSON。

    4. **请求体**：
    - 是一个JSON对象，包含两个字段：
        - `"model": "qwen-plus"`：指定了使用的模型名称。
        - `"messages": [...]`：是一个消息数组，每个元素都是一个对象，包含角色（`role`）和内容（`content`）。
    ```
- 使用python构造相同的http请求(需要先安装requests库，命令是`pip install requests`)
    ```py
    import requests
    import os

    url = 'https://dashscope.aliyuncs.com/compatible-mode/v1/chat/completions'
    headers = {
        'Authorization': f'Bearer {os.getenv("DASHSCOPE_API_KEY")}',
        'Content-Type': 'application/json'
    }
    data = {
        "model": "qwen-plus",
        "messages": [
            {
                "role": "system",
                "content": "You are a helpful assistant."
            },
            {
                "role": "user",
                "content": "你是谁？"
            }
        ]
    }

    response = requests.post(url, headers=headers, json=data)

    print(response.status_code)
    print(response.json())
    ```
- 我的输出如下：
    ```
    root@Youer:~/TestInClass/apitest# pip install requests
    Requirement already satisfied: requests in /usr/lib/python3/dist-packages (2.25.1)
    WARNING: Running pip as the 'root' user can result in broken permissions and conflicting behaviour with the system package manager. It is recommended to use a virtual environment instead: https://pip.pypa.io/warnings/venv
    root@Youer:~/TestInClass/apitest# nano http_api.py
    root@Youer:~/TestInClass/apitest# python3 http_api.py
    200
    {'choices': [{'message': {'role': 'assistant', 'content': '我是Qwen，由阿里云开发的超大规模语言模型。我被设计用于生成各 种类型的文本，如文章、故事、诗歌等，并能根据不同的场景和需求进行对话、提供信息查询、解决问题等任务。很高兴为您服务！如果您有任何问题或需要帮助，请随时告诉我。'}, 'finish_reason': 'stop', 'index': 0, 'logprobs': None}], 'object': 'chat.completion', 'usage': {'prompt_tokens': 32, 'completion_tokens': 62, 'total_tokens': 94}, 'created': 1732002295, 'system_fingerprint': None, 'model': 'qwen-plus', 'id': 'chatcmpl-44e7f891-274c-90f3-afb1-dde2f4e89b7c'}
    root@Youer:~/TestInClass/apitest#
    ```
- 从输出中也可以看出(当然直接阅读文档更好)回答的内容在'content'之中，所以如果用python代码直接读取'content'内容再输出就好了
    - 这是一个JSON数据，如何解析各位自行探索吧

- 不同的模型功能不一，对不同的访问方式的支持并不一致。这需要自己去看文档了。

## 结语

- 坦白说，我只访问过百度智能云应用和通义千问大模型，同时也只局限在文本交流上。
- 不过就我之前查阅的资料，我更喜欢KIMI大模型，其上传文件似乎更加方便，也没有那么多的模型，既不想百度的需要新建一个应用才能使用，也不像阿里的各种模型花里胡哨的。其支持的文件格式如下：
    ```
    文件接口与 Kimi 智能助手中上传文件功能所使用的相同，支持相同的文件格式，它们包括``等格式。.pdf.txt.csv.doc.docx.xls.xlsx.ppt.pptx.md.jpeg.png.bmp.gif.svg.svgz.webp.ico.xbm.dib.pjp.tif.pjpeg.avif.dot.apng.epub.tiff.jfif.html.json.mobi.log.go.h.c.cpp.cxx.cc.cs.java.js.css.jsp.php.py.py3.asp.yaml.yml.ini.conf.ts.tsx
    ```
- 但kimi暂时不支持音频理解，且免费用户的使用受限
- 所以大家感兴趣的可以多了解了解各种产品，玩点花的






