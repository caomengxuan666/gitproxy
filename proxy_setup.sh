#!/bin/bash

# 编译C语言程序
gcc -o gitproxy gitproxy.c

# 检查编译是否成功
if [ $? -ne 0 ]; then
    echo "编译失败，请检查代码和依赖项。"
    exit 1
fi

# 将可执行文件复制到 /usr/local/bin
sudo cp -f gitproxy /usr/local/bin/

# 检查复制是否成功
if [ $? -ne 0 ]; then
    echo "无法将可执行文件复制到 /usr/local/bin，请检查权限。"
    exit 1
fi

# 设置可执行文件权限
sudo chmod 755 /usr/local/bin/gitproxy

# 创建或更新 git_proxy.ini 文件
sudo bash -c 'cat <<EOF > /etc/git_proxy.ini
[proxy]
address=127.0.0.1
port=17890
EOF'

# 检查文件创建是否成功
if [ $? -ne 0 ]; then
    echo "无法创建或更新 /etc/git_proxy.ini 文件，请检查权限。"
    exit 1
fi

# 设置 git_proxy.ini 文件权限
sudo chmod 664 /etc/git_proxy.ini

# 设置 git_proxy.ini 文件的所有者和组
sudo chown root:users /etc/git_proxy.ini

echo "安装完成。"
