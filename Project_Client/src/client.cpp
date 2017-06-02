#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/swingame.h"

struct DBEntry {
    color color;
    char* name;
};

void render(DBEntry* db, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            fill_rectangle(db[width*i + j].color, 100*i, 100*j, 100, 100);
        }
    }
}
char* network(connection &con) {
    check_network_activity();
    if (has_message_on_connection(con)) {
        message msg = read_message(con);
        char* buffer = (char*) malloc(256);
        message_data(msg, buffer);            
        return buffer;
    }
    return NULL;
}

int main() {
    char username[17];
    printf("Enter a username (16 char max): ");
    scanf("%16[^\n]c\n", &username);

    connection con = open_connection_named_with_protocol("SwinClient", "127.0.0.1", 25565, TCP);
    open_graphics_window("Network Client", 400, 400);

    //guiset_background_color(color_white());

    DBEntry db[16];

    //TODO: Change this to match future 'protocol' specs.
    char initMsg[17+6];
    sprintf(initMsg, "HELLO %s", username);

    bool doRender = false;
    int out = send_message_to(initMsg, con);
    while(true) {
        if (doRender)
            render(db, 4, 4);
        refresh_screen(60);
        process_events();
        char* newMsg = network(con);
        if (newMsg == NULL) {
            continue;
        }
        printf("Message Get: %s\n", newMsg); 
        if (strlen(newMsg) > 5 && strncmp(newMsg, "CHANGE ", 6) == 0) {
            int id;
            color color;
            char name[17];
            if (sscanf(newMsg, "CHANGE %d %d %s", &id, &color, &name) == EOF) {
                exit(1);
            }
            db[id].color = color;
            db[id].name = name;
        }
        if (strlen(newMsg) > 3 && strncmp(newMsg, "DB1 ", 4) == 0) {
            printf("I AM DB1\n");
            int out = sscanf(newMsg, "DB1 %s %d|%s %d|%s %d|%s %d|%s %d|%s %d|%s %d|%s %d|", 
                &(db[0x0].name), &(db[0x0].color), &(db[0x1].name), &(db[0x1].color),
                &(db[0x2].name), &(db[0x2].color), &(db[0x3].name), &(db[0x3].color),
                &(db[0x4].name), &(db[0x4].color), &(db[0x5].name), &(db[0x5].color),
                &(db[0x6].name), &(db[0x6].color), &(db[0x7].name), &(db[0x7].color)
            );
            printf("DB1 Out: %d\n", out);
        }
        if (strlen(newMsg) > 3 && strncmp(newMsg, "DB2 ", 4) == 0) {
            printf("I AM DB2\n");
            int out = sscanf(newMsg, "DB2 %s %d|%s %d|%s %d|%s %d|%s %d|%s %d|%s %d|%s %d|", 
                &(db[0x8].name), &(db[0x8].color), &(db[0x9].name), &(db[0x9].color),
                &(db[0xA].name), &(db[0xA].color), &(db[0xB].name), &(db[0xB].color),
                &(db[0xC].name), &(db[0xC].color), &(db[0xD].name), &(db[0xD].color),
                &(db[0xE].name), &(db[0xE].color), &(db[0xF].name), &(db[0xF].color)
            );
            printf("DB2 Out: %d\n", out);
            doRender = true;
        }
    }
}