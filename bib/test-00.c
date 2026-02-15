#include <stdio.h>
#include <ini.h>

int main(void) {

    ini_t *config = ini_load("config.ini");

    const char *host = ini_get(config, "default", "host");
    const char *nick = ini_get(config, "default", "nick");
    const char *chan = ini_get(config, "default", "chan");

    int port; 
    ini_sget(config, "default", "port", "%d", &port);

    printf("host: %s\n",host);
    printf("port: %d\n",port);
    printf("nick: %s\n",nick);
    printf("chan: %s\n",chan);

    ini_free(config);

    return 0;
}

