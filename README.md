# GitProxy - 简单易用的Git Socks5代理配置工具

## 简介

**GitProxy** 是一个用于配置Git Socks5代理的轻量级脚本，基于单个C文件开发，没有项目依赖。旨在简化在不同网络环境下配置Git代理的过程。无论是在Linux、WSL1|WSL2还是其他支持GCC的环境中，您都可以轻松设置或取消Git的HTTP/HTTPS代理。

## 特性

- **一键配置**：只需一条命令即可完成Git代理的配置。
- **自动保存设置**：配置信息将被保存到`/etc/gitproxy.ini`文件中，方便下次快速应用。
- **灵活切换**：支持随时更改代理服务器地址及端口，满足多变的网络需求。
- **状态查看**：提供命令用于检查当前Git代理的状态。
- **跨平台兼容**：适用于多种操作系统环境，包括但不限于Linux和WSL2。

## 安装指南

确保您的系统已安装GCC编译器后，按照以下步骤操作：

```bash
chmod +x proxy_setup.sh
使用说明
场景1: 配置HTTP与HTTPS代理
首次配置

bash
gitproxy set
默认使用127.0.0.1:17890作为代理服务器

自定义代理服务器

bash
gitproxy set 127.0.0.1:17891
此命令会更新配置文件中的代理信息，以便后续直接使用新设置

取消代理

bash
gitproxy unset
仅取消当前会话中的代理设置，不影响配置文件

查看代理状态

bash
gitproxy status
显示当前Git代理的HTTP和HTTPS状态
```

联系我们
如果您有任何疑问或建议，请通过GitHub Issues联系我们。