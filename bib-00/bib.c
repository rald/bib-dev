#include <ini.h>
#include <dyad.h>

#include <stdio.h>
#include <string.h>
#include <time.h>



/* A simple IRC bot. Connects to an IRC network, joins a channel then sits
 * idle, responding to the server's PING messges and printing everything the
 * server sends it. */

static char *host = "irc.dal.net";
static char *nick = "frio";
static char *chan = "#pantasya";
static int   port = 6667;
 
static int   isRegistered = 0;


static void onConnect(dyad_Event *e) {
    /* Introduce ourselves to the server */
    dyad_writef(e->stream, "NICK %s\r\n", nick);
    dyad_writef(e->stream, "USER %s %s bla :%s\r\n", nick, nick, nick);
}

static void onError(dyad_Event *e) {
    printf("error: %s\n", e->msg);
}

static void onLine(dyad_Event *e) {
    printf("%s\n", e->data);
    /* Handle PING */
    if (!memcmp(e->data, "PING", 4)) {
        dyad_writef(e->stream, "PONG%s\r\n", e->data + 4);
    }
    /* Handle RPL_WELCOME */
    if (!isRegistered && strstr(e->data, "001")) {
    /* Join channel */
        dyad_writef(e->stream, "JOIN %s\r\n", chan);
        isRegistered = 1;
    }
}

int main(void) {

    ini_t *config = ini_load("config.ini");

    host = (char*)ini_get(config, "default", "host");
    nick = (char*)ini_get(config, "default", "nick");
    chan = (char*)ini_get(config, "default", "chan");

    ini_sget(config, "default", "port", "%d", &port);

    printf("host: %s\n",host);
    printf("port: %d\n",port);
    printf("nick: %s\n",nick);
    printf("chan: %s\n",chan);




    dyad_Stream *s;
    dyad_init();

    s = dyad_newStream();
    dyad_addListener(s, DYAD_EVENT_CONNECT, onConnect, NULL);
    dyad_addListener(s, DYAD_EVENT_ERROR,   onError,   NULL);
    dyad_addListener(s, DYAD_EVENT_LINE,    onLine,    NULL);
    dyad_connect(s, host, port);

    while (dyad_getStreamCount() > 0) {
        dyad_update();
    }

    dyad_shutdown();
    ini_free(config);

    return 0;
}
