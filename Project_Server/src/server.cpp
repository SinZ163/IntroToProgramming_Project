#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/swingame.h"

struct DBEntry {
    color color;
    char* name;
};

void init_db(DBEntry* db, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            db[i*width + j].color = random_color();
            db[i*width + j].name = "SERVER";
        }
    }
}
int main() {
    //Create the server socket, with a name we will never use, TCP port 25565, and well, TCP
    server_socket server = create_server_with_protocol("SwinServer", 25565, TCP);

    DBEntry db[16];
    init_db(db, 4, 4);
    //We want to contantly repeat this shit
    while(true) {
        //This is like process_events() for the gui stuff, and is what actually reads the network, checks for new connections and shit.
        check_network_activity();
        //This is actually a utility function which loops over all active connections, and tells us if there is *a* message.
        if (has_message_on_server(server)) {
            //This is getting the most recent message from the stack (pop style).
            message newMessage = read_message_from_server(server);
            //The following two lines are to extract the data from the message pointer. its actually impossible to do it without this function.
            char buffer[512];
            message_data(newMessage, buffer);

            //this also exists if you want host
            //message_host(newMessage, buffer2);

            //as does this.
            //int port message_port(newMessage);

            //Success :D
            printf("Message Get: |%s|\n", buffer);


            if (strlen(buffer) > 5 && strncmp(buffer, "HELLO ", 6) == 0) {
                //We could sscanf to get the username, but fuck that.
                printf("Initializing new user\n");
                char newMsg[3+1+8*(17+10+1)];
                newMsg[0] = 'D';
                newMsg[1] = 'B';
                newMsg[2] = '1';
                newMsg[3] = ' ';
                newMsg[4] = '\0';
                for (int i = 0; i < 8; i++) {
                    strcat(newMsg, db[i].name);
                    strcat(newMsg, " ");
                    char tmp[11];
                    sprintf(tmp, "%d", db[i].color);
                    strcat(newMsg, tmp);
                    strcat(newMsg, "|");
                }
                send_message_to(newMsg, message_connection(newMessage));
                char newMsg2[3+1+8*(17+10+1)];
                newMsg2[0] = 'D';
                newMsg2[1] = 'B';
                newMsg2[2] = '2';
                newMsg2[3] = ' ';
                newMsg2[4] = '\0';
                for (int i = 8; i < 16; i++) {
                    strcat(newMsg2, db[i].name);
                    strcat(newMsg2, " ");
                    char tmp[11];
                    sprintf(tmp, "%d", db[i].color);
                    strcat(newMsg2, tmp);
                    strcat(newMsg2, "|");
                }
                send_message_to(newMsg2, message_connection(newMessage));
                printf("Sending DB to user\n");
                continue; //Don't blindly broadcast
            } else if(strlen(buffer) > 5 && strncmp(buffer, "CHANGE ", 6) == 0) {
                int id;
                int color;
                char name[17];
                sscanf(buffer, "CHANGE %d %d %s", &id, &color, &name);
                db[id].color = color;
                db[id].name = name; 
            }
            broadcast_message_to_server(buffer, server);
        }
        delay(1);
    }
}