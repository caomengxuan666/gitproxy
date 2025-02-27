#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INI_FILE "/etc/gitproxy.ini"
#define DEFAULT_ADDRESS "127.0.0.1"
#define DEFAULT_PORT "17890"

typedef struct {
    char address[256];
    char port[256];
} ProxyConfig;

void read_config(ProxyConfig *config) {
    FILE *file = fopen(INI_FILE, "r");
    if (!file) {
        // 如果文件不存在，使用默认值
        strcpy(config->address, DEFAULT_ADDRESS);
        strcpy(config->port, DEFAULT_PORT);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "address=%s", config->address) == 1)
            continue;
        if (sscanf(line, "port=%s", config->port) == 1)
            continue;
    }
    fclose(file);
}

void write_config(const ProxyConfig *config) {
    FILE *file = fopen(INI_FILE, "w");
    if (!file) {
        perror("无法打开配置文件进行写入");
        return;
    }
    fprintf(file, "address=%s\n", config->address);
    fprintf(file, "port=%s\n", config->port);
    fclose(file);
}

void set_git_proxy(const char *address, const char *port) {
    char command[256];
    snprintf(command, sizeof(command),
             "git config --global https.proxy 'socks5://%s:%s'", address, port);
    system(command);
    snprintf(command, sizeof(command),
             "git config --global http.proxy 'socks5://%s:%s'", address, port);
    system(command);
    printf("Git代理已设置为 socks5://%s:%s\n", address, port);
}

void unset_git_proxy() {
    system("git config --global --unset https.proxy");
    system("git config --global --unset http.proxy");
    printf("Git代理已取消设置\n");
}

void print_status() {
    char command[256];
    char output[256];

    // 获取HTTPS代理
    snprintf(command, sizeof(command), "git config --global --get https.proxy");
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("无法获取HTTPS代理");
        return;
    }
    if (fgets(output, sizeof(output), fp) == NULL) {
        printf("HTTPS代理: 没有代理\n");
    } else {
        printf("HTTPS代理: %s", output);
    }
    pclose(fp);

    // 获取HTTP代理
    snprintf(command, sizeof(command), "git config --global --get http.proxy");
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("无法获取HTTP代理");
        return;
    }
    if (fgets(output, sizeof(output), fp) == NULL) {
        printf("HTTP代理: 没有代理\n");
    } else {
        printf("HTTP代理: %s", output);
    }
    pclose(fp);
}

void print_usage() {
    printf("Usage: gitproxy set [address] [port] | git_proxy unset | git_proxy "
           "status\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    ProxyConfig config;
    read_config(&config);

    if (strcmp(argv[1], "set") == 0) {
        const char *address = (argc > 2) ? argv[2] : config.address;
        const char *port = (argc > 3) ? argv[3] : config.port;
        set_git_proxy(address, port);
        strcpy(config.address, address);
        strcpy(config.port, port);
        write_config(&config);
    } else if (strcmp(argv[1], "unset") == 0) {
        unset_git_proxy();
        strcpy(config.address, DEFAULT_ADDRESS);
        strcpy(config.port, DEFAULT_PORT);
        write_config(&config);
    } else if (strcmp(argv[1], "status") == 0) {
        print_status();
    } else {
        print_usage();
        return 1;
    }

    return 0;
}
