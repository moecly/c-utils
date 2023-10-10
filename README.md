# 一个C工具类库
从utils-configs.h里面定义需要使用的库即可应用库，需要自己创建
# 工具模块结构
```
c-utils
    |
    |______lib                      # 需要的动态库
    |
    |______common                   # 通用库
    |
    |______crypto                   # 加密库(openssl)
    |
    |______list                     # 链表库
    |
    |______log_msg                  # 日志库
    |
    |______process                  # 进程管理库
    |
    |______socket                   # socket库
    |
    |______str_util                 # 字符串工具库
    |
    |______sys_time                 # Linux系统时间库
```